/* <HTML><BODY><PRE> */
/* oklatea.cpp is an interpreter of the Teapro programming language */
/* oklatea.cpp begun on 2004/11/12 */

/* The computer program oklatea.exe may be used for free by anyone, */
/* but there is no warranty of any kind whatsoever on oklatea.exe. */

/* The computer language teapro may be used for free by anyone, */
/* but there is no warranty of any kind whatsoever on teapro. */

/* This computer program source code, oklatea.cpp, may be used for free by */
/* anyone, but there is no warranty of any kind whatsoever on oklatea.cpp. */
/* People need computer software that actually works. */
/* header files */
#include <stdio.h>  /* stdio.h */
#include <stdlib.h> /* stdlib.h */
#include <time.h>   /* time.h */
#include <math.h>   /* math.h */
/* C99 uses CLOCKS_PER_SEC instead of CLK_TCK */
#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC CLK_TCK
#endif
/* plines is the max number of lines for a program */
/* pstack is the number of the depth of the link stack */
/* vstrings is the number of string variables */
/* vslong is the max length of a string */
/* vdecimals is the number of decimal variables */
/* vstack is the number of depth of subroutines possible */
/* darray is the number of elements in the decimal array */
/* sarray is the number of elements in the string array */
/* vcharname is the length of the variable name arrays */
/* maxstring is the max length of variable length strings */
#define PLINES 18020
#define PSTACK 18020
#define VSTRINGS 4000
#define VSLONG 8192  /* 16384 */
#define VDECIMALS 2000
#define VSTACK 2000
#define DARRAY 32000
#define SARRAY 2000
#define VCHARNAME 2000
#define MAXSTRING 100000000  /* 100,000,000 */

/* utility prototypes below */
int tfni_compare_strings(char *sp1, char *sp2, long np_long);
int tfni_char_type(char cp_1);
int tfni_is_digits(char *sp1, int ip_long);
int tfni_string_to_integer(char *sp1, int ip_long);
long tfnn_string_lookup(char *sp1, long np1, char *sp2, long np2);
long tfnn_string_char_search(char *sp1, long np_long, char cp1);
long tfnn_hash(char *sp1, int ip_long);

void tsub_blank(char *sp1, long np_long);
void tsub_blank_escapes(char *sp1, long np_long);
void tsub_bug(char *sp1);
void tsub_case_lower(char *sp1, long np_long);
void tsub_case_upper(char *sp1, long np_long);
void tsub_copy(char *sp1, char *sp2, long np_long);
void tsub_debug(void);
void tsub_double_to_string(void);
void tsub_inp79(void);
void tsub_inp1024(void);
void tsub_line_of_char(char *sp1, char cp1, long np_long);
void tsub_make_long_string(char **psp1, long np_long);
void tsub_out79(char *sp1, int ip_long);
void tsub_show_pline(int ip_index, char *sp1, int ip_long);
void tsub_show_pline_by_index(int ip_index);
void tsub_show_vdecimal_info(int ip_index);
void tsub_show_vstring_info(int ip_index);
void tsub_string_to_double(char *sp1, int ip_long);
void tsub_timeline(void);

void tsub_use_append(char *psp_app, long np_app);
void tsub_use_insert321(long np_beg);
void tsub_use_replace(long np_beg, char *psp_rep, long np_rep);
void tsub_use_delete21(long np_beg, long np_long);
void tsub_use_move12(void);
void tsub_use_move21(void);
void tsub_use_trim_left(char *psp_str, long np_long);
void tsub_use_trim_right(char *psp_str, long np_long);

void tsub_pass_delete(long np_beg, long np_long);
void tsub_pass_insert(long np_beg, char *sp1, long np_long);
void tsub_pass_trim_left(void);
void tsub_pass_trim_right(void);
/* utility prototypes above */

/* fetch and store prototypes below */
/* these use sg_pass, ng_pass_lg, dg_1pass */
void sub_fetch_decimal_variable_1dbl(char *sp_var);
void sub_fetch_decimal_variable_2dbl(char *sp_var);
void sub_fetch_decimal_variable_lng(char *sp_var);
void sub_fetch_decimal_variable_int(char *sp_var);
void sub_fetch_decimal_pointer_dbl(char *sp_var, double *dp_var);

void sub_fetch_string_expression_use(int ip_byte);
void sub_fetch_string_pass(int ip_byte);
void sub_fetch_string3(int ip_byte, char **psp_1, long *pnp_long);
void sub_fetch_string_byref(int ip_byte);

void sub_store_decimal_variable(char *sp_var);
void sub_store_decimal_variable_in_link(void);
void sub_store_string3(char *sp_var, char *sp_string, long np_long);
void sub_store_string_in_link(char *sp_string, long np_long);
/* fetch and store prototypes above */
/* program preparation prototypes below */
void sub_prep_literal_numbers(void);
void sub_prep_literal_strings(void);
void sub_prep_format1(void);
void sub_prep_format2(void);
void sub_prep_no_spaces(void);
void sub_prep_split(int *ip_colon);
void sub_prep_variables_str(char *ps_vars, int *pi_vars_lg);
void sub_prep_variables_dec(char *ps_vars, int *pi_vars_lg);
void sub_prep_evar(int pi_type,
	char *ps_pline, char *ps_vars, int pi_vars_lg);
/* program preparation prototypes below */
void sub_program_variable_overlap(char *sp1, int ip1, char *sp2, int ip2);
void sub_program_validate_commands(void);
void sub_program_validate_variable(int ip_beg, int ip_type);
void sub_program_validate_var_last(int ip_beg);
void sub_program_validate_expression(int ip_beg, int ip_type);
void sub_program_error_end(char *sp_1, int ip_long);
void sub_program_help(void);
void sub_program_info(void);
void sub_program_initialize(int ip_which);
void sub_program_link_commands(void);
void sub_program_link_dift_dwhi(void);
void sub_program_link_esub(void);
void sub_program_load(int ip_mode);
void sub_program_run(void);
void sub_program_show(void);

void sub_command_dabs(int ip1);
void sub_command_dbad(void);
void sub_command_dduo(void);
void sub_command_dfac(void);
void sub_command_dfak(void);
void sub_command_dfaq1(void);
void sub_command_dfaq2(void);
void sub_command_dift_dwhi(void);
void sub_command_dinc(int ip1);
void sub_command_dpow(void);
void sub_command_dset(void);
void sub_command_dsys(void);
void sub_command_dtoi(int ip1);
void sub_command_dtos(int ip1);
void sub_command_itod(void);

void sub_command_evar(void);
void sub_command_ends(void);

void sub_command_file(int ip1);

void sub_command_sapp(void);
void sub_command_schs(int ip1);
void sub_command_scnt(void);
void sub_command_scut(void);
void sub_command_sdat(void);
void sub_command_sdel(void);
void sub_command_sdot(void);
void sub_command_sift_swhi(void);
void sub_command_sinp(void);
void sub_command_sins(void);
void sub_command_sisc(int ip1);
void sub_command_slen(int ip1);
void sub_command_slok(int ip1);
void sub_command_spkd(int ip1);
void sub_command_ssor(void);
void sub_command_sout(int ip1);
void sub_command_spar(void);
void sub_command_srep(void);
void sub_command_sset(void);
void sub_command_stod(int ip1);
void sub_command_stoi(int ip1);
void sub_command_strl(int ip1);
void sub_command_sswp(void);
void sub_command_ssys(void);
void sub_command_stoe(void);
/* prototypes above */

/* global variables are below */
/* program lines globals below */
char sg_path[80];
int ig_path;
char sg_program[80];
char sg_version[60];
char *psga_plines[PLINES];
int iga_plines_lg[PLINES];
int iga_link_commands[PLINES];
double dg_plines_done = 0;

char sg_pline[200];
char *psg_pline = NULL;
int ig_pline_lg;
int ig_pline_ix;

/* global true=1 */
int ig_true;

/* variable strings globals below */
char *psga_strings[VSTRINGS];
long nga_strings_lg[VSTRINGS];

/* variable decimals globals below */
double dga_decimals[VDECIMALS];

/* decimal array */
double dga_darray[DARRAY];

/* string array */
char *psga_sarray[SARRAY];
int iga_sarray_lg[SARRAY];

/* sg_pass, ng_pass_lg, dg_1pass are used */
/* for passing to/from fetch and store */
char sg_pass[VSLONG];
long ng_pass_lg;

char sg_buff1[VSLONG];
long ng_buff1_lg;

char sg_buff2[VSLONG];
long ng_buff2_lg;

/* psg_1,ng_1 string pointer */
/* use tsub_make_long_string(char **psp1, long np_long); */
char *psg_use1 = NULL;
long ng_use1 = 0;

char *psg_use2 = NULL;
long ng_use2 = 0;

char *psg_use3 = NULL;
long ng_use3 = 0;

char *psg_use4 = NULL;
long ng_use4 = 0;

char *psg_byref = NULL;
long ng_byref = 0;
char sg_byref[100];

/* dg_1pass,ig_pass,ng_pass for passing numbers */
double dg_1pass, dg_2pass;
int ig_pass_int;
long ng_pass_long;

/* for getting screen input from tsub_inp79 */
char sg_inp79[80];
int ig_inp79_lg;
long ng_inp79_long;

/* for getting screen input from tsub_inp1024 */
char sg_inp1024[1025];
int ig_inp1024_lg;
long ng_inp1024_long;

/* link globals below */
int iga_links[PLINES];
int ig_link_ix;
int iga_subr_links[100];
int ig_subr_ix;

/* variable stacks for global/local and variables below */
int ig_dvstack_ct, ig_svstack_ct;
int ig_dvstack_ix, ig_svstack_ix;
int iga_dvstack[VSTACK], iga_svstack[VSTACK];
int ig_dmaxglobal_ct, ig_smaxglobal_ct;
int ig_dmaxliteral_ct, ig_smaxliteral_ct;

/* debug variables ig_debug, sg_debug, ig_trace below */
int ig_debug;
char sg_debug[80];
char sg_subr[70];
int ig_trace;
int ig_step;
int ig_subr;
int ig_exit;
/* global variables are above */


int main(int ip_argc, char *psp_argv[]) {
/* updated 2009/01/25 */
/* 2008/02/22, 2007/02/24, 2006/11/07, 2006/08/09, 2005/11/05 */
/* 2005/10/07, 2005/08/02, 2005/06/14, 2005/05/19, 2005/04/27 */
/* 2005/04/24, 2005/04/09, 2005/04/02, 2005/03/28, 2005/03/27 */
/* 2005/03/12, 2005/03/05, 2005/02/24, 2005/02/08, 2004/11/29 */
	int i_loop, iz;
	long nz;
	char s_action[80];
	char sz[80];

    if(ip_argc > 0) {
		/* get path from psp_argv */
	    ig_path = tfnn_string_char_search(psp_argv[0], 79, 0);
    	tsub_copy(sg_path, psp_argv[0], ig_path);
		sg_path[ig_path] = 0;
	    printf("path=%s\n", sg_path);
	}

	tsub_line_of_char(sz, '-', 79);
	tsub_out79(sz, 79);

	tsub_copy(sg_version, "Program: oklatea.exe, build=558, 2010/03/08", 43);
    puts(sg_version);
    puts("oklatea.cpp is in the public domain");
    puts("Written 2004-2010 by D La Pierre Ballard");
    puts("email: dlb@teapro.com.");
	puts("oklatea.exe is an interpreter of the Teapro programming language");
	tsub_line_of_char(sz, '-', 79);
	tsub_out79(sz, 79);
	puts("The computer program oklatea.exe may be used");
    puts("for free by anyone, but there is no warranty");
	puts("of any kind whatsoever on oklatea.exe.");

	tsub_line_of_char(sz, '-', 79);
	tsub_out79(sz, 79);

    puts("The OpenTea technology makes Teapro simple and solid.");

	tsub_line_of_char(sz, '-', 79);
	tsub_out79(sz, 79);

    puts("People need computer software that actually works.");

	tsub_line_of_char(sz, '-', 79);
	tsub_out79(sz, 79);

	ig_trace = 2;
	ig_step = 2;
	ig_debug = 2;
	i_loop = 1;

    if(ip_argc > 1) {
		/* load and run program on command line */
		tsub_blank(sg_program, 80);
	    nz = tfnn_string_char_search(psp_argv[1], 79, 0);
		tsub_copy(sg_program, psp_argv[1], nz);
		sg_program[nz] = 0;
		sub_program_load(2);
        sub_program_run();
		i_loop++;
    }

	while(i_loop == 1) {
		puts("oklatea.exe console actions follow:");
		puts("debug, help, info, load, run, show, step, subr, trace");
		tsub_line_of_char(sz, '-', 79);
		tsub_out79(sz, 79);

		if(ig_step == 1) puts("step on");
		else puts("step off");

		if(ig_subr == 1) puts("subr on");
		else puts("subr off");

		if(ig_trace == 1) puts("trace on");
		else puts("trace off");

		if(ig_debug == 1) puts("debug on");
		else puts("debug off");

		puts("* to end");

        tsub_inp79();
        tsub_copy(s_action, sg_inp79, ig_inp79_lg);
		tsub_case_upper(s_action, 79);

		if(s_action[0] == '*') i_loop++;
		if(tfni_compare_strings(s_action, "HELP", 4) == 0)
			sub_program_help();
		if(tfni_compare_strings(s_action, "LOAD", 4) == 0)
			sub_program_load(1);
		if(tfni_compare_strings(s_action, "INFO", 4) == 0)
			sub_program_info();
		if(tfni_compare_strings(s_action, "RUN", 3) == 0) {
			sub_program_run();
            i_loop++;
        }
		if(tfni_compare_strings(s_action, "SHOW", 4) == 0)
			sub_program_show();
		if(tfni_compare_strings(s_action, "DEBUG", 5) == 0) {
			if(ig_debug == 1) ig_debug++;
			else ig_debug = 1;
		}
		if(tfni_compare_strings(s_action, "TRACE", 5) == 0) {
			if(ig_trace == 1) ig_trace++;
			else ig_trace = 1;
		}
		if(tfni_compare_strings(s_action, "SUBR", 4) == 0) {
			if(ig_subr == 1) ig_subr++;
			else ig_subr = 1;
		}
		if(tfni_compare_strings(s_action, "STEP", 4) == 0) {
			if(ig_step == 1) ig_step++;
			else ig_step = 1;
		}
		tsub_blank(s_action, 80);
	}
	/* free the memory of psga_plines */
	for(iz = 0; iz < PLINES; iz++) {
		free(psga_plines[iz]);
		psga_plines[iz] = NULL;
		iga_plines_lg[iz] = 0;
	}
	/* free memory of psga_strings */
	for(iz = 0; iz < VSTRINGS; iz++) {
		free(psga_strings[iz]);
		psga_strings[iz] = NULL;
		nga_strings_lg[iz] = 0;
	}
	/* free memory of psga_sarray */
	for(iz = 0; iz < SARRAY; iz++) {
		free(psga_sarray[iz]);
		psga_sarray[iz] = NULL;
		iga_sarray_lg[iz] = 0;
	}
	return 0;
} /* main */


void sub_program_help(void) {
/* updated 2010/02/25 */
/* 2009/09/05, 2008/12/06, 2008/01/23, 2007/12/14, 2007/09/20 */
/* 2007/07/08, 2007/05/04, 2007/04/11, 2007/04/10, 2007/03/19 */
/* 2007/03/17, 2007/02/24, 2007/01/14, 2007/01/08, 2006/12/01 */
/* 2006/11/14, 2006/11/11, 2006/11/10, 2006/11/08, 2006/11/07 */
	char s_dashes[75];
	int i_good;

    i_good = 1;
	tsub_line_of_char(s_dashes, '-', 75);

if(i_good == 1) {

puts(s_dashes);
puts("Teapro Commands");
puts(s_dashes);

puts("ARRB");
puts("Blank string array of strings ranging from 1 to 2000.");
puts(s_dashes);

puts("$APP s_appto, s_appwith");
puts("Append string s_appwith to the end of string s_appto.");
puts(s_dashes);

puts("$BAK d_where, s_lookin, d_start, s_lookfor");
puts("Backward lookup in s_lookin for s_lookfor starting at");
puts("d_start. If found put first byte in d_where or zero if not.");
puts(s_dashes);

puts("$BES s_new, s_old");
puts("Blank escapes in s_old and put into s_new.");
puts(s_dashes);

puts("$CH$ s_new, s_char, d_long");
puts("Make string of characters s_new of length d_long");
puts("of first char of s_char.");
puts(s_dashes);

puts("$CHD d_char, s_char");
puts("Put decimal value of first char of s_char into d_char.");
puts(s_dashes);

	tsub_inp79();
	if(sg_inp79[0] == '*') i_good++;
}
if(i_good == 1) {

puts("$CLO s_new, s_old");
puts("Make s_old lower case and put into s_new.");
puts(s_dashes);

puts("$CNT d_count, s_string, s_find");
puts("Put count of occurrences of s_find in s_string into d_count.");
puts(s_dashes);

puts("$COD s_new, s_old");
puts("Code or decode s_old into s_new. Code and decode are the same.");
puts(s_dashes);

puts("$CUP s_new, s_old");
puts("Make s_old uppercase and put into s_new.");
puts(s_dashes);

puts("$CUT s_part, s_whole, d_beg, d_long");
puts("Cut s_part from s_whole beginning at d_beg for length d_long.");
puts(s_dashes);

puts("$DAT s_date");
puts("Put date and time into s_date: 22-MAR-2002 21:28:16 20020322212816.");
puts(s_dashes);

puts("$DEL s_string, d_beg, d_long");
puts("Starting at d_beg delete d_long bytes from s_string.");
puts(s_dashes);

	tsub_inp79();
	if(sg_inp79[0] == '*') i_good++;
}
if(i_good == 1) {

puts("$DOT d_where, s_whole, s_part, d_occurrence");
puts("Put location of d_which occurrence of s_part in s_whole.");
puts(s_dashes);

puts("$HSH d_hash, s_string");
puts("Put a hash number for s_string into d_hash.");
puts(s_dashes);

puts("$IFT s_str1 >= s_str2");
puts("If string compare is true do all lines down to ELSE or ENDI.");
puts(s_dashes);

puts("$IFT s_str1 >= s_str2: d_any = d_dot");
puts("If string compare is true do statement to right of colon.");
puts(s_dashes);

puts("$INP s_input, s_output");
puts("Output s_output and recieve terminal input into s_input.");
puts(s_dashes);

puts("$INS s_insertinto, d_where, s_insertstr");
puts("Insert s_insertstr into s_insertinto beginning at d_where.");
puts(s_dashes);

puts("$ISC d_yesno, s_whole, s_char");
puts("If s_whole is a string of the first char of s_char");
puts("put 1 into d_yesno else 2.");
puts(s_dashes);

	tsub_inp79();
	if(sg_inp79[0] == '*') i_good++;
}
if(i_good == 1) {

puts("$ISD d_yesno, s_number");
puts("If s_number can be converted to a decimal put 1 in d_yesno else 2.");
puts(s_dashes);

puts("$ISP d_yesno, s_string, s_pattern");
puts("If s_string is same pattern as s_pattern put 1 in d_yesno else 2.");
puts("Patterns: escapes,blanks,punctuation,numbers,uppers,lowers,>126.");
puts(s_dashes);

puts("$IST d_yesno, s_string, s_type");
puts("If s_string is same type as first char of s_type put 1 in d_yesno");
puts("Types: escapes,blanks,punctuation,numbers,uppers,lowers,>126.");
puts(s_dashes);

puts("$LEN d_long, s_string");
puts("Put length of s_string into d_long.");
puts(s_dashes);

puts("$LOK d_where, s_lookin, d_start, s_lookfor");
puts("Lookup in s_lookin for s_lookfor starting at d_start.");
puts("If found put first byte in d_where or zero if not.");
puts(s_dashes);

puts("$OFF s_end, s_string, d_long");
puts("Cut s_end off of end of s_string for length d_long.");
puts(s_dashes);

puts("$OUT s_output");
puts("Output s_output to the terminal.");
puts(s_dashes);

	tsub_inp79();
	if(sg_inp79[0] == '*') i_good++;
}
if(i_good == 1) {

puts("$PAR s_part, s_whole, s_char, d_which");
puts("Parse s_whole which is a char separated value string to get");
puts("s_part which is occurrence d_which. The first char of s_char");
puts("separates the string s_whole.");
puts(s_dashes);

puts("$PKD d_yesno, d_decimal, s_packednumber");
puts("Change packed number in BCD to d_decimal. Put 1 in d_yesno if good.");
puts(s_dashes);

puts(s_dashes);

puts("$REP s_whole, d_beg, s_part");
puts("In s_whole replace with s_part beginning at d_beg.");
puts(s_dashes);

puts("$SET s_assignto = s_string1 + \"ABC\" + d_number + #\"hello\"#");
puts("Set s_assignto equal to a string expression. $SET is not needed.");
puts(s_dashes);

puts("$SHO s_output");
puts("Output to the terminal s_output without a new line at the end.");
puts(s_dashes);

puts("$SOR s_new, s_old, d_elementlength");
puts("Sort s_old using d_elementlength into s_new.");
puts(s_dashes);

puts("$SWP s_swapin, s_oldpart, s_newpart");
puts("In s_swapin replace occurrences of s_oldpart with s_newpart.");
puts(s_dashes);

	tsub_inp79();
	if(sg_inp79[0] == '*') i_good++;
}
if(i_good == 1) {

puts("$SYS s_systeminfo, d_which");
puts("If d_which=1 get path and filename of this Teapro interpreter.");
puts("If d_which=2 get current Teapro subroutine name.");
puts("If d_which=3 get version of current Teapro program.");
puts(s_dashes);

puts("$TLO s_new, s_old");
puts("Trim and lowercase s_old into s_new.");
puts(s_dashes);

puts("$TOD d_number, s_number");
puts("Change s_number to decimal and put in d_number.");
puts(s_dashes);

puts("$TOE s_oldtoe, s_string, s_key, d_which");
puts("Encode or decode s_string into s_oldtoe using s_key.");
puts("If d_which=1 encode, if d_which=2 decode.");
puts(s_dashes);

puts("$TOI d_index, s_string");
puts("Put s_string in string array at index d_index, 1 to 2000 range.");
puts(s_dashes);

puts("$TRB s_new, s_old");
puts("Trim s_old on right and left and put into s_new.");
puts(s_dashes);

puts("$TRL s_new, s_old");
puts("Trim left s_old and put into s_new.");
puts(s_dashes);

	tsub_inp79();
	if(sg_inp79[0] == '*') i_good++;
}
if(i_good == 1) {

puts("$TRR s_new, s_old");
puts("Trim right s_old and put into s_new.");
puts(s_dashes);

puts("$TUP s_new, s_old");
puts("Trim both and uppercase s_old and put into s_new.");
puts(s_dashes);

puts("$WHI s_string1 <= s_string2");
puts("If string compare is true do all lines downto ENDW.");
puts(s_dashes);

puts("ITO$ s_new, d_index");
puts("Get from string array at d_index, range 1 to 2000, into s_new.");
puts(s_dashes);

	tsub_inp79();
	if(sg_inp79[0] == '*') i_good++;
}
if(i_good == 1) {

puts("Teapro decimal commands");
puts(s_dashes);

puts("ADDI d_arrayindex, d_addtoelement");
puts(s_dashes);

puts("ARRZ");
puts("Zero elements of decimal array 1..32000.");
puts(s_dashes);

puts("DABS d_new, d_number");
puts("Put absolute value of d_number into d_new.");
puts(s_dashes);

	tsub_inp79();
	if(sg_inp79[0] == '*') i_good++;
}
if(i_good == 1) {

puts("DARC d_radians, d_sine");
puts("For sine d_sine put angle in radians in d_radians.");
puts(s_dashes);

puts("DBAD d_number1 >= d_number2");
puts("If numeric condition is true then bad and end program.");
puts(s_dashes);

puts("DBUG");
puts("Toggle teapro debug on and off.");
puts(s_dashes);

puts("DCH$ s_stringofchars, d_char, d_howmany");
puts(s_dashes);

puts("DDEC d_number");
puts("Decrement decimal in d_number.");
puts(s_dashes);

puts("DDUO d_factor, d_number, d_mult");
puts("Factor of possible duo beginning at (d_number + d_mult * 1E15).");
puts("If the factor is 1 then the duo is a prime duo.");
puts(s_dashes);

puts("DED$ s_number, d_number, d_long, d_decimals");
puts("Edit d_number with dashes into s_number.");
puts(s_dashes);

puts("DFAC d_factor, d_number");
puts("Find factor of d_number, d_number is prime if factor is 1.");
puts(s_dashes);

	tsub_inp79();
	if(sg_inp79[0] == '*') i_good++;
}
if(i_good == 1) {

puts("DFAK d_factor, d_number, d_mult");
puts("Find factor of (d_number + d_mult * 1E15).");
puts("If the factor is 1 then the expression value is prime.");
puts(s_dashes);

puts("DIFT d_number1 <= d_number2");
puts(s_dashes);

puts("DINC d_number");
puts("Increment d_number by 1.");
puts(s_dashes);

puts("DLOG d_base10logarithm, d_number");
puts(s_dashes);

puts("DPK$ s_packednumber, d_number, d_long");
puts(s_dashes);

puts("DPOW d_result, d_number, d_power");
puts("d_result = d_number ^ d_power");
puts("Raise d_number to power d_power and put into d_result.");
puts("DPOW works exactly the same as using ^ in the decimal assignment.");
puts(s_dashes);

puts("DRAN d_random");
puts("Put a positive random number less than 1 into d_random.");
puts(s_dashes);

	tsub_inp79();
	if(sg_inp79[0] == '*') i_good++;
}
if(i_good == 1) {

puts("DROU d_rounded, d_number");
puts("Round d_number to a whole number into d_rounded.");
puts(s_dashes);

puts("DSEC d_seconds");
puts("Put number of seconds into d_seconds.");
puts(s_dashes);

puts("DSIN d_sine, d_radians");
puts("Put the sine of d_radians into d_sine.");
puts(s_dashes);

puts("DSET d_result = -2.5 ? 2 * d_num1 - d_num2 \\ 4 / d_num3 + 0.5 @ 2 ^ 2");
puts("DSET the decimal expression assignment command.");
puts("The command DSET may be left out.");
puts(s_dashes);

puts("DSET operators");
puts("+ is add, - is subtract, * is multiply, / is divide, % is mod.");
puts("\\ is integer divide, @ 2 is round to 2, ? 2 is truncate to 2.");
puts("^ is exponentiate.");
puts(s_dashes);

puts("DSYS d_system, d_which");
puts(s_dashes);

puts("DTO$ s_number, d_number, d_long, d_decimals");
puts("Change d_number to string s_number with no commas.");
puts(s_dashes);

puts("DTOF s_field, d_number, d_long");
puts("Change d_number to a field number s_field with length d_long.");
puts(s_dashes);

	tsub_inp79();
	if(sg_inp79[0] == '*') i_good++;
}
if(i_good == 1) {

puts("DTOI d_index, d_number");
puts("Put d_number into the 32000 element array at d_index");
puts(s_dashes);

puts("DTRU d_truncated, d_number");
puts("Truncate d_number towards zero to an integer");
puts(s_dashes);

puts("DWHI d_number1 <= d_number2");
puts(s_dashes);

puts("ITOD d_number, d_index");
puts("Put decimal from 32000 element array at d_index into d_number");
puts(s_dashes);

	tsub_inp79();
	if(sg_inp79[0] == '*') i_good++;
}
if(i_good == 1) {

puts("ELSE");
puts("Else in a DIFT or $IFT if block");
puts(s_dashes);

puts("ENDI");
puts("End of DIFT or $IFT if block");
puts(s_dashes);

puts("ENDP");
puts("Ends program");
puts(s_dashes);

puts("ENDW");
puts("Ends DWHI or $WHI while loops");
puts(s_dashes);

puts("GTAG tag_loop1");
puts("GOTO tag_loop1");
puts("GOTO the tag GTAG with the same tag name.");
puts("GOTO cannot jump into or outof a subroutine.");
puts(s_dashes);

puts("SUBR sub_some_subroutine");
puts("Begins a subroutine sub_some_subroutine");
puts(s_dashes);

puts("ENDS sub_some_subroutine");
puts("Ends a subroutine sub_some_subroutine");
puts(s_dashes);

puts("VARI d_number, s_string");
puts("Defines local decimal variable d_number and");
puts("defines local string variable s_string");
puts(s_dashes);

	tsub_inp79();
	if(sg_inp79[0] == '*') i_good++;
}
if(i_good == 1) {

puts("FADD d_long, s_filename, s_record");
puts("Append s_record to file s_filename put length in d_long.");
puts("This command puts a linefeed on the end of the record.");
puts(s_dashes);

puts("FAPP d_long, s_filename, s_record");
puts("Append s_record to file s_filename put length in d_long.");
puts("This command puts a carriage return and line feed on.");
puts(s_dashes);

puts("FDEL d_result, s_filename");
puts("Delete file s_filename put 1 in d_result.");
puts(s_dashes);

puts("FINP s_wholefile, s_filename");
puts("Input whole file s_filename into s_wholefile.");
puts(s_dashes);

puts("FLEN d_long, s_filename");
puts("Put length of file s_filename into d_long.");
puts(s_dashes);

	tsub_inp79();
	if(sg_inp79[0] == '*') i_good++;
}
if(i_good == 1) {

puts("FOUT d_length, s_outfilename, s_wholefile");
puts("Output s_wholefile to s_outfilename put length in d_length.");
puts(s_dashes);

puts("FREA s_record, s_filename, d_byte, d_long");
puts("Read file s_filename beginning at d_byte for d_long into s_record.");
puts(s_dashes);

puts("FREN s_newfilename, s_oldfilename");
puts("Rename file s_oldfilename to file s_newfilename.");
puts(s_dashes);

puts("FSIP s_record, s_filename, d_filebyte");
puts("Sip s_record from s_filename beginning at d_filebyte and");
puts("beginning of next record in d_filebyte.");
puts(s_dashes);

puts("FWRI d_long, s_filename, d_byte, s_record");
puts("Write s_record to s_filename at d_byte put length in d_long.");
puts(s_dashes);

	tsub_inp79();
}
} /* sub_program_help */

void sub_program_load(int ip_mode) {
/* updated 2008/02/20, 2007/10/13, 2005/12/02, 2005/11/30 */
/* 2005/10/29, 2005/09/03, 2005/06/18, 2005/06/14, 2005/06/01 */
/* 2005/04/30, 2005/04/14, 2005/04/04, 2005/04/01, 2005/03/29 */
/* 2005/03/14, 2005/03/12, 2005/03/01, 2005/02/19, 2005/02/13 */
/* 2005/02/08, 2005/02/06, 2005/01/31, 2005/01/30, 2004/12/18 */
	FILE *pf_program;
	char s_record[200];
	char s_pline[200];
	char s_vars_str[VCHARNAME];
	int i_vars_str_lg;
	char s_vars_dec[VCHARNAME];
	int i_vars_dec_lg;
	char s_split[200];
    int i_split_lg;
	char *psz;
	int i_process, i_good, i_loop, i_read_record, i_colon;
    int i_type, i_subrline, i_insubr, i_newsubr, i_first_not_vari_hit;
	int iy, iz;

    /* zero max global and stored literal counts */
    ig_dmaxglobal_ct = 0;
    ig_smaxglobal_ct = 0;
	ig_dmaxliteral_ct = 0;
    ig_smaxliteral_ct = 0;

	tsub_blank(s_vars_str, VCHARNAME);
	i_vars_str_lg = 0;

	tsub_blank(s_vars_dec, VCHARNAME);
	i_vars_dec_lg = 0;

    if(ip_mode == 1) {
		/* begin load from the menu */
		puts("enter program name");
		tsub_inp79();
		tsub_copy(sg_program, sg_inp79, 20);
		sg_program[ig_inp79_lg] = 0;
	}

    /* open the file */
	i_process = 1;
	pf_program = fopen(sg_program, "r");
	if(pf_program == NULL) {
		puts("file not opened");
		i_process++;
		tsub_inp79();
	}
	/* initial psga_plines pointers to NULL */
	if(i_process == 1) {
		for(iz = 0; iz < PLINES; iz++) {
			free(psga_plines[iz]);
			psga_plines[iz] = NULL;
			iga_plines_lg[iz] = 0;
		}
		sub_program_initialize(1);
	}

    /* get program plines from file */
	ig_exit = 2;
	i_first_not_vari_hit = 2;
	i_split_lg = 0;
	i_read_record = 1;
	i_insubr = 2;
	i_newsubr = 1;
	ig_pline_ix = 0;
	i_loop = i_process;

	while(i_loop == 1) {
		i_good = 1;
		tsub_blank(s_record, 200);

		if(i_read_record == 1) {
			/* read record in from program file */
			psz = fgets(s_record, sizeof(s_record), pf_program);
			if(psz == NULL) {
            	i_loop++;
                i_good++;
            }
		}
		else {
			/* last part of a split */
			tsub_copy(s_record, s_split, i_split_lg);
            i_read_record = 1;
        }

		if(i_good == 1) {
			tsub_copy(sg_pass, s_record, 200);
			tsub_blank_escapes(sg_pass, VSLONG);
            ng_pass_lg = 200;
            tsub_pass_trim_right();
            tsub_pass_trim_left();
			tsub_blank(sg_pline, 200);
			tsub_copy(sg_pline, sg_pass, ng_pass_lg);
			ig_pline_lg = ng_pass_lg;

			if(sg_pline[0] <= 32) i_good++;
			if(sg_pline[0] == '\'') i_good++;
			if(sg_pline[0] == '<') i_good++;
		}

		if(i_good == 1) {
			/* do we have a split record */
			sub_prep_split(&i_colon);

			if(i_colon > 0) {
				/* we have a split */
				i_read_record = 2;

				i_split_lg = ig_pline_lg - i_colon;
				tsub_copy(s_split, &sg_pline[i_colon + 1], i_split_lg);
				ig_pline_lg = i_colon;
			    tsub_case_upper(sg_pline, 4);

                iz = tfni_compare_strings(sg_pline, "DIFT", 4);
                if(iz == 0) sg_pline[3] = '1';

                iz = tfni_compare_strings(sg_pline, "$IFT", 4);
                if(iz == 0) sg_pline[3] = '1';
            }
        }

		if(i_good == 1) {
			/* store string literals */
            sub_prep_literal_strings();

			/* remove not needed spaces in sg_pline,ig_pline_lg */
			sub_prep_no_spaces();

			/* make unquoted upper case */
			tsub_case_upper(sg_pline, ig_pline_lg);

			/* store number literals */
            sub_prep_literal_numbers();

            /* do we have a subr line ie SUBR,SUB_ set i_subrline */
			iz = tfni_compare_strings(sg_pline, "SUBR", 4);
			if(iz != 0) iz = tfni_compare_strings(sg_pline, "SUB_", 4);
			if(iz == 0) i_subrline = 1;
            else i_subrline = 2;

			/* prep the format of the sg_pline,ig_pline_ig */
			/* put in DSET,$SET,ESUB */
			sub_prep_format1();

            /* prep variables in the pline */
			if(i_subrline != 1) {
				/* ENDS has to run through these */
				sub_prep_variables_str(s_vars_str, &i_vars_str_lg);
                if(i_vars_str_lg > VCHARNAME) {
                	sub_program_error_end("too many str", 12);
                    i_vars_str_lg = 1;
                }
				sub_prep_variables_dec(s_vars_dec, &i_vars_dec_lg);
                if(i_vars_str_lg > VCHARNAME) {
                	sub_program_error_end("too many dec", 12);
                    i_vars_str_lg = 1;
                }
			}

			/* prep the format of the sg_pline,ig_pline_ig */
			/* put + in DSET and make compare two bytes in DIFT,$IFT */
			sub_prep_format2();

            /* 1=SUBR, 2=VARI */
            i_type = 0;

            /* i_insubr=1 means we are in a subroutine */
			iz =tfni_compare_strings(sg_pline, "SUBR,", 5);
            if(iz == 0) {
               	i_insubr = 1;
				i_newsubr = 1;
            	i_type = 1;
			}

			iz = tfni_compare_strings(sg_pline, "VARI,", 5);
			if(iz == 0) i_type = 2;

			if(i_newsubr == 1 && i_type == 0) {
				/* we need an EVAR line: EVAR,N00000,N00000; */
				tsub_copy(s_pline, "EVAR,N00000,N00000;", 19);

				sub_prep_evar(i_insubr, s_pline, s_vars_dec, i_vars_dec_lg);

				sub_prep_evar(i_insubr, s_pline, s_vars_str, i_vars_str_lg);

                tsub_make_long_string(&psga_plines[ig_pline_ix], 19);

				tsub_copy(psga_plines[ig_pline_ix], s_pline, 19);
                iga_plines_lg[ig_pline_ix] = 19;

                i_newsubr++;
                ig_pline_ix++;
            }

            if(i_first_not_vari_hit != 1 && i_type != 2) {
				/* first not vari so have all globals */
				i_first_not_vari_hit = 1;
			    iy = 0;
			    for(iz = 0; iz < i_vars_dec_lg; iz++) {
                	if(s_vars_dec[iz] == ':') iy++;
                }
				ig_dmaxglobal_ct = iy;

			    iy = 0;
    			for(iz = 0; iz < i_vars_str_lg; iz++) {
                	if(s_vars_str[iz] == ':') iy++;
                }
				ig_smaxglobal_ct = iy;
				if(ig_debug == 1) {
					printf("ig_dmaxglobal_ct=%d, ig_smaxglobal_ct=%d\n",
                    ig_dmaxglobal_ct, ig_smaxglobal_ct);
					tsub_inp79();
                }
            }

            /* allocate space and store the pline */
            tsub_make_long_string(&psga_plines[ig_pline_ix], ig_pline_lg);

			tsub_copy(psga_plines[ig_pline_ix], sg_pline, ig_pline_lg);
			iga_plines_lg[ig_pline_ix] = ig_pline_lg;

            if(ig_trace == 1) tsub_show_pline_by_index(ig_pline_ix);

			if(ig_debug == 1) {
            	tsub_show_pline_by_index(ig_pline_ix);
            }
			/* tsub_show_pline(ig_pline_ix, sg_pline, ig_pline_lg); */
			/* tell */
			if((ig_pline_ix % 1000) == 0) printf("load=%d\r", ig_pline_ix);

			ig_pline_ix++;

			/* tell */
			if((ig_pline_ix % 1000) == 0) printf("load=%d\r", ig_pline_ix);

			if(ig_pline_ix >= (PLINES - 20)) i_loop++;
            if(ig_exit == 1) i_loop++;
		}
	}

	/* prep the global/local variable stacks */
	iy = ig_dmaxliteral_ct;
	iga_dvstack[0] = iy;
	ig_dvstack_ct = iy;
    ig_dvstack_ix = 0;

	iy = ig_smaxliteral_ct;
	iga_svstack[0] = iy;
    ig_svstack_ct = iy;
    ig_svstack_ix = 0;

	printf("lines=%d\n", --ig_pline_ix);
	if(i_process == 1) fclose(pf_program);
} /* sub_program_load */


