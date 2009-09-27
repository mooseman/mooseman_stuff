/*
 * The routines in this file move the cursor around on the screen. They
 * compute a new value for the cursor, then adjust ".". The display code
 * always updates the cursor location, so only moves between lines, or
 * functions that adjust the top line in the window and invalidate the
 * framing, are hard.
 */

#include "estruct.h"
#include "edef.h"

extern int getccol (int bflg);
extern int inword ();
extern void mlwrite ();

int forwchar (int f, int n);
int backchar (int f, int n);
int forwline (int f, int n);
int backline (int f, int n);
int gotobop (int f, int n);
int gotoeop (int f, int n);
int forwpage (int f, int n);
int backpage (int f, int n);

/*
 * This routine, given a pointer to a LINE, and the current cursor goal
 * column, return the best choice for the offset. The offset is returned.
 * Used by "C-N" and "C-P".
 */
long getgoal (LINE *dlp)
{
  int col, newcol, dbo, c;

  col = 0;
  dbo = 0;
  while (dbo != llength (dlp))
    {
      c = lgetc (dlp, dbo);
      newcol = col;
      if (c == '\t')
	newcol |= 0x07;
      else if (c < 0x20 || c == 0x7F)
	++newcol;
      ++newcol;
      if (newcol > curgoal)
	break;
      col = newcol;
      ++dbo;
    }
  return (dbo);
}

/*
 * Move the cursor to the
 * beginning of the current line.
 * Trivial.
 */
/* ARGSUSED0 */
int gotobol (int f, int n)
{
  curwp->w_doto = 0;
  return (TRUE);
}

/*
 * Move the cursor to the end of the current line. Trivial. No errors.
 */
/* ARGSUSED0 */
int gotoeol (int f, int n)
{
  curwp->w_doto = llength (curwp->w_dotp);
  return (TRUE);
}

/*
 * Move the cursor backwards by "n" characters. If "n" is less than zero call
 * "forwchar" to actually do the move. Otherwise compute the new cursor
 * location. Error if you try and move out of the buffer. Set the flag if the
 * line pointer for dot changes.
 */
int backchar (int f, int n)
{
  LINE *lp;

  if (n < 0)
    return (forwchar (f, -n));
  while (n--)
    {
      if (curwp->w_doto == 0)
	{
	  if ((lp = lback (curwp->w_dotp)) == curbp->b_linep)
	    return (FALSE);
	  curwp->w_dotp = lp;
	  curwp->w_doto = llength (lp);
	  curwp->w_flag |= WFMOVE;
	}
      else
	curwp->w_doto--;
    }
  return (TRUE);
}

/*
 * Move the cursor forwards by "n" characters. If "n" is less than zero call
 * "backchar" to actually do the move. Otherwise compute the new cursor
 * location, and move ".". Error if you try and move off the end of the
 * buffer. Set the flag if the line pointer for dot changes.
 */
int forwchar (int f, int n)
{
  if (n < 0)
    return (backchar (f, -n));
  while (n--)
    {
      if (curwp->w_doto == llength (curwp->w_dotp))
	{
	  if (curwp->w_dotp == curbp->b_linep)
	    return (FALSE);
	  curwp->w_dotp = lforw (curwp->w_dotp);
	  curwp->w_doto = 0;
	  curwp->w_flag |= WFMOVE;
	}
      else
	curwp->w_doto++;
    }
  return (TRUE);
}

/* move to a particular line. argument (n) must be a positive integer for this
 * to actually do anything
 */
int gotoline (int f, int n)
{
  if (n < 1)		       /* if a bogus argument...then leave */
    return (FALSE);

  /* first, we go to the start of the buffer */
  curwp->w_dotp = lforw (curbp->b_linep);
  curwp->w_doto = 0;
  return (forwline (f, n - 1));
}

/*
 * Goto the beginning of the buffer. Massive adjustment of dot. This is
 * considered to be hard motion; it really isn't if the original value of dot
 * is the same as the new value of dot. Normally bound to "M-<".
 */
/* ARGSUSED0 */
int gotobob (int f, int n)
{
  curwp->w_dotp = lforw (curbp->b_linep);
  curwp->w_doto = 0;
  curwp->w_flag |= WFHARD;
  return (TRUE);
}

/*
 * Move to the end of the buffer. Dot is always put at the end of the file
 * (ZJ). The standard screen code does most of the hard parts of update.
 * Bound to "M->".
 */
/* ARGSUSED0 */
int gotoeob (int f, int n)
{
  curwp->w_dotp = curbp->b_linep;
  curwp->w_doto = 0;
  curwp->w_flag |= WFHARD;
  return (TRUE);
}

/*
 * Move forward by full lines. If the number of lines to move is less than
 * zero, call the backward line function to actually do it. The last command
 * controls how the goal column is set. Bound to "C-N". No errors are possible.
 */
int forwline (int f, int n)
{
  LINE *dlp;

  if (n < 0)
    return (backline (f, -n));
  if ((lastflag & CFCPCN) == 0)/* Reset goal if last */
    curgoal = getccol (FALSE); /* not C-P or C-N */
  thisflag |= CFCPCN;
  dlp = curwp->w_dotp;
  while (n-- && dlp != curbp->b_linep)
    dlp = lforw (dlp);
  curwp->w_dotp = dlp;
  curwp->w_doto = getgoal (dlp);
  curwp->w_flag |= WFMOVE;
  return (TRUE);
}

/*
 * This function is like "forwline", but goes backwards. The scheme is exactly
 * the same. Check for arguments that are less than zero and call your
 * alternate. Figure out the new line and call "movedot" to perform the
 * motion. No errors are possible. Bound to "C-P".
 */
