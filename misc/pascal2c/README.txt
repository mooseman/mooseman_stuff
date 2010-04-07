
This is a public domain Pascal to C translation utility.  Please read the
documentation below for a further description of the utility.

You must be on a Unix system (with /bin/sh accessible) to unpack the shell
archive "pascal2c.sh".  To install this program,

<LI> Download pascal2c.sh from this site (see your browser manual if you are
uncertain how to do this)
<LI> Move pascal2c.sh to a directory in which you wish to unpack the source
files 
<LI> Type <strong>pascal2c.sh</strong> in this directory -- this will cause
the source and documentation files to be expanded
<LI> Compile the C source code (both cc and gcc seem to work fine).  Since
there isn't a Makefile you'll need to type something like
<CENTER><STRONG>cc p2c.c proc.c doalloc.c -o p2c</STRONG></CENTER><BR>
to generate the executable p2c.
<LI> Read the documentation file p2c.doc for more information 

<HR>

The following is an excerpt from the shell archive "pascal2c.sh" contained
in this directory:

<HR>
 NAME
     p2c	- Pascal to C translator
 
 SYNOPSIS
     p2c < foo.pas > foo.c
 
 DESCRIPTION
     p2c converts many Pascal structures to their C equivalent.
     The Pascal source can be in upper, lower, or mixed case; case is
     preserved during translation.
 
     Structures translated properly include simple assignment
     and comparison statments, variable, type, and label declarations, 
     enumerated types, and procedure and function declarations and instances.
 
     Structures NOT translated properly include sets, constant declarations,
     variant records, files, subrange types, VAR parameters, CASE, FOR, 
     WITH, READ, and WRITE statements, and nested procedures.
 
     The translator provides hints about untranslated regions by inserting
     UPPERCASE messages enclosed with /* and */ into the translated source.
     Error messages are of the form /***# Expected ... ***/.
 
     Human massaging of the output will certainly be needed.
     In fact, you may want to modify the keyword translation table
     to better translate your particular variant of Pascal.
 
 IMPLEMENTATION
     Written in C for Sun UNIX workstations; ought to compile on other 
     systems without change...
     Some of the translation is done with a keyword table, but most of
     the work is done by a recursive-descent parser.
 
 BUGS
     Not well tested.
     Error recovery is very poor- the first error in translation inside
     the recursive-descent section will result in a very long stream of
     error messages.
     Some of the bread-and-butter structures of Pascal- like CASE and FOR-
     are not translated properly, although it would be easy to extend
     the parser to understand them.
 
     I welcome bug reports, and invite anyone interested to implement
     more PASCAL structures; I probably won't work on it much, because
     I don't use Pascal these days.
 
 VERSION
     This version by Daniel Kegel <dan@srs.UUCP> or <seismo!rochester!srs!dan>,
     25 March 87.
     Based on a program by James A Mullens  <jcm@ornl-msr.arpa>  29-Jan-87
     which was in turn based on two nearly identical programs by Robert Heller  
     (1 Feb 1985) and Rick Walker <walker@hpl-opus.hp.COM> (8 Sep 1986)
     which were reportedly derived from a similar program in the Feb 85 Byte
     which did a C TO PASCAL conversion.

<HR>
<A HREF="mailto:algorith@cs.sunysb.edu">Send us mail</A><BR>
<A HREF="http://www.cs.sunysb.edu/~algorith">Return to Main Page<A>
 