void sub_program_show(void) {
/* updated 2006/03/06, 2005/12/04 */
/* 2005/03/30, 2005/03/29, 2005/03/13, 2005/02/06, 2004/11/21 */
	int i_loop, i_index, i_linect, i_subr, iz;
	FILE *pf_export;

    i_subr = 2;
	i_index = 0;
	i_linect = 0;
	i_loop = 1;
	while(i_loop == 1) {
		ig_pline_lg = iga_plines_lg[i_index];
		tsub_copy(sg_pline, psga_plines[i_index], ig_pline_lg);

		if(ig_debug == 1) {
			printf("i_index=%d, i_long=%d\n", i_index, ig_pline_lg);
			i_linect++;
		}
		if(tfni_compare_strings(sg_pline, "SUBR", 4) == 0) {
			if(i_subr == 1) {
				tsub_show_pline(i_index, sg_pline, ig_pline_lg);
            }
            else {
				/* put a blank line above a SUBR */
				puts(" ");
			}
			i_linect++;
        }

		if(i_subr != 1) {
        	tsub_show_pline(i_index, sg_pline, ig_pline_lg);
			i_linect++;
		}

		i_index++;
		if(i_index >= PLINES) i_linect = 50;
		if(iga_plines_lg[i_index] == 0) i_linect = 50;
        if(i_linect == 50) i_index = 0;

		if(i_linect >= 22) {
			i_linect = 1;
			tsub_out79("return, line#, SUBR, NUM, EXP or * to end", 41);
            tsub_inp79();

            /* toggle looking at just SUBR */
            tsub_case_upper(sg_inp79, 79);
            iz = tfni_compare_strings(sg_inp79, "SUBR", 4);
            if(iz == 0) {
            	if(i_subr != 1) i_subr = 1;
                else i_subr = 2;
			}

            /* show numbers */
            iz = tfni_compare_strings(sg_inp79, "NUM", 3);
            if(iz == 0) {
				printf(" ig_dmaxglobal_ct=%d\n", ig_dmaxglobal_ct);
				printf("ig_dmaxliteral_ct=%d\n", ig_dmaxliteral_ct);
				printf(" ig_smaxglobal_ct=%d\n", ig_smaxglobal_ct);
				printf("ig_smaxliteral_ct=%d\n", ig_smaxliteral_ct);
				tsub_inp79();
			}

            iz = tfni_compare_strings(sg_inp79, "EXP", 3);
            if(iz == 0) {
				puts("1=export to file export1.txt");
                tsub_inp79();
                if(sg_inp79[0] == '1') {
					pf_export = fopen("export1.txt", "w");
                    if(pf_export != NULL) {
						for(iz = 0; iz <= PLINES
                        && iga_plines_lg[iz] != 0; iz++) {
							ig_pline_lg = iga_plines_lg[iz];
							tsub_copy(sg_pline, psga_plines[iz],
                            ig_pline_lg);
                            sg_pline[ig_pline_lg] = 0;
                            fprintf(pf_export, "%s\n", sg_pline);
                        }
						fclose(pf_export);
                    }
                }
			}

			if(sg_inp79[0] == '*') i_loop++;
			if(ng_inp79_long > 0) {
            	i_index = ng_inp79_long - 1;
                i_subr = 2;
            }

			if(i_index < 0 || i_index >= PLINES) i_index = 0;
		}
	}
} /* sub_program_show */


void sub_program_run(void) {
/* updated 2009/03/07, 2009/03/08, 2008/11/20, 2008/10/20 */
/* 2008/03/06, 2008/02/21, 2008/02/20, 2008/02/10, 2008/01/30 */
/* 2008/01/27, 2008/01/26, 2008/01/23, 2008/01/16, 2007/10/15 */
/* 2006/10/26, 2006/09/26, 2006/09/25, 2006/09/24, 2006/05/31 */
/* 2006/05/12, 2006/04/29, 2006/04/23, 2006/03/17, 2006/03/11 */
/* 2006/01/17, 2005/11/30, 2005/09/18, 2005/09/04, 2005/09/03 */
/* 2005/08/05, 2005/07/26, 2005/06/20, 2005/05/09, 2005/05/03 */
/* 2005/04/12, 2005/04/09, 2005/04/06, 2005/04/02, 2005/03/31 */
/* 2005/03/27, 2005/03/25, 2005/03/19, 2005/03/14, 2005/03/13 */
/* 2005/03/12, 2005/03/06, 2005/03/05, 2005/03/01, 2005/02/27 */
/* 2005/02/26, 2005/02/24, 2005/02/21, 2005/02/20, 2005/02/17 */
/* 2005/02/13, 2005/02/06, 2005/02/03, 2005/01/30, 2004/12/11 */
	int i_command, i_extra;
    long n_index;

    ig_exit = 2;
    if(ig_debug == 1) tsub_bug("sub_program_run");

	sub_program_initialize(2);
    if(ig_debug == 1) tsub_bug("sub_program_initialize(2)");

	/* link dwhi,$whi,dift,$ift,else,endi,endw */
	sub_program_link_dift_dwhi();
    if(ig_debug == 1) tsub_bug("sub_program_link_dift_dwhi");

	/* link esub to subr */
	sub_program_link_esub();
    if(ig_debug == 1) tsub_bug("sub_program_link_esub");

    /* link the commands into iga_link_commands */
    sub_program_link_commands();
    if(ig_debug == 1) tsub_bug("sub_program_link_commands");

	/* validate the commands and variables */
	if(ig_exit != 1) sub_program_validate_commands();
    if(ig_exit != 1 && ig_debug == 1) {
        tsub_bug("sub_program_validate_commands");
    }

    if(ig_step == 1) ig_trace = 1;
    i_extra = 2;
    if(ig_trace == 1 || ig_debug == 1) i_extra = 1;

	ig_pline_ix = -1;

	while(ig_exit != 1) {
        if(i_extra == 1) {
    		if(ig_debug == 1 && ig_pline_ix >= 0) {
	    		/* debug in turned on */
		    	puts("debug after");

                /* tsub_debug shows the line at index ig_pline_ix */
                tsub_debug();
                i_extra = ig_debug;
		    }

            ig_pline_ix++;
            /* dg_plines_done is how many lines were run */
            dg_plines_done++;

    		/* get the command number into i_command */
	    	i_command = iga_link_commands[ig_pline_ix];

            /* get the line sg_pline,ig_pline_lg from index ig_pline_ix */
    		/* ig_pline_lg = iga_plines_lg[ig_pline_ix]; */

            /* tsub_copy(sg_pline, psga_plines[ig_pline_ix], ig_pline_lg); */
            /* psg_pline = psga_plines[ig_pline_ix]; */

    		/* get the link for this line */
	    	ig_link_ix = iga_links[ig_pline_ix];

    		if(ig_trace == 1) {
	    		/* trace is turned on */
		    	tsub_show_pline_by_index(ig_pline_ix);
			    if(ig_step == 1) {
                	tsub_inp79();
                    if(sg_inp79[0] == '*') ig_exit = 1;
                }
    		}

	    	if(ig_debug == 1) {
		    	/* debug is turned on */
			    puts("debug before");

                /* tsub_debug shows the line at index ig_pline_ix */
                tsub_debug();
		    }
        }
        else {
            /* not i_extra just regular stuff */

            ig_pline_ix++;
            /* dg_plines_done is how many lines were run */
            dg_plines_done++;

    		/* get the command number into i_command */
	    	i_command = iga_link_commands[ig_pline_ix];

            /* get the line sg_pline,ig_pline_lg from index ig_pline_ix */
    		/* ig_pline_lg = iga_plines_lg[ig_pline_ix]; */

            /* tsub_copy(sg_pline, psga_plines[ig_pline_ix], ig_pline_lg); */
            /* psg_pline = psga_plines[ig_pline_ix]; */

    		/* get the link for this line */
	    	ig_link_ix = iga_links[ig_pline_ix];
        }
/*
DDEC,DDUO,DFAK,DFAC,DIFT,DINC,
DRAN,DSEC,DSET,DTO$,DTOI,DWHI,
ELSE,ENDI,ENDP,ENDS,ENDW,ESUB,
EVAR,ITOD,$APP,$BES,$CHD,$CLO,
$CUP,$CUT,$DAT,$DEL,$SHO,$IFT,
$INP,$INS,$ISD,$LEN,$OUT,$REP,
$SET,$TLO,$TOD,$TRB,$TRL,$TRR,
$TUP,$WHI,FWRI,FREA,FAPP,FLEN,
FDEL,FSIP,DBAD,DIF1,$IF1,$LOK,
$BAK,$CH$,DCH$,$TOI,ITO$,$ISC,
$IST,$ISP,$OFF,DBUG,FREN,$PAR,
ARRB,ARRZ,$SYS,DABS,DROU,DTRU,
$SWP,$SOR,$CNT,$PKD,DPK$,DTOF,
FINP,FOUT,FADD,DSYS,VARI,SUBR,
$COD,$TOE,DLOG,DSIN,DARC,ADDI,
$DEL,$HSH,DED$,GTAG,GOTO,DPOW, 96 */

		if(i_command < 13) {
            /* make psg_pline point to the command line */
            psg_pline = psga_plines[ig_pline_ix];

        	if(i_command == 9) {
                /* DSET */
                /* get ig_pline_lg from index ig_pline_ix */
		        ig_pline_lg = iga_plines_lg[ig_pline_ix];
                sub_command_dset();  /* DSET */
            }
	        else if(i_command == 5) {
				/* DIFT,DWHI,DIF1 */
            	sub_command_dift_dwhi();
				if(ig_true != 1) ig_pline_ix = ig_link_ix;
			}
			else if(i_command == 6) {
                /* DINC */
                if(psg_pline[5] == 'E')
                    n_index = ig_link_ix + ig_dvstack_ct;
                else n_index = ig_link_ix;

                dga_decimals[n_index]++;
            }
			else if(i_command == 1) sub_command_dinc(2); /* DDEC */
    	    else if(i_command == 2) sub_command_dduo(); /* dduo */
    	    else if(i_command == 8) sub_command_dinc(3); /* dsec */
    	    else if(i_command == 3) sub_command_dfak(); /* DFAK */
        	else if(i_command == 4) sub_command_dfac();  /* DFAC */
	        else if(i_command == 7) sub_command_dinc(4); /* DRAN */
	        else if(i_command == 10) sub_command_dtos(1); /* DTOS */
    	    else if(i_command == 11) sub_command_dtoi(1); /* DTOI */
        	else if(i_command == 12) {
				/* DWHI same as DIFT */
            	sub_command_dift_dwhi();
				if(ig_true != 1) ig_pline_ix = ig_link_ix;
			}
        }
		else if(i_command < 21) {
            /* ELSE,ENDW,GOTO */
	        if(i_command == 13) ig_pline_ix = ig_link_ix;
    	    else if(i_command == 14); /* ENDI,GTAG */
        	else if(i_command == 20) {
                /* ITOD */
                /* make psg_pline point to the command line */
                psg_pline = psga_plines[ig_pline_ix];
                sub_command_itod(); /* ITOD */
            }
	        else if(i_command == 16) sub_command_ends(); /* ENDS */
        	else if(i_command == 18) {
	        	/* ESUB */
				if(ig_subr == 1) {
                	tsub_show_pline_by_index(ig_pline_ix);
					tsub_inp79();
                }
				ig_subr_ix++;
				iga_subr_links[ig_subr_ix] = ig_pline_ix;
				ig_pline_ix = ig_link_ix;
			}
    	    else if(i_command == 19) {
                /* EVAR */
                /* make psg_pline point to the command line */
                psg_pline = psga_plines[ig_pline_ix];
                sub_command_evar(); /* EVAR */
            }
        	else if(i_command == 15) ig_exit = 1; /* ENDP */
            /* ENDW see ELSE */
    	    else if(i_command == 17) ig_pline_ix = ig_link_ix;
        }
		else if(i_command < 31) {
            /* make psg_pline point to the command line */
            psg_pline = psga_plines[ig_pline_ix];

	        if(i_command == 30) {
				/* $IFT and $IF1 and $WHI */
            	sub_command_sift_swhi();
				if(ig_true != 1) ig_pline_ix = ig_link_ix;
            }
	        else if(i_command == 21) {
                /* $APP */
                /* get ig_pline_lg from index ig_pline_ix */
		        ig_pline_lg = iga_plines_lg[ig_pline_ix];
                sub_command_sapp(); /* $APP */
            }
    	    else if(i_command == 22) sub_command_strl(4); /* $BES */
        	else if(i_command == 23) sub_command_slen(2); /* $CHD */
	        else if(i_command == 24) sub_command_strl(5); /* $CLO */
    	    else if(i_command == 25) sub_command_strl(6); /* $CUP */
        	else if(i_command == 26) sub_command_scut();  /* $CUT */
	        else if(i_command == 27) sub_command_sdat();  /* $DAT */
    	    else if(i_command == 28) sub_command_sdel();  /* $DEL */
        	else if(i_command == 29) {
                /* $SHO */
                /* get ig_pline_lg from index ig_pline_ix */
		        ig_pline_lg = iga_plines_lg[ig_pline_ix];
                sub_command_sout(2); /* $SHO */
            }
        }
		else if(i_command < 41) {
            /* make psg_pline point to the command line */
            psg_pline = psga_plines[ig_pline_ix];

	        if(i_command == 31) {
                /* $INP */
                /* get ig_pline_lg from index ig_pline_ix */
		        ig_pline_lg = iga_plines_lg[ig_pline_ix];
                sub_command_sinp(); /* $INP */
            }
    	    else if(i_command == 32) sub_command_sins(); /* $INS */
        	else if(i_command == 33) sub_command_stod(2); /* $ISD */
	        else if(i_command == 34) sub_command_slen(1); /* $LEN */
    	    else if(i_command == 35) {
                /* $OUT */
                /* get ig_pline_lg from index ig_pline_ix */
		        ig_pline_lg = iga_plines_lg[ig_pline_ix];
                sub_command_sout(1); /* $OUT */
            }
        	else if(i_command == 36) sub_command_srep(); /* $REP */
	        else if(i_command == 37) {
                /* $SET */
                /* get ig_pline_lg from index ig_pline_ix */
		        ig_pline_lg = iga_plines_lg[ig_pline_ix];
                sub_command_sset();  /* $SET */
            }
    	    else if(i_command == 38) sub_command_strl(7); /* $TLO */
        	else if(i_command == 39) sub_command_stod(1); /* $TOD */
	        else if(i_command == 40) sub_command_strl(3); /* $TRB */
        }
		else if(i_command < 51) {
            /* make psg_pline point to the command line */
            psg_pline = psga_plines[ig_pline_ix];

	        if(i_command == 41) sub_command_strl(1); /* $TRL */
    	    else if(i_command == 42) sub_command_strl(2); /* $TRR */
        	else if(i_command == 43) sub_command_strl(8); /* $TUP */
    	    else if(i_command == 45) sub_command_file(1); /* FWRI */
        	else if(i_command == 46) sub_command_file(2); /* FREA */
	        else if(i_command == 47) sub_command_file(10); /* FAPP */
    		else if(i_command == 48) sub_command_file(4); /* FLEN */
	        else if(i_command == 49) sub_command_file(5); /* FDEL */
 	        else if(i_command == 50) sub_command_file(6); /* FSIP */
	        else if(i_command == 44) {
				/* $WHI see $IFT=30 */
            	sub_command_sift_swhi();
				if(ig_true != 1) ig_pline_ix = ig_link_ix;
			}
		}
		else if(i_command < 61) {
            /* make psg_pline point to the command line */
            psg_pline = psga_plines[ig_pline_ix];

    	    if(i_command == 51) {
				/* DBAD */
            	sub_command_dift_dwhi();
				if(ig_true == 1) sub_command_dbad();
			}
			else if(i_command == 54) sub_command_slok(1); /* $LOK */
            else if(i_command == 55) sub_command_slok(2); /* $BAK */
			else if(i_command == 56) sub_command_schs(1); /* $CH$ */
            else if(i_command == 57) sub_command_schs(2); /* DCH$ */
            else if(i_command == 58) sub_command_stoi(1); /* $TOI */
            else if(i_command == 59) sub_command_stoi(2); /* ITO$ */
    	    else if(i_command == 60) sub_command_sisc(1); /* $ISC */
    	    else if(i_command == 52) {
            	/* DIF1 same as DIFT=4 */
            	sub_command_dift_dwhi();
				if(ig_true != 1) ig_pline_ix++;
			}
			else if(i_command == 53) {
            	/* $IF1 same as $IFT=30 */
            	sub_command_sift_swhi();
				if(ig_true != 1) ig_pline_ix++;
			}
		}
        else if(i_command < 71) {
            /* make psg_pline point to the command line */
            psg_pline = psga_plines[ig_pline_ix];

    	    if(i_command == 61) sub_command_sisc(2); /* $IST */
    	    else if(i_command == 62) sub_command_sisc(3); /* $ISP */
            else if(i_command == 63) sub_command_schs(3); /* $OFF */
			else if(i_command == 64) {
				/* DBUG */
				if(ig_debug == 1) {
                	ig_debug++;
                    i_extra++;
					puts("debug off");
                }
                else {
                	ig_debug = 1;
                    i_extra = 1;
					puts("debug on");
                }
            }
			else if(i_command == 65) sub_command_file(7); /* FREN */
            else if(i_command == 66) sub_command_spar(); /* $PAR */
			else if(i_command == 67) sub_command_stoi(3); /* ARRB */
			else if(i_command == 68) sub_command_stoi(4); /* ARRZ */
            else if(i_command == 69) sub_command_ssys(); /* $SYS */
    	    else if(i_command == 70) sub_command_dabs(1); /* DABS */
        }
		else if(i_command < 81) {
            /* make psg_pline point to the command line */
            psg_pline = psga_plines[ig_pline_ix];

    	    if(i_command == 71) sub_command_dabs(2); /* DROU */
    	    else if(i_command == 72) sub_command_dabs(3); /* DTRU */
			else if(i_command == 73) sub_command_sswp(); /* $SWP */
            else if(i_command == 74) sub_command_ssor(); /* $SOR */
            else if(i_command == 75) sub_command_scnt(); /* $CNT */
			else if(i_command == 76) sub_command_spkd(1); /* $PKD */
			else if(i_command == 77) sub_command_spkd(2); /* DPK$ */
			else if(i_command == 78) sub_command_spkd(3); /* DTOF */
    	    else if(i_command == 79) sub_command_file(8); /* FINP */
    	    else if(i_command == 80) sub_command_file(9); /* FOUT */
		}
		else if(i_command < 97) {
            /* make psg_pline point to the command line */
            psg_pline = psga_plines[ig_pline_ix];

			if(i_command == 81) sub_command_file(3); /* FADD */
			else if(i_command == 82) sub_command_dsys(); /* dsys */
    	    else if(i_command == 83); /* VARI */
			/* else if(i_command == 84); SUBR would be an error */
			else if(i_command == 85) sub_command_strl(9); /* $COD */
			else if(i_command == 86) sub_command_stoe(); /* $TOE */
			else if(i_command == 87) sub_command_dabs(4); /* DLOG */
			else if(i_command == 88) sub_command_dabs(5); /* DSIN */
			else if(i_command == 89) sub_command_dabs(6); /* DARC */
			else if(i_command == 90) sub_command_dtoi(3); /* ADDI */
			else if(i_command == 91) sub_command_sdot(); /* $DOT */
	        else if(i_command == 92) sub_command_slen(3); /* $HSH */
    	    else if(i_command == 93) sub_command_dtos(2); /* DED$ */
			else if(i_command == 94); /* GTAG see ENDI */
            /* GOTO see ENDW */
            else if(i_command == 95) ig_pline_ix = ig_link_ix;
			else if(i_command == 96) sub_command_dpow();  /* DPOW */
        }
		else {
			/* we have a not known command */
            tsub_debug();
			tsub_out79("bad command at run", 18);
			tsub_inp79();
			ig_exit = 1;
        }
	}
} /* sub_program_run */


void sub_program_info(void) {
/* updated 2005/06/07 */
/* 2005/05/29, 2005/04/14, 2005/04/06, 2005/03/14, 2005/03/12 */
/* 2005/03/03, 2005/02/24, 2005/02/15, 2005/02/01, 2004/11/26 */
	printf("plines=%d\n", PLINES);
	printf("pstack=%d\n", PSTACK);
	printf("vstrings=%d\n", VSTRINGS);
	printf("vslong=%d\n", VSLONG);
	printf("vdeciamls=%d\n", VDECIMALS);
	printf("vstack=%d\n", VSTACK);
	printf("darray=%d\n", DARRAY);
	printf("sarray=%d\n", SARRAY);
	printf("max new string length=%d\n", MAXSTRING);
	printf("lines run=%.0f\n", dg_plines_done);

	tsub_inp79();
} /* sub_program_info */


void sub_program_initialize(int ip_which) {
/* updated 2005/12/02, 2005/06/05, 2005/05/09 */
/* 2005/04/06, 2005/03/12, 2005/02/24, 2005/02/01, 2004/11/25 */
	int iz;

    /* dg_plines_done is how many lines were run */
    dg_plines_done = 0;

	ig_subr_ix = 0;

    if(ip_which == 1) {
		for(iz = 0; iz < VSTRINGS; iz++) {
			free(psga_strings[iz]);
			psga_strings[iz] = NULL;
			nga_strings_lg[iz] = 0;
		}

		for(iz = 0; iz < VDECIMALS; iz++) {
			dga_decimals[iz] = 0;
		}
	}

	for(iz = 0; iz < 100; iz++) {
		iga_subr_links[iz] = 0;
	}

    ig_dvstack_ix = 0;
    ig_svstack_ix = 0;
	if(ip_which == 1) {
		for(iz = 0; iz < VSTACK; iz++) {
    		iga_dvstack[iz] = 0;
        	iga_svstack[iz] = 0;
	    }
	}

	for(iz = 0; iz < DARRAY; iz++) dga_darray[iz] = 0;

	for(iz = 0; iz < SARRAY; iz++) {
		free(psga_sarray[iz]);
		psga_sarray[iz] = NULL;
		iga_sarray_lg[iz] = 0;
	}

    free(psg_use1);
	psg_use1 = NULL;
    ng_use1 = 0;

    free(psg_use2);
	psg_use2 = NULL;
    ng_use2 = 0;

    free(psg_use3);
	psg_use3 = NULL;
    ng_use3 = 0;
} /* sub_program_initialize */


void sub_program_link_commands(void) {
/* updated 2008/12/06, 2008/10/20, 2008/01/30 */
/* 2008/01/23, 2007/04/17, 2007/04/10, 2006/10/26, 2006/05/31 */
/* 2006/05/12, 2006/04/29, 2006/04/23, 2006/03/17, 2006/01/17 */
/* 2005/09/18, 2005/07/27, 2005/06/20, 2005/05/09, 2005/05/05 */
/* 2005/05/03, 2005/04/12, 2005/04/03, 2005/04/02, 2005/03/31 */
/* 2005/03/30, 2005/03/27, 2005/03/25, 2005/03/19, 2005/03/13 */
/* 2005/03/12, 2005/03/06, 2005/03/05, 2005/03/01, 2005/02/26 */
	int i_loop, i_command, iz;
	char s_commands[500];

    for(iz = 0; iz < PLINES; iz++) iga_link_commands[iz] = 9999;
	tsub_blank(s_commands, 500);
/*
DDEC,DDUO,DFAK,DFAC,DIFT,DINC,
DRAN,DSEC,DSET,DTO$,DTOI,DWHI,
ELSE,ENDI,ENDP,ENDS,ENDW,ESUB,
EVAR,ITOD,$APP,$BES,$CHD,$CLO,
$CUP,$CUT,$DAT,$DEL,$SHO,$IFT,
$INP,$INS,$ISD,$LEN,$OUT,$REP,
$SET,$TLO,$TOD,$TRB,$TRL,$TRR,
$TUP,$WHI,FWRI,FREA,FAPP,FLEN,
FDEL,FSIP,DBAD,DIF1,$IF1,$LOK,
$BAK,$CH$,DCH$,$TOI,ITO$,$ISC,
$IST,$ISP,$OFF,DBUG,FREN,$PAR,
ARRB,ARRZ,$SYS,DABS,DROU,DTRU,
$SWP,$SOR,$CNT,$PKD,DPK$,DTOF,
FINP,FOUT,FADD,DSYS,VARI,SUBR,
$COD,$TOE,DLOG,DSIN,DARC,ADDI,
$DOT,$HSH,DED$,GTAG,GOTO,DPOW, */
	tsub_copy(s_commands,       "DDEC,DDUO,DFAK,DFAC,DIFT,DINC,", 30);
	tsub_copy(&s_commands[30],  "DRAN,DSEC,DSET,DTO$,DTOI,DWHI,", 30);
    tsub_copy(&s_commands[60],  "ELSE,ENDI,ENDP,ENDS,ENDW,ESUB,", 30);
    tsub_copy(&s_commands[90],  "EVAR,ITOD,$APP,$BES,$CHD,$CLO,", 30);
    tsub_copy(&s_commands[120], "$CUP,$CUT,$DAT,$DEL,$SHO,$IFT,", 30);
    tsub_copy(&s_commands[150], "$INP,$INS,$ISD,$LEN,$OUT,$REP,", 30);
    tsub_copy(&s_commands[180], "$SET,$TLO,$TOD,$TRB,$TRL,$TRR,", 30);
    tsub_copy(&s_commands[210], "$TUP,$WHI,FWRI,FREA,FAPP,FLEN,", 30);
    tsub_copy(&s_commands[240], "FDEL,FSIP,DBAD,DIF1,$IF1,$LOK,", 30);
    tsub_copy(&s_commands[270], "$BAK,$CH$,DCH$,$TOI,ITO$,$ISC,", 30);
	tsub_copy(&s_commands[300], "$IST,$ISP,$OFF,DBUG,FREN,$PAR,", 30);
	tsub_copy(&s_commands[330], "ARRB,ARRZ,$SYS,DABS,DROU,DTRU,", 30);
	tsub_copy(&s_commands[360], "$SWP,$SOR,$CNT,$PKD,DPK$,DTOF,", 30);
    tsub_copy(&s_commands[390], "FINP,FOUT,FADD,DSYS,VARI,SUBR,", 30);
	tsub_copy(&s_commands[420], "$COD,$TOE,DLOG,DSIN,DARC,ADDI,", 30);
	tsub_copy(&s_commands[450], "$DOT,$HSH,DED$,GTAG,GOTO,DPOW,", 30);

    /* go through lines and put command numbers in iga_link_commands */
	ig_pline_ix = 0;
	i_loop = 1;
	while(i_loop == 1) {
		/* get length of line ig_pline_ix */
		ig_pline_lg = iga_plines_lg[ig_pline_ix];

		/* put line ig_pline_ix into sg_pline */
		tsub_copy(sg_pline, psga_plines[ig_pline_ix], ig_pline_lg);

        /* lookup command in s_commands */
        iz = tfnn_string_lookup(s_commands, 500, sg_pline, 4);
		if(iz >= 0) {
			/* get the command number into i_command */
			/* the first command is command 1 */
			i_command = iz / 5 + 1;

            /* optimized 2008/01/23 */
            /* some commands are really the same */
            /* DWHI is the same as DIFT */
            if(i_command == 12) i_command = 5;

            /* DIF1 is the same as DIFT */
            if(i_command == 52) i_command = 5;

            /* $IF1 is the same as $IFT */
            if(i_command == 53) i_command = 30;

            /* $WHI is the same as $IFT */
            if(i_command == 44) i_command = 30;

            /* ENDW is the same as ELSE */
			if(i_command == 17) i_command = 13;

            /* GOTO is the same as ELSE */
			if(i_command == 95) i_command = 13;

			/* GTAG is the same as ENDI */
			if(i_command == 94) i_command = 14;

            /* store command number in iga_link_commands */
			iga_link_commands[ig_pline_ix] = i_command;
        }
        else {
			/* unknown command */
			tsub_show_pline_by_index(ig_pline_ix);
			tsub_out79("bad command at link", 19);
           	tsub_inp79();
           	ig_exit = 1;
			i_loop++;
        }

		ig_pline_ix++;
		if(ig_pline_ix >= PLINES) i_loop++;
		if(iga_plines_lg[ig_pline_ix] == 0) i_loop++;
	}
} /* sub_program_link_commands */