int backline (int f, int n)
{
  LINE *dlp;

  if (n < 0)
    return (forwline (f, -n));
  if ((lastflag & CFCPCN) == 0)/* Reset goal if the */
    curgoal = getccol (FALSE); /* last isn't C-P, C-N */
  thisflag |= CFCPCN;
  dlp = curwp->w_dotp;
  while (n-- && lback (dlp) != curbp->b_linep)
    dlp = lback (dlp);
  curwp->w_dotp = dlp;
  curwp->w_doto = getgoal (dlp);
  curwp->w_flag |= WFMOVE;
  return (TRUE);
}

/* go back to the begining of the current paragraph here we look for a
 * <NL><NL> or <NL><TAB> or <NL><SPACE> combination to delimit the begining of
 * a paragraph
 */
int gotobop (int f, int n)
{
  int suc;			/* success of last backchar */

  if (n < 0)			/* the other way.. */
    return (gotoeop (f, -n));

  while (n-- > 0)
    {				/* for each one asked for */
      /* first scan back until we are in a word */
      suc = backchar (FALSE, 1);
      while (!inword () && suc)
	suc = backchar (FALSE, 1);
      curwp->w_doto = 0;	/* and go to the B-O-Line */

      /* and scan back until we hit a <NL><NL> or <NL><TAB> or a <NL><SPACE> */
      while (lback (curwp->w_dotp) != curbp->b_linep)
	if (llength (curwp->w_dotp) != 0 &&
	    lgetc (curwp->w_dotp, curwp->w_doto) != TAB &&
	    lgetc (curwp->w_dotp, curwp->w_doto) != ' ')
	  curwp->w_dotp = lback (curwp->w_dotp);
	else
	  break;

      /* and then forward until we are in a word */
      suc = forwchar (FALSE, 1);
      while (suc && !inword ())
	suc = forwchar (FALSE, 1);
    }
  curwp->w_flag |= WFMOVE;	/* force screen update */
  return (TRUE);
}

/* go forword to the end of the current paragraph here we look for a <NL><NL>
 * or <NL><TAB> or <NL><SPACE> combination to delimit the begining of a
 * paragraph
 */
int gotoeop (int f, int n)
{
  int suc;			/* success of last backchar */

  if (n < 0)			/* the other way.. */
    return (gotobop (f, -n));

  while (n-- > 0)
    {				/* for each one asked for */
      /* first scan forward until we are in a word */
      suc = forwchar (FALSE, 1);
      while (!inword () && suc)
	suc = forwchar (FALSE, 1);
      curwp->w_doto = 0;	/* and go to the B-O-Line */
      if (suc)			/* of next line if not at EOF */
	curwp->w_dotp = lforw (curwp->w_dotp);

      /* and scan forword until hit a <NL><NL> or <NL><TAB> or a <NL><SPACE> */
      while (curwp->w_dotp != curbp->b_linep)
	{
	  if (llength (curwp->w_dotp) != 0 &&
	      lgetc (curwp->w_dotp, curwp->w_doto) != TAB &&
	      lgetc (curwp->w_dotp, curwp->w_doto) != ' ')
	    curwp->w_dotp = lforw (curwp->w_dotp);
	  else
	    break;
	}

      /* and then backward until we are in a word */
      suc = backchar (FALSE, 1);
      while (suc && !inword ())
	{
	  suc = backchar (FALSE, 1);
	}
      curwp->w_doto = llength (curwp->w_dotp); /* and to the EOL */
    }
  curwp->w_flag |= WFMOVE;	/* force screen update */
  return (TRUE);
}

/*
 * Scroll forward by a specified number of lines, or by a full page if no
 * argument. Bound to "C-V". The "2" in the arithmetic on the window size is
 * the overlap; this value is the default overlap value in ITS EMACS. Because
 * this zaps the top line in the display window, we have to do a hard update.
 */
int forwpage (int f, int n)
{
  LINE *lp;

  if (f == FALSE)
    {
      n = curwp->w_ntrows - 2;	 /* Default scroll */
      if (n <= 0)		 /* Forget the overlap */
	n = 1;			 /* if tiny window */
    }
  else if (n < 0)
    return (backpage (f, -n));
  else			       /* Convert from pages */
    n *= curwp->w_ntrows;      /* to lines */
  lp = curwp->w_linep;
  while (n-- && lp != curbp->b_linep)
    lp = lforw (lp);
  curwp->w_linep = lp;
  curwp->w_dotp = lp;
  curwp->w_doto = 0;
  curwp->w_flag |= WFHARD;
  return (TRUE);
}

/*
 * This command is like "forwpage", but it goes backwards. The "2", like
 * above, is the overlap between the two windows. The value is from the ITS
 * EMACS manual. Bound to "M-V". We do a hard update for exactly the same
 * reason.
 */
int backpage (int f, int n)
{
  LINE *lp;

  if (f == FALSE)
    {
      n = curwp->w_ntrows - 2;	 /* Default scroll */
      if (n <= 0)		 /* Don't blow up if the window is tiny */
	n = 1;
    }
  else if (n < 0)
    return (forwpage (f, -n));
  else			       /* Convert from pages to lines */
    n *= curwp->w_ntrows;
  lp = curwp->w_linep;
  while (n-- && lback (lp) != curbp->b_linep)
    lp = lback (lp);
  curwp->w_linep = lp;
  curwp->w_dotp = lp;
  curwp->w_doto = 0;
  curwp->w_flag |= WFHARD;
  return (TRUE);
}

/*
 * Set the mark in the current window to the value of "." in the window. No
 * errors are possible. Bound to "M-.".
 */
/* ARGSUSED0 */
int setmark (int f, int n)
{
  curwp->w_markp = curwp->w_dotp;
  curwp->w_marko = curwp->w_doto;
  mlwrite ("[Mark set]");
  return (TRUE);
}