void sub_program_validate_commands(void) {
/* updated 2008/12/06, 2008/01/30, 2007/08/07, 2007/04/10, 2007/01/14 */
/* 2006/10/26, 2006/06/21, 2006/06/11, 2006/06/09, 2006/05/31 */
/* 2006/05/23, 2006/05/12, 2006/04/08, 2006/03/17, 2006/01/17 */
/* 2005/11/02, 2005/11/01, 2005/10/29, 2005/09/18, 2005/09/07 */
/* 2005/09/05, 2005/09/04, 2005/08/07, 2005/08/06, 2005/08/05 */
/* edit the form of the commands */
	int i_loop, i_command;

/*
DDEC,DDUO,DFAK,DFAC,DIFT,DINC, 6
DRAN,DSEC,DSET,DTO$,DTOI,DWHI, 12
ELSE,ENDI,ENDP,ENDS,ENDW,ESUB, 18
EVAR,ITOD,$APP,$BES,$CHD,$CLO, 24
$CUP,$CUT,$DAT,$DEL,$SHO,$IFT, 30
$INP,$INS,$ISD,$LEN,$OUT,$REP, 36
$SET,$TLO,$TOD,$TRB,$TRL,$TRR, 42
$TUP,$WHI,FWRI,FREA,FAPP,FLEN, 48
FDEL,FSIP,DBAD,DIF1,$IF1,$LOK, 54
$BAK,$CH$,DCH$,$TOI,ITO$,$ISC, 60
$IST,$ISP,$OFF,DBUG,FREN,$PAR, 66
ARRB,ARRZ,$SYS,DABS,DROU,DTRU, 72
$SWP,$SOR,$CNT,$PKD,DPK$,DTOF, 78
FINP,FOUT,FADD,DSYS,VARI,SUBR, 84
$COD,$TOE,DLOG,DSIN,DARC,ADDI, 90
$DOT,$HSH,DED$,GTAG,GOTO,DDUO, 96 */
	ig_pline_ix = 0;
	i_loop = 1;
	while(i_loop == 1) {
		i_command = iga_link_commands[ig_pline_ix];

        tsub_blank(sg_pline, 200);
		ig_pline_lg = iga_plines_lg[ig_pline_ix];
		tsub_copy(sg_pline, psga_plines[ig_pline_ix], ig_pline_lg);

        if(i_command == 84) {
            tsub_copy(sg_subr, sg_pline, ig_pline_lg);
            sg_subr[ig_pline_lg] = 0;
        }

        /* 01234567890123456789012345678901 */
        /* DED$ S12345,D12345,N12345,N12345 */
		/* one parameter */
        if(i_command == 1
        || i_command == 6
		|| i_command == 7
        || i_command == 8) {
			/* DDEC=1,DINC=6,DRAN=7,DSEC=8 */
			sub_program_validate_variable(5, 2);
			sub_program_validate_var_last(5);
        }
		else if(i_command == 27) {
			/* $DAT=27 */
			sub_program_validate_variable(5, 12);
			sub_program_validate_var_last(5);
        }

		/* two parameters */
		else if(i_command == 11
        || i_command == 90) {
			/* DTOI=11,ADDI=90 */
			sub_program_validate_variable(5, 1);
			sub_program_validate_variable(12, 1);
			sub_program_validate_var_last(12);
        }
		else if(i_command == 4
        || i_command == 20
        || i_command == 70
        || i_command == 71
        || i_command == 72
        || i_command == 87
        || i_command == 88
        || i_command == 89) {
			/* DFAC=4,ITOD=20,DABS=70,DROU=71,DTRU=72 */
			/* DLOG=87,DSIN=88,DARC=89 */
			sub_program_validate_variable(5, 2);
			sub_program_validate_variable(12, 1);
			sub_program_validate_var_last(12);
        }
		else if(i_command == 5
        || i_command == 12
        || i_command == 51
        || i_command == 52) {
			/* DIFT=5,DWHI=12,DBAD=51,DIF1=52 */
			/* DIFT D12345==E12345 */
			sub_program_validate_variable(5, 1);
			sub_program_validate_variable(13, 1);
			sub_program_validate_var_last(13);
        }
		else if(i_command == 58) {
			/* $TOI=58 */
			/* 012345678901234567 */
			/* $TOI,D12345,N12345 */
			sub_program_validate_variable(5, 1);
			sub_program_validate_variable(12, 11);
			sub_program_validate_var_last(12);
        }
		else if(i_command == 23
        || i_command == 33
        || i_command == 34
        || i_command == 39
		|| i_command == 48
        || i_command == 49
        || i_command == 92) {
			/* $CHD=23,$ISD=33,$LEN=34,$TOD=39,FLEN=48,FDEL=49,$HSH=92 */
			sub_program_validate_variable(5, 2);
			sub_program_validate_variable(12, 11);
			sub_program_validate_var_last(12);
        }
		else if(i_command == 59) {
			/* ITO$=59 */
			sub_program_validate_variable(5, 12);
			sub_program_validate_variable(12, 1);
			sub_program_validate_var_last(12);
        }
		else if(i_command == 22
        || i_command == 24
        || i_command == 25
        || i_command == 38
        || i_command == 40
        || i_command == 41
        || i_command == 42
        || i_command == 43
        || i_command == 79
        || i_command == 85) {
			/* $BES=22,$CLO=24,$CUP=25,$TLO=38,$TRB=40,$TRL=41 */
            /* $TRR=42,$TUP=43,FINP=79, $COD=85 */
			sub_program_validate_variable(5, 12);
			sub_program_validate_variable(12, 11);
			sub_program_validate_var_last(12);
        }
		else if(i_command == 30
        || i_command == 43
        || i_command == 53) {
			/* $IFT=30,$WHI=43,$IF1=53 */
			/* $IFT S12345==T12345 */
			sub_program_validate_variable(5, 11);
			sub_program_validate_variable(13, 11);
			sub_program_validate_var_last(13);
        }

		/* three parameters */
		else if(i_command == 96
        || i_command == 2
        || i_command == 3) {
			/* DPOW=96,DDUO=2,DFAK=3 */
			sub_program_validate_variable(5, 2);
			sub_program_validate_variable(12, 1);
			sub_program_validate_variable(19, 1);
			sub_program_validate_var_last(19);
        }
		else if(i_command == 76) {
			/* $PKD=76 */
			sub_program_validate_variable(5, 2);
			sub_program_validate_variable(12, 1);
			sub_program_validate_variable(19, 11);
			sub_program_validate_var_last(19);
        }
		else if(i_command == 47
        || i_command == 60
		|| i_command == 61
        || i_command == 62
		|| i_command == 65
        || i_command == 75
        || i_command == 80
        || i_command == 81) {
			/* FAPP=47,$ISC=60,$IST=61,$ISP=62,FREN=65 *
            /* $CNT=75,FOUT=80,FADD=81 */
			sub_program_validate_variable(5, 2);
			sub_program_validate_variable(12, 11);
			sub_program_validate_variable(19, 11);
			sub_program_validate_var_last(19);
        }
		else if(i_command == 28
        || i_command == 77
        || i_command == 78) {
			/* $DEL=28,DPK$=77,DTOF=78 */
			sub_program_validate_variable(5, 12);
			sub_program_validate_variable(12, 1);
			sub_program_validate_variable(19, 1);
			sub_program_validate_var_last(19);
        }
		else if(i_command == 32
        || i_command == 36) {
			/* $INS=32,$REP=36 */
			sub_program_validate_variable(5, 12);
			sub_program_validate_variable(12, 1);
			sub_program_validate_variable(19, 11);
			sub_program_validate_var_last(19);
        }
		else if(i_command == 50) {
			/* FSIP=50 */
			sub_program_validate_variable(5, 12);
			sub_program_validate_variable(12, 11);
			sub_program_validate_variable(19, 2);
			sub_program_validate_var_last(19);
        }
		else if(i_command == 56
        || i_command == 63
        || i_command == 74) {
			/* $CH$=56,$OFF=63,$SOR=74 */
			sub_program_validate_variable(5, 12);
			sub_program_validate_variable(12, 11);
			sub_program_validate_variable(19, 1);
			sub_program_validate_var_last(19);
        }
		else if(i_command == 73) {
			/* $SWP=73 */
			sub_program_validate_variable(5, 12);
			sub_program_validate_variable(12, 11);
			sub_program_validate_variable(19, 11);
			sub_program_validate_var_last(19);
        }

		/* four parameters */
		else if(i_command == 45
        || i_command == 54
        || i_command == 55) {
			/* FWRI=45,$LOK=54,$BAK */
			sub_program_validate_variable(5, 2);
			sub_program_validate_variable(12, 11);
			sub_program_validate_variable(19, 1);
			sub_program_validate_variable(26, 11);
			sub_program_validate_var_last(26);
        }
		else if(i_command == 93
        || i_command == 10) {
			/* DED$=93,DTO$=10 */
			sub_program_validate_variable(5, 12);
			sub_program_validate_variable(12, 1);
			sub_program_validate_variable(19, 1);
			sub_program_validate_variable(26, 1);
			sub_program_validate_var_last(26);
        }
		else if(i_command == 26
        || i_command == 46) {
			/* $CUT=26,FREA=46 */
			sub_program_validate_variable(5, 12);
			sub_program_validate_variable(12, 11);
			sub_program_validate_variable(19, 1);
			sub_program_validate_variable(26, 1);
			sub_program_validate_var_last(26);
        }
		else if(i_command == 66
        || i_command == 86) {
			/* $PAR=66, $TOE=86 */
			sub_program_validate_variable(5, 12);
			sub_program_validate_variable(12, 11);
			sub_program_validate_variable(19, 11);
			sub_program_validate_variable(26, 1);
			sub_program_validate_var_last(26);
        }
		else if(i_command == 91) {
			/* $DOT=91 */
			sub_program_validate_variable(5, 2);
			sub_program_validate_variable(12, 11);
			sub_program_validate_variable(19, 11);
			sub_program_validate_variable(26, 1);
			sub_program_validate_var_last(26);
        }

        /* expressions */
		else if(i_command == 9) {
			/* DSET=9 */
			/* 0123456789012345678 */
			/* DSET,D12345=+N12345 */
			sub_program_validate_variable(5, 2);
			sub_program_validate_expression(13, 1);
        }
		else if(i_command == 29
        || i_command == 35) {
			/* $SHO=29,$OUT=35 */
			/* 0123456789012345678901234 */
			/* $SHO,S12345+T12345+S12345 */
			sub_program_validate_expression(5, 11);
        }
		else if(i_command == 21
        || i_command == 31
        || i_command == 37) {
			/* $APP=21,$INP=31,$SET=37 */
			/* 0123456789012345678901234 */
			/* $APP,S12345,T12345+S12345 */
			sub_program_validate_variable(5, 12);
			sub_program_validate_expression(12, 11);
        }

/*
DDEC,DDUO,DFAK,DFAC,DIFT,DINC, 6
DRAN,DSEC,DSET,DTO$,DTOI,DWHI, 12
ELSE,ENDI,ENDP,ENDS,ENDW,ESUB, 18
EVAR,ITOD,$APP,$BES,$CHD,$CLO, 24
$CUP,$CUT,$DAT,$DEL,$SHO,$IFT, 30
$INP,$INS,$ISD,$LEN,$OUT,$REP, 36
$SET,$TLO,$TOD,$TRB,$TRL,$TRR, 42
$TUP,$WHI,FWRI,FREA,FAPP,FLEN, 48
FDEL,FSIP,DBAD,DIF1,$IF1,$LOK, 54
$BAK,$CH$,DCH$,$TOI,ITO$,$ISC, 60
$IST,$ISP,$OFF,DBUG,FREN,$PAR, 66
ARRB,ARRZ,$SYS,DABS,DROU,DTRU, 72
$SWP,$SOR,$CNT,$PKD,DPK$,DTOF, 78
FINP,FOUT,FADD,DSYS,VARI,SUBR, 84
$COD,$TOE,DLOG,DSIN,DARC,ADDI, 90
$DOT,$HSH,DED$,GTAG,GOTO,DDUO, 95 */
		ig_pline_ix++;
		if(ig_pline_ix >= PLINES) i_loop++;
		if(iga_plines_lg[ig_pline_ix] == 0) i_loop++;
		if(ig_exit == 1) i_loop++;
	}
} /* sub_program_validate_commands */


void sub_program_validate_variable(int ip_beg, int ip_type) {
/* updated 2007/08/07, 2007/05/04 */
/* 2006/06/11, 2005/12/05, 2005/12/04, 2005/12/01, 2005/10/29 */
/* 2005/09/05, 2005/09/04, 2005/08/07, 2005/08/06, 2005/08/05 */
/* edit variable */
	char c_1;
	int iz;
	int i_error = 2;

    /* sg_pline,ig_pline_lg */
    /* 012345 */
    /* N12345 */
    c_1 = sg_pline[ip_beg];

    /* is the index numeric */
   	iz = tfni_is_digits(&sg_pline[ip_beg + 1], 5);
	if(iz != 1) i_error = 1;

/* decimal variable types */
/* D=global decimal variable */
/* E=local decimal variable */
/* F=stored decimal constant */
/* N=positive number */
/* M=negative number */

/* string variable types */
/* C=character literal */
/* S=global string variable */
/* T=local string variable */
/* U=stored string literal */

	if(ip_type == 1) {
		/* decimal read */
		if(c_1 != 'D' && c_1 != 'E' && c_1 != 'F'
        && c_1 != 'N' && c_1 != 'M') i_error = 1;
    }
    else if(ip_type == 2) {
		/* decimal read/write */
		if(c_1 != 'D' && c_1 != 'E') i_error = 1;
    }
    else if(ip_type == 11) {
		/* string read */
		if(c_1 != 'C'
        && c_1 != 'S'
        && c_1 != 'T'
        && c_1 != 'U'
		&& c_1 != 'D'
        && c_1 != 'E'
        && c_1 != 'F'
		&& c_1 != 'N'
        && c_1 != 'M') i_error = 1;
    }
    else if(ip_type == 12) {
		/* string read/write */
		if(c_1 != 'S' && c_1 != 'T') i_error = 1;
    }

    if(i_error == 1) {
        puts(sg_subr);
		tsub_out79(&sg_pline[ip_beg], 6);
		tsub_show_pline_by_index(ig_pline_ix);
        sub_program_error_end("bad variable", 12);
    }
} /* sub_program_validate_variable */


void sub_program_validate_var_last(int ip_beg) {
/* updated 2006/06/21, 2005/10/29 */
/* validate to see if last variable is last */
    /* sg_pline,ig_pline_lg */
    /* 012345 */
    /* N12345 */

	if(sg_pline[ip_beg + 6] != ';') {
		puts("bad last");
		ig_exit = 1;
		tsub_show_pline_by_index(ig_pline_ix);
        sub_program_error_end("bad last var", 12);
    }
} /* sub_program_validate_var_last */


void sub_program_validate_expression(int ip_beg, int ip_type) {
/* updated 2010/01/17 */
/* 2010/01/11, 2008/02/02, 2007/10/11, 2007/07/08, 2007/05/04 */
/* 2007/04/11, 2005/12/05, 2005/10/29, 2005/09/05, 2005/09/04 */
    int i_byte;
	int i_error = 2;
	char c_1;

    /* sg_pline,ig_pline_lg */
    if(ip_type == 1) {
		/* validate decimal expression */
		/* 012345678901234567890123456 */
		/* DSET,D12345=+N12345*D12345; */
        if(sg_pline[11] != '=') i_error = 1;
        if(sg_pline[12] != '+' && sg_pline[12] != '-') i_error = 1;

		i_byte = ip_beg;
    	for(; i_byte < ig_pline_lg; i_byte = i_byte + 7) {
			/* validate the operator */
			c_1 = sg_pline[i_byte - 1];
            if(c_1 != '+'
            && c_1 != '-'
            && c_1 != '*'
            && c_1 != '/'
            && c_1 != '\\'
			&& c_1 != '^'
            && c_1 != '%'
            && c_1 != '@'
            && c_1 != '?') i_error = 1;

			sub_program_validate_variable(i_byte, 1);
	    }
    }
	else if(ip_type == 11) {
		/* validate string expression */
		/* 012345678901234567890123456 */
		/* $SET,S12345=N12345*D12345; */

        /* if $SET then must have = in 11 */
        if(tfni_compare_strings(sg_pline, "$SET", 4) == 0
        && sg_pline[11] != '=') i_error = 1;

		i_byte = ip_beg;
    	for(; i_byte < ig_pline_lg;) {
			/* validate the operator */
			c_1 = sg_pline[i_byte - 1];
            if(c_1 != '+' && c_1 != ',' && c_1 != '=') i_error = 1;

			sub_program_validate_variable(i_byte, 11);
			i_byte = i_byte + 7;
	    }
        if(ig_pline_lg - ip_beg < 7) i_error = 1;
    }

    if(i_error == 1) {
		ig_exit = 1;
		tsub_out79(&sg_pline[ip_beg], 6);
		tsub_show_pline_by_index(ig_pline_ix);
        sub_program_error_end("bad variable/op", 15);
    }
} /* sub_program_validate_expression */


void sub_program_link_dift_dwhi(void) {
/* updated 2010/02/25, 2008/01/29, 2008/01/07, 2006/09/26 */
/* 2006/09/24, 2005/08/04, 2005/04/09, 2005/02/27, 2004/11/27 */
/* link following commands into iga_links */
/* DWHI,$WHI,ENDW,DIFT,$IFT,ELSE,ENDI,ESUB,SUBR,ENDS,DIF1,$IF1 */
	int ia_stack[PSTACK], ia_lines[PSTACK], i_stack, i_command;
	int i_index, i_loop, i_line, i_error, iz;

    /* initialize */
	for(iz = 0; iz < PLINES; iz++) {
    	iga_links[iz] = 0;
        iga_link_commands[iz] = 0;
    }
	for(iz = 0; iz < PSTACK; iz++) {
		/* only 10 to pstack-10 of ia_stack and ia_lines are used */
		ia_stack[iz] = 0;
		ia_lines[iz] = 0;
	}

	i_index = 0;
	i_loop = 1;
	while(i_loop == 1) {
		/* get the commnads into iga_link_commands */
		ig_pline_lg = iga_plines_lg[i_index];
		tsub_copy(sg_pline, psga_plines[i_index], ig_pline_lg);

		i_command = 0;
		if(tfni_compare_strings(sg_pline, "DWHI", 4) == 0) i_command = 1;
		if(tfni_compare_strings(sg_pline, "$WHI", 4) == 0) i_command = 1;
		if(tfni_compare_strings(sg_pline, "DIFT", 4) == 0) i_command = 2;
		if(tfni_compare_strings(sg_pline, "$IFT", 4) == 0) i_command = 2;
		if(tfni_compare_strings(sg_pline, "ELSE", 4) == 0) i_command = 3;
		if(tfni_compare_strings(sg_pline, "ENDI", 4) == 0) i_command = 4;
		if(tfni_compare_strings(sg_pline, "ENDW", 4) == 0) i_command = 5;
		if(tfni_compare_strings(sg_pline, "ESUB", 4) == 0) i_command = 6;
		if(tfni_compare_strings(sg_pline, "SUBR", 4) == 0) i_command = 7;
		if(tfni_compare_strings(sg_pline, "ENDS", 4) == 0) i_command = 8;
		if(tfni_compare_strings(sg_pline, "DIF1", 4) == 0) i_command = 9;
		if(tfni_compare_strings(sg_pline, "$IF1", 4) == 0) i_command = 9;
		iga_link_commands[i_index] = i_command;

        /* put variable numbers in iga_links for all else */
        if(i_command == 0 && ig_pline_lg > 10) {
            /* 01234567890 */
            /* DINC E12345 */
            /* 533328 = 480000 + 48000 + 4800 + 480 + 48 */
            iga_links[i_index] = sg_pline[6] * 10000
            + sg_pline[7] * 1000
            + sg_pline[8] * 100 + sg_pline[9] * 10
            + sg_pline[10] - 533328;
        }

		i_index++;
		if(iga_plines_lg[i_index] == 0 || i_index >= PLINES) i_loop++;
	}

	i_error = 2;
	i_index = 0;
	i_stack = 10;
	i_loop = 1;

	while(i_loop == 1) {
		i_command = iga_link_commands[i_index];

		if(i_command > 0) {
			/* we have a command to link */

			/* dwhi=1, $whi=1, dift=1, $ift=1, esub=6 */
			if(i_command < 3) {
				/* dwhi=1, $whi=1, dift=2, $ift=2 */
				i_stack++;
				ia_stack[i_stack] = i_command;
				ia_lines[i_stack] = i_index;
if(ig_debug == 1) {
	printf("i_stack=%d, i_index=%d, i_command=%d\n",
	i_stack, i_index, i_command);
}
			}
			if(i_command == 3) {
				/* else=3, dift=2, $ift=2, endi=4 */
				if(ia_stack[i_stack] != 2) i_error = 1;

				/* link dift=2, $ift=2 to here */
				i_line = ia_lines[i_stack];
				iga_links[i_line] = i_index;
				/* save line for endi=4 */
                /* else in essence is now the dift,$ift */
				ia_lines[i_stack] = i_index;
			}
			if(i_command == 4) {
				/* endi=4, dift=2, $ift=2, else=3 */
				iz = ia_stack[i_stack];
				if(iz != 2 && iz != 3) i_error = 1;

				/* link dift=2, $ift=2, else=3 to here */
				i_line = ia_lines[i_stack];
				iga_links[i_line] = i_index;

                /* if another endi next line link to it */
                iz = iga_link_commands[i_index + 1];
                if(iz == 4) {
                    iga_links[i_line] = i_index + 1;

                    /* if still another endi next line link to it */
                    iz = iga_link_commands[i_index + 2];
                    if(iz == 4) iga_links[i_line] = i_index + 2;
                }

if(ig_debug == 1) {
	printf("i_stack=%d, i_index=%d, i_command=%d, i_line=%d\n",
	i_stack, i_index, i_command, i_line);
}

				i_stack--;
			}
			if(i_command == 5) {
				/* endw=5, dwhi=1, $whi=1 */
				if(ia_stack[i_stack] != 1) i_error = 1;

				/* link here to dwhi=1, $whi=1 */
				i_line = ia_lines[i_stack];
				iga_links[i_index] = i_line - 1;
				/* link dwhi=1, $whi=1 to here */
				iga_links[i_line] = i_index;

				i_stack--;
			}
			/* if(i_command == 6) esub */
			if(i_command == 7) {
				/* subr=7, ends=8 */
				if(i_stack != 10) i_error = 1;

				i_stack++;
				ia_stack[i_stack] = 7;
			}
			if(i_command == 8) {
				/* ends=8, subr=7 */
				if(i_stack != 11) i_error = 1;
				if(ia_stack[i_stack] != 7) i_error = 1;

				i_stack--;
			}
			if(i_command == 9) {
				/* DIF1,$IF1 */
				iga_links[i_index] = i_index + 1;
			}
		}

		if(i_stack < 10 || i_stack > (PSTACK - 10)) i_error = 1;
		if(i_error == 1) {
			i_loop++;
			ig_exit = 1;
			tsub_show_pline_by_index(i_index);
			tsub_out79("bad link dift", 13);
			tsub_inp79();
		}

		i_index++;
		if(iga_plines_lg[i_index] == 0 || i_index >= PLINES) i_loop++;
	}
	if(ig_debug == 1) {
		for(i_index = 0; i_index < PLINES; i_index++) {
			if(iga_links[i_index] > 0)
				printf("link debug: i_index=%d, i_link=%d\n",
				i_index, iga_links[i_index]);
		}
	}
} /* sub_program_link_dift_dwhi */


void sub_program_link_esub(void) {
/* updated 2007/10/13, 2007/04/11, 2007/04/10, 2006/09/24, 2005/10/21 */
/* 2005/04/09, 2005/04/01, 2005/03/09, 2005/02/08, 2004/11/27 */
/* ESUB,SUBR,ENDS */
/* 012345678 */
/* esub sub_do_something */
/* subr sub_do_something */
/* goto tag_top1 */
/* gtag tag_top1 */
	long na_esubs[PLINES], na_subrs[PLINES];
	int ia_evars[PLINES];
	long na_gotos[PLINES], na_gtags[PLINES];
	int i_good, i_command;
	int i_index, i_loop1, i_loop2, i_subr_ix, iz;
	long n_hash, n_esub, n_subr, n_goto, n_gtag, nz;

 	/* iga_links was initialized in sub_program_link_dift_dwhi */
	for(iz = 0; iz < PLINES; iz++) {
		na_esubs[iz] = -1;
		na_subrs[iz] = -1;
		ia_evars[iz] = -1;
		na_gotos[iz] = -1;
        na_gtags[iz] = -1;
	}

    /* first get the subroutine names */
    /* index of last subr */
 	i_subr_ix = 0;
	i_index = 0;
	i_loop1 = 1;
	while(i_loop1 == 1) {
		/* put the program line in sg_pline,ig_pline_lg */
		ig_pline_lg = iga_plines_lg[i_index];
		tsub_copy(sg_pline, psga_plines[i_index], ig_pline_lg);

		/* hash the name into a long number */
		n_hash = tfnn_hash(&sg_pline[5], ig_pline_lg - 5);

        /* do we have a subroutine command esub,subr,ends */
		i_command = 0;
		if(tfni_compare_strings(sg_pline, "ESUB", 4) == 0) i_command = 1;
		if(tfni_compare_strings(sg_pline, "SUBR", 4) == 0) i_command = 2;
		if(tfni_compare_strings(sg_pline, "ENDS", 4) == 0) i_command = 3;
		if(tfni_compare_strings(sg_pline, "EVAR", 4) == 0) i_command = 4;
		if(tfni_compare_strings(sg_pline, "GOTO", 4) == 0) i_command = 5;
		if(tfni_compare_strings(sg_pline, "GTAG", 4) == 0) i_command = 6;

		if(i_command == 1) {
			/* esub */
			na_esubs[i_index] = n_hash;
		}
		if(i_command == 2) {
			/* subr */
			/* do we already have this subr */
            for(nz = 0; nz < i_index; nz++) {
				if(na_subrs[nz] == n_hash) {
					ig_pline_ix = i_index;
					sub_program_error_end("duplicate subr", 14);
                    i_loop1++;
                }
            }

			na_subrs[i_index] = n_hash;

			/* save position of subr for evar and gtag */
			i_subr_ix = i_index;

            /* put in 1 for subr in na_gtags */
            na_gtags[i_index] = 1;
		}
		if(i_command == 4) {
			/* evar */
			/* save position of evar */
			ia_evars[i_subr_ix] = i_index;
        }
		if(i_command == 5) {
			/* goto */
			if(tfni_compare_strings(&sg_pline[5], "TAG_", 4) != 0) {
				sub_program_error_end("GOTO not TAG_", 13);
                i_loop1++;
            }

			na_gotos[i_index] = n_hash;
		}
		if(i_command == 6) {
			/* gtag */
			if(tfni_compare_strings(&sg_pline[5], "TAG_", 4) != 0) {
				sub_program_error_end("GTAG not TAG_", 13);
                i_loop1++;
            }

			/* do we already have this gtag */
            for(nz = i_subr_ix; nz < i_index; nz++) {
				if(na_gtags[nz] == n_hash) {
					ig_pline_ix = i_index;
					sub_program_error_end("duplicate gtag", 14);
                    i_loop1++;
                }
            }
			na_gtags[i_index] = n_hash;
		}

		i_index++;
		if(i_index >= PLINES || iga_plines_lg[i_index] == 0) i_loop1++;
	}

    /* now link */
	i_subr_ix = 0;
	i_index = 0;
	i_loop1 = 1;

	while(i_loop1 == 1) {
		n_esub = na_esubs[i_index];
		if(n_esub >= 0) {
			/* we have an esub at line i_index */
			/* find matching subrs */
			for(i_good = 2, iz = 0; iz < PLINES; iz++) {
				n_subr = na_subrs[iz];
				if(n_esub == n_subr) {
					i_good = 1;
					iga_links[i_index] = ia_evars[iz] - 1;
				}
			}
			if(i_good != 1) {
				/* error here */
				i_loop1++;
				ig_exit = 1;
				tsub_show_pline_by_index(i_index);
				tsub_out79("bad link esub", 13);
				tsub_inp79();
			}
		}

        /* save i_index for latest subr */
        if(na_subrs[i_index] > 0) i_subr_ix = i_index;

        n_goto = na_gotos[i_index];
        if(n_goto > 0) {
			/* we have a goto at line i_index */
			/* find matching gtag */
			i_good = 2;
            iz = i_subr_ix;
            i_loop2 = 1;
			while(i_loop2 == 1) {
				n_gtag = na_gtags[iz];
				if(n_goto == n_gtag) {
					i_good = 1;
					iga_links[i_index] = iz;
				}

				/* stop at next subr */
				iz++;
				if(na_gtags[iz] == 1
                || iz > PLINES
                || iga_plines_lg[iz] == 0) i_loop2++;
			}
			if(i_good != 1) {
				/* error here */
				i_loop1++;
				ig_exit = 1;
				tsub_show_pline_by_index(i_index);
				tsub_out79("bad link esub", 13);
				tsub_inp79();
			}
        }

		i_index++;
		if(i_index >= PLINES || iga_plines_lg[i_index] == 0) i_loop1++;
	}

	if(ig_debug == 1) {
		for(i_index = 0; i_index < PLINES; i_index++) {
			if(iga_links[i_index] > 0)
				printf("link debug: i_index=%d, i_link=%d\n",
				i_index, iga_links[i_index]);
		}
	}
} /* sub_program_link_esub */


void sub_program_error_end(char *sp_1, int ip_long) {
/* updated 2009/07/10, 2007/10/16 */
/* 2007/10/11, 2007/01/14, 2007/01/08, 2005/04/03, 2005/02/17 */
    int iz;

    for(iz = 20; iz >= 0; iz--) {
    	tsub_show_pline_by_index(ig_pline_ix - iz);
    }
    tsub_out79(sp_1, ip_long);

    tsub_debug();

    /* get timeline into sg_pass,ng_pass_lg */
    tsub_timeline();
    tsub_out79(sg_pass, ng_pass_lg);

    ig_exit = 1;
    puts("program will end");
    tsub_inp79();

/*    exit(1); */
} /* sub_program_error_end */
/* program subroutines above */


/* command subroutines below */
void sub_command_dabs(int ip1) {
/* updated 2007/03/17, 2006/04/23, 2005/07/31, 2005/03/31 */
/* 012345678901234567 */
/* dabs D12345,D12345 */
/* 1=dabs, 2=drou, 3=dtru, 4=dlog, 5=dsin, 6=darc */
	int i_negative = 2;
	double d_number1, d_number2;
	double dz;

	sub_fetch_decimal_variable_1dbl(&psg_pline[12]);
	d_number1 = dg_1pass;

    /* d_number2 is always positive */
    if(d_number1 < 0) {
    	i_negative = 1;
		d_number2 = - d_number1;
    }
	else d_number2 = d_number1;

    if(ip1 == 1) dg_1pass = d_number2;  /* DABS */
    else if(ip1 == 2) {               /* DROU */
		/* 0.5 is too much with numbers close to 2^53 */
    	dg_1pass = floor(d_number2 + 0.499);
		if(i_negative == 1) dg_1pass = -dg_1pass;
    }
    else if(ip1 == 3) {               /* DTRU */
    	dg_1pass = floor(d_number2);
		if(i_negative == 1) dg_1pass = -dg_1pass;
    }
    else if(ip1 == 4) {               /* DLOG */
		if(d_number2 == 0) d_number2 = 1;
    	dg_1pass = log10(d_number2);
    }
    else if(ip1 == 5) {               /* DSIN */
		/* M_PI = 3.14159... */
		dz = 2 * 3.1415926535897932385;
        if(d_number1 > dz) d_number1 = dz;
        else if(d_number1 < -dz) d_number1 = -dz;

    	dg_1pass = sin(d_number1);
    }
    else if(ip1 == 6) {               /* DARC */
		if(d_number1 > 1) d_number1 = 1;
        else if(d_number1 < -1) d_number1 = -1;
    	dg_1pass = asin(d_number1);
    }

	sub_store_decimal_variable_in_link();
} /* sub_command_dabs */


void sub_command_dbad(void) {
/* updated 2009/07/05, 2005/02/27 */
	tsub_show_pline(ig_pline_ix, psg_pline, ig_pline_lg);

    /* get timeline into sg_pass,ng_pass_lg */
    tsub_timeline();
    tsub_out79(sg_pass, ng_pass_lg);
    tsub_out79("dbad bad", 8);
    tsub_inp79();
    ig_exit = 1;
} /* sub_command_dbad */


void sub_command_dfac(void) {
/* updated 2006/11/14, 2006/10/27, 2005/05/02, 2005/03/12, 2005/02/17 */
/* 012345678901234567 */
/* dfac d00001,d00002 */
	double d_number;
    double d_factor = 1.0;
    double d_root = 1.0;
    double d_divisor = 3.0;
	int i_loop = 1;

	/* get the number */
	sub_fetch_decimal_variable_1dbl(&psg_pline[12]);
	d_number = floor(fabs(dg_1pass));

    if(d_number < 4.0) i_loop++;
    else {
		d_root = sqrt(d_number);

		/* is 2 a factor */
        if(fmod(d_number, 2) == 0.0) {
			i_loop++;
			d_factor = 2.0;
        }
    }

    while(i_loop == 1) {
		/* do we have a prime */
		/* try d_divisor */
        if(fmod(d_number, d_divisor) == 0.0) {
			/* we do not have a prime */
            i_loop++;
            d_factor = d_divisor;
        }
		else {
        	d_divisor = d_divisor + 2.0;
            if(d_divisor > d_root) i_loop++;
		}
    }

	dg_1pass = d_factor;
	sub_store_decimal_variable_in_link();
} /* sub_command_dfac */


void sub_command_dfak(void) {
/* updated 2008/12/06, 2007/10/07 */
/* 2007/09/22, 2007/09/21, 2007/09/20, 2007/03/28, 2007/03/02 */
/* 2007/02/27, 2007/02/24, 2006/12/01, 2006/11/14, 2006/11/11 */
/* 2006/10/27, 2006/10/26, 2005/05/02, 2005/03/12, 2005/02/17 */
/* find factor of parm2 + parm3 * 1quadrillion */
/* 0123456789012345678901234 */
/* dfak d00001,d00002,d00003 */
	double d_teaquadpart;
	double d_teaquadmult;
	/*                  1234567890123456 */
    double d_teaquadone = 1000000000000000.0;
	double d_modulus;
    double d_factor = 1.0;
    double d_root = 0.0;
    double d_divisor07 = 7.0;
    double d_divisor11 = 11.0;
    double d_divisor13 = 13.0;
    double d_divisor17 = 17.0;
    double d_divisor19 = 19.0;
    double d_divisor23 = 23.0;
    double d_divisor29 = 29.0;
    double d_divisor31 = 31.0;
	int i_loop = 1;

	/* get the number1 */
	sub_fetch_decimal_variable_1dbl(&psg_pline[12]);
	d_teaquadpart = floor(fabs(dg_1pass));

	sub_fetch_decimal_variable_1dbl(&psg_pline[19]);
	d_teaquadmult = floor(fabs(dg_1pass));

    /* trivial primes */
    if(d_teaquadmult == 0.0) {
        if(d_teaquadpart < 4
        || d_teaquadpart == 5
        || d_teaquadpart == 7
        || d_teaquadpart == 11
        || d_teaquadpart == 13
        || d_teaquadpart == 17
        || d_teaquadpart == 19
        || d_teaquadpart == 23
        || d_teaquadpart == 29
        || d_teaquadpart == 31) {
            i_loop++;
        }
    }

    /* d_teaquadmult is factored by 2,5
	/* is 2 a factor */
    if(i_loop == 1 && fmod(d_teaquadpart, 2.0) == 0.0) {
		i_loop++;
		d_factor = 2.0;
    }

    /* is 3 a factor */
    /* since fmod(d_teaquadone, 3) is 1 */
    if(i_loop == 1 && fmod(d_teaquadpart + d_teaquadmult, 3.0) == 0) {
		i_loop++;
        d_factor = 3.0;
    }

    /* d_teaquadmult is factored by 2,5
	/* is 5 a factor */
    if(i_loop == 1 && fmod(d_teaquadpart, 5.0) == 0.0) {
		i_loop++;
		d_factor = 5.0;
    }

    if(i_loop == 1)
        d_root = sqrt(d_teaquadpart + d_teaquadmult * d_teaquadone);

    while(i_loop == 1) {
		/* do we have a prime */
        /* d_modulus = fmod(fmod(d_teaquadpart, d_divisor)
        + d_teaquadmult * fmod(d_teaquadone, d_divisor), d_divisor); */

        /* d_divisor07 */
        d_modulus = fmod(d_teaquadpart
        + d_teaquadmult * fmod(d_teaquadone, d_divisor07), d_divisor07);

		if(d_modulus == 0.0) {
			/* we do not have a prime */
            i_loop++;
            d_factor = d_divisor07;
        }
		else {
	       	d_divisor07 = d_divisor07 + 30.0;

            /* d_divisor11 */
            d_modulus = fmod(d_teaquadpart
            + d_teaquadmult * fmod(d_teaquadone, d_divisor11), d_divisor11);

		    if(d_modulus == 0.0) {
			    /* we do not have a prime */
                i_loop++;
                d_factor = d_divisor11;
            }
    		else {
	           	d_divisor11 = d_divisor11 + 30.0;

                /* d_divisor13 */
                d_modulus = fmod(d_teaquadpart
                + d_teaquadmult
                * fmod(d_teaquadone, d_divisor13), d_divisor13);

    		    if(d_modulus == 0.0) {
	    		    /* we do not have a prime */
                    i_loop++;
                    d_factor = d_divisor13;
                }
        		else {
	               	d_divisor13 = d_divisor13 + 30.0;

                    /* d_divisor17 */
                    d_modulus = fmod(d_teaquadpart
                    + d_teaquadmult
                    * fmod(d_teaquadone, d_divisor17), d_divisor17);

    		        if(d_modulus == 0.0) {
	    		        /* we do not have a prime */
                        i_loop++;
                        d_factor = d_divisor17;
                    }
        	    	else {
    	               	d_divisor17 = d_divisor17 + 30.0;

                        /* d_divisor19 */
                        d_modulus = fmod(d_teaquadpart
                        + d_teaquadmult
                        * fmod(d_teaquadone, d_divisor19), d_divisor19);

    		            if(d_modulus == 0.0) {
    	    		        /* we do not have a prime */
                            i_loop++;
                            d_factor = d_divisor19;
                        }
        	        	else {
        	               	d_divisor19 = d_divisor19 + 30.0;

                            /* d_divisor23 */
                            d_modulus = fmod(d_teaquadpart
                            + d_teaquadmult
                            * fmod(d_teaquadone, d_divisor23), d_divisor23);

    		                if(d_modulus == 0.0) {
    	    		            /* we do not have a prime */
                                i_loop++;
                                d_factor = d_divisor23;
                            }
            	        	else {
            	               	d_divisor23 = d_divisor23 + 30.0;

                                /* d_divisor29 */
                                d_modulus = fmod(d_teaquadpart
                                + d_teaquadmult
                                * fmod(d_teaquadone, d_divisor29),
                                d_divisor29);

    		                    if(d_modulus == 0.0) {
    	    		                /* we do not have a prime */
                                    i_loop++;
                                    d_factor = d_divisor29;
                                }
                	        	else {
                	               	d_divisor29 = d_divisor29 + 30.0;

                                    /* d_divisor31 */
                                    d_modulus = fmod(d_teaquadpart
                                    + d_teaquadmult
                                    * fmod(d_teaquadone, d_divisor31),
                                    d_divisor31);

    		                        if(d_modulus == 0.0) {
    	    		                    /* we do not have a prime */
                                        i_loop++;
                                        d_factor = d_divisor31;
                                    }
                    	        	else {
                                        d_divisor31 = d_divisor31 + 30.0;
                                        if(d_divisor07 > d_root) i_loop++;
                                    }
                                }
                            }
                        }
                    }
                }
    		}
        }

    }

	dg_1pass = d_factor;
	sub_store_decimal_variable_in_link();
} /* sub_command_dfak */


void sub_command_dduo(void) {
/* updated 2009/09/06, 2008/12/06, 2007/10/07 */
/* 2007/09/22, 2007/09/21, 2007/09/20, 2007/03/28, 2007/03/02 */
/* 2007/02/27, 2007/02/24, 2006/12/01, 2006/11/14, 2006/11/11 */
/* 2006/10/27, 2006/10/26, 2005/05/02, 2005/03/12, 2005/02/17 */
/* find factor of parm2 + parm3 * 1quadrillion */
/* and of parm2 + 2 + parm3 * 1quadrillion */
/* 0123456789012345678901234 */
/* dduo d00001,d00002,d00003 */
	double d_teaquadpart;
	double d_teaquadmult;
	/*                  1234567890123456 */
    double d_teaquadone = 1000000000000000.0;
	double d_modulus;
    double d_factor = 1.0;
    double d_root = 0.0;
    double d_divisor07 = 7.0;
    double d_divisor11 = 11.0;
    double d_divisor13 = 13.0;
    double d_divisor17 = 17.0;
    double d_divisor19 = 19.0;
    double d_divisor23 = 23.0;
    double d_divisor29 = 29.0;
    double d_divisor31 = 31.0;
	int i_loop = 1;

	/* get the number1 + 2 */
	sub_fetch_decimal_variable_1dbl(&psg_pline[12]);
	d_teaquadpart = floor(fabs(dg_1pass)) + 2;

	sub_fetch_decimal_variable_1dbl(&psg_pline[19]);
	d_teaquadmult = floor(fabs(dg_1pass));

    /* trivial duo second primes */
    if(d_teaquadmult == 0.0) {
        if(d_teaquadpart < 4
        || d_teaquadpart == 5
        || d_teaquadpart == 7
        || d_teaquadpart == 13
        || d_teaquadpart == 19
        || d_teaquadpart == 31) {
            i_loop++;
        }
    }

    /* d_teaquadmult is factored by 2,5 */
	/* is 2 a factor of d_teaquadpart */
    if(i_loop == 1 && fmod(d_teaquadpart, 2.0) == 0.0) {
		i_loop++;
		d_factor = 2.0;
    }

    /* is 3.0 a factor */
    /* since fmod(d_teaquadone, 3) is 1 */
    if(i_loop == 1) {
        d_modulus = fmod(d_teaquadpart + d_teaquadmult, 3.0);
        if(d_modulus == 0.0 || d_modulus == 2.0) {
    		i_loop++;
            d_factor = 3.0;
        }
    }

    /* d_teaquadmult is factored by 2,5 */
	/* is 5 a factor of d_teaquadpart */
    if(i_loop == 1) {
        d_modulus = fmod(d_teaquadpart, 5.0);
        if(d_modulus == 0.0 || d_modulus == 2.0) {
    		i_loop++;
	    	d_factor = 5.0;
        }
    }

    if(i_loop == 1)
        d_root = sqrt(d_teaquadpart + d_teaquadmult * d_teaquadone);

    while(i_loop == 1) {
		/* do we have a prime */
        /* d_modulus = fmod(fmod(d_teaquadpart, d_divisor)
        + d_teaquadmult * fmod(d_teaquadone, d_divisor), d_divisor); */

        /* d_divisor07 */
        d_modulus = fmod(d_teaquadpart
        + d_teaquadmult * fmod(d_teaquadone, d_divisor07), d_divisor07);

		if(d_modulus == 0.0 || d_modulus == 2.0) {
			/* we do not have a prime */
            i_loop++;
            d_factor = d_divisor07;
        }
		else {
            /* d_divisor11 */
            d_modulus = fmod(d_teaquadpart
            + d_teaquadmult * fmod(d_teaquadone, d_divisor11), d_divisor11);

		    if(d_modulus == 0.0 || d_modulus == 2.0) {
			    /* we do not have a prime */
                i_loop++;
                d_factor = d_divisor11;
            }
    		else {
                /* d_divisor13 */
                d_modulus = fmod(d_teaquadpart
                + d_teaquadmult
                * fmod(d_teaquadone, d_divisor13), d_divisor13);

    		    if(d_modulus == 0.0 || d_modulus == 2.0) {
	    		    /* we do not have a prime */
                    i_loop++;
                    d_factor = d_divisor13;
                }
        		else {
                    /* d_divisor17 */
                    d_modulus = fmod(d_teaquadpart
                    + d_teaquadmult
                    * fmod(d_teaquadone, d_divisor17), d_divisor17);

    		        if(d_modulus == 0.0 || d_modulus == 2.0) {
	    		        /* we do not have a prime */
                        i_loop++;
                        d_factor = d_divisor17;
                    }
        	    	else {
                        /* d_divisor19 */
                        d_modulus = fmod(d_teaquadpart
                        + d_teaquadmult
                        * fmod(d_teaquadone, d_divisor19), d_divisor19);

    		            if(d_modulus == 0.0 || d_modulus == 2.0) {
    	    		        /* we do not have a prime */
                            i_loop++;
                            d_factor = d_divisor19;
                        }
        	        	else {
                            /* d_divisor23 */
                            d_modulus = fmod(d_teaquadpart
                            + d_teaquadmult
                            * fmod(d_teaquadone, d_divisor23), d_divisor23);

    		                if(d_modulus == 0.0 || d_modulus == 2.0) {
    	    		            /* we do not have a prime */
                                i_loop++;
                                d_factor = d_divisor23;
                            }
            	        	else {
                                /* d_divisor29 */
                                d_modulus = fmod(d_teaquadpart
                                + d_teaquadmult
                                * fmod(d_teaquadone, d_divisor29),
                                d_divisor29);

    		                    if(d_modulus == 0.0 || d_modulus == 2.0) {
    	    		                /* we do not have a prime */
                                    i_loop++;
                                    d_factor = d_divisor29;
                                }
                	        	else {
                                    /* d_divisor31 */
                                    d_modulus = fmod(d_teaquadpart
                                    + d_teaquadmult
                                    * fmod(d_teaquadone, d_divisor31),
                                    d_divisor31);

    		                        if(d_modulus == 0.0
                                    || d_modulus == 2.0) {
    	    		                    /* we do not have a prime */
                                        i_loop++;
                                        d_factor = d_divisor31;
                                    }
                    	        	else {
                                        d_divisor07 = d_divisor07 + 30.0;

                                        if(d_divisor07 > d_root) i_loop++;
                                        else {
                                            d_divisor11 = d_divisor11 + 30.0;
                                            d_divisor13 = d_divisor13 + 30.0;
                                            d_divisor17 = d_divisor17 + 30.0;
                                            d_divisor19 = d_divisor19 + 30.0;
                                            d_divisor23 = d_divisor23 + 30.0;
                                            d_divisor29 = d_divisor29 + 30.0;
                                            d_divisor31 = d_divisor31 + 30.0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
    		}
        }
    }

	dg_1pass = d_factor;
	sub_store_decimal_variable_in_link();
} /* sub_command_dduo */


void sub_command_dfaq1(void) {
/* updated 2007/09/22, 2007/09/21, 2007/09/20, 2007/03/28, 2007/03/02 */
/* 2007/02/27, 2007/02/24, 2006/12/01, 2006/11/14, 2006/11/11 */
/* 2006/10/27, 2006/10/26, 2005/05/02, 2005/03/12, 2005/02/17 */
/* find factor of parm2 + parm3 * 1quadrillion */
/* 0123456789012345678901234 */
/* dfak d00001,d00002,d00003 */
	double d_teaquadpart;
	double d_teaquadmult;
	/*                  1234567890123456 */
    double d_teaquadone = 1000000000000000.0;
	double d_modulus;
    double d_factor = 1.0;
    double d_root = 0.0;
    double d_divisor1 = 5.0;
    double d_divisor2 = 7.0;
	int i_loop = 1;

	/* get the number1 */
	sub_fetch_decimal_variable_1dbl(&psg_pline[12]);
	d_teaquadpart = floor(fabs(dg_1pass));

	sub_fetch_decimal_variable_1dbl(&psg_pline[19]);
	d_teaquadmult = floor(fabs(dg_1pass));

    /* trivial primes */
    if(d_teaquadmult == 0.0) {
        if(d_teaquadpart < 4
        || d_teaquadpart == 5
        || d_teaquadpart == 7) {
            i_loop++;
        }
    }

    /* d_teaquadmult is factored by 2,5
	/* is 2 a factor */
    if(i_loop == 1 && fmod(d_teaquadpart, 2.0) == 0.0) {
		i_loop++;
		d_factor = 2.0;
    }

    if(i_loop == 1 && fmod(d_teaquadpart + d_teaquadmult, 3.0) == 0) {
		i_loop++;
        d_factor = 3.0;
    }

    /* d_teaquadmult is factored by 2,5
	/* is 5 a factor */
    if(i_loop == 1 && fmod(d_teaquadpart, 5.0) == 0.0) {
		i_loop++;
		d_factor = 5.0;
    }

    if(i_loop == 1)
        d_root = sqrt(d_teaquadpart + d_teaquadmult * d_teaquadone);

    while(i_loop == 1) {
		/* do we have a prime */
        /* d_modulus = fmod(fmod(d_teaquadpart, d_divisor)
        + d_teaquadmult * fmod(d_teaquadone, d_divisor), d_divisor); */

        d_modulus = fmod(d_teaquadpart
        + d_teaquadmult * fmod(d_teaquadone, d_divisor1), d_divisor1);

		if(d_modulus == 0.0) {
			/* we do not have a prime */
            i_loop++;
            d_factor = d_divisor1;
        }
		else {
	       	d_divisor1 = d_divisor1 + 6.0;

            d_modulus = fmod(d_teaquadpart
            + d_teaquadmult * fmod(d_teaquadone, d_divisor2), d_divisor2);

		    if(d_modulus == 0.0) {
			    /* we do not have a prime */
                i_loop++;
                d_factor = d_divisor2;
            }
    		else {
	           	d_divisor2 = d_divisor2 + 6.0;

                if(d_divisor1 > d_root) i_loop++;
    		}
        }

    }

	dg_1pass = d_factor;
	sub_store_decimal_variable_in_link();
} /* sub_command_dfaq1 */


void sub_command_dfaq2(void) {
/* updated 2007/03/28, 2007/03/02 */
/* 2007/02/27, 2007/02/24, 2006/12/01, 2006/11/14, 2006/11/11 */
/* 2006/10/27, 2006/10/26, 2005/05/02, 2005/03/12, 2005/02/17 */
/* find factor of parm2 + parm3 * 1quadrillion */
/* 0123456789012345678901234 */
/* dfak d00001,d00002,d00003 */
	double d_teaquadpart;
	double d_teaquadmult;
	/*                  1234567890123456 */
    double d_teaquadone = 1000000000000000.0;
	double d_modulus;
    double d_factor = 1.0;
    double d_root = 0.0;
    double d_divisor = 3.0;
	int i_loop = 1;

	/* get the number1 */
	sub_fetch_decimal_variable_1dbl(&psg_pline[12]);
	d_teaquadpart = floor(fabs(dg_1pass));

	sub_fetch_decimal_variable_1dbl(&psg_pline[19]);
	d_teaquadmult = floor(fabs(dg_1pass));

    /* d_teaquadmult is factored by 2,5
	/* is 2 a factor */
    if(fmod(d_teaquadpart, 2.0) == 0.0) {
		i_loop++;
		d_factor = 2.0;
    }

    if(i_loop == 1)
        d_root = sqrt(d_teaquadpart + d_teaquadmult * d_teaquadone);

    while(i_loop == 1) {
		/* do we have a prime */
        /* d_modulus = fmod(fmod(d_teaquadpart, d_divisor)
        + d_teaquadmult * fmod(d_teaquadone, d_divisor), d_divisor); */

        d_modulus = fmod(d_teaquadpart
        + d_teaquadmult * fmod(d_teaquadone, d_divisor), d_divisor);

		if(d_modulus == 0.0) {
			/* we do not have a prime */
            i_loop++;
            d_factor = d_divisor;
        }
		else {
	       	d_divisor = d_divisor + 2.0;
    	    if(d_divisor > d_root) i_loop++;
		}
    }

	dg_1pass = d_factor;
	sub_store_decimal_variable_in_link();
} /* sub_command_dfaq2 */


void sub_command_dift_dwhi(void) {
/* updated 2008/02/10 */
/* 2008/02/02, 2008/01/26, 2005/03/12, 2005/02/27, 2004/11/28 */
/* 0123456789012345678 */
/* dift D00001==D00002 */
/* ==,>>,<<,>=,<=,<> */
    /* fetch decimal into dg_1pass */
	sub_fetch_decimal_variable_1dbl(&psg_pline[5]);

    /* fetch decimal into dg_2pass */
	sub_fetch_decimal_variable_2dbl(&psg_pline[13]);

	/* ==,<<,<=,<>,>>,>= */
	if(dg_1pass < dg_2pass) {
        /* <<,<=,<> */
    	if(psg_pline[11] == '<') ig_true = 1;
        else ig_true = 2;
    }
    else if(dg_1pass == dg_2pass) {
        /* ==,<=,>= */
    	if(psg_pline[12] == '=') ig_true = 1;
        else ig_true = 2;
    }
	else {
        /* <>,>>,>= */
    	if(psg_pline[11] == '>' || psg_pline[12] == '>') ig_true = 1;
        else ig_true = 2;
    }
	/* ig_true=1 means true */

} /* sub_command_dift_dwhi */


void sub_command_dinc(int ip1) {
/* updated 2010/03/08, 2009/03/08, 2008/02/10, 2008/01/23, 2008/01/07 */
/* 2007/04/09, 2007/03/19, 2007/03/17, 2005/02/20, 2004/11/29 */
/* 1=DINC, 2=DDEC, 3=DSEC, 4=DRAN */
/* optimized 2008/01/23 */
    long n_index;

    if(psg_pline[5] == 'E') n_index = ig_link_ix + ig_dvstack_ct;
    else n_index = ig_link_ix;

    /* if(n_index >= 0 && n_index < VDECIMALS) { */
    if(ip1 == 2) {
	    /* DDEC */
        dga_decimals[n_index] = dga_decimals[n_index] - 1;
   	}
    else if(ip1 == 3) {
   		/* DSEC */
    	/* dg_1pass = clock() / CLK_TCK; */
	    /* dg_1pass = clock() / CLOCKS_PER_SEC; */
   		/* dg_1pass = time(NULL); */
    	/* CLOCKS_PER_SEC is always 1E6 if POSIX */
        /* dg_1pass = clock() / 1000000.0; */
        dga_decimals[n_index] = (double)clock() / CLOCKS_PER_SEC;
   	}
    else if(ip1 == 4) {
   		/* DRAN */
    	dga_decimals[n_index] = (double)rand() / RAND_MAX;
    }
   	else if(ip1 == 1) {
    	/* DINC */
        dga_decimals[n_index]++;
        /* dga_decimals[n_index] = dga_decimals[n_index] + 1; */
   	}
} /* sub_command_dinc */


void sub_command_dpow(void) {
/* updated 2007/07/23, 2007/07/08, 2003/03/12, 2005/02/13 */
/* 0123456789012345678901234 */
/* dpow d00001,d00002,d00003 */
	double d_number, d_power;

	/* get the number */
	sub_fetch_decimal_variable_1dbl(&psg_pline[12]);
	d_number = dg_1pass;

	/* get the power */
	sub_fetch_decimal_variable_1dbl(&psg_pline[19]);
	d_power = dg_1pass;

    /* cannot have negative number and non-integer power */
    if(d_number < 0 && d_power != floor(d_power)) {
		d_number = fabs(d_number);
    }

    if(d_number == 0 || d_power == 0) {
		d_number = 1;
        d_power = 1;
    }

    dg_1pass = pow(d_number, d_power);

	sub_store_decimal_variable_in_link();
} /* sub_command_dpow */


void sub_command_dset(void) {
/* updated 2009/03/08, 2008/02/10 */
/* 2008/02/02, 2008/01/30, 2007/07/23, 2007/07/08, 2007/05/06 */
/* 2007/05/04, 2007/04/11, 2006/11/10, 2005/08/20, 2005/07/31 */
/* 2005/06/11, 2005/03/12, 2005/02/19, 2005/02/11, 2004/11/27 */
/* 012345678901234567890123456789012 */
/* dset D00012=+N00543*D00001/N00003; */
	double d_posresult, d_posterm;
	int i_loop, i_byte, i_last, n_index;
	char c_operator;

    /* pline is in psg_pline,ig_pline_lg */
	i_last = ig_pline_lg - 4;

    /* get decimal into dg_1pass */
	sub_fetch_decimal_variable_1dbl(&psg_pline[13]);

    /* dg_1pass is the result decimal */
	if(psg_pline[12] == '-') dg_1pass = -dg_1pass;

    i_byte = 19;
	i_loop = 1;
    if(i_byte > i_last) i_loop++;

	while(i_loop == 1) {
		c_operator = psg_pline[i_byte];

        /* fetch decimal into dg_2pass */
		sub_fetch_decimal_variable_2dbl(&psg_pline[i_byte + 1]);

		if(c_operator == '+') dg_1pass = dg_1pass + dg_2pass;
		else if(c_operator == '-') dg_1pass = dg_1pass - dg_2pass;
		else if(c_operator == '*') dg_1pass = dg_1pass * dg_2pass;
		else if(c_operator == '/') {
			if(dg_2pass == 0) {
				i_loop++;
				sub_program_error_end("zero div", 8);
            }
            else dg_1pass = dg_1pass / dg_2pass;
		}
		else if(c_operator == '\\') {
			/* \ is the integer divide operator */
			d_posresult = floor(fabs(dg_1pass) + 0.499);
			d_posterm = floor(fabs(dg_2pass) + 0.499);

			if(d_posterm == 0) {
				i_loop++;
				sub_program_error_end("zero int div", 12);
            }
			else {
				d_posresult = floor(d_posresult / d_posterm);

                if(dg_1pass < 0) d_posresult = - d_posresult;
                if(dg_2pass < 0) d_posresult = - d_posresult;

				dg_1pass = d_posresult;
            }

		}
		else if(c_operator == '%') {
			/* % is the mod operator */
			/* 0.5 is too much with numbers close to 2^53 */
			d_posresult = floor(fabs(dg_1pass) + 0.499);
			d_posterm = floor(fabs(dg_2pass) + 0.499);

			if(dg_2pass == 0) {
				i_loop++;
				sub_program_error_end("zero mod", 8);
            }
			else {
            	d_posresult = fmod(d_posresult, d_posterm);

                if(dg_1pass < 0) d_posresult = - d_posresult;

				dg_1pass = d_posresult;
            }
		}
		else if(c_operator == '^') {
			/* ^ is the exponentiation operator */
			/* negatives cannot be raised to a non-integer power */
			if(dg_1pass < 0 && dg_2pass != floor(dg_2pass)) {
				dg_1pass = fabs(dg_1pass);
			}

			if(dg_1pass == 0 || dg_2pass == 0) {
				dg_1pass = 1;
                dg_2pass = 1;
            }

			dg_1pass = pow(dg_1pass, dg_2pass);
        }
		else if(c_operator == '@') {
			/* @ is the round operator */
            d_posresult = fabs(dg_1pass);

			dg_2pass = floor(fabs(dg_2pass) + 0.001);

			d_posresult = floor(d_posresult * pow(10, dg_2pass) + 0.499);
            d_posresult = d_posresult / pow(10, dg_2pass);

            if(dg_1pass < 0) dg_1pass = -d_posresult;
            else dg_1pass = d_posresult;
        }
		else if(c_operator == '?') {
			/* ? is the truncate operator */
            d_posresult = fabs(dg_1pass);

			dg_2pass = floor(fabs(dg_2pass) + 0.001);

			d_posresult = floor(d_posresult * pow(10, dg_2pass) + 0.001);
            d_posresult = d_posresult / pow(10, dg_2pass);

            if(dg_1pass < 0) dg_1pass = -d_posresult;
            else dg_1pass = d_posresult;
        }
		else {
            i_loop++;
        	sub_program_error_end("bad op", 6);
		}

		i_byte = i_byte + 7;
		if(i_byte >= i_last) i_loop++;
	}

	/* store dg_1pass */
/*	sub_store_decimal_variable_in_link(); */

    if(psg_pline[5] == 'E') n_index = ig_link_ix + ig_dvstack_ct;
    else n_index = ig_link_ix;

    /* if(n_index >= 0 && n_index < VDECIMALS) */
    dga_decimals[n_index] = dg_1pass;
} /* sub_command_dset */


void sub_command_dsys(void) {
/* updated 2005/10/07, 2005/04/12 */
/* 012345678901234567 */
/* DSYS D12345,D12345 */
	double d_total;
    int i_which, iz;

	sub_fetch_decimal_variable_int(&psg_pline[12]);
    i_which = ig_pass_int;

    d_total = 0;

    if(i_which == 1) {
		/* total up string lengths */
		for(iz = 0; iz < PLINES; iz++)
        	d_total = d_total + iga_plines_lg[iz];

		for(iz = 0; iz < SARRAY; iz++)
        	d_total = d_total + iga_sarray_lg[iz];

		for(iz = 0; iz < VSTRINGS; iz++)
        	d_total = d_total + nga_strings_lg[iz];

        d_total = d_total + ng_pass_lg + ng_buff1_lg + ng_buff2_lg;
    }
	else if(i_which == 2) d_total = dg_plines_done;

    dg_1pass = d_total;
	sub_store_decimal_variable_in_link();
} /* sub_command_dsys */


void sub_command_dtoi(int ip1) {
/* updated 2008/02/10 */
/* 2008/02/02, 2008/01/23, 2006/04/29, 2005/03/12, 2005/02/24 */
/* 012345678901234567 */
/* DTOI D00001,D00002 */
/* 1=DTOI, 3=ADDI */
/* optimized 2008/01/23 */
    long n_index;
    double d_number;

	if(ip1 == 1) {
		/* DTOI */
    	sub_fetch_decimal_variable_int(&psg_pline[5]);
        n_index = ig_pass_int;

        /* fetch the decimal into dg_1pass */
    	sub_fetch_decimal_variable_1dbl(&psg_pline[12]);

		if(n_index >= 1 && n_index <= DARRAY)
        	dga_darray[n_index - 1] = dg_1pass;
		else sub_program_error_end("dtoi bad index", 14);
	}
	else if(ip1 == 3) {
		/* ADDI */
    	sub_fetch_decimal_variable_int(&psg_pline[5]);
        n_index = ig_pass_int;

    	sub_fetch_decimal_variable_1dbl(&psg_pline[12]);
	    d_number = dg_1pass;

		if(n_index >= 1 && n_index <= DARRAY)
        	dga_darray[n_index - 1] = dga_darray[n_index - 1] + d_number;
		else sub_program_error_end("dtoi bad index", 14);
	}
} /* sub_command_dtoi */


void sub_command_itod(void) {
/* updated 2009/03/08, 2008/07/19, 2008/02/10 */
/* 2008/02/02, 2008/01/23, 2006/04/29, 2005/03/12, 2005/02/24 */
/* 012345678901234567 */
/* ITOD D00001,D00002 */
    long n_index;
    double dz = 0.0;

	/* fetch/store use sg_pass, ng_pass_lg, dg_1pass */
	/* char 48 is zero */
	/* n_index = tfni_string_to_integer(&sp_var[1], 5); */
	n_index = psg_pline[13] * 10000 + psg_pline[14] * 1000
    + psg_pline[15] * 100 + psg_pline[16] * 10 + psg_pline[17] - 533328;

    /* D means global, E means local, F means constant, N means number */
	if(psg_pline[12] == 'E') {
		/* local */
       	dz = dga_decimals[n_index + ig_dvstack_ct];
	}
	else if(psg_pline[12] == 'D') {
		/* global */
       	dz = dga_decimals[n_index];
    }
	else if(psg_pline[12] == 'F') {
		/* stored decimal literal */
       	dz = dga_decimals[n_index];
    }
	/* number */
	else if(psg_pline[12] == 'N') dz = n_index;
	else if(psg_pline[12] == 'M') dz = -n_index;

	if(dz >= 1 && dz <= DARRAY) {
        /* this will not word if dz=DARRAY + 0.1 */
        /* which would be bad programming anyway */
        /* 0.5 is too much for numbers close to 2^53 */
	    n_index = (int)floor(dz + 0.499);

       	dg_1pass = dga_darray[n_index - 1];
		sub_store_decimal_variable_in_link();
	}
	else sub_program_error_end("dtoi bad index", 14);
} /* sub_command_itod */


void sub_command_dtos(int ip1) {
/* updated 2006/05/19, 2006/05/08, 2005/11/05, 2005/04/25, 2005/04/24 */
/* 2005/04/13, 2005/04/05, 2005/03/31, 2005/02/12, 2004/12/02 */
/* 01234567890123456789012345678901 */
/* dto$ S00001,D00001,D00002,D00003 */
/* ded$ S00001,D00001,D00002,D00003 */
	int i_parm3, i_parm4, i_long, i_digit;
	int i_neg, i_beg, i_dot, i_just, ix, iy, iz;
	double d_number, d_more;
	char sy[100], sz[100];

	sub_fetch_decimal_variable_1dbl(&psg_pline[12]);
	d_number = dg_1pass;

    /* make number positive and i_neg = 1 means negative */
    if(d_number < 0) {
		i_neg = 1;
        d_number = -d_number;
    }
    else i_neg = 2;

	sub_fetch_decimal_variable_int(&psg_pline[19]);
	i_parm3 = ig_pass_int;
	if(i_parm3 > 30) i_parm3 = 30;
	if(i_parm3 < 1) i_parm3 = 0;

	sub_fetch_decimal_variable_int(&psg_pline[26]);
	i_parm4 = ig_pass_int;
	if(i_parm4 > 16) i_parm4 = 16;
	if(i_parm4 < 1) i_parm4 = 0;

    if(d_number > pow(10, 16)) {
		/* if number greater than 10E16 */
		i_beg = 1;
		i_long = sprintf(&sz[1], "%.15E", d_number);
		if(i_neg == 1) {
			sz[0] = '-';
            i_beg = 0;
            i_long++;
        }

	    /* copy into sg_pass,ng_pass_lg */
		tsub_copy(sg_pass, &sz[i_beg], i_long);
		ng_pass_lg = i_long;
    }
    else {
	    /* d_more avoids truncation problems below */
		/* ie. 0.03 = 0.02999999 etc. */
	    d_more = 0;
    	if(i_parm4 > 0) d_more = pow(10, -i_parm4) * 0.5001;

	    /* do we want just the number */
    	i_just = 2;
	    if(i_parm3 == 0 && i_parm4 == 0) i_just = 1;

    	if(i_parm3 == 0 && i_parm4 > 0) i_parm3 = i_parm4 + 1;

	    /* sz is 100 long */
    	tsub_blank(sz, 90);
		sprintf(sz, "%60.20f", d_number + d_more);
    	tsub_blank_escapes(sz, 90);

	    /* find . for sure */
		i_dot = 39;
	    for(iz = 20; iz < 60; iz++) {
    		if(sz[iz] == '.') {
        		i_dot = iz;
            	iz = 90;
	        }
    	}

	    /* no more than 16 numbers not counting leading zero left of . */
		if(d_number < 1) iz = i_dot;
	    else iz = 20;

    	for(iy = 0; iz < 60; iz++) {
			if(sz[iz] >= '0' && sz[iz] <= '9') {
				iy++;

    	        if(iy > 16 && iz > i_dot) sz[iz] = '0';
        	}
	    }

		/* decimal is in sz[39], i_dot=39 */
		if(ip1 == 2) {
			/* put commas in the number if needed */
			/* 1,234,567,890,123,456. */
			/* sy,sz are 100 long */
			tsub_copy(sy, sz, 90);
			/* the decimal is in sz[39] */
			i_digit = 0;
			for(iy = 39, iz = 39; iy >= 0 ;iz--, iy--) {
				if(sz[iz] >= '0' && sz[iz] <= '9') {
					i_digit++;
					ix = i_digit % 3;
					if(i_digit > 1 && ix == 1) {
						sy[iy] = ',';
						iy--;
					}
					sy[iy] = sz[iz];
				}
			}
			tsub_copy(sz, sy, 90);
		}

		/* the decimal is in sz[39] */
		/* find iz = first blank going to left of decimal */
		for(iz = 39; iz >= 0 && sz[iz] != ' '; iz--);

	    /* put in leading - if needed */
    	if(i_neg == 1) sz[iz] = '-';
	    /* else add 1 to get first digit of number */
    	else iz++;

	    /* iz has actual beginning of number now */
    	/* get i_beg = proposed beginning of field */
		/* 12345678901 */
    	/*      123.45 */
		i_beg = 39 + i_parm4 - i_parm3 + 1;

		/* get i_beg = actual beginning of field */
		if(iz < i_beg) i_beg = iz;

    	if(i_just == 1) {
			/* just the number */
			i_beg = iz;

        	/* we know that sz[39] is a "." */
			/* remove trailing zeros */
			/* find last non-zero byte */
			for(iz = 1, iy = 65; iz == 1; iy--) {
				if(sz[iy] <= ' ' || sz[iy] == '0') sz[iy] = ' ';
				else iz = iy;
			}

			/* remove trailing decimal */
			if(sz[iz] == '.') iz--;
			i_long = iz - i_beg + 1;
	    }
		else {
			/* get i_long = length of field */
			/* 12345678901 */
		    /*      123.45 */
			i_long = 39 + i_parm4 - i_beg + 1;
		}

	    /* if no decimal wanted */
		if(i_parm3 > 0 && i_parm4 == 0) {
	    	if(i_long > i_parm3) i_long--;
			else i_beg--;
		}

	    /* copy into sg_pass,ng_pass_lg */
		tsub_copy(sg_pass, &sz[i_beg], i_long);
		ng_pass_lg = i_long;
	}

	sub_store_string_in_link(sg_pass, ng_pass_lg);
} /* sub_command_dtos */


void sub_command_evar(void) {
/* updated 2005/03/13, 2005/03/12, 2005/02/03, 2005/01/31 */
/* 012345678901234567 */
/* evar,N12345,N12345; */
	int i_dvstack, i_svstack;

    i_dvstack = tfni_string_to_integer(&psg_pline[6], 5);
    i_svstack = tfni_string_to_integer(&psg_pline[13], 5);

    /* decimals */
    /* ig_dvstack_ct is how many decimals there are before this */
    ig_dvstack_ct = iga_dvstack[ig_dvstack_ix];
	ig_dvstack_ix++;

    i_dvstack = i_dvstack + ig_dvstack_ct;
	iga_dvstack[ig_dvstack_ix] = i_dvstack;

    /* strings */
    /* ig_svstack_ct is how many strings there are before this */
    ig_svstack_ct = iga_svstack[ig_svstack_ix];
	ig_svstack_ix++;

    i_svstack = i_svstack + ig_svstack_ct;
	iga_svstack[ig_svstack_ix] = i_svstack;
} /* sub_command_evar */


void sub_command_ends(void) {
/* updated 2005/02/08, 2005/02/03 */
	int i_beg, i_end, iz;
/*
int ig_dvstack_ct, ig_svstack_ct;
int ig_dvstack_ix;
int iga_dvstack[VSTACK], iga_svstack[VSTACK];
*/

    /* decimals */
	/* prepare to zero the decimal variables for this subr */

	i_beg = ig_dvstack_ct + 1;
    i_end = iga_dvstack[ig_dvstack_ix];
    for(iz = i_beg; iz <= i_end; iz++) dga_decimals[iz] = 0;


	/* ig_dvstack_ct is how many decimals before this subr */
	ig_dvstack_ix--;
	iz = ig_dvstack_ix;
    iz--;
	ig_dvstack_ct = iga_dvstack[iz];

    /* strings */
	/* prepare to free the string variables for this subr */

	i_beg = ig_svstack_ct + 1;
    i_end = iga_svstack[ig_svstack_ix];
    for(iz = i_beg; iz <= i_end; iz++) {
        free(psga_strings[iz]);
		psga_strings[iz] = NULL;
    	nga_strings_lg[iz] = 0;
    }

	/* ig_svstack_ct is how many decimals before this subr */
	ig_svstack_ix--;
	iz = ig_svstack_ix;
    iz--;
	ig_svstack_ct = iga_svstack[iz];

    /* get return pline number and adjust subr stack */
	ig_pline_ix = iga_subr_links[ig_subr_ix];
	ig_subr_ix--;
} /* sub_command_ends */


void sub_command_file(int ip1) {
/* updated 2007/08/23, 2006/05/23, 2005/09/11, 2005/09/10, 2005/09/03 */
/* 2005/07/26, 2005/07/25, 2005/07/24, 2005/07/02, 2005/06/20 */
/* 2005/05/09, 2005/04/27, 2005/04/12, 2005/04/05, 2005/03/31 */
/* 2005/03/13, 2005/03/12, 2005/03/07, 2005/03/03, 2005/03/02 */
/* 2005/02/13, 2005/02/12, 2005/02/11, 2005/02/09, 2004/12/04 */
/* ip1=1 fwri write a record */
/* ip1=2 frea read a record */
/* ip1=3 fadd add a record to the end */
/* ip1=4 flen get length of a file */
/* ip1=5 fdel delete a file */
/* ip1=6 fsip sip a variable length record */
/* ip1=7 fren rename a file */
/* ip1=8 finp input a whole file */
/* ip1=9 fout output a whole file */
/* ip1=10 fapp append a record to the end of a file */

	/* define a file pointer needed for processing a file */
	FILE *pf_file;

	char s_filename[100];
	long n_bytes_read, n_towrite, n_byte, n_length, n_long;
	int i_process, i_long, i_loop;
	int iy, iz;

	if(ip1 == 1) {
		/* 01234567890123456789012345678901 */
		/* fwri D00001,S00001,D00002,S00002 */
		/* write record to a file by begin byte and length */
		i_process = 1;

		/* get the record to write into sg_pass for length ng_pass_lg */
		/* sg_pass is a char array of 8K and ng_pass_lg is a long */
		sub_fetch_string_pass(26);

		/* copy sg_pass to sg_buff1 and put length in ng_buff1_lg */
        /* sg_buff1 is a char array of 8K and ng_buff1_lg is a long */
		tsub_copy(sg_buff1, sg_pass, ng_pass_lg);

		ng_buff1_lg = ng_pass_lg;

		/* get the byte into long n_byte */
		/* n_byte is the beginning byte of the file to write to */
		sub_fetch_decimal_variable_lng(&psg_pline[19]);

		/* put writeto byte in n_byte and subtract 1 to make first at 0 */
		n_byte = ng_pass_long - 1;

		/* get the filename into sg_pass of length ng_pass_lg */
		sub_fetch_string_pass(12);

		/* C90 expects a null character at the end of strings */
		sg_pass[ng_pass_lg] = 0;

		/* try opening an existing file with filename in sg_pass */
		/* "rb+" means read/write binary */
		pf_file = fopen(sg_pass, "rb+");

        /* if file pointer is NULL then file not opened */
		if(pf_file == NULL) {

			/* if the file pointer has NULL in it the file was not opened */
			/* try opening a new file */
            /* "wb+" means open new file read/write binary */
			pf_file = fopen(sg_pass, "wb+");

			/* if the file pointer has NULL in it no file was opened */
			if(pf_file == NULL) i_process++;
		}

		i_long = 0;
		if(i_process == 1) {

			/* get the length of the file plus 1 in n_length */
			/* pf_file is the file pointer to the now open file */
            /* next command sets file pointer to the end of the file */
			/* the 0L is a type long that is zero that is an offset */
            /* from the SEEK_END but here we want the end */
			fseek(pf_file, 0L, SEEK_END);

			/* ftell gives the file pointer location then add 1 */
			n_length = ftell(pf_file) + 1;

			/* set n_byte to no more than n_length */
			/* we cannot write a record to further than the end + 1 */
			if(n_byte > n_length) n_byte = n_length;

			/* set the file pointer to byte n_byte */
			fseek(pf_file, n_byte, SEEK_SET);

			/* write the record in sg_buff1 for length ng_buff1_lg */
            /* i_long returns the number of bytes written */
            /* the 1 means length is in bytes */
			i_long = fwrite(sg_buff1, 1, ng_buff1_lg, pf_file);

			/* close the file */
			fclose(pf_file);
		}

		/* store the length written */
		dg_1pass = i_long;
		sub_store_decimal_variable_in_link();
	}
	else if(ip1 == 2) {
		/* 01234567890123456789012345678901 */
		/* frea S00002,S00001,D00001,D00002 */
		/* read a record by beginning byte and length */
		i_process = 1;

		/* get the readfrom byte in n_byte */
		sub_fetch_decimal_variable_lng(&psg_pline[19]);

        /* oklatea files begin with byte 1 */
		/* subtract 1 since C90 files begin in byte 0 */
		n_byte = ng_pass_long - 1;
		if(n_byte < 0) i_process++;

		/* get the length to be read */
		sub_fetch_decimal_variable_int(&psg_pline[26]);

		ng_buff1_lg = ig_pass_int;

		/* get the filename in sg_pass for length ng_pass_lg */
		sub_fetch_string_pass(12);

		/* C90 expects a null character at the end of strings */
		sg_pass[ng_pass_lg] = 0;

        if(i_process == 1) {
			/* try opening an existing file for read binary */
			/* binary access means you get exactly what is there */
			pf_file = fopen(sg_pass, "rb");

            /* if file not opened then end processing */
			if(pf_file == NULL) i_process++;
		}

		i_long = 0;
		if(i_process == 1) {
			/* set the file pointer to n_byte */
			fseek(pf_file, n_byte, SEEK_SET);

			/* read the record into char array sg_buff1 for */
            /* length ng_buff1_lg and put number of bytes read */
			/* into integer i_long */
            /* the 1 means the length is in bytes */
			i_long = fread(sg_buff1, 1, ng_buff1_lg, pf_file);

			/* close the file */
			fclose(pf_file);
		}

		/* copy the record read into sg_pass of length ng_pass_lg */
		tsub_copy(sg_pass, sg_buff1, i_long);
		ng_pass_lg = i_long;

		/* store the record */
		sub_store_string_in_link(sg_pass, ng_pass_lg);
	}
	else if(ip1 == 3) {
		/* 0123456789012345678901234 */
		/* fadd D00001,S00001,S00002 */
		/* add a record to the end of the file and append a line feed */
		/* same as fapp but with lf instead of crlf */
		i_process = 1;

		/* get the filename */
		sub_fetch_string_pass(12);
		tsub_copy(s_filename, sg_pass, ng_pass_lg);
		s_filename[ng_pass_lg] = 0;

		/* get the record */
		sub_fetch_string_pass(19);
		tsub_pass_trim_right();
		tsub_copy(sg_buff1, sg_pass, ng_pass_lg);
		ng_buff1_lg = ng_pass_lg;

        /* put just a line feed at the record end */
		sg_buff1[ng_buff1_lg] = 10;
		ng_buff1_lg++;
		sg_buff1[ng_buff1_lg] = 0;

		/* try opening an existing file */
		pf_file = fopen(s_filename, "rb+");
		if(pf_file == NULL) {
			/* try opening a new file */
			pf_file = fopen(s_filename, "wb+");
			if(pf_file == NULL) i_process++;
		}

		i_long = 0;
		if(i_process == 1) {
			/* get the length of the file in n_byte */
			fseek(pf_file, 0L, SEEK_END);
			n_byte = ftell(pf_file);

			/* set the file pointer to n_byte */
			fseek(pf_file, n_byte, SEEK_SET);

			/* write the record */
			i_long = fwrite(sg_buff1, 1, ng_buff1_lg, pf_file);
			fclose(pf_file);
		}
		dg_1pass = i_long;
		sub_store_decimal_variable_in_link();
	}
	else if(ip1 == 4) {
		/* 012345678901234567 */
		/* flen D00001,S00001 */
		/* get the length of the file */
		i_process = 1;

		/* get the filename */
		sub_fetch_string_pass(12);
		sg_pass[ng_pass_lg] = 0;

		/* try opening an existing file read binary */
		pf_file = fopen(sg_pass, "rb");
		if(pf_file == NULL) i_process++;

		n_length = -1;
		if(i_process == 1) {
			/* get the length of the file in n_length */
			fseek(pf_file, 0L, SEEK_END);
			n_length = ftell(pf_file);
			fclose(pf_file);
		}
		dg_1pass = n_length;
		sub_store_decimal_variable_in_link();
	}
	else if(ip1 == 5) {
		/* 012345678901234567 */
        /* fdel d00001,s00001 */
		/* get the filename of the file to be deleted */
		sub_fetch_string_pass(12);
		sg_pass[ng_pass_lg] = 0;

        /* delete or remove the file */
        iz = remove(sg_pass);
        if(iz == 0) dg_1pass = 1;
        else dg_1pass = 2;
		sub_store_decimal_variable_in_link();
    }
	else if(ip1 == 6) {
		/* 0123456789012345678901234 */
		/* fsip S00002,S00001,D00001 */
		/* sip a record from a byte for a length to a line feed */
		i_process = 1;

		/* get the byte n_byte to read */
		sub_fetch_decimal_variable_lng(&psg_pline[19]);
		n_byte = ng_pass_long - 1;

		/* get the filename */
		sub_fetch_string_pass(12);
		sg_pass[ng_pass_lg] = 0;

		/* try opening an existing file to read */
		pf_file = fopen(sg_pass, "rb");
		if(pf_file == NULL) {
        	i_process++;
            n_byte = -1;
        }

		n_bytes_read = 0;

		if(i_process == 1) {
            tsub_blank(sg_buff1, VSLONG);

			/* set the file pointer to n_byte */
			fseek(pf_file, n_byte, SEEK_SET);

			/* read the record */
			n_bytes_read = fread(sg_buff1, 1, VSLONG, pf_file);
			fclose(pf_file);

            /* can we find a line feed=LF=10 */
			n_long = n_bytes_read;
			iy = -5;
            for(iz = 0; iy == -5 && iz < n_long; iz++) {
            	if(sg_buff1[iz] == 10) iy = iz;
            }

            if(iy > -5) {
				/* we found a LF at iy */
    	        n_byte = n_byte + iy + 1;
				n_long = iy;

				if(iy > 0) {
					/* blank carriage return at end if any */
                	if(sg_buff1[iy - 1] == 13) {
                    	sg_buff1[iy - 1] = ' ';
                        n_long--;
                    }
				}
            }
            else {
				/* no LF found */
    	        n_byte = n_byte + n_long;
            }

			tsub_copy(sg_pass, sg_buff1, n_long);
			ng_pass_lg = n_long;

			sub_store_string_in_link(sg_pass, ng_pass_lg);
        }

		if(n_bytes_read > 0) dg_1pass = n_byte + 1;
        else dg_1pass = 0;
		sub_store_decimal_variable(&psg_pline[19]);
	}
	else if(ip1 == 7) {
		/* fren */
		/* 0123456789012345678901234 */
		/* fren D00001,S00002,S00003 */
		/* rename a file */
		/* get the old filename */
		sub_fetch_string_pass(19);
		sg_pass[ng_pass_lg] = 0;
        tsub_copy(s_filename, sg_pass, ng_pass_lg + 1);

		/* get the new filename */
		sub_fetch_string_pass(12);
		sg_pass[ng_pass_lg] = 0;

        /* rename the file named in sg_pass to the name in s_filename */
        iz = rename(s_filename, sg_pass);

        if(iz == 0) dg_1pass = 1;
        else dg_1pass = 2;
		sub_store_decimal_variable_in_link();
    }
	else if(ip1 == 8) {
		/* finp */
		/* 012345678901234567 */
		/* finp S00002,S00001 */
		/* read into a char array and entire file */
		i_process = 1;

		/* get the filename into sg_pass,ng_pass_lg */
		sub_fetch_string_pass(12);
		sg_pass[ng_pass_lg] = 0;

        if(i_process == 1) {
			/* try opening an existing file */
			pf_file = fopen(sg_pass, "rb");
			if(pf_file == NULL) i_process++;
			sub_store_string_in_link(" ", 0);
		}

		if(i_process == 1) {
			/* get the length of the file in n_length */
			fseek(pf_file, 0L, SEEK_END);
			n_length = ftell(pf_file);

            /* make a string to hold the file psg_use1,ng_use1 */
			ng_use1 = n_length;
	        tsub_make_long_string(&psg_use1, ng_use1);
			if(ig_exit == 1) {
				fclose(pf_file);
                i_process++;
                sub_program_error_end("finp too long", 13);
            }
		}
        if(i_process == 1) {
			n_byte = 0;
			i_loop = 1;
            while(i_loop == 1) {
				/* set the file pointer to n_byte */
				fseek(pf_file, n_byte, SEEK_SET);

				/* read the record into sg_pass,ng_pass_lg */
				n_long = fread(sg_pass, 1, 4096, pf_file);

				tsub_copy(&psg_use1[n_byte], sg_pass, n_long);
				n_byte = n_byte + n_long;
				if(n_byte >= n_length) i_loop++;
				if(n_long == 0) {
					ng_use1 = n_byte - 1;
                	i_loop++;
                }
			}

			fclose(pf_file);
			sub_store_string_in_link(psg_use1, ng_use1);

            free(psg_use1);
            psg_use1 = NULL;
            ng_use1 = 0;
		}
	}
	else if(ip1 == 9) {
		/* fout */
		/* 0123456789012345678901234 */
        /* fout d12345,s12345,s12345 */
		/* store a char array into an entire file */
		i_process = 1;

		/* get the filename into sg_pass,ng_pass_lg */
		sub_fetch_string_pass(12);
		sg_pass[ng_pass_lg] = 0;

        sub_fetch_string3(19, &psg_use1, &ng_use1);
        if(ig_exit == 1) {
			i_process++;
            sub_program_error_end("fout too long", 13);
        }

        if(i_process == 1) {
			/* try opening a new file */
			pf_file = fopen(sg_pass, "wb+");
			if(pf_file == NULL) i_process++;
		}

        if(i_process == 1) {
			n_byte = 0;
			i_loop = 1;
            while(i_loop == 1) {
				/* set the file pointer to n_byte */
				fseek(pf_file, n_byte, SEEK_SET);

                n_towrite = 4096;
				if((ng_use1 - n_byte) < n_towrite)
                	n_towrite = ng_use1 - n_byte;

                /* put 4096 of the string from n_byte into sg_pass */
                tsub_copy(sg_pass, &psg_use1[n_byte], n_towrite);

				/* write the record into sg_pass,ng_pass_lg */
				n_long = fwrite(sg_pass, 1, n_towrite, pf_file);

				n_byte = n_byte + n_long;
				if(n_byte >= ng_use1) i_loop++;
				if(n_long == 0) {
					ng_use1 = n_byte - 1;
                	i_loop++;
                }
			}

			fclose(pf_file);
			dg_1pass = ng_use1;
			sub_store_decimal_variable_in_link();
		}
	}
	else if(ip1 == 10) {
		/* 0123456789012345678901234 */
		/* fapp D00001,S00001,S00002 */
		/* append a record to a file with a carriage return + line feed */
		/* same as fadd but with crlf instead of just lf */
		i_process = 1;

		/* get the filename */
		sub_fetch_string_pass(12);
		tsub_copy(s_filename, sg_pass, ng_pass_lg);
		s_filename[ng_pass_lg] = 0;

		/* get the record */
		sub_fetch_string_pass(19);
		tsub_pass_trim_right();
		tsub_copy(sg_buff1, sg_pass, ng_pass_lg);
		ng_buff1_lg = ng_pass_lg;

        /* put a carriage return and a line feed at the record end */
		sg_buff1[ng_buff1_lg] = 13;
		ng_buff1_lg++;
		sg_buff1[ng_buff1_lg] = 10;
		ng_buff1_lg++;
		sg_buff1[ng_buff1_lg] = 0;

		/* try opening an existing file */
		pf_file = fopen(s_filename, "rb+");
		if(pf_file == NULL) {
			/* try opening a new file */
			pf_file = fopen(s_filename, "wb+");
			if(pf_file == NULL) i_process++;
		}

		i_long = 0;
		if(i_process == 1) {
			/* get the length of the file in n_byte */
			fseek(pf_file, 0L, SEEK_END);
			n_byte = ftell(pf_file);

			/* set the file pointer to n_byte */
			fseek(pf_file, n_byte, SEEK_SET);

			/* write the record */
			i_long = fwrite(sg_buff1, 1, ng_buff1_lg, pf_file);
			fclose(pf_file);
		}
		dg_1pass = i_long;
		sub_store_decimal_variable_in_link();
	}
	else sub_program_error_end("file command", 12);
} /* sub_command_file */


void sub_command_sapp(void) {
/* updated 2005/07/21, 2005/07/20, 2005/04/05, 2005/03/12, 2005/02/21 */
/* uses long strings */
/* 0123456789012345678901234 */
/* $APP s12345,s12345+s12345 */
	long n_long;
	int i_error = 2;

	/* fetch into psg_use4,ng_use4 */
	sub_fetch_string3(5, &psg_use4, &ng_use4);

	/* fetch into psg_use1,ng_use1 */
	sub_fetch_string_expression_use(12);
	n_long = ng_use4 + ng_use1;

	if(n_long <= MAXSTRING) {
		ng_use2 = n_long;
        tsub_make_long_string(&psg_use2, ng_use2);

        tsub_copy(psg_use2, psg_use4, ng_use4);
		tsub_copy(&psg_use2[ng_use4], psg_use1, ng_use1);
        ng_use2 = n_long;
    }
    else i_error = 1;

	if(i_error != 1) sub_store_string_in_link(psg_use2, ng_use2);
    else sub_program_error_end("$app too long", 13);
} /* sub_command_sapp */


void sub_command_schs(int ip1) {
/* updated 2005/07/03, 2005/05/06, 2005/05/11 */
/* 2005/05/09, 2005/04/05, 2005/03/27, 2005/03/12, 2005/03/06 */
/* uses long strings */
/* 0123456789012345678901234 */
/* $CH$ S00001,S00002,D00003 */
/* DCH$ S00001,D00002,D00003 */
/* OFF$ S12345,S12345,D12345 */
/* 1=$CH$, 2=DCH$, 3=$OFF */
    char c_1;
	long nz, n_count;

	sub_fetch_decimal_variable_lng(&psg_pline[19]);
	n_count = ng_pass_long;
	if(n_count > MAXSTRING) n_count = MAXSTRING;
    if(n_count < 0) n_count = 0;

    if(ip1 == 1) {
		/* $CH$ */
		sub_fetch_string3(12, &psg_use2, &ng_use2);

		if(ng_use2 > 0) c_1 = psg_use2[0];
	    else c_1 = 0;

		free(psg_use2);
		psg_use2 = NULL;

        tsub_make_long_string(&psg_use1, n_count);
		ng_use1 = n_count;

	    for(nz = 0; nz < ng_use1; nz++) psg_use1[nz] = c_1;

		sub_store_string_in_link(psg_use1, ng_use1);
		free(psg_use1);
		psg_use1 = NULL;
	}
    else if(ip1 == 2) {
		/* DCH$ */
		sub_fetch_decimal_variable_int(&psg_pline[12]);
		c_1 = (char)ig_pass_int;

        tsub_make_long_string(&psg_use1, n_count);
		ng_use1 = n_count;

	    for(nz = 0; nz < n_count; nz++) psg_use1[nz] = c_1;

		sub_store_string_in_link(psg_use1, ng_use1);
		free(psg_use1);
		psg_use1 = NULL;
    }
	else if(ip1 == 3) {
		/* $OFF */
		sub_fetch_string3(12, &psg_use2, &ng_use2);
		if(n_count > ng_use2) n_count = ng_use2;

		nz = ng_use2 - n_count;
        tsub_make_long_string(&psg_use1, n_count);
		ng_use1 = n_count;

        tsub_copy(psg_use1, &psg_use2[nz], n_count);
		free(psg_use2);
		psg_use2 = NULL;

		sub_store_string_in_link(psg_use1, ng_use1);
		free(psg_use1);
		psg_use1 = NULL;
    }
} /* sub_command_schs */


void sub_command_scnt(void) {
/* updated 2006/10/23, 2005/07/03, 2005/06/26, 2005/04/05, 2005/04/02 */
/* uses long strings */
/* 0123456789012345678901234 */
/* $CNT D12345,S12345,S12345 */
	int iy;
	long n_end, n_count, nz;


    /* get string to find to psg_use2,ng_use2 */
	sub_fetch_string3(19, &psg_use2, &ng_use2);

    /* get string to find in to psg_byref,ng_byref */
	sub_fetch_string_byref(12);

	n_end = ng_byref - ng_use2;
    n_count = 0;

    for(nz = 0; nz <= n_end; nz++) {
		if(psg_byref[nz] == psg_use2[0]) {
			iy = tfni_compare_strings(&psg_byref[nz], psg_use2, ng_use2);
            if(iy == 0) n_count++;
        }
    }

    psg_byref = NULL;

    free(psg_use2);
    psg_use2 = NULL;
	ng_use2 = 0;

	dg_1pass = n_count;
	sub_store_decimal_variable_in_link();
} /* sub_command_scnt */


void sub_command_scut(void) {
/* updated 2006/10/11 */
/* 2005/07/24, 2005/07/03, 2005/04/05, 2005/03/12, 2004/11/27 */
/* uses long strings */
/* 01234567890123456789012345678901 */
/* $cut S00001,S00002,D00001,D00002 */
	long n_begin, n_long, nz;

    /* get the beginning byte */
	sub_fetch_decimal_variable_lng(&psg_pline[19]);
	n_begin = ng_pass_long;

    /* get the length to cut */
	sub_fetch_decimal_variable_lng(&psg_pline[26]);
	n_long = ng_pass_long;

	/* fetch cut from into psg_byref,ng_byref */
    sub_fetch_string_byref(12);

    if(n_long < 0) n_long = 0;
	if(n_begin < 1) n_begin = 1;

	if(n_begin <= ng_byref) {
		/* get actual length of part to cut */
		/* 1234567890 */
		nz = ng_byref - n_begin + 1;
		if(n_long > nz) n_long = nz;
	}
    else {
    	n_long = 0;
		n_begin = 0;
    }

    ng_use1 = n_long;
   	tsub_make_long_string(&psg_use1, ng_use1);

	tsub_copy(psg_use1, &psg_byref[n_begin - 1], ng_use1);
    psg_byref = NULL;

	sub_store_string_in_link(psg_use1, ng_use1);

    free(psg_use1);
    psg_use1 = NULL;
	ng_use1 = 0;

} /* sub_command_scut */


void sub_command_sdel(void) {
/* updated 2005/07/16, 2005/05/12, 2005/03/12, 2004/12/09 */
/* uses long strings */
/* 0123456789012345678901234 */
/* $DEL S00001,D00001,D00002 */
	long n_begin, n_long;

	sub_fetch_decimal_variable_lng(&psg_pline[12]);
	n_begin = ng_pass_long;

	sub_fetch_decimal_variable_lng(&psg_pline[19]);
	n_long = ng_pass_long;

	/* fetch into psg_use2,ng_use2 */
	sub_fetch_string3(5, &psg_use2, &ng_use2);

	/* put string with delete done in sg_pass,ng_pass_lg */
	tsub_use_delete21(n_begin - 1, n_long);

	sub_store_string_in_link(psg_use1, ng_use1);

    free(psg_use1);
    psg_use1 = NULL;

    free(psg_use2);
    psg_use2 = NULL;
} /* sub_command_sdel */


void sub_command_sdat(void) {
/* updated 2007/12/21, 2005/07/02, 2005/03/15, 2005/02/23, 2004/11/28 */
/* does not need long strings */
/* 01234567890 */
/* $DAT S00001 */
	/* 01234567890123456789012345678901234 */
	/* Sun Nov 28 19:10:06 2004 */
	/* 20-NOV-2004 19:10:06 20041120191006 */
    /* get timeline into sg_pass,ng_pass_lg */
    tsub_timeline();
	sub_store_string_in_link(sg_pass, ng_pass_lg);
} /* sub_command_sdat */


void sub_command_sift_swhi(void) {
/* updated 2008/01/26, 2005/07/23 */
/* 2005/07/13, 2005/04/05, 2005/03/12, 2005/02/27, 2004/11/27 */
/* uses long strings */
/* 0123456789012345678 */
/* $ift S00001==S00002 */
/* ==,>>,<<,>=,<=,<> */
	int i_type, i_result;
    long n_long;

    /* get first string into psg_use1,ng_use1 */
	sub_fetch_string3(5, &psg_use1, &ng_use1);

    /* get second string into psg_use2,ng_use2 */
	sub_fetch_string3(13, &psg_use2, &ng_use2);

    if(ng_use1 < ng_use2) n_long = ng_use1;
    else n_long = ng_use2;

	i_result = tfni_compare_strings(psg_use1, psg_use2, n_long);
	if(i_result == 0 && ng_use1 != ng_use2) {
    	i_result = ng_use1 - ng_use2;
	}

    free(psg_use1);
    psg_use1 = NULL;
	ng_use1 = 0;

    free(psg_use2);
    psg_use2 = NULL;
	ng_use2 = 0;

	/* ==,<<,<=,<>,>>,>= */
	i_type = 0;
	if(psg_pline[11] == '=') i_type = 10;
	else if(psg_pline[11] == '<') i_type = 20;
	else if(psg_pline[11] == '>') i_type = 30;

	if(psg_pline[12] == '=') i_type = i_type + 1;
	else if(psg_pline[12] == '<') i_type = i_type + 2;
	else if(psg_pline[12] == '>') i_type = i_type + 3;

	ig_true = 2;
	/* == */
	if(i_type == 11) {
        if(i_result == 0) ig_true = 1;
    }
	/* <= */
	else if(i_type == 21) {
        if(i_result <= 0) ig_true = 1;
    }
	/* << */
	else if(i_type == 22) {
        if(i_result < 0) ig_true = 1;
    }
	/* <> */
	else if(i_type == 23) {
        if(i_result != 0) ig_true = 1;
    }
	/* >= */
	else if(i_type == 31) {
        if(i_result >= 0) ig_true = 1;
    }
	/* >> */
	else if(i_type == 33 && i_result > 0) ig_true = 1;
	/* ig_true=1 means true */

} /* sub_command_sift_swhi */


void sub_command_sinp(void) {
/* updated 2008/05/06, 2005/09/07, 2005/03/12, 2005/02/23, 2004/11/25 */
/* 012345678901234567890 */
/* $inp S00001,"hello there" */
/* $inp S00001,S00002 */

	/* fetch into psg_use1,ng_use1 */
	sub_fetch_string_expression_use(12);
	tsub_out79(psg_use1, ng_use1);

	/* get term input into sg_pass, ng_pass_lg */
	tsub_inp1024();
	tsub_copy(sg_pass, sg_inp1024, ig_inp1024_lg);
    ng_pass_lg = ig_inp1024_lg;
	sub_store_string_in_link(sg_pass, ng_pass_lg);
} /* sub_command_sinp */


void sub_command_sins(void) {
/* updated 2006/10/21, 2005/07/17, 2005/05/12, 2005/04/06, 2005/04/05 */
/* 2005/04/04, 2005/03/12, 2005/02/21, 2005/02/19, 2004/12/08 */
/* 0123456789012345678901234 */
/* $ins S00001,D00001,S00002 */
	long n_beg;
	int i_error = 2;

    /* get first string into psg_use2,ng_use2 */
	sub_fetch_string3(5, &psg_use2, &ng_use2);

    /* get second string into psg_use3,ng_use3 */
	sub_fetch_string3(19, &psg_use3, &ng_use3);

    /* get the insert byte into n_beg */
	sub_fetch_decimal_variable_lng(&psg_pline[12]);
    n_beg = ng_pass_long;

	/* $INS */
	if(n_beg < 1) n_beg = 1;
	if(n_beg > ng_use2) n_beg = ng_use2 + 1;
	n_beg--;

   	if((ng_use2 + ng_use3) <= MAXSTRING) {
		/* insert string and put into sg_pass,ng_pass_lg */
		tsub_use_insert321(n_beg);
		sub_store_string_in_link(psg_use1, ng_use1);
	}
    else i_error = 1;

    free(psg_use2);
    psg_use2 = NULL;

    free(psg_use3);
    psg_use3 = NULL;

	if(i_error == 1) sub_program_error_end("in $INS", 7);
} /* sub_command_sins */


void sub_command_srep(void) {
/* updated 2006/10/21, 2005/07/17, 2005/05/12, 2005/04/06, 2005/04/05 */
/* 2005/04/04, 2005/03/12, 2005/02/21, 2005/02/19, 2004/12/08 */
/* 0123456789012345678901234 */
/* $REP S00001,D00001,S00002 */
	long n_beg;
	int i_error = 2;

    /* get second string into psg_use3,ng_use3 */
	sub_fetch_string3(19, &psg_use3, &ng_use3);

    /* get the insert byte into n_beg */
	sub_fetch_decimal_variable_lng(&psg_pline[12]);
    n_beg = ng_pass_long;

    /* get first string into psg_byref,ng_byref */
	sub_fetch_string_byref(5);

	/* $REP */
    n_beg--;
	if(n_beg >= 0 && (n_beg + ng_use3) <= ng_byref) {
		tsub_copy(&psg_byref[n_beg], psg_use3, ng_use3);
    }
    else i_error = 1;

    psg_byref = NULL;
    ng_byref = 0;

    free(psg_use3);
    psg_use3 = NULL;
    ng_use3 = 0;

	if(i_error == 1) sub_program_error_end("in $REP", 7);
} /* sub_command_srep */


void sub_command_sisc(int ip1) {
/* updated 2005/10/13, 2005/07/12 */
/* 2005/04/09, 2005/04/06, 2005/04/03, 2005/03/25, 2005/03/19 */
/* uses long strings */
/* 0123456789012345678901234 */
/* $ISC D12345,S12345,S12345 */
/* 1=$ISC */
/* 2=$IST */
/* 3=$ISP */
	int i_yesno, i_type, ix, iy;
	long nz;

    /* get string to consider in psg_use1,ng_use1 */
	sub_fetch_string3(12, &psg_use1, &ng_use1);

    /* get pattern string into psg_use2,ng_use2 */
	sub_fetch_string3(19, &psg_use2, &ng_use2);

    i_yesno = 2;

    if(ip1 == 1) {
		/* $ISC string is a certain char */
		for(iy = 1, nz = 0; iy == 1 && nz < ng_use1; nz++) {
			if(psg_use1[nz] != psg_use2[0]) iy++;
       	}
		if(iy == 1) i_yesno = 1;
    }
	else if(ip1 == 2) {
		/* $IST string is a certain type */
		i_type = tfni_char_type(psg_use2[0]);

		for(iy = 1, nz = 0; iy == 1 && nz < ng_use1; nz++) {
			ix = tfni_char_type(psg_use1[nz]);
			if(ix != i_type) iy++;
        }
		if(iy == 1) i_yesno = 1;
    }
	else if(ip1 == 3) {
		/* $ISP string is a certain pattern */
		if(ng_use1 == ng_use2) {
			for(iy = 1, nz = 0; iy == 1 && nz < ng_use1; nz++) {
				i_type = tfni_char_type(psg_use1[nz]);
				ix = tfni_char_type(psg_use2[nz]);
				if(ix != i_type) iy++;
	        }
			if(iy == 1) i_yesno = 1;
		}
    }

    if(ng_use1 == 0 || ng_use2 == 0) i_yesno = 2;

    free(psg_use1);
    psg_use1 = NULL;
    ng_use1 = 0;

    free(psg_use2);
    psg_use2 = NULL;
    ng_use2 = 0;

	dg_1pass = i_yesno;
	sub_store_decimal_variable_in_link();
} /* sub_command_sisc */


void sub_command_slen(int ip1) {
/* updated 2006/06/02, 2006/05/31 */
/* 2005/10/12, 2005/07/04, 2005/03/12, 2005/02/21, 2004/12/03 */
/* uses long strings */
/* 0123456789012345 */
/* $len D0001,S0001 */
/* 1=$len, 2=$chd, 3=$hsh */
	int iz;
	int i_error = 2;
	long nx, ny, nz;

    /* get string to find in */
	sub_fetch_string3(12, &psg_use1, &ng_use1);

    if(ip1 == 1) {
		/* $LEN */
    	dg_1pass = ng_use1;
    }
	else if(ip1 == 2) {
		/* $CHD */
        if(ng_use1 > 0) {
        	iz = (int)psg_use1[0];
			if(iz < 0) iz = iz + 256;
            dg_1pass = iz;
        }
        else i_error = 1;
    }
	else if(ip1 == 3) {
		/* $hsh */
		nx = 0;
        ny = 0;
		for(nz = 0; nz < ng_use1; nz++) {
			iz = (int)psg_use1[nz] + 1;

			/* nx is just a total, 1,000,000,000 */
			nx = (nx + iz) % 1000000000;

			/* 701 is prime, 1,000,000 */
			ny = (ny + (nz % 701 + 1) * iz) % 1000000;
        }
		/* 1,000,000 */
		dg_1pass = (double)nx * 1000000 + ny;
    }
    else i_error = 1;

    free(psg_use1);
    psg_use1 = NULL;
	ng_use1 = 0;

	if(i_error != 1) sub_store_decimal_variable_in_link();
    else sub_program_error_end("bad $chd", 8);
} /* sub_command_slen */


void sub_command_slok(int ip1) {
/* updated 2006/10/21, 2005/07/23 */
/* 2005/07/22, 2005/04/11, 2005/04/06, 2005/03/12, 2005/03/05 */
/* uses long strings */
/* 01234567890123456789012345678901 */
/* $LOK D00001,S00001,D00002,S00002 */
/* 1=$LOK, 2=$BAK */
    int i_loop;
	long n_begin, n_result, n_max;
	long nx, ny, nz;

    /* where to begin */
	sub_fetch_decimal_variable_lng(&psg_pline[19]);
	n_begin = ng_pass_long;

    /* get lookfor in psg_use2,ng_use2 */
	sub_fetch_string3(26, &psg_use2, &ng_use2);

    /* string to look in is psg_use1,ng_use1 */
	/* sub_fetch_string3(12, &psg_use1, &ng_use1); */
    sub_fetch_string_byref(12);

    n_result = 0;
	/* look for cannot be longer than look in */
    if(ng_use2 > ng_byref) ip1 = 9999;

    if(ip1 == 1) {
		/* $LOK */
		i_loop = 1;
		if(n_begin < 1) n_begin = 1;
	    n_begin--;

        /* get i_max = maximum possible find byte */
		n_max = ng_byref - ng_use2;
		if(n_begin > n_max) i_loop++;

		nz = n_begin;

        while(i_loop == 1) {
			if(psg_byref[nz] == psg_use2[0]) {
				for(ny = 1, nx = 0; ny == 1 && nx < ng_use2; nx++) {
					if(psg_byref[nz + nx] != psg_use2[nx]) ny++;
                }
				if(ny == 1) {
					i_loop++;
                    n_result = nz + 1;
                }
            }

			nz++;
			if(nz > n_max) i_loop++;
        }
    }
    else if(ip1 == 2) {
		/* $BAK */
		i_loop = 1;
		if(n_begin > ng_byref) n_begin = ng_byref;
	    n_begin--;

        /* get n_max = maximum possible find byte */
		n_max = ng_byref - ng_use2;
		if(n_begin > n_max) n_begin = n_max;
		if(n_begin < 0) i_loop++;
		nz = n_begin;

        while(i_loop == 1) {
			if(psg_byref[nz] == psg_use2[0]) {
				for(ny = 1, nx = 0; ny == 1 && nx < ng_use2; nx++) {
					if(psg_byref[nz + nx] != psg_use2[nx]) ny++;
                }
				if(ny == 1) {
					i_loop++;
                    n_result = nz + 1;
                }
            }

			nz--;
			if(nz < 0) i_loop++;
        }
    }

    psg_byref = NULL;
	ng_byref = 0;

    free(psg_use2);
    psg_use2 = NULL;
	ng_use2 = 0;

	dg_1pass = n_result;
	sub_store_decimal_variable_in_link();
} /* sub_command_slok */


void sub_command_sout(int ip1) {
/* updated 2005/07/31, 2005/07/25, 2005/07/24, 2005/07/23 */
/* 2005/07/22, 2005/07/15, 2005/05/03, 2005/04/20, 2004/12/02 */
/* uses long strings */
/* 01234567890123456789 */
/* $out S00001+D00321+"hello there" */
/* $sho S00001 */
	char sz[80];

    /* get string to output psg_use1,ng_use1 */
	sub_fetch_string_expression_use(5);

	if(ng_use1 > 79) ng_use1 = 79;
	tsub_blank(sz, 80);
	tsub_copy(sz, psg_use1, ng_use1);
	tsub_blank_escapes(sz, 80);
	sz[79] = 0;

	if(ip1 == 2) {
		/* ip1 = 2 is $SHO */
		printf("%s\r", sz);
		fflush(stdout);
	}
	else {
		/* ip1 = 1 is $OUT */
		printf("%s\n", sz);
		fflush(stdout);
    }

    free(psg_use1);
    psg_use1 = NULL;
	ng_use1 = 0;
} /* sub_command_sout */


void sub_command_spkd(int ip1) {
/* updated 2005/07/31, 2005/06/06, 2005/05/03 */
/* does not need long strings */
/* ip1=1 for $PKD */
/* ip1=2 for DPK$ */
/* ip1=3 for DTOF */
	double d_decimal;
    int i_good, i_long, i_negative;
	int ix, iy, iz;

	if(ip1 == 1) {
		/* 0123456789012345678901234 */
		/* $PKD D12345,D12345,S12345 */

	    /* get packed decimal number string */
		sub_fetch_string_pass(19);
		tsub_pass_trim_left();
        tsub_pass_trim_right();

        /* if nothing make zero */
		if(ng_pass_lg == 0) {
			sg_pass[0] = '0';
            ng_pass_lg = 1;
        }

        /* get the last character and do we need to change it */
		ix = ng_pass_lg - 1;
		iz = sg_pass[ix];


        /* 48 is 0 and 57 is 9 */
        i_negative = 1;
        if(iz >= 48 && iz <= 57) i_negative = 2;

    	else if(iz >= 65 && iz <= 73) {
		    /* 65 is A and 73 is I */
    	    i_negative = 2;
        	iz = iz - 16;
	        sg_pass[ix] = (char)iz;
    	}

    	else if(iz >= 74 && iz <= 82) {
		    /* 74 is J=1 and 82 is R=9 */
    	    i_negative = 1;
        	iz = iz - 25;
	        sg_pass[ix] = (char)iz;
    	}

    	else if(iz == 125) {
		    /* a right brace is 125 which is negative zero */
    	    i_negative = 1;
        	sg_pass[ix] = '0';
	    }

	    else if(iz == 123) {
	    	/* a left brace is 123 which is positive zero */
        	i_negative = 2;
	        sg_pass[ix] = '0';
    	}

        /* make sure we now have all digits and not too long */
		d_decimal = 0;
		i_good = 1;
        if(ng_pass_lg > 15) i_good = 2;

        for(iz = 0; iz < ng_pass_lg; iz++) {
			iy = sg_pass[iz] - 48;
			if(iy < 0 || iy > 9) i_good = 2;
			else d_decimal = d_decimal * 10 + iy;
        }

        if(i_negative == 1) d_decimal = - d_decimal;

        if(i_good == 1) {
			dg_1pass = d_decimal;
			sub_store_decimal_variable(&psg_pline[12]);
		}

		dg_1pass = i_good;
		sub_store_decimal_variable_in_link();
    }
    else if(ip1 == 2) {
		/* 0123456789012345678901234 */
		/* DPK$ S12345,D12345,D12345 */

	    /* get decimal to make into packed decimal string */
		sub_fetch_decimal_variable_1dbl(&psg_pline[12]);
		d_decimal = dg_1pass;

        i_negative = 2;
        if(d_decimal < 0) {
			i_negative = 1;
			d_decimal = - d_decimal;
        }

        /* 0.5 is too much for numbers close to 2^53 */
		d_decimal = floor(d_decimal + 0.499);

	    /* get length of string */
		sub_fetch_decimal_variable_int(&psg_pline[19]);
		i_long = ig_pass_int;

		if(i_long < 0) i_good = 2;
        else i_good = 1;

		/* put right most digit in sg_buff1[29] zero filled */
		sprintf(sg_buff1, "%030.0f", d_decimal);

        if(i_negative == 1) {
			/* put in right most digit to show negative */
			iz = sg_buff1[29];
			/* char 48 is a zero */
            if(iz == 48) sg_buff1[29] = '}';
            else {
				iz = iz + 25;
                sg_buff1[29] = (char)iz;
            }
        }
        iz = 29 - i_long + 1;

        tsub_copy(sg_pass, &sg_buff1[iz], i_long);
        ng_pass_lg = i_long;

		if(i_good == 1) sub_store_string_in_link(sg_pass, ng_pass_lg);
		else sub_program_error_end("$pkd", 4);
    }
    else if(ip1 == 3) {
		/* 0123456789012345678901234 */
		/* DTOF S12345,D12345,D12345 */
	    /* get decimal to make into packed decimal string */
		sub_fetch_decimal_variable_1dbl(&psg_pline[12]);
        d_decimal = dg_1pass;

        i_negative = 2;
        if(d_decimal < 0) {
			i_negative = 1;
			d_decimal = - d_decimal;
        }

        /* 0.5 is too much for numbers close to 2^53 */
		d_decimal = floor(d_decimal + 0.499);

	    /* get length of string */
		sub_fetch_decimal_variable_int(&psg_pline[19]);
		i_long = ig_pass_int;

		if(i_long < 0) i_good = 2;
        else i_good = 1;

        /* put into sg_buff1 with the right most digit in sg_buff1[29] */
		sprintf(sg_buff1, "%030.0f", d_decimal);

        iz = 29 - i_long + 1;
        if(i_negative == 1) sg_buff1[iz] = '-';
        else sg_buff1[iz] = '+';

        tsub_copy(sg_pass, &sg_buff1[iz], i_long);
        ng_pass_lg = i_long;

		if(i_good == 1) sub_store_string_in_link(sg_pass, ng_pass_lg);
		else sub_program_error_end("$tof", 4);
	}
} /* sub_command_spkd */


void sub_command_spar(void) {
/* updated 2006/10/23, 2006/04/13, 2005/07/19, 2005/04/06, 2005/04/01 */
/* uses long strings */
/* 01234567890123456789012345678901 */
/* $PAR S12345,S12345,S12345,D12345 */
	char c_csv;
	long n_which, n_beg, n_count, ny, nz;
	int i_good = 1;

    /* get the number of which one we want into n_which */
	sub_fetch_decimal_variable_lng(&psg_pline[26]);
	n_which = ng_pass_long;

    /* put the one length csv delimiter into c_csv */
	sub_fetch_string3(19, &psg_use3, &ng_use3);
	c_csv = psg_use3[0];
	if(ng_use3 <= 0) i_good++;

	if(i_good == 1) {
	    /* reference look-in string with psg_byref,ng_byref */
		sub_fetch_string_byref(12);
		if(ng_byref < 2) i_good++;
	}
	if(i_good == 1) {
	    /* change n_which to the char at the beginning of the wanted string */
		n_which--;

	    /* find the beginning of one we want into n_beg */
		if(n_which < 1) n_beg = 0;
	    else {
			n_beg = -1;
	    	n_count = 0;

			for(nz = 0; n_beg == -1 && nz < ng_byref; nz++) {
				if(psg_byref[nz] == c_csv) {
					n_count++;
					if(n_count == n_which) n_beg = nz + 1;
	    	    }
		    }
		}
		if(n_beg < 0 || n_beg >= ng_byref) i_good++;
	}
	if(i_good == 1) {
		/* how long into ng_use1 */
		ny = 1;
	    ng_use1 = 0;
    	for(nz = n_beg; ny == 1 && nz < ng_byref; nz++) {
			if(psg_byref[nz] == c_csv) {
    	    	ng_use1 = nz - n_beg;
				ny++;
	        }
    	}
		if(ny == 1) {
			/* string ends at end of in-string */
            ng_use1 = ng_byref - n_beg + 1;
        }
	}

    if(i_good != 1) ng_use1 = 0;
    tsub_make_long_string(&psg_use1, ng_use1);

    if(i_good == 1) {
	    /* copy the one wanted to psg_use1,ng_use1 */
    	if(n_beg >= 0) {
			n_count = 0;
    	    nz = n_beg;
			for(; psg_byref[nz] != c_csv && nz < ng_byref; nz++, n_count++) {
				psg_use1[n_count] = psg_byref[nz];
	        }
			ng_use1 = n_count;
	    }
		else ng_use1 = 0;
	}

	sub_store_string_in_link(psg_use1, ng_use1);
} /* sub_command_spar */


void sub_command_sdot(void) {
/* updated 2006/10/23, 2006/05/12 */
/* find location of certain occurrence of a string in a string */
/* 01234567890123456789012345678901 */
/* $DOT N12345,S12345,S12345,D12345 */
	char c_csv;
    long n_which, n_last, n_count, ny, nz;
	long n_dot = 0;
	int i_good = 1;

    /* get which one we want into n_which */
	sub_fetch_decimal_variable_lng(&psg_pline[26]);
	n_which = ng_pass_long;

    /* get string parameters */
	sub_fetch_string3(19, &psg_use3, &ng_use3);
	sub_fetch_string_byref(12);

    /* get first byte of psg_use3,ng_use3 */
	c_csv = psg_use3[0];

	/* both must have length */
	if(ng_byref <= 0) i_good++;
	if(ng_use3 <= 0) i_good++;
	if(n_which <= 0) i_good++;

	if(i_good == 1) {
		n_last = ng_byref - ng_use3 + 1;
		n_count = 0;

		for(nz = 0; nz < n_last; nz++) {
			if(psg_byref[nz] == c_csv) {
				ny = tfni_compare_strings(&psg_byref[nz], psg_use3, ng_use3);

				if(ny == 0) {
					/* we have a match */
					n_count++;

					if(n_count == n_which) {
						/* we have the wanted count */
						n_dot = nz;
                        nz = n_last;
					}
                    else {
						nz = nz + ng_use3;
                    }
                }
            }
        }
	}

	dg_1pass = n_dot + 1;
	sub_store_decimal_variable_in_link();
} /* sub_command_sdot */


void sub_command_stoe(void) {
/* updated 2006/08/22, 2006/08/21, 2006/04/08 */
/* $toe old toe */
/* 01234567890123456789012345678901 */
/* $TOE S12345,S12345,S12345,D12345 */
	long n_number, n_byte, n_slip, n_which, ny, nz;
	long n_bigprime = 700000001; /* 700,000,001 */

    /* get key string into psg_use3,ng_use3 */
	sub_fetch_string3(19, &psg_use3, &ng_use3);

    /* put begin string into psg_use2,ng_use2 */
	sub_fetch_string3(12, &psg_use2, &ng_use2);

    /* get which one we want into n_which */
	sub_fetch_decimal_variable_lng(&psg_pline[26]);
	n_which = ng_pass_long;
    if(n_which != 1) n_which = 2;

	/* get n_number from psg_use3,ng_use3 */
	tsub_case_upper(psg_use3, ng_use3);
	n_number = 0;
    if(ng_use3 > 16) ng_use3 = 16;

    for(nz = 0; nz < ng_use3; nz++) {
		ny = psg_use3[nz];
        if((ny >= '0' && ny <= '9')
        || (ny >= 'A' && ny <= 'Z'))
        n_number = n_number * 10 + ny;

        if(n_number > n_bigprime) n_number = n_number - n_bigprime;
    }

    for(n_byte = 0; n_byte < ng_use2; n_byte++) {
		/* get next n_number */
        n_number = (n_number * 3 + 35731) % n_bigprime;
		n_slip = (n_number / 103) % 95 + 1;

        ny = psg_use2[n_byte];

		if(ny >= 32 && ny <= 126) {
	        if(n_which == 1) ny = ny + n_slip;
    	    else ny = ny - n_slip;

            if(ny > 126) ny = ny - 95;
            else if(ny < 32) ny = ny + 95;

			psg_use2[n_byte] = (char)ny;
		}
    }

	sub_store_string_in_link(psg_use2, ng_use2);
} /* sub_command_stoe */


void sub_command_sset(void) {
/* updated 2005/07/21, 2005/03/12, 2004/11/27 */
/* uses long strings */
/* 012345678901234567 */
/* $set S00001=S00002
/* $set S00001="hello there" */

	sub_fetch_string_expression_use(12);

	sub_store_string_in_link(psg_use1, ng_use1);
} /* sub_command_sset */


void sub_command_ssor(void) {
/* updated 2005/07/23, 2005/07/22, 2005/04/12, 2005/04/03, 2005/04/02 */
/* uses long strings */
/* 0123456789012345678901234 */
/* $SOR S00001,S00002,D00001 */
	int i_process;
    long n_long, n_max, nz;
	long n_part1, n_part2, n_byte1, n_byte2;

    i_process = 1;
	/* the the length of the sort part */
	sub_fetch_decimal_variable_lng(&psg_pline[19]);
	n_long = ng_pass_long;

    /* put string to be sorted into psg_use1,ng_use1 */
	sub_fetch_string3(12, &psg_use1, &ng_use1);

    /* make a swap string n_long */
    tsub_make_long_string(&psg_use2, n_long);

	if(ng_use1 < n_long) i_process++;
	if(n_long > 0) {
		nz = ng_use1 % n_long;
        if(nz != 0) i_process++;
    }
    else i_process++;

	if(i_process == 1) {
		n_max = ng_use1 / n_long;

    	for(n_part1 = 1; n_part1 < n_max; n_part1++) {
			n_byte1 = (n_part1 - 1) * n_long;

			for(n_part2 = n_part1 + 1; n_part2 <= n_max; n_part2++) {
				n_byte2 = (n_part2 - 1) * n_long;

                nz = tfni_compare_strings(
                &psg_use1[n_byte1], &psg_use1[n_byte2], n_long);

                /* first is greater so swap */
                if(nz > 0) {
					tsub_copy(psg_use2, &psg_use1[n_byte1], n_long);
					tsub_copy(&psg_use1[n_byte1], &psg_use1[n_byte2], n_long);
					tsub_copy(&psg_use1[n_byte2], psg_use2, n_long);
                }
            }
        }
    }

	if(i_process == 1) sub_store_string_in_link(psg_use1, ng_use1);

    free(psg_use1);
    psg_use1 = NULL;
	ng_use1 = 0;

    free(psg_use2);
    psg_use2 = NULL;
	ng_use2 = 0;
} /* sub_command_ssor */


void sub_command_stod(int ip1) {
/* updated 2005/03/12, 2004/11/30 */
/* does not need long strings */
/* 012345678901234567 */
/* $tod D00012,S00001 */
/* $tod D00004,"12345.6789" */

	sub_fetch_string_pass(12);

	tsub_string_to_double(sg_pass, ng_pass_lg);

	/* ip1=1 is $tod, ip1=2 is $isd */
	if(ip1 == 2) dg_1pass = ig_pass_int;

	sub_store_decimal_variable_in_link();
} /* sub_command_stod */


void sub_command_stoi(int ip1) {
/* updated 2005/07/23, 2005/04/14, 2005/04/09, 2005/03/31, 2005/03/12 */
/* uses long strings */
/* 012345678901234567 */
/* $TOI D12345,S12345 = 1 */
/* Ito$ S12345,D12345 = 2 */
/* ARRB = 3 */
/* ARRZ = 4 */
	int i_index;

	if(ip1 == 1) {
		/* $TOI */
		sub_fetch_decimal_variable_int(&psg_pline[5]);
		i_index = ig_pass_int - 1;

        if(i_index >= 0 && i_index < SARRAY) {
			sub_fetch_string_expression_use(12);

            tsub_make_long_string(&psga_sarray[i_index], ng_use1);
			tsub_copy(psga_sarray[i_index], psg_use1, ng_use1);

			iga_sarray_lg[i_index] = ng_use1;
		}
        else sub_program_error_end("$TOI bad index", 14);
    }
    else if(ip1 == 2) {
		/* ITO$ */
		sub_fetch_decimal_variable_int(&psg_pline[12]);
		i_index = ig_pass_int - 1;

		if(i_index >= 0 && i_index < SARRAY) {
			ng_use1 = iga_sarray_lg[i_index];
            tsub_make_long_string(&psg_use1, ng_use1);
			tsub_copy(psg_use1, psga_sarray[i_index], ng_use1);
			sub_store_string_in_link(psg_use1, ng_use1);
        }
        else sub_program_error_end("ITO$ bad index", 14);
    }
	else if(ip1 == 3) {
		/* ARRB */
		/* free memory of psga_sarray */
		for(i_index = 0; i_index < SARRAY; i_index++) {
			free(psga_sarray[i_index]);
			psga_sarray[i_index] = NULL;
			iga_sarray_lg[i_index] = 0;
		}
    }
    else if(ip1 == 4) {
    	for(i_index = 0; i_index < DARRAY; i_index++)
			dga_darray[i_index] = 0;
    }
} /* sub_command_stoi */


void sub_command_strl(int ip1) {
/* updated 2006/03/17, 2006/01/17, 2005/10/12 */
/* 2005/08/16, 2005/07/17, 2005/03/12, 2005/02/21, 2005/02/20 */
/* uses long strings */
/* 012345678901234567 */
/* $trl s12345,s12345 */
/* 1=$TRL, 2=$TRR, 3=$TRB, 4=$BES, 5=$CLO, 6=$CUP */
/* 7=$TLO, 8=$TUP, 9=$COD, 10=$TOE */
	int i_error = 2;
	int i_char;
	long nz;

    /* get the string into psg_use2,ng_use2 */
	sub_fetch_string3(12, &psg_use2, &ng_use2);

	if(ip1 == 1) {
		/* $TRL */
		/* trim left into psg_use1,ng_use1 */
		tsub_use_trim_left(psg_use2, ng_use2);
    }
	else if(ip1 == 2) {
		/* $TRR */
		/* trim right into psg_use1,ng_use1 */
		tsub_use_trim_right(psg_use2, ng_use2);
    }
	else if(ip1 == 3) {
		/* $TRB */
		/* trim left into psg_use1,ng_use1 */
		tsub_use_trim_left(psg_use2, ng_use2);

		tsub_use_move12();

		/* trim right into psg_use1,ng_use1 */
		tsub_use_trim_right(psg_use2, ng_use2);
    }
	else if(ip1 == 4) {
		/* $BES */
		tsub_blank_escapes(psg_use2, ng_use2);

        tsub_use_move21();
    }
	else if(ip1 == 5) {
		/* $CLO */
		tsub_case_lower(psg_use2, ng_use2);

        tsub_use_move21();
    }
	else if(ip1 == 6) {
		/* $CUP */
		tsub_case_upper(psg_use2, ng_use2);

        tsub_use_move21();
    }
	else if(ip1 == 7) {
		/* $TLO */
		tsub_case_lower(psg_use2, ng_use2);

		tsub_use_trim_left(psg_use2, ng_use2);

        tsub_use_move12();

		tsub_use_trim_right(psg_use2, ng_use2);
    }
	else if(ip1 == 8) {
		/* $TUP */
		tsub_case_upper(psg_use2, ng_use2);

		tsub_use_trim_left(psg_use2, ng_use2);

        tsub_use_move12();

		tsub_use_trim_right(psg_use2, ng_use2);
    }
	else if(ip1 == 9) {
		/* $COD */
		for(nz = 0; nz < ng_use2; nz++) {
			i_char = psg_use2[nz];
			if(i_char > 32 && i_char < 127) {
	            i_char = i_char + 47;
    	        if(i_char > 126) i_char = i_char - 94;
                psg_use2[nz] = (char)i_char;
			}
        }
        tsub_use_move21();
    }
	else if(ip1 == 10) {
		/* $TOE */
		for(nz = 0; nz < ng_use2; nz++) {
			i_char = psg_use2[nz];
			if(i_char > 32 && i_char < 127) {
	            i_char = 159 - i_char;
                psg_use2[nz] = (char)i_char;
			}
        }
        tsub_use_move21();
    }
	else i_error++;

	if(i_error != 1) sub_store_string_in_link(psg_use1, ng_use1);

	free(psg_use1);
    psg_use1 = NULL;
    ng_use1 = 0;
} /* sub_command_strl */


void sub_command_sswp(void) {
/* updated 2008/02/11, 2008/10/02, 2006/08/09, 2005/07/23 */
/* 2005/06/05, 2005/04/07, 2005/04/06, 2005/04/03, 2005/04/02 */
/* 0123456789012345678901234 */
/* $swp S12345,S12345,S12345 */
/* $swp s_string, s_old, s_new */
    int i_error, i_loop, iy;
	long n1, n2;

    /* put swapout string in psg_use4,ng_use4 */
	sub_fetch_string3(12, &psg_use4, &ng_use4);

    /* put swapin string in psg_use3,ng_use3 */
	sub_fetch_string3(19, &psg_use3, &ng_use3);

    /* get main string to make changes to into sg_pass,ng_pass_lg */
	sub_fetch_string3(5, &psg_use2, &ng_use2);

    if(ng_use3 <= ng_use4) ng_use1 = ng_use2 + 50;
    else ng_use1 = ng_use2 + ng_use2 / 2 + 50;

    /* make new string to put new main into in psg_use1,ng_use1 */
    tsub_make_long_string(&psg_use1, ng_use1);
    tsub_blank(psg_use1, ng_use1);

    i_error = 2;
    n1 = 0;
    n2 = 0;
    i_loop = 1;

    while(i_loop == 1) {
		if(psg_use2[n2] != psg_use4[0]) {
            psg_use1[n1] = psg_use2[n2];
        }
        else {
            /* does psg_use2 match the swapout string psg_use4 */
			iy = tfni_compare_strings(&psg_use2[n2], psg_use4, ng_use4);
            if(iy == 0) {
                /* we have a match so swap */
				tsub_copy(&psg_use1[n1], psg_use3, ng_use3);

				/* skip to end of in swapped string */
                n2 = n2 + ng_use4 - 1;
                n1 = n1 + ng_use3 - 1;
            }
            else psg_use1[n1] = psg_use2[n2];
        }
        n1++;
        n2++;

        if(n2 >= ng_use2) i_loop++;
        if(n1 >= ng_use1) {
            sub_program_error_end("too long swp", 12);
            i_loop++;
        }
    }

    ng_use1 = n1;

    /* store the new main string in psg_use1,ng_use1 */
	if(i_error != 1) sub_store_string_in_link(psg_use1, ng_use1);

	free(psg_use1);
    psg_use1 = NULL;
    ng_use1 = 0;

	free(psg_use2);
    psg_use2 = NULL;
    ng_use2 = 0;

	free(psg_use3);
    psg_use3 = NULL;
    ng_use3 = 0;

	free(psg_use4);
    psg_use4 = NULL;
    ng_use4 = 0;
} /* sub_command_sswp */


void sub_command_ssys(void) {
/* updated 2007/12/14, 2006/08/29, 2005/03/31 */
/* 012345678901234567 */
/* $sys S12345,D12345 */
	char s_string[100];
    int i_parm2, iy, iz;

	sub_fetch_decimal_variable_int(&psg_pline[12]);
	i_parm2 = ig_pass_int;

    if(i_parm2 == 1) {
		/* path of current application */
        tsub_copy(sg_pass, sg_path, ig_path);
        ng_pass_lg = ig_path;
    }
	else if(i_parm2 == 2) {
		/* name of current subroutine */
		tsub_copy(sg_pass, "no subr", 7);
		ng_pass_lg = 7;

        for(iz = ig_pline_ix; iz > 0; iz--) {
			iy = iga_plines_lg[iz];
			tsub_copy(s_string, psga_plines[iz], iy);
			if(tfni_compare_strings(s_string, "SUBR", 4) == 0) {
				tsub_copy(sg_pass, &s_string[5], iy - 5);
                ng_pass_lg = iy - 5;
				iz = 0;
            }
		}
    }
    else if(i_parm2 == 3) {
        tsub_copy(sg_pass, sg_version, 60);
        ng_pass_lg = 60;
    }

	sub_store_string_in_link(sg_pass, ng_pass_lg);
} /* sub_command_ssys */
/* command subroutines above */


/* fetch and store subroutines below */
void sub_fetch_decimal_variable_1dbl(char *sp_var) {
/* updated 2009/03/08 */
/* 2008/07/19, 2008/07/15, 2008/07/14, 2008/07/09, 2008/02/02 */
/* 2006/03/01, 2006/02/28, 2005/11/30, 2005/07/31, 2005/03/13 */
/* 2005/03/12, 2005/02/18, 2005/02/17, 2005/02/01, 2004/12/04 */
/* 012456 */
/* D12345 */
	int i_index;

	/* fetch/store use sg_pass, ng_pass_lg, dg_1pass */
	/* char 48 is zero */
	/* i_index = tfni_string_to_integer(&sp_var[1], 5); */
	i_index = sp_var[1] * 10000 + sp_var[2] * 1000 + sp_var[3] * 100
    + sp_var[4] * 10 + sp_var[5] - 533328;

    /* D means global, E means local, F means constant, N means number */
    /* N means number */
	if(sp_var[0] == 'N') dg_1pass = i_index;
	else if(sp_var[0] == 'E') {
		/* local */
       	dg_1pass = dga_decimals[i_index + ig_dvstack_ct];
	}
	else if(sp_var[0] == 'D') {
		/* global */
       	dg_1pass = dga_decimals[i_index];
    }
	else if(sp_var[0] == 'F') {
		/* stored decimal literal */
       	dg_1pass = dga_decimals[i_index];
    }
	/* negative number */
	else if(sp_var[0] == 'M') dg_1pass = -i_index;
    else sub_program_error_end("bad dec var", 11);
} /* sub_fetch_decimal_variable_1dbl */


void sub_fetch_decimal_variable_2dbl(char *sp_var) {
/* updated 2009/03/08 */
/* 2008/07/19, 2008/07/15, 2008/07/14, 2008/07/08, 2008/02/02 */
/* 2006/03/01, 2006/02/28, 2005/11/30, 2005/07/31, 2005/03/13 */
/* 2005/03/12, 2005/02/18, 2005/02/17, 2005/02/01, 2004/12/04 */
/* 012456 */
/* D12345 */
	int i_index;

	/* fetch/store use sg_pass, ng_pass_lg, dg_2pass */
	/* char 48 is zero */
	/* i_index = tfni_string_to_integer(&sp_var[1], 5); */
	i_index = sp_var[1] * 10000 + sp_var[2] * 1000 + sp_var[3] * 100
    + sp_var[4] * 10 + sp_var[5] - 533328;

    /* D means global, E means local, F means constant, N means number */
    /* N means positive integer */
	if(sp_var[0] == 'N') dg_2pass = i_index;
	else if(sp_var[0] == 'E') {
		/* local */
       	dg_2pass = dga_decimals[i_index + ig_dvstack_ct];
	}
	else if(sp_var[0] == 'D') {
		/* global */
       	dg_2pass = dga_decimals[i_index];
    }
	else if(sp_var[0] == 'F') {
		/* stored decimal literal */
       	dg_2pass = dga_decimals[i_index];
    }
	/* negative number */
	else if(sp_var[0] == 'M') dg_2pass = -i_index;
    else sub_program_error_end("bad dec var", 11);
} /* sub_fetch_decimal_variable_2dbl */


void sub_fetch_decimal_pointer_dbl(char *sp_var, double *dp_var) {
/* updated 2008/02/02 */
/* 2006/03/01, 2006/02/28, 2005/11/30, 2005/07/31, 2005/03/13 */
/* 2005/03/12, 2005/02/18, 2005/02/17, 2005/02/01, 2004/12/04 */
/* 01245 */
/* D1234 */
	int i_index;
    int i_error = 2;
/* this sub is currently not used */
	*dp_var = 0;
	/* fetch/store use sg_pass, ng_pass_lg, dp_var */
	/* char 48 is zero */
	/* i_index = tfni_string_to_integer(&sp_var[1], 5); */
	i_index = sp_var[1] * 10000 + sp_var[2] * 1000 + sp_var[3] * 100
    + sp_var[4] * 10 + sp_var[5] - 533328;

    /* D means global, E means local, F means constant, N means number */
	if(sp_var[0] == 'D') {
		/* global */
		if(i_index >= 0 && i_index < VDECIMALS)
        	*dp_var = dga_decimals[i_index];
        else i_error = 1;
    }
	else if(sp_var[0] == 'E') {
		/* local */
		i_index = i_index + ig_dvstack_ct;
    	if(i_index >= 0 && i_index < VDECIMALS)
        	*dp_var = dga_decimals[i_index];
        else i_error = 1;
	}
	else if(sp_var[0] == 'F') {
		/* stored decimal literal */
		if(i_index >= 0 && i_index < VDECIMALS)
        	*dp_var = dga_decimals[i_index];
        else i_error = 1;
    }
	/* number */
	else if(sp_var[0] == 'N') *dp_var = i_index;
	else if(sp_var[0] == 'M') *dp_var = -i_index;
    else i_error = 1;

    if(i_error == 1) sub_program_error_end("bad dec var", 11);
} /* sub_fetch_decimal_pointer_dbl */


void sub_fetch_decimal_variable_lng(char *sp_var) {
/* updated 2009/03/14, 2008/02/02 */
/* 2006/03/01, 2006/02/28, 2005/11/30, 2005/07/31, 2005/03/13 */
/* 2005/03/12, 2005/02/18, 2005/02/17, 2005/02/01, 2004/12/04 */
/* 01245 */
/* D1234 */
	int i_index;
	double dz;

	/* fetch/store use sg_pass, ng_pass_lg, dg_1pass */
	/* char 48 is zero */
	/* i_index = tfni_string_to_integer(&sp_var[1], 5); */
	i_index = sp_var[1] * 10000 + sp_var[2] * 1000 + sp_var[3] * 100
    + sp_var[4] * 10 + sp_var[5] - 533328;

    /* D means global, E means local, F means constant, N means number */
	if(sp_var[0] == 'D') {
		/* global */
       	dz = dga_decimals[i_index];
    }
	else if(sp_var[0] == 'E') {
		/* local */
       	dz = dga_decimals[i_index + ig_dvstack_ct];
	}
	else if(sp_var[0] == 'F') {
		/* stored decimal literal */
       	dz = dga_decimals[i_index];
    }
	/* number */
	else if(sp_var[0] == 'N') dz = i_index;
	else if(sp_var[0] == 'M') dz = -i_index;

	/* get ng_pass_long from dz */
   	if(dz > 2147483647) dz = 2147483647;
	else if(dz < -2147483647) dz = -2147483647;

    /* 0.5 is too much for numbers close to 2^53 */
	ng_pass_long = (long)floor(dz + 0.499);
} /* sub_fetch_decimal_variable_lng */


void sub_fetch_decimal_variable_int(char *sp_var) {
/* updated 2009/03/14, 2008/02/02 */
/* 2006/03/01, 2006/02/28, 2005/11/30, 2005/07/31, 2005/03/13 */
/* 2005/03/12, 2005/02/18, 2005/02/17, 2005/02/01, 2004/12/04 */
/* 01245 */
/* D1234 */
	int i_index;
    double dz;

	/* fetch/store use sg_pass, ng_pass_lg, dg_1pass */
	/* char 48 is zero */
	/* i_index = tfni_string_to_integer(&sp_var[1], 5); */
	i_index = sp_var[1] * 10000 + sp_var[2] * 1000 + sp_var[3] * 100
    + sp_var[4] * 10 + sp_var[5] - 533328;

    /* D means global, E means local, F means constant, N means number */
	if(sp_var[0] == 'D') {
		/* global */
       	dz = dga_decimals[i_index];
    }
	else if(sp_var[0] == 'E') {
		/* local */
       	dz = dga_decimals[i_index + ig_dvstack_ct];
	}
	else if(sp_var[0] == 'F') {
		/* stored decimal literal */
       	dz = dga_decimals[i_index];
    }
	/* number */
	else if(sp_var[0] == 'N') dz = i_index;
	else if(sp_var[0] == 'M') dz = -i_index;

	/* get ig_pass_int from dz */
	if(dz > 32767) dz = 32767;
	else if(dz < -32767) dz = -32767;
    /* 0.5 is too much for numbers close to 2^53 */
	ig_pass_int = (int)floor(dz + 0.499);
} /* sub_fetch_decimal_variable_int */


void sub_store_decimal_variable(char *sp_var) {
/* updated 2009/03/14 */
/* 2008/02/02, 2005/06/08, 2005/03/12, 2005/02/01, 2004/11/27 */
/* 012345 */
/* D00001 */
	int i_index;

	/* fetch/store use sg_pass, ng_pass_lg, dg_1pass */
	/* char 48 is zero */
	/* i_index = tfni_string_to_integer(&sp_var[1], 5); */
	i_index = sp_var[1] * 10000 + sp_var[2] * 1000 + sp_var[3] * 100
    + sp_var[4] * 10 + sp_var[5] - 533328;

    /* D means global decimal, E means local decimal */
	if(sp_var[0] == 'D') {
		/* global */
    	dga_decimals[i_index] = dg_1pass;
    }
	else if(sp_var[0] == 'E') {
		/* local */
    	dga_decimals[i_index + ig_dvstack_ct] = dg_1pass;
    }
} /* sub_store_decimal_variable */


void sub_store_decimal_variable_in_link(void) {
/* updated 2009/03/14, 2008/02/10, 2008/01/07, 2007/11/10 */
/* 2007/11/06, 2005/06/08, 2005/03/12, 2005/02/01, 2004/11/27 */
/* 012345 */
/* D00001 */
    long n_index;

    /* 01234567890 */
    /* DSET E12345 */
    /* D means global decimal, E means local decimal */
    if(psg_pline[5] == 'E') n_index = ig_link_ix + ig_dvstack_ct;
    else n_index = ig_link_ix;

    dga_decimals[n_index] = dg_1pass;
} /* sub_store_decimal_variable_in_link */


void sub_fetch_string_expression_use(int ip_byte) {
/* updated 2005/12/05 */
/* 2005/12/02, 2005/07/23, 2005/07/21, 2005/07/20, 2005/06/07 */
/* 2005/04/12, 2005/03/12, 2005/02/19, 2005/02/06, 2004/11/27 */
/* evaluate string expression in psg_pline,ig_pline_lg beginning at ip_byte */
/* put string in psg_use1,ng_use1 */
/* 01234567890123 */
/* S0123+"hello there"+D0032+S0034 */
	int i_loop, i_byte;
	long n_long;
	int i_error = 2;
	char cz;

    /* tsub_make_long_string(&psg_use2, ng_use2); */
	free(psg_use1);
    psg_use1 = NULL;
    ng_use1 = 0;

	n_long = 0;
	i_byte = ip_byte;
	i_loop = 1;
	while(i_loop == 1) {
    	cz = psg_pline[i_byte];

		/* fetch/store use sg_pass, ng_pass_lg, dg_1pass */
		if(cz == 'S' || cz == 'T' || cz == 'U' || cz == 'D' || cz == 'E'
        || cz == 'F' || cz == 'C' || cz == 'N' || cz == 'M') {
			/* global string variable */
			sub_fetch_string3(i_byte, &psg_use3, &ng_use3);
			n_long = n_long + ng_use3;

            if(n_long <= MAXSTRING) {
				tsub_use_move12();
				ng_use1 = n_long;
			    tsub_make_long_string(&psg_use1, ng_use1);
				if(ng_use2 > 0) tsub_copy(psg_use1, psg_use2, ng_use2);
				tsub_copy(&psg_use1[ng_use2], psg_use3, ng_use3);

				i_byte = i_byte + 7;
			}
            else i_error = 1;
		}
		else i_loop++;

		if(i_byte >= ig_pline_lg) i_loop++;
		if(i_error == 1) i_loop++;
	}

    free(psg_use2);
    psg_use2 = NULL;
    ng_use2 = 0;

    free(psg_use3);
    psg_use3 = NULL;
	ng_use3 = 0;

    if(i_error == 1) {
		printf("length=%d\n", n_long);
    	sub_program_error_end("$expression too long", 20);
    }
} /* sub_fetch_string_expression_use */


void sub_fetch_string_pass(int ip_byte) {
/* updated 2005/12/10, 2005/12/05 */
/* 2005/11/30, 2005/06/07, 2005/06/01, 2005/03/12, 2005/02/21 */
/* fetch string in psg_pline,ig_pline_lg at ip_byte */
/* and put into sg_pass,ng_pass_lg */
/* 012345 */
/* S12345 */
	int i_index;
	int i_error = 2;
	char cz;
	/* vslong is 8096 */
	/* fetch/store use sg_pass, ng_pass_lg, dg_1pass */
	/* fetch/store use psg_use1,ng_use1, dg_1pass */
	/* char 48 is zero */

    cz = psg_pline[ip_byte];
	i_index = tfni_string_to_integer(&psg_pline[ip_byte + 1], 5);

	if(cz == 'S') {
		/* global string variable */
		if(i_index >= 0 && i_index < VSTRINGS) {
			ng_pass_lg = nga_strings_lg[i_index];
			if(ng_pass_lg <= VSLONG) {
				tsub_copy(sg_pass, psga_strings[i_index], ng_pass_lg);
			}
            else i_error = 1;
        }
        else i_error = 1;
	}
	else if(cz == 'T') {
		/* local string variable */
		i_index = i_index + ig_svstack_ct;
		if(i_index >= 0 && i_index < VSTRINGS) {
			ng_pass_lg = nga_strings_lg[i_index];
			if(ng_pass_lg <= VSLONG) {
				tsub_copy(sg_pass, psga_strings[i_index], ng_pass_lg);
			}
            else i_error = 1;
        }
        else i_error = 1;
	}
	else if(cz == 'U') {
		/* stored string literal */
		if(i_index >= 0 && i_index < VSTRINGS) {
			ng_pass_lg = nga_strings_lg[i_index];
			if(ng_pass_lg <= VSLONG) {
				tsub_copy(sg_pass, psga_strings[i_index], ng_pass_lg);
			}
            else i_error = 1;
        }
        else i_error = 1;
	}
	else if(cz == 'D') {
		/* global decimal variable */
		if(i_index >= 0 && i_index < VDECIMALS) {
			dg_1pass = dga_decimals[i_index];
			tsub_double_to_string();
		}
        else i_error = 1;
	}
	else if(cz == 'E') {
		/* local decimal variable */
		i_index = i_index + ig_dvstack_ct;
		if(i_index >= 0 && i_index < VDECIMALS) {
			dg_1pass = dga_decimals[i_index];
			tsub_double_to_string();
		}
        else i_error = 1;
	}
	else if(cz == 'F') {
		/* stored decimal literal */
		if(i_index >= 0 && i_index < VDECIMALS) {
			dg_1pass = dga_decimals[i_index];
			tsub_double_to_string();
		}
        else i_error = 1;
	}
	else if(cz == 'C') {
		/* single character literal */
		if(i_index >= 0 && i_index < 256) {
			ng_pass_lg = 1;
			sg_pass[0] = (char)i_index;
        }
        else i_error = 1;
	}
	else if(cz == 'N') {
		/* positive numeric literal */
		dg_1pass = i_index;
		tsub_double_to_string();
	}
	else if(cz == 'M') {
		/* negative numeric literal */
		dg_1pass = -i_index;
		tsub_double_to_string();
	}
	else i_error = 1;

    if(i_error == 1) sub_program_error_end("string int bad", 14);
} /* sub_fetch_string_pass */


void sub_fetch_string_byref(int ip_byte) {
/* updated 2006/10/11, 2005/12/10, 2005/12/05 */
/* 2005/11/30, 2005/06/07, 2005/06/01, 2005/03/12, 2005/02/21 */
/* fetch string in psg_pline,ig_pline_lg at ip_byte */
/* and point at with psg_byref,ng_byref or put in sg_byref */
/* 012345 */
/* S12345 */
	int i_index;
	int i_error = 2;
	char cz;
	/* vslong is 8096 */
	/* fetch/store use sg_pass, ng_pass_lg, dg_1pass */
	/* fetch/store use psg_use1,ng_use1, dg_1pass */
	/* char 48 is zero */

    ng_byref = 0;
    psg_byref = NULL;

    cz = psg_pline[ip_byte];
	i_index = tfni_string_to_integer(&psg_pline[ip_byte + 1], 5);

	if(cz == 'S') {
		/* global string variable */
		if(i_index >= 0 && i_index < VSTRINGS) {
			ng_byref = nga_strings_lg[i_index];
			if(ng_byref <= MAXSTRING) {
				psg_byref = psga_strings[i_index];
			}
            else i_error = 1;
        }
        else i_error = 1;
	}
	else if(cz == 'T') {
		/* local string variable */
		i_index = i_index + ig_svstack_ct;
		if(i_index >= 0 && i_index < VSTRINGS) {
			ng_byref = nga_strings_lg[i_index];
			if(ng_byref <= MAXSTRING) {
				psg_byref = psga_strings[i_index];
			}
            else i_error = 1;
        }
        else i_error = 1;
	}
	else if(cz == 'U') {
		/* stored string literal */
		if(i_index >= 0 && i_index < VSTRINGS) {
			ng_byref = nga_strings_lg[i_index];
			if(ng_byref <= MAXSTRING) {
				psg_byref = psga_strings[i_index];
			}
            else i_error = 1;
        }
        else i_error = 1;
	}
	else if(cz == 'D') {
		/* global decimal variable */
		if(i_index >= 0 && i_index < VDECIMALS) {
			dg_1pass = dga_decimals[i_index];
			tsub_double_to_string();
			tsub_copy(sg_byref, sg_pass, ng_pass_lg);
	        psg_byref = sg_byref;
    	    ng_byref = ng_pass_lg;
		}
        else i_error = 1;
	}
	else if(cz == 'E') {
		/* local decimal variable */
		i_index = i_index + ig_dvstack_ct;
		if(i_index >= 0 && i_index < VDECIMALS) {
			dg_1pass = dga_decimals[i_index];
			tsub_double_to_string();
			tsub_copy(sg_byref, sg_pass, ng_pass_lg);
	        psg_byref = sg_byref;
    	    ng_byref = ng_pass_lg;
		}
        else i_error = 1;
	}
	else if(cz == 'F') {
		/* stored decimal literal */
		if(i_index >= 0 && i_index < VDECIMALS) {
			dg_1pass = dga_decimals[i_index];
			tsub_double_to_string();
			tsub_copy(sg_byref, sg_pass, ng_pass_lg);
	        psg_byref = sg_byref;
    	    ng_byref = ng_pass_lg;
		}
        else i_error = 1;
	}
	else if(cz == 'C') {
		/* single character literal */
		if(i_index >= 0 && i_index < 256) {
			ng_pass_lg = 1;
			sg_byref[0] = (char)i_index;
	        psg_byref = sg_byref;
    	    ng_byref = 1;
        }
        else i_error = 1;
	}
	else if(cz == 'N') {
		/* positive numeric literal */
		dg_1pass = i_index;
		tsub_double_to_string();
		tsub_copy(sg_byref, sg_pass, ng_pass_lg);
        psg_byref = sg_byref;
        ng_byref = ng_pass_lg;
	}
	else if(cz == 'M') {
		/* negative numeric literal */
		dg_1pass = -i_index;
		tsub_double_to_string();
		tsub_copy(sg_byref, sg_pass, ng_pass_lg);
        psg_byref = sg_byref;
        ng_byref = ng_pass_lg;
	}
	else i_error = 1;

    if(i_error == 1) sub_program_error_end("string_byref bad", 16);
} /* sub_fetch_string_byref */


void sub_fetch_string3(int ip_byte, char **psp_1, long *pnp_long) {
/* updated 2005/12/05, 2005/11/30, 2005/07/21 */
/* 2005/06/26, 2005/06/07, 2005/06/01, 2005/03/12, 2005/02/21 */
/* evaluate string var_lit into *psp_1,*pnp_long at ip_byte */
/* 012345 */
/* S12345 */
	int i_index, i_beg;
	int i_error = 2;
	long n_long;
	char cz;

	/* char 48 is zero */
    cz = psg_pline[ip_byte];
	i_beg = ip_byte + 1;

	if(cz == 'S') {
		/* global string variable */
		i_index = tfni_string_to_integer(&psg_pline[i_beg], 5);

		if(i_index >= 0 && i_index < VSTRINGS) {
			n_long = nga_strings_lg[i_index];

			tsub_make_long_string(psp_1, n_long);
			tsub_copy(*psp_1, psga_strings[i_index], n_long);
			*pnp_long = n_long;
        }
        else i_error = 1;
	}
	else if(cz == 'T') {
		/* local string variable */
		i_index = tfni_string_to_integer(&psg_pline[i_beg], 5);

		i_index = i_index + ig_svstack_ct;
		if(i_index >= 0 && i_index < VSTRINGS) {
			n_long = nga_strings_lg[i_index];

			tsub_make_long_string(psp_1, n_long);
			tsub_copy(*psp_1, psga_strings[i_index], n_long);
			*pnp_long = n_long;
        }
        else i_error = 1;
	}
	else if(cz == 'U') {
		/* stored string literal */
		i_index = tfni_string_to_integer(&psg_pline[i_beg], 5);

		if(i_index >= 0 && i_index < VSTRINGS) {
			n_long = nga_strings_lg[i_index];

			tsub_make_long_string(psp_1, n_long);
			tsub_copy(*psp_1, psga_strings[i_index], n_long);
			*pnp_long = n_long;
        }
        else i_error = 1;
	}
	else if(cz == 'D') {
		/* global decimal variable */
		i_index = tfni_string_to_integer(&psg_pline[i_beg], 5);

		if(i_index >= 0 && i_index < VDECIMALS) {
			dg_1pass = dga_decimals[i_index];
			tsub_double_to_string();

			n_long = ng_pass_lg;
			tsub_make_long_string(psp_1, n_long);
			tsub_copy(*psp_1, sg_pass, n_long);
			*pnp_long = n_long;
		}
        else i_error = 1;
	}
	else if(cz == 'E') {
		/* local decimal variable */
		i_index = tfni_string_to_integer(&psg_pline[i_beg], 5);

		i_index = i_index + ig_dvstack_ct;
		if(i_index >= 0 && i_index < VDECIMALS) {
			dg_1pass = dga_decimals[i_index];
			tsub_double_to_string();

			n_long = ng_pass_lg;
			tsub_make_long_string(psp_1, n_long);
			tsub_copy(*psp_1, sg_pass, n_long);
			*pnp_long = n_long;
		}
        else i_error = 1;
	}
	else if(cz == 'F') {
		/* stored decimal literal */
		i_index = tfni_string_to_integer(&psg_pline[i_beg], 5);

		if(i_index >= 0 && i_index < VDECIMALS) {
			dg_1pass = dga_decimals[i_index];
			tsub_double_to_string();

			n_long = ng_pass_lg;
			tsub_make_long_string(psp_1, n_long);
			tsub_copy(*psp_1, sg_pass, n_long);
			*pnp_long = n_long;
		}
        else i_error = 1;
	}
	else if(cz == 'C') {
		/* single character literal */
		i_index = tfni_string_to_integer(&psg_pline[i_beg], 5);

		if(i_index >= 0 && i_index < 256) {
			tsub_make_long_string(psp_1, 5);
			*psp_1[0] = (char)i_index;
			*pnp_long = 1;
        }
        else i_error = 1;
	}
	else if(cz == 'N') {
		/* positive numeric literal */
		i_index = tfni_string_to_integer(&psg_pline[i_beg], 5);

		dg_1pass = i_index;
		tsub_double_to_string();

		n_long = ng_pass_lg;
		tsub_make_long_string(psp_1, n_long);
		tsub_copy(*psp_1, sg_pass, n_long);
		*pnp_long = n_long;
	}
	else if(cz == 'M') {
		/* negative numeric literal */
		i_index = tfni_string_to_integer(&psg_pline[i_beg], 5);

		dg_1pass = -i_index;
		tsub_double_to_string();

		n_long = ng_pass_lg;
		tsub_make_long_string(psp_1, n_long);
		tsub_copy(*psp_1, sg_pass, n_long);
		*pnp_long = n_long;
	}
	else i_error = 1;

    if(i_error == 1) sub_program_error_end("fetch str3 bad", 14);
} /* sub_fetch_string3 */


void sub_store_string3(char *sp_var, char *sp_string, long np_long) {
/* updated 2005/06/24, 2005/04/15, 2005/04/14 */
/* 2005/03/12, 2005/02/18, 2005/02/17, 2005/02/01, 2004/11/20 */
/* 012345 */
/* S12345 */
	int i_index;
    int i_error = 2;
	int i_number;

    /* the string is in psp_string,np_long */
    if(np_long > MAXSTRING) {
    	i_error = 1;
		np_long = MAXSTRING;
    }

    /* S is a global string, T is a local string */
	/* use psp_string, np_long */
	/* char 48 is zero */
	i_number = tfni_string_to_integer(&sp_var[1], 5);

	if(sp_var[0] == 'S') i_index = i_number;
	else if(sp_var[0] == 'T') i_index = i_number + ig_svstack_ct;
    else i_error = 1;

    if(i_index >= 0 && i_index < VSTRINGS) {
		/* input here is psg_use1, ng_use1 */
        tsub_make_long_string(&psga_strings[i_index], np_long);
		tsub_copy(psga_strings[i_index], sp_string, np_long);

		nga_strings_lg[i_index] = np_long;
	}
    else i_error = 1;

    if(i_error == 1) sub_program_error_end("bad use str store", 17);
} /* sub_store_string3 */


void sub_store_string_in_link(char *sp_string, long np_long) {
/* updated 2008/01/08, 2005/06/24, 2005/04/15, 2005/04/14 */
/* 2005/03/12, 2005/02/18, 2005/02/17, 2005/02/01, 2004/11/20 */
/* 012345 */
/* S12345 */
	int i_index;
    int i_error = 2;

    /* the string is in psp_string,np_long */
    if(np_long > MAXSTRING) {
    	i_error = 1;
		np_long = MAXSTRING;
    }

    /* S is a global string, T is a local string */
	if(psg_pline[5] == 'S') i_index = ig_link_ix;
	else if(psg_pline[5] == 'T') i_index = ig_link_ix + ig_svstack_ct;
    else i_error = 1;

    if(i_index >= 0 && i_index < VSTRINGS) {
		/* input here is sp_string, np_long */
        tsub_make_long_string(&psga_strings[i_index], np_long);
		tsub_copy(psga_strings[i_index], sp_string, np_long);

		nga_strings_lg[i_index] = np_long;
	}
    else i_error = 1;

    if(i_error == 1) sub_program_error_end("bad use str store", 17);
} /* sub_store_string_in_link */


/* fetch and store subroutines above */

/* program prepare subroutines below */
void sub_prep_no_spaces(void) {
/* updated 2005/12/05, 2005/09/03, 2004/12/17 */
/* remove spaces and add comma in 4 and ; at end */
	int iy, iz;
	char s_pline[200];

	if(sg_pline[4] == ' ') sg_pline[4] = ',';
	/* program line is in sg_pline with length ig_pline_lg */
	/* put semi-colon on end */
	sg_pline[ig_pline_lg] = ';';
	ig_pline_lg++;

	/* sg_pline and s_pline are 200 long */
	/* iz in index for sg_pline, iy is index for s_pline */
	for(iy = 0, iz = 0; iz < ig_pline_lg; iz++) {
        /* to copy from sg_pline to s_pline or not */
		if(sg_pline[iz] != ' ') {
			s_pline[iy] = sg_pline[iz];
			iy++;
		}
	}

	/* put back into sg_pline,100 */
	tsub_copy(sg_pline, s_pline, iy);
	ig_pline_lg = iy;
} /* sub_prep_no_spaces */


void sub_prep_split(int *ip_colon) {
/* updated 2005/03/01 */
/* find out of quotes colon */
	int i_inquotes, i_colon, iz;
	char c_quote, cz;

	/* program line is in sg_pline with length ig_pline_lg */
	i_colon = -1;
	c_quote = '"';
	i_inquotes = 2;
	for(iz = 0; iz < ig_pline_lg; iz++) {
		cz = sg_pline[iz];

		/* set i_inquotes = 1 if in quoted else 2 */
		if(i_inquotes == 2) {
			if(cz == ':') i_colon = iz;

			if(cz == '"' || cz == '#') {
				i_inquotes = 1;
				c_quote = cz;
			}
		}
		else if(cz == c_quote) i_inquotes = 2;
	}
	*ip_colon = i_colon;
} /* sub_prep_split */


void sub_prep_literal_strings(void) {
/* updated 2005/12/03, 2005/12/01 */
/* 2005/11/30, 2005/09/03, 2005/04/19, 2005/03/31, 2005/03/16 */
/* replace literal strings in sg_pline,ig_pline_lg */
	int i_byte, i_char, i_long, i_index, i_beg, i_end, iz;
    char sz[10];

	tsub_copy(sg_pass, sg_pline, ig_pline_lg);
    ng_pass_lg = ig_pline_lg;

    /* ig_smaxglobal_ct is the max of string global variables */
    /* ig_smaxliteral_ct is the count of stored literal strings */
    for(i_byte = 0; i_byte < ng_pass_lg; i_byte++) {

		if(sg_pass[i_byte] == '"' || sg_pass[i_byte] == '#') {
			i_beg = i_byte + 1;
			i_end = 0;
			for(iz = i_beg; iz < ng_pass_lg; iz++) {
				if(sg_pass[iz] == sg_pass[i_byte]) {
					i_end = iz;
					i_long = i_end - i_beg;
                    iz = ng_pass_lg;
                }
            }
			if(i_end > i_beg && i_long == 1) {
				/* one byte string */
				/* replace "A" with C00065 */
				i_char = sg_pass[i_byte + 1];
				sprintf(sz, "C%05d", i_char);
            	tsub_pass_insert(i_byte, "000", 3);
	            tsub_copy(&sg_pass[i_byte], sz, 6);

				i_end = 0;
            }
			if(i_end >= i_beg) {
				/* we have a string to store */
                ig_smaxliteral_ct++;
				i_index = ig_smaxglobal_ct + ig_smaxliteral_ct;

                if(i_index > VSTRINGS) {
                	sub_program_error_end("too many strings", 16);
                    i_end = 0;
                }
            }
			if(i_end >= i_beg) {
				/* store the string at i_index */
		        tsub_make_long_string(&psga_strings[i_index], i_long);
				tsub_copy(psga_strings[i_index], &sg_pass[i_beg], i_long);

				nga_strings_lg[i_index] = i_long;

				/* replace the string with U00000 */
				tsub_pass_delete(i_byte, i_long + 2);
				sprintf(sz, "U%05d", i_index);
				tsub_pass_insert(i_byte, sz, 6);
			}
        }
    }

    tsub_copy(sg_pline, sg_pass, ng_pass_lg);
    ig_pline_lg = ng_pass_lg;
} /* sub_prep_literal_strings */


void sub_prep_variables_str(char *ps_vars, int *pi_vars_lg) {
/* updated 2005/10/29, 2005/09/03 */
/* 2005/02/07, 2005/02/06, 2005/02/05, 2005/01/30, 2004/12/18 */
/* prep variables for string variables */
/* program line is in sg_pline,ig_pline_lg */
	int i_long, i_byte, ix, iy, iz;
	int i_inquotes, i_vari_pline, i_vars_lg;
	int i_typevar;
	int i_action;
	char s_var[65];
	char c_quote, c_z;
	int i_var_string;
	char s_var_string[10];

    /* ps_vars has the variable names in it csv */
    /* pi_vars_lg and i_vars_lg have the length of ps_vars */
	/* put value of *pi_vars_lg into i_vars_lg */
	i_vars_lg = *pi_vars_lg;

    /* program line is in sg_pline,ig_pline_lg */
	i_action = 1;

    /* do we have an ENDS line */
    if(tfni_compare_strings(sg_pline, "ENDS", 4) == 0) i_action = 200;

	/* do we have a VARI line to define variables */
	if(tfni_compare_strings(sg_pline, "VARI", 4) == 0) i_vari_pline = 1;
	else i_vari_pline = 2;

	c_quote = '"';
	i_inquotes = 2;
    i_byte = 5;
    if(i_action > 20) i_byte = 1000;

	for(; i_byte < ig_pline_lg; i_byte++) {
		if(i_inquotes == 1) {
			/* leaving inquotes */
			if(sg_pline[i_byte] == c_quote) i_inquotes = 2;
		}
		else if(sg_pline[i_byte] == '"' || sg_pline[i_byte] == '#') {
			/* entering inquotes */
			i_inquotes = 1;
			c_quote = sg_pline[i_byte];
		}

		if(i_inquotes != 1) {
			/* we are not inquotes */
			/* do we have either a global or local decimal */
			i_typevar = 0;
			if(tfni_compare_strings(&sg_pline[i_byte], "SG_", 3) == 0) {
				i_typevar = 1;
            }
            else if(tfni_compare_strings(&sg_pline[i_byte], "S_", 2) == 0) {
            	i_typevar = 2;
            }
			if(i_typevar > 0) {
				/* find end of variable */
				if(i_typevar == 1) iy = i_byte + 3;
                else iy = i_byte + 2;

				for(ix = 1; ix == 1; iy++) {
					/* must be letters or numbers */
					c_z = sg_pline[iy];
					ix = 2;
					if(c_z >= 'A' && c_z <= 'Z') ix = 1;
					else if(c_z >= '0' && c_z <= '9') ix = 1;
				}

                /* get new variable into s_var,i_long */
				i_long = iy - i_byte - 1;
				if(i_long > 64) i_long = 64;
				tsub_copy(s_var, &sg_pline[i_byte], i_long);

				/* variable in s_var begins at i_byte for i_long */
				if(i_vari_pline == 1) {
					/* vari line */
					/* globals begin with a colon, locals with a comma */
					if(i_typevar == 1) ps_vars[i_vars_lg] = ':';
                    else ps_vars[i_vars_lg] = ',';
					i_vars_lg++;

                    /* variable is in s_var,i_long */
                    /* do we have variable overlap in ps_vars,i_vars_lg */
					sub_program_variable_overlap(s_var, i_long,
                    ps_vars, i_vars_lg);

					/* add new variable to ps_vars,pi_vars_lg csv */
					tsub_copy(&ps_vars[i_vars_lg], s_var, i_long);
					i_vars_lg = i_vars_lg + i_long;
				}
				else {
					/* non vari line */
					/* is this variable in ps_vars,pi_vars_lg */
					ix = tfnn_string_lookup(ps_vars, i_vars_lg,
                    s_var, i_long);

                    /* is the end really the end in ps_var */
					c_z = ps_vars[ix + i_long];
                    if(c_z != ':' && c_z != ',' && c_z != ' ') ix = -1;

					if(ix >= 0) {
						/* we have this variable */
						if(i_typevar == 1) {
							/* global variable */
		                    /* how many colons to determine i_var_string */
							i_var_string = 0;
    	                    for(iz = 0; iz < ix; iz++) {
								if(ps_vars[iz] == ':') i_var_string++;
            	            }

							/* global make S12345 string of i_var_string */
	                        sprintf(s_var_string, "S%05d", i_var_string);
						}
						else {
							/* local variable */
		                    /* how many commas to determine i_var_string */
							i_var_string = 0;
    	                    for(iz = 0; iz < ix; iz++) {
								if(ps_vars[iz] == ',') i_var_string++;
            	            }

							/* local make T12345 string of i_var_string */
    	                    sprintf(s_var_string, "T%05d", i_var_string);
						}

                        /* replace s_var in sg_pline,ig_pline_lg with */
						tsub_copy(sg_pass, sg_pline, ig_pline_lg);
						ng_pass_lg = ig_pline_lg;

                        tsub_pass_delete(i_byte, i_long);
                        tsub_pass_insert(i_byte, s_var_string, 6);

                        tsub_copy(sg_pline, sg_pass, ng_pass_lg);
						ig_pline_lg = ng_pass_lg;
                    }
				}
			}
		}
	}

    if(i_action == 200) {
		/* we have an ENDS line and must blank local variables */
		/* find first comma and blank from there on */
		iy = -1;
        for(iz = 0; iz < i_vars_lg && iy == -1; iz++) {
        	if(ps_vars[iz] == ',') iy = iz;
		}

        if(iy > -1) {
        	for(iz = iy; iz < VCHARNAME; iz++) ps_vars[iz] = ' ';
			i_vars_lg = iy;
        }
    }

	/* put i_vars_lg into *pi_vars_lg */
	*pi_vars_lg = i_vars_lg;
} /* sub_prep_variables_str */


void sub_prep_variables_dec(char *ps_vars, int *pi_vars_lg) {
/* updated 2005/10/29, 2005/09/03 */
/* 2005/03/12, 2005/02/06, 2005/02/05, 2005/01/30, 2004/12/18 */
/* prep variables for decimal variables */
/* program line is in sg_pline,ig_pline_lg */
	int i_long, i_byte, ix, iy, iz;
	int i_inquotes, i_vari_pline, i_vars_lg;
	int i_typevar;
	int i_action;
	char s_var[65];
	char c_quote, c_z;
	int i_var_decimal;
	char s_var_decimal[10];

    /* ps_vars has the variable names in it csv */
    /* pi_vars_lg and i_vars_lg have the length of ps_vars */
	/* put value of *pi_vars_lg into i_vars_lg */
	i_vars_lg = *pi_vars_lg;

    /* program line is in sg_pline,ig_pline_lg */
	i_action = 1;

    /* do we have an ENDS line */
    if(tfni_compare_strings(sg_pline, "ENDS", 4) == 0) i_action = 200;

	/* do we have a VARI line to define variables */
	if(tfni_compare_strings(sg_pline, "VARI", 4) == 0) i_vari_pline = 1;
	else i_vari_pline = 2;

	c_quote = '"';
	i_inquotes = 2;
    i_byte = 5;
    if(i_action > 20) i_byte = 1000;

	for(; i_byte < ig_pline_lg; i_byte++) {
		if(i_inquotes == 1) {
			/* leaving inquotes */
			if(sg_pline[i_byte] == c_quote) i_inquotes = 2;
		}
		else if(sg_pline[i_byte] == '"' || sg_pline[i_byte] == '#') {
			/* entering inquotes */
			i_inquotes = 1;
			c_quote = sg_pline[i_byte];
		}

		if(i_inquotes != 1) {
			/* we are not inquotes */
			/* do we have either a global or local decimal */
			i_typevar = 0;
			if(tfni_compare_strings(&sg_pline[i_byte], "DG_", 3) == 0) {
				i_typevar = 1;
            }
            else if(tfni_compare_strings(&sg_pline[i_byte], "D_", 2) == 0) {
            	i_typevar = 2;
            }
			if(i_typevar > 0) {
				/* find end of variable */
				if(i_typevar == 1) iy = i_byte + 3;
                else iy = i_byte + 2;

				for(ix = 1; ix == 1; iy++) {
					/* must be letters or numbers */
					c_z = sg_pline[iy];
					ix = 2;
					if(c_z >= 'A' && c_z <= 'Z') ix = 1;
					else if(c_z >= '0' && c_z <= '9') ix = 1;
				}

                /* get new variable into s_var,i_long */
				i_long = iy - i_byte - 1;
				if(i_long > 64) i_long = 64;
				tsub_copy(s_var, &sg_pline[i_byte], i_long);

				/* variable begins in s_var at i_byte for i_long */
				if(i_vari_pline == 1) {
					/* vari line */
					/* globals begin with a colon, locals with a comma */
					if(i_typevar == 1) ps_vars[i_vars_lg] = ':';
                    else ps_vars[i_vars_lg] = ',';
					i_vars_lg++;

                    /* variable is in s_var,i_long */
                    /* do we have variable overlap in ps_vars,i_vars_lg */
					sub_program_variable_overlap(s_var, i_long,
                    ps_vars, i_vars_lg);

					/* add new variable to ps_vars,pi_vars_lg csv */
					tsub_copy(&ps_vars[i_vars_lg], s_var, i_long);
					i_vars_lg = i_vars_lg + i_long;
				}
				else {
					/* non vari line */
					/* is this variable in ps_vars,pi_vars_lg */
					ix = tfnn_string_lookup(ps_vars, i_vars_lg,
                    s_var, i_long);

                    /* is the end really the end in ps_vars */
					c_z = ps_vars[ix + i_long];
                    if(c_z != ':' && c_z != ',' && c_z != ' ') ix = -1;

					if(ix >= 0) {
						/* we have this variable */
						if(i_typevar == 1) {
							/* global variable */
		                    /* how many colons to determine i_var_decimal */
							i_var_decimal = 0;
    	                    for(iz = 0; iz < ix; iz++) {
								if(ps_vars[iz] == ':') i_var_decimal++;
            	            }

							/* global make D12345 string of i_var_decimal */
	                        sprintf(s_var_decimal, "D%05d", i_var_decimal);
						}
						else {
							/* local variable */
		                    /* how many commas to determine i_var_decimal */
							i_var_decimal = 0;
    	                    for(iz = 0; iz < ix; iz++) {
								if(ps_vars[iz] == ',') i_var_decimal++;
            	            }

							/* local make E12345 string of i_var_decimal */
    	                    sprintf(s_var_decimal, "E%05d", i_var_decimal);
						}

                        /* replace s_var in sg_pline,ig_pline_lg with */
						tsub_copy(sg_pass, sg_pline, ig_pline_lg);
						ng_pass_lg = ig_pline_lg;

                        tsub_pass_delete(i_byte, i_long);
                        tsub_pass_insert(i_byte, s_var_decimal, 6);

                        tsub_copy(sg_pline, sg_pass, ng_pass_lg);
						ig_pline_lg = ng_pass_lg;
                    }
				}
			}
		}
	}

    if(i_action == 200) {
		/* we have an ENDS line and must blank local variables */
		/* find first comma and blank from there on */
		iy = -1;
        for(iz = 0; iz < i_vars_lg && iy == -1; iz++) {
        	if(ps_vars[iz] == ',') iy = iz;
		}

        if(iy > -1) {
        	for(iz = iy; iz < VCHARNAME; iz++) ps_vars[iz] = ' ';
			i_vars_lg = iy;
        }
    }

	/* put i_vars_lg into *pi_vars_lg */
	*pi_vars_lg = i_vars_lg;
} /* sub_prep_variables_dec */


void sub_program_variable_overlap(char *sp1, int ip1, char *sp2, int ip2) {
/* updated 2005/10/29 */
/* compare var in sp1 against : or , delimited variables in sp2 */
	int i_byte, iy, iz;
    int i_error = 2;

    /* 1 is a find, 2 is a no find */
    for(iy = 1, i_byte = 0; iy == 1 && i_byte < ip2; i_byte++) {
		if(sp1[0] == sp2[i_byte]
        && sp1[1] == sp2[i_byte + 1]
        && sp1[2] == sp2[i_byte + 2]
        && sp1[3] == sp2[i_byte + 3]) {
			for(iz = 4; iz < ip1; iz++) {
				if(sp1[iz] != sp2[i_byte + iz]) {
                    if(sp2[i_byte + iz] == ','
                    || sp2[i_byte + iz] == ':') {
						i_error = 1;
                        iy = i_byte;
                    }
					else iz = 1000;
                }
                else if(iz == (ip1 - 1)) {
					i_error = 1;
                    iy = i_byte;
                }
            }
        }
    }

	if(i_error == 1) {
		/* line is not in program array yet */
		tsub_out79(sp1, ip1);
		tsub_out79(&sp2[iy], 12);
		tsub_show_pline(ig_pline_ix, sg_pline, ig_pline_lg);
	    tsub_out79("var overlap", 11);
		tsub_inp79();

	    ig_exit = 1;
    }
} /* sub_program_variable_overlap */


void sub_prep_evar(int pi_type,
char *ps_pline, char *ps_vars, int pi_vars_lg) {
/* updated 2005/09/03, 2005/03/12, 2005/02/06 */
/* we have an EVAR line, how many colons */
/* pi_type=1 means local, pi_type=2 means global */
/* 012345678901234567
/* EVAR N12345,N12345 */
	int iy, iz;
	char s_count[10];

    if(pi_type == 1) {
		/* local */
		iy = 0;
    	for(iz = 0; iz < pi_vars_lg; iz++) if(ps_vars[iz] == ',') iy++;
    }
	else {
		/* global */
		iy = 0;
    	for(iz = 0; iz < pi_vars_lg; iz++) if(ps_vars[iz] == ':') iy++;
    }

	sprintf(s_count, "%05d", iy);

    if(ps_vars[1] == 'D') tsub_copy(&ps_pline[6], s_count, 5);
	else tsub_copy(&ps_pline[13], s_count, 5);
} /* sub_prep_evar */


void sub_prep_format1(void) {
/* updated 2005/09/03, 2005/02/13 */
/* prep the format of sg_pline,ig_pline_lg */
/* put in DSET,$SET,ESUB if needed */
	int iz;

    /* copy to sg_pass,ng_pass_lg */
    tsub_copy(sg_pass, sg_pline, ig_pline_lg);
    ng_pass_lg = ig_pline_lg;

    /* insert DSET, if needed */
    iz = tfni_compare_strings(sg_pass, "DG_", 3);
    if(iz != 0) iz = tfni_compare_strings(sg_pass, "D_", 2);
    if(iz == 0) tsub_pass_insert(0, "DSET,", 5);

    /* insert $SET, if needed */
    iz = tfni_compare_strings(sg_pass, "SG_", 3);
    if(iz != 0) iz = tfni_compare_strings(sg_pass, "S_", 2);
    if(iz == 0) tsub_pass_insert(0, "$SET,", 5);

    /* insert ESUB, if needed */
    iz = tfni_compare_strings(sg_pass, "SUB_", 4);
    if(iz == 0) tsub_pass_insert(0, "ESUB,", 5);

    /* copy sg_pass,ng_pass_lg to sg_pline,ig_pline_lg */
    tsub_copy(sg_pline, sg_pass, ng_pass_lg);
    ig_pline_lg = ng_pass_lg;
} /* sub_prep_format1 */


void sub_prep_format2(void) {
/* updated 2005/09/03, 2005/03/12, 2005/03/01, 2005/02/27, 2005/02/13 */
/* prep the format of sg_pline,ig_pline_lg */
/* put + in DSET and make compare two bytes in DIFT,$IFT */
	int iz;
	char cz;

    /* copy to sg_pass,ng_pass_lg */
    tsub_copy(sg_pass, sg_pline, ig_pline_lg);
    ng_pass_lg = ig_pline_lg;

    /* insert a + in a DSET, command */
    if(tfni_compare_strings(sg_pass, "DSET,", 5) == 0) {
        /* do we need a plus sign after the = */
		/* 012345678901234567 */
        /* DSET,D00001=N00001 */
        if(sg_pass[12] != '+' && sg_pass[12] != '-')
           	tsub_pass_insert(12, "+", 1);
    }

    /* make the compare two bytes in DWHI,$WHI,DIFT,$IFT */
    iz = tfni_compare_strings(sg_pass, "DIFT,", 5);
    if(iz != 0) iz =tfni_compare_strings(sg_pass, "DIF1,", 5);
    if(iz != 0) iz =tfni_compare_strings(sg_pass, "DWHI,", 5);
    if(iz != 0) iz =tfni_compare_strings(sg_pass, "DBAD,", 5);
    if(iz != 0) iz =tfni_compare_strings(sg_pass, "$IFT,", 5);
    if(iz != 0) iz =tfni_compare_strings(sg_pass, "$IF1,", 5);
    if(iz != 0) iz =tfni_compare_strings(sg_pass, "$WHI,", 5);
	if(iz == 0) {
        /* do we need a second byte to the compare */
		/* 012345678901234567 */
        /* DIFT,D12345=N12345 */
		/* ==,>=,<=,<>,<<,>> */
		cz = sg_pass[12];
        if(cz != '=' && cz != '<' && cz != '>') {
			tsub_pass_insert(12, " ", 1);
            sg_pass[12] = sg_pass[11];
        }
    }

    /* copy sg_pass,ng_pass_lg to sg_pline,ig_pline_lg */
    tsub_copy(sg_pline, sg_pass, ng_pass_lg);
    ig_pline_lg = ng_pass_lg;
} /* sub_prep_format2 */


void sub_prep_literal_numbers(void) {
/* updated 2005/12/03, 2005/09/03, 2005/03/13, 2005/03/12, 2005/02/12 */
/* prep or store literal numbers in sg_pline,ig_pline_lg */
/* change 1 to N0001 */
	int i_action, i_byte, i_long, i_decimal;
    int i_prev, i_pprev, iz;
	int i_index = 0;
	char c_prev, c_pprev, c_byte, c_char;
	char sz[10];
	double d_number;

    /* copy sg_pline,ig_pline_lg to sg_pass,ng_pass_lg */
    tsub_copy(sg_pass, sg_pline, ig_pline_lg);
    ng_pass_lg = ig_pline_lg;


	for(i_byte = 0; i_byte < ng_pass_lg; i_byte++) {
		i_action = 1;

		if(i_action == 1) {
			/* not inquotes */
			i_prev = i_byte - 1;
			i_pprev = i_byte - 2;
			c_prev = sg_pass[i_prev];
			c_pprev = sg_pass[i_pprev];
			c_byte = sg_pass[i_byte];

			/* prev cannot be a number, letter, underline or decimal */
        	if(c_prev >= '0' && c_prev <= '9') i_action = 0;
	        if(c_prev >= 'A' && c_prev <= 'Z') i_action = 0;
			if(c_prev == '_') i_action = 0;
			if(c_prev == '.') i_action = 0;

			/* current i_byte must be a number */
			if(c_byte < '0' || c_byte > '9') i_action = 0;
		}
        if(i_action == 1) {
			/* how long is the number and is there a decimal */
			d_number = 0;
			i_decimal = -5;
			i_long = 0;

        	for(iz = i_byte; iz < ng_pass_lg; iz++) {
				c_char = sg_pass[iz];

                if(c_char >= '0' && c_char <= '9') {
					d_number = d_number * 10 + c_char - 48;
                    if(i_decimal != -5) i_decimal++;
	            	i_long++;
                }
				else if(c_char == '.') {
					if(i_decimal != -5) i_action = 0;
	            	i_long++;
					i_decimal = 0;
                }
				else iz = ng_pass_lg;
            }

            for(iz = 0; iz < i_decimal; iz++) d_number = d_number / 10;

            if(i_long <= 5 && i_decimal == -5) i_action = 2;
			if(i_long > 5 || i_decimal != -5) i_action = 3;
		}
		if(i_action == 2) {
			/* reformat the number to N12345 */
            /* insert into sg_pass */
			tsub_pass_insert(i_byte, "N00000", 6 - i_long);

            /* should it be M instead of N to mean negative */
            if(c_prev == '-' || c_prev == '+') {
				/* there must be some operator just previous */
				iz = tfnn_string_char_search(",=<>+-*/\%", 10, c_pprev);
				if(iz >= 0) {
					tsub_pass_delete(i_prev, 1);
                    i_byte--;
                    if(c_prev== '-') sg_pass[i_byte] = 'M';
                }
            }
        }

		if(i_action == 3) {
			/* we have a decimal number to store */
            ig_dmaxliteral_ct++;
			i_index = ig_dmaxglobal_ct + ig_dmaxliteral_ct;

            if(i_index > VDECIMALS) {
               	sub_program_error_end("too many numbers", 16);
                i_action = 9;
            }
		}
        if(i_action == 3) {
            /* is our decimal number negative */
            if(c_prev == '-' || c_prev == '+') {
				/* there must be some operator just previous */
				iz = tfnn_string_char_search(",=<>+-*/\%", 10, c_pprev);
				if(iz >= 0) {
					tsub_pass_delete(i_prev, 1);
                    i_byte--;
                    if(c_prev== '-') d_number = -d_number;
                }
            }
			/* store the decimal number at i_index */
			dga_decimals[i_index] = d_number;

			/* replace the string with F00000 */
			tsub_pass_delete(i_byte, i_long);
			sprintf(sz, "F%05d", i_index);
			tsub_pass_insert(i_byte, sz, 6);
        }
    }

    /* put the pline back into sg_pline,ig_pline_lg */
	tsub_copy(sg_pline, sg_pass, ng_pass_lg);
    ig_pline_lg = ng_pass_lg;
} /* sub_prep_literal_numbers */
/* program prepare subroutines above */

/* utility subroutines below */
int tfni_char_type(char cp_1) {
/* updated 2009/11/01, 2005/03/25 */
/* long */
	int i_type;
/*
    Case pi_char of
        0 .. 31 : i_result := 1;
        32      : i_result := 2;
        33 .. 47 : i_result := 3;
        48 .. 57 : i_result := 4;
        58 .. 64 : i_result := 3;
        65 .. 90 : i_result := 5;
        91 .. 96 : i_result := 3;
        97 .. 122 : i_result := 6;
        123 .. 126 : i_result := 3;
    else
        i_result := 7;
    end;
*/
	if(cp_1 <= 31) i_type = 1;        /* escape characters */
    else if(cp_1 == 32) i_type = 2;   /* the space */
    else if(cp_1 <= 47) i_type = 3;   /* punctuation etc */
    else if(cp_1 <= 57) i_type = 4;   /* numbers */
    else if(cp_1 <= 64) i_type = 3;   /* punctuation etc */
    else if(cp_1 <= 90) i_type = 5;   /* upper case */
    else if(cp_1 <= 96) i_type = 3;   /* punctuation etc */
    else if(cp_1 <= 122) i_type = 6;  /* lower case */
    else if(cp_1 <= 126) i_type = 3;  /* punctuation etc */
    else i_type = 7;                  /* greater than 126 */

    return i_type;
} /* tfni_char_type */


int tfni_is_digits(char *sp1, int ip_long) {
/* updated 2005/08/06 */
	int i_result = 1;
    int iz;

    for(iz = 0; i_result == 1 && iz < ip_long; iz++) {
		if(sp1[iz] < '0' || sp1[iz] > '9') i_result++;
    }

    return i_result;
} /* tfni_is_digits */


int tfni_compare_strings(char *sp1, char *sp2, long np_long) {
/* updated 2005/07/24, 2005/05/10, 2004/11/13 */
/* long */
/* compare strings sp1>sp2=1,sp1<sp2=-1,sp1=sp2=0 */
	int i_result = 0;
    long nz;

	for(nz = 0; nz < np_long && i_result == 0; nz++) {
		if(sp1[nz] < sp2[nz]) i_result = -1;
		else if(sp1[nz] > sp2[nz]) i_result = 1;
	}

	return i_result;
} /* tfni_compare_strings */


long tfnn_string_lookup(char *sp1, long np1, char *sp2, long np2) {
/* updated 2004/12/13 */
/* long */
/* look up sp2 for length ip2 in sp1 for length ip1 */
	int i_loop, i_test;
    long n_return, nx, nz;

	n_return = -1;
	nz = 0;
	i_loop = 1;
	if(np2 > np1) i_loop++;
	if(np1 == 0 || np2 == 0) i_loop++;

	while(i_loop == 1) {
		if(sp1[nz] == sp2[0]) {
			for(i_test = 1, nx = 1; i_test == 1 && nx < np2; nx++)
				if(sp1[nz + nx] != sp2[nx]) i_test++;
			if(i_test == 1) n_return = nz;
		}

		nz++;
		if(nz > (np1 - np2)) i_loop++;
	}

	return n_return;
} /* tfnn_string_lookup */


long tfnn_string_char_search(char *sp1, long np_long, char cp1) {
/* updated 2005/05/10, 2005/03/13, 2004/12/13 */
/* long */
	long ny, nz;

	for(ny = -1, nz = 0; ny == -1 && nz < np_long; nz++) {
		if(sp1[nz] == cp1) ny = nz;
	}
	return ny;
} /* tfni_string_char_search */


int tfni_string_to_integer(char *sp1, int ip_long) {
/* updated 2005/02/17, 2004/11/14 */
/* long */
	int iy, iz;
	int i_integer = 0;
	int i_error = 2;

	for(iz = 0; iz < ip_long; iz++) {
		/* 0 is 48, 9 is 57 */
		iy = sp1[iz] - 48;
		if(iy >= 0 && iy <= 9) i_integer = i_integer * 10 + iy;
		else i_error = 1;
	}

    if(i_error == 1) {
		tsub_out79(sp1, ip_long);
		sub_program_error_end("bad variable int", 16);
        i_integer = 0;
    }

	return i_integer;
} /* tfni_string_to_integer */


long tfnn_hash(char *sp1, int ip_long) {
/* updated 2007/04/10, 2005/02/08 */
/* to change a string into a fairly unique number */
/* the string is a subr identifier or a tag identifier */
	int iz;
    long n_hash = 0;
    long n_value, n_char;

    for(iz = 0; iz < ip_long; iz++) {
		/* 48 to 57 is 0 thru 9 */
        /* 65 to 90 is A thru Z, _ is 95 */
		n_char = sp1[iz];

        n_value = 0;
        if(n_char >= 48 && n_char <= 95) n_value = n_char * n_char * n_char;
		n_hash = n_hash * 2 + n_value;

		/* one billion */
		if(n_hash > 1000000000) n_hash = n_hash - 1000000000;
    }

    return n_hash;
} /* tfnn_hash */


void tsub_string_to_double(char *sp1, int ip_long) {
/* updated 2005/02/19, 2004/11/30 */
/* long */
	double d_double = 0;
	int i_good = 1;
    int i_commas = 0;
    int i_decimal = -1;
    int i_negative = 2;
	int i_numbers = 0;
    int i_beg, i_end, iz;

    /* trim right blanks */
    for(i_end = ip_long - 1; i_end > 0 && sp1[i_end] == ' '; i_end--);
    ip_long = i_end + 1;

    /* trim left blanks */
    for(i_beg = 0; i_beg < ip_long && sp1[i_beg] == ' '; i_beg++);

	if(ip_long < 1) i_good++;

	iz = i_beg;

    if(i_good == 1) {
		if(sp1[0] == '-') {
			i_negative = 1;
			iz = 1;
		} else if(sp1[0] == '+') iz = 1;
		if(iz >= ip_long) i_good++;
	}

    if(i_good == 1) {
		for(; iz < ip_long; iz++) {
			if(sp1[iz] >= '0' && sp1[iz] <= '9') {
				/* we do have a number */
				i_numbers++;

				/* zero is 48 */
				d_double = d_double * 10 + sp1[iz] - 48;
				if(i_decimal >= 0) i_decimal++;
			}
            else {
				/* we do not have a number */
				if(sp1[iz] == '.') i_decimal = 0;
				else if(sp1[iz] == ',') i_commas++;
				else i_good++;
			}
		}
		if(i_commas > 6) i_good++;
		if(i_numbers == 0) i_good++;
	}

    if(i_good == 1) {
		/* put decimal in correctly */
		for(iz = 0; iz < i_decimal; iz++) d_double = d_double / 10;

		if(i_negative == 1) d_double = - d_double;
	}

	ig_pass_int = i_good;
	dg_1pass = d_double;
} /* tsub_string_to_double */


void tsub_timeline(void) {
/* updated 2009/07/05 */
	struct tm *ptr_tm;
	time_t t_time_t;
	char sz[80];
	int iz;

	/* 01234567890123456789012345678901234 */
	/* Sun Nov 28 19:10:06 2004 */
	/* 20-NOV-2004 19:10:06 20041120191006 */
	t_time_t = time(NULL);
	ptr_tm = localtime(&t_time_t);
	sprintf(sz, "%s", asctime(ptr_tm));
    if(sz[8] == ' ') sz[8] = '0';
    if(sz[11] == ' ') sz[11] = '0';
    if(sz[14] == ' ') sz[14] = '0';
    if(sz[17] == ' ') sz[17] = '0';

	tsub_blank(sg_pass, 40);
	tsub_copy(sg_pass, &sz[8], 2);
	sg_pass[2] = '-';
	tsub_copy(&sg_pass[3], &sz[4], 3);
	sg_pass[6] = '-';
	tsub_copy(&sg_pass[7], &sz[20], 4);
	tsub_copy(&sg_pass[12], &sz[11], 8);
	tsub_case_upper(sg_pass, 20);

	tsub_copy(&sg_pass[21], &sz[20], 4);
	iz = ptr_tm->tm_mon + 1;
	sprintf(&sz[41], "%2d", iz);
	if(sz[41] == ' ') sz[41] = '0';
	tsub_copy(&sg_pass[25], &sz[41], 2);
    tsub_copy(&sg_pass[27], &sz[8], 2);
    tsub_copy(&sg_pass[29], &sz[11], 2);
    tsub_copy(&sg_pass[31], &sz[14], 2);
    tsub_copy(&sg_pass[33], &sz[17], 2);

	ng_pass_lg = 35;
    /* string is in sg_pass,ng_pass_lg */

} /* void tsub_timeline(char *sp1, int ip_long) */


void tsub_blank(char *sp1, long np_long) {
/* updated 2005/05/10, 2004/11/13 */
/* long */
	long nz;

	for(nz = 0; nz < np_long; nz++) sp1[nz] = ' ';
} /* tsub_blank */


void tsub_blank_escapes(char *sp1, long np_long) {
/* updated 2005/05/10, 2004/11/13 */
/* long */
	long nz;

	for(nz = 0; nz < np_long; nz++) if(sp1[nz] < 32) sp1[nz] = 32;
} /* tsub_blank_escapes */


void tsub_bug(char *sp1) {
/* updated 2005/05/11 */
	char sz[20];

	puts(sp1);
	fgets(sz, 10, stdin);
} /* void tsub_bug */


void tsub_case_lower(char *sp1, long np_long) {
/* updated 2005/05/10, 2004/11/14 */
/* long */
	char cz;
	long nz;

	for(nz = 0; nz < np_long; nz++) {
		cz = sp1[nz];
		if(cz >= 'A' && cz <= 'Z') sp1[nz] = (char)(cz + 32);
	}
} /* tsub_case_lower */


void tsub_case_upper(char *sp1, long np_long) {
/* updated 2005/05/10, 2005/02/21 */
/* long */
	char cz;
	long nz;

	for(nz = 0; nz < np_long; nz++) {
		cz = sp1[nz];
		if(cz >= 'a' && cz <= 'z') sp1[nz] = (char)(cz - 32);
	}
} /* tsub_case_upper */


void tsub_copy(char *sp1, char *sp2, long np_long) {
/* updated 2005/05/10, 2005/02/09, 2004/11/13 */
/* long */
/* copy from sp2 to sp1 for length np_long */
	long nz;

	for(nz = 0; nz < np_long; nz++) sp1[nz] = sp2[nz];
} /* tsub_copy */


void tsub_debug(void) {
/* updated 2009/07/10, 2008/01/29, 2005/11/27, 2005/11/23, 2004/11/21 */
	int i_loop, iz;

	i_loop = 1;
	while(i_loop == 1) {
        /* dg_plines_done is how many lines were run */
        /* dg_plines_done++; */

		/* get the command number into i_command */
		/* i_command = iga_link_commands[ig_pline_ix]; */

        /* get the line sg_pline,ig_pline_lg from index ig_pline_ix */
		ig_pline_lg = iga_plines_lg[ig_pline_ix];

        /* tsub_copy(sg_pline, psga_plines[ig_pline_ix], ig_pline_lg); */
        /* psg_pline = psga_plines[ig_pline_ix]; */

		/* get the link for this line */
		ig_link_ix = iga_links[ig_pline_ix];

        /* show the current line */
    	tsub_show_pline_by_index(ig_pline_ix);

        /* show line index, length and link */
printf("ig_pline_ix=%d, ig_pline_lg=%d, ig_link_ix=%d, lines=%0.0f\n",
ig_pline_ix, ig_pline_lg, ig_link_ix, dg_plines_done);

        /* show decimal and string stack counts */
        printf("ig_dvstack_ct=%d, ig_svstack_ct=%d\n",
        ig_dvstack_ct, ig_svstack_ct);

        /* show decimal and string stack values */
        printf("iga_dvstack[]=%d, iga_svstack[]=%d\n",
        iga_dvstack[ig_dvstack_ix], iga_svstack[ig_dvstack_ix]);

        /* get timeline into sg_pass,ng_pass_lg */
        tsub_timeline();
        tsub_out79(sg_pass, ng_pass_lg);

		i_loop++;

        puts("1=strings, 2=decimals, debug=debug off");
       	puts("return, exit=exit prog");

        /* get terminal input */
        tsub_inp79();
		tsub_blank_escapes(sg_inp79, 80);
		tsub_case_upper(sg_inp79, 80);

		if(tfni_compare_strings(sg_inp79, "DEBUG", 5) == 0) {
			ig_debug++;
		}

		if(tfni_compare_strings(sg_inp79, "EXIT", 4) == 0) {
        	ig_exit = 1;
        }

		if(ng_inp79_long == 1) {
			i_loop = 1;

			for(iz = 0; iz < 10; iz++) {
				tsub_show_vstring_info(ng_inp79_long + iz);
			}
        }

        if(ng_inp79_long == 2) {
            i_loop = 1;

            for(iz = 0; iz < 10; iz++) {
                tsub_show_vdecimal_info(ig_dvstack_ct + iz);
            }
        }
 	}
} /* tsub_debug */


void tsub_double_to_string(void) {
/* updated 2006/05/20 */
/* 2006/05/02, 2006/05/01, 2005/05/11, 2005/04/13, 2004/11/27 */
/* put dg_1pass into sg_pass, ng_pass_lg */
	int iz;

    tsub_blank(sg_pass, 40);

    if(dg_1pass > pow(10, 16)) {
		/* if number greater than 10E16 */
		ng_pass_lg = sprintf(sg_pass, "%.15E", dg_1pass);
    }
	else {
		/* default is six beyond decimal */
		ng_pass_lg = sprintf(sg_pass, "%f", dg_1pass);

		/* eliminate trailing zeros */
		for(iz = ng_pass_lg - 1; sg_pass[iz] == '0'; iz--);

		/* eliminate trailing decimal */
		if(sg_pass[iz] == '.') iz--;

		ng_pass_lg = iz + 1;
   	}
} /* tsub_double_to_string */


void tsub_inp79(void) {
/* updated 2005/03/13, 2005/02/23, 2004/12/11 */
/* long */
/* get screen input into sg_inp79,ig_inp79_lg,ng_inp79_long */
	char sz[80], cz;
	int iy, iz;

    ng_inp79_long = 0;
	tsub_blank(sg_inp79, 79);
	fgets(sz, 79, stdin);

	for(iy = 0, iz = 0; iz < 79; iz++) {
		cz = sz[iz];

		if(cz != 0) {
			sg_inp79[iz] = cz;
			iy = iz;

            if(cz >= '0' && cz <= '9')
            	ng_inp79_long = ng_inp79_long * 10 + cz - 48;
		}
		else iz = 99;
	}

	ig_inp79_lg = iy;
	tsub_blank_escapes(sg_inp79, ig_inp79_lg);
} /* tsub_inp79 */


void tsub_inp1024(void) {
/* updated 2008/05/07, 2005/03/13, 2005/02/23, 2004/12/11 */
/* long */
/* get screen input into sg_inp1024,ig_inp1024_lg,ng_inp1024_long */
	char sz[1025], cz;
	int iy, iz;

    ng_inp1024_long = 0;
	tsub_blank(sg_inp1024, 1024);
	fgets(sz, 1024, stdin);

	for(iy = 0, iz = 0; iz < 1024; iz++) {
		cz = sz[iz];

		if(cz != 0) {
			sg_inp1024[iz] = cz;
			iy = iz;

            if(cz >= '0' && cz <= '9')
            	ng_inp1024_long = ng_inp1024_long * 10 + cz - 48;
		}
		else iz = 2000;
	}

	ig_inp1024_lg = iy;
	tsub_blank_escapes(sg_inp1024, ig_inp1024_lg);
} /* tsub_inp1024 */


void tsub_line_of_char(char *sp1, char cp1, long np_long) {
/* updated 2005/05/10, 2004/11/14 */
/* long */
	long nz;

	for(nz = 0; nz < np_long; nz++) sp1[nz] = cp1;
} /* tsub_line_of_char */


void tsub_out79(char *sp1, int ip_long) {
/* updated 2004/12/18 */
/* long */
	char sz[80];

	if(ip_long > 79) ip_long = 79;
	tsub_blank(sz, 80);
	tsub_copy(sz, sp1, ip_long);
	tsub_blank_escapes(sz, 80);
	sz[79] = 0;
	puts(sz);
} /* tsub_out79 */


void tsub_show_pline(int ip_index, char *sp1, int ip_long) {
/* updated 2005/03/30, 2005/02/19, 2004/11/27 */
	char sz[80];

	tsub_blank(sz, 80);
	sprintf(sz, "%5d", ip_index);

	if(ip_long > 73) ip_long = 73;
	tsub_copy(&sz[6], sp1, ip_long);

	tsub_out79(sz, 79);
} /* tsub_show_pline */


void tsub_show_pline_by_index(int ip_index) {
/* updated 2007/10/11, 2005/04/01 */
	char sz[80];
	int i_long;

    if(ip_index > 0) {
        i_long = iga_plines_lg[ip_index];

	    tsub_blank(sz, 80);
    	sprintf(sz, "%5d", ip_index);

	    if(i_long > 73) i_long = 73;
    	tsub_copy(&sz[6], psga_plines[ip_index], i_long);

	    tsub_out79(sz, 79);
    }
} /* tsub_show_pline */


void tsub_show_vstring_info(int ip_index) {
/* updated 2007/10/15, 2005/05/11, 2005/04/14, 2004/11/27 */
	int i_long;
	char s_string[80];

    if(ip_index >= 0 && ip_index <= VSTRINGS) {
    	i_long = nga_strings_lg[ip_index];
	    printf("string index=%d, length=%d\n", ip_index, i_long);

    	if(i_long > 79) i_long = 79;
	    tsub_copy(s_string, psga_strings[ip_index], i_long);
    	tsub_out79(s_string, i_long);
    }
} /* tsub_show_vstring_info */


void tsub_show_vdecimal_info(int ip_index) {
/* updated 2007/10/15 */
    double dz;

    if(ip_index >= 0 && ip_index <= VDECIMALS) {
        dz = dga_decimals[ip_index];
        printf("index=%d  decimal=%20.20f\n", ip_index, dz);
    }
} /* tsub_show_vdecimal_info */


void tsub_make_long_string(char **psp1, long np_long) {
/* updated 2007/01/08, 2006/10/17, 2005/09/11, 2005/08/17 */
/* 2005/07/21, 2005/07/19, 2005/07/03, 2005/05/11, 2005/05/09 */
/* **psp1 is a pointer to a string pointer */
/* MAXSTRING is the maximum string length */
/* tsub_make_long_string(&psg_1, ng_1, int ip_local); */
/* tsub_copy(psg_1, sz, 50); */
    int i_error = 2;

	/* free does nothing to a pointer set to NULL */
    free(*psp1);
    *psp1 = NULL;

    /* make the string one longer than needed for a 0 */
    np_long = abs(np_long);
    np_long++;

    if(np_long < 2) {
		/* make a string of zero length */
		/* the string can be a little longer */
		*psp1 = (char *)malloc(5);
		if(*psp1 == NULL) i_error = 1;
    }
	else if(np_long <= MAXSTRING) {
		/* make a string of length np_long */
		*psp1 = (char *)malloc(np_long);
		/* try again if it did not work */
		if(*psp1 == NULL) *psp1 = (char *)malloc(np_long);
		if(*psp1 == NULL) i_error = 1;
	}
    else i_error = 1;

	if(i_error == 1) {
		printf("\nlength=%d\n", np_long);
		sub_program_error_end("make_long_string", 16);
    }

} /* tsub_make_long_string */


void tsub_use_append(char *psp_app, long np_app) {
/* updated 2005/05/23, 2005/05/14, 2005/05/12, 2005/05/11 */
/* append psp_app,np_app to psg_use2,ng_use2 put in psg_use1,ng_use1 */
    if(np_app < 0) np_app = 0;
    if(ng_use2 < 0) ng_use2 = 0;

    tsub_make_long_string(&psg_use1, ng_use2 + np_app);

    if(ig_exit != 1) {
		tsub_copy(psg_use1, psg_use2, ng_use2);
		tsub_copy(&psg_use1[ng_use2], psp_app, np_app);
	    ng_use1 = ng_use2 + np_app;
    }
} /* tsub_use_append */


void tsub_use_insert321(long np_beg) {
/* updated 2005/07/17, 2005/05/22, 2005/05/19, 2005/05/16 */
/* insert string psg_use3,ng_use3 into psg_use2,ng_use2 at np_beg */
/* to make psg_use1,ng_use1 */
    if(np_beg < 0) np_beg = 0;
    if(np_beg > ng_use2) np_beg = ng_use2;

	/* get a total final length */
	ng_use1 = ng_use2 + ng_use3;

	/* create string psg_use1,ng_use1 */
	tsub_make_long_string(&psg_use1, ng_use1);

	if(ig_exit != 1) {
		tsub_copy(psg_use1, psg_use2, np_beg);

		/* put in from psg_use3 into psg_use1 */
		tsub_copy(&psg_use1[np_beg], psg_use3, ng_use3);

		/* put the ending from psg_use2,ng_use2 into psg_use1,ng_use1 */
		tsub_copy(&psg_use1[np_beg + ng_use3], &psg_use2[np_beg],
        ng_use2 - np_beg);
	}
} /* tsub_use_insert321 */


void tsub_use_move12(void) {
/* updated 2005/06/05 */
/* move string psg_use1,ng_use1 to psg_use2,ng_use2 */
	free(psg_use2);
	psg_use2 = psg_use1;
    ng_use2 = ng_use1;

	psg_use1 = NULL;
	ng_use1 = 0;
} /* tsub_use_move12 */


void tsub_use_move21(void) {
/* updated 2005/06/05 */
/* move string psg_use2,ng_use2 to psg_use1,ng_use1 */
	free(psg_use1);
	psg_use1 = psg_use2;
    ng_use1 = ng_use2;

	psg_use2 = NULL;
	ng_use2 = 0;
} /* tsub_use_move21 */


void tsub_use_replace(long np_beg, char *psp_rep, long np_rep) {
/* updated 2005/06/05, 2005/05/22, 2005/05/19, 2005/05/17 */
/* in psg_use1,ng_use1 replace with psp_rep,np_rep beginning at np_beg */
	long ny, nz;

    if(np_beg < 0) np_beg = 0;
    if(np_beg < ng_use1) {
		ny = np_beg;
		for(nz = 0; nz < np_rep && ny < ng_use1; nz++, ny++) {
	        psg_use1[ny] = psp_rep[nz];
        }
    }
} /* tsub_use_replace */


void tsub_use_trim_left(char *psp_str, long np_long) {
/* updated 2005/08/23, 2005/05/22, 2005/05/14 */
/* left trim psp_str,np_long into psg_use1,ng_use1 */
/* 0123456789 */
/*       AAAA */
	long n_long, nz;

    for(nz = 0; psp_str[nz] <= 32 && nz < np_long; nz++);
	n_long = np_long - nz;
    tsub_make_long_string(&psg_use1, n_long);

    if(ig_exit != 1) {
		tsub_copy(psg_use1, &psp_str[nz], n_long);
    	ng_use1 = n_long;
	}
} /* tsub_use_trim_left */


void tsub_use_trim_right(char *psp_str, long np_long) {
/* updated 2005/05/23, 2005/05/14 */
/* right trim psp_str,np_long into psg_use1,ng_use1 */
	long nz;

    for(nz = np_long - 1; psp_str[nz] <= 32 && nz >= 0; nz--);
	nz++;
    tsub_make_long_string(&psg_use1, nz);

    if(ig_exit != 1) {
		tsub_copy(psg_use1, psp_str, nz);
    	ng_use1 = nz;
	}
} /* tsub_use_trim_right */


void tsub_use_delete21(long np_beg, long np_long) {
/* updated 2005/05/23 */
/* beginning at np_beg delete np_long in psg_use2,ng_use2 */
/* put in psg_use1,ng_use1 */
	long n_part2beg, n_part2_lg;
	int i_good = 1;

    if(np_beg < 0 || np_long < 1 || np_beg >= ng_use2) i_good++;

    if(i_good == 1) {
	    /* find start of after deleted */
		n_part2beg = np_beg + np_long;

        /* get length of part to hold */
		n_part2_lg = ng_use2 - np_beg - np_long;

		/* make a string to psg_use1 */
        tsub_make_long_string(&psg_use1, ng_use2 - np_long);
		if(ig_exit == 1) i_good++;
    }
    if(i_good == 1) {
		tsub_copy(psg_use1, psg_use2, np_beg);

		tsub_copy(&psg_use1[np_beg], &psg_use2[n_part2beg], n_part2_lg);
		ng_use1 = ng_use2 - np_long;
	}
} /* tsub_use_delete21 */


void tsub_pass_delete(long np_beg, long np_long) {
/* updated 2005/07/19, 2005/05/12, 2005/05/11, 2005/05/10, 2004/12/09 */
/* long */
	char *ps_hold = NULL;
	long n_holdbeg, n_hold_lg;
	int i_good = 1;
	int i_mustfree = 2;

    if(np_beg < 0 || np_long < 1 || np_beg >= ng_pass_lg) i_good++;

    if(i_good == 1) {
	    /* find start of after deleted */
		n_holdbeg = np_beg + np_long;

        /* get length of part to hold */
		n_hold_lg = ng_pass_lg - n_holdbeg;

		if(n_holdbeg >= ng_pass_lg) {
			/* delete goes to end or beyond */
			ng_pass_lg = np_beg;
        	i_good++;
	    }
	}

    if(i_good == 1) {
		/* make a string to hold */
        tsub_make_long_string(&ps_hold, n_hold_lg);
		if(ig_exit == 1) i_good++;
        else i_mustfree = 1;
    }
    if(i_good == 1) {
		tsub_copy(ps_hold, &sg_pass[n_holdbeg], n_hold_lg);

		tsub_copy(&sg_pass[np_beg], ps_hold, n_hold_lg);
		ng_pass_lg = ng_pass_lg - np_long;
	}
	/* free long string in ps_hold */
    if(i_mustfree == 1) free(ps_hold);
} /* tsub_pass_delete */


void tsub_pass_insert(long np_beg, char *sp1, long np_long) {
/* updated 2005/05/11, 2005/05/10, 2005/02/12, 2004/12/08 */
/* long */
/* insert string sp1,np_long in front of byte np_beg of sg_pass */
    char *ps_hold = NULL;
	long n_hold_lg;
	int i_good = 1;
    int i_mustfree = 2;

    if(np_beg < 0) np_beg = 0;
    if(np_beg > ng_pass_lg) np_beg = ng_pass_lg;

	/* get n_hold_lg the length of ps_hold */
	n_hold_lg = ng_pass_lg - np_beg;

	/* create string ps_hold for length n_hold_lg */
	tsub_make_long_string(&ps_hold, n_hold_lg);
	if(ig_exit == 1) i_good++;
    else i_mustfree = 1;

	if(i_good == 1) {
		tsub_copy(ps_hold, &sg_pass[np_beg], n_hold_lg);

		/* put in from sp1 into sg_pass */
		tsub_copy(&sg_pass[np_beg], sp1, np_long);

		/* put the ending from s_hold into sg_pass */
		tsub_copy(&sg_pass[np_beg + np_long], ps_hold, n_hold_lg);
		ng_pass_lg = ng_pass_lg + np_long;
	}

    /* free ps_hold if needed */
    if(i_mustfree == 1) free(ps_hold);
} /* tsub_pass_insert */


void tsub_pass_trim_left(void) {
/* updated 2005/05/10, 2005/02/12 */
/* long */
/* trim left on sg_pass,ng_pass_lg */
	long ny, nz;
	char sz[VSLONG];

    /* blank sz */
	tsub_blank(sz, VSLONG);

	/* find beginning of sg_pass to iz */
    for(nz = 0; nz < VSLONG && sg_pass[nz] <= 32; nz++);

    /* copy left trimmed sg_pass to sz */
    for(ny = 0; nz < ng_pass_lg; nz++, ny++) sz[ny] = sg_pass[nz];

    /* put new length in ng_pass_lg */
    ng_pass_lg = ny;

    /* copy from sz back to sg_pass */
	tsub_copy(sg_pass, sz, VSLONG);
} /* tsub_pass_trim_left */


void tsub_pass_trim_right(void) {
/* updated 2005/05/10, 2005/02/19, 2005/02/12 */
/* long */
/* trim right on sg_pass,ng_pass_lg */
	long nz;

    for(nz = ng_pass_lg - 1; sg_pass[nz] <= 32 && nz >= 0; nz--);

    ng_pass_lg = nz + 1;
} /* tsub_pass_trim_right */

/* oklatea.cpp is an interpreter of the Teapro programming language */
/* </PRE></BODY></HTML> */
