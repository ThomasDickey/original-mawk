/********************************************
bi_funct.h
copyright 2009-2010,2012 Thomas E. Dickey
copyright 1991, Michael D. Brennan

This is a source file for mawk, an implementation of
the AWK programming language.

Mawk is distributed without warranty under the terms of
the GNU General Public License, version 2, 1991.
********************************************/

/*
 * $MawkId: bi_funct.h,v 1.5 2012/10/27 14:09:10 tom Exp $
 * @Log: bi_funct.h,v @
 * Revision 1.2  1994/12/11  22:10:15  mike
 * fflush
 *
 * Revision 1.1.1.1  1993/07/03  18:58:08  mike
 * move source to cvs
 *
 * Revision 5.1  1991/12/05  07:59:03  brennan
 * 1.1 pre-release
 *
*/

#ifndef  BI_FUNCT_H
#define  BI_FUNCT_H  1

#include "symtype.h"
#include <setjmp.h>

extern BI_REC bi_funct[];

void bi_init(void);

/* builtin string functions */
CELL *bi_print(CELL *);
CELL *bi_printf(CELL *);
CELL *bi_length(CELL *);
CELL *bi_index(CELL *);
CELL *bi_substr(CELL *);
CELL *bi_sprintf(CELL *);
CELL *bi_split(CELL *);
CELL *bi_match(CELL *);
CELL *bi_getline(CELL *);
CELL *bi_sub(CELL *);
CELL *bi_gsub(CELL *);
CELL *bi_toupper(CELL *);
CELL *bi_tolower(CELL *);

/* builtin arith functions */
CELL *bi_sin(CELL *);
CELL *bi_cos(CELL *);
CELL *bi_atan2(CELL *);
CELL *bi_log(CELL *);
CELL *bi_exp(CELL *);
CELL *bi_int(CELL *);
CELL *bi_sqrt(CELL *);
CELL *bi_srand(CELL *);
CELL *bi_rand(CELL *);

CELL * bi_compl(CELL *);
CELL * bi_lshift(CELL *);
CELL * bi_rshift(CELL *);
CELL * bi_xor(CELL *);
CELL * bi_and(CELL *);
CELL * bi_or(CELL *);

#ifdef HAVE_C99_FUNCS
/* C99 eqivalent functions (NON-STANDARD) */
CELL *bi_tan(CELL *);
CELL *bi_acos(CELL *);
CELL *bi_asin(CELL *);
CELL *bi_atan(CELL *);
CELL *bi_cosh(CELL *);
CELL *bi_sinh(CELL *);
CELL *bi_tanh(CELL *);
CELL *bi_acosh(CELL *);
CELL *bi_asinh(CELL *);
CELL *bi_atanh(CELL *);
CELL *bi_ldexp(CELL *);
CELL *bi_log10(CELL *);
CELL *bi_mod(CELL *);
CELL *bi_pow(CELL *);
CELL *bi_ceil(CELL *);
CELL *bi_floor(CELL *);
CELL *bi_trunc(CELL *);
CELL *bi_round(CELL *);
CELL *bi_abs(CELL *);
CELL *bi_min(CELL *);
CELL *bi_max(CELL *);
CELL *bi_exp2(CELL *);
CELL *bi_expm1(CELL *);
CELL *bi_log2(CELL *);
CELL *bi_log1p(CELL *);
CELL *bi_ilogb(CELL *);
CELL *bi_logb(CELL *);
CELL *bi_cbrt(CELL *);
CELL *bi_hypot(CELL *);
CELL *bi_erf(CELL *);
CELL *bi_erfc(CELL *);
CELL *bi_lgamma(CELL *);
CELL *bi_tgamma(CELL *);
#ifdef _GNU_SOURCE
CELL *bi_bessel_j0(CELL *);
CELL *bi_bessel_j1(CELL *);
CELL *bi_bessel_jn(CELL *);
CELL *bi_bessel_y0(CELL *);
CELL *bi_bessel_y1(CELL *);
CELL *bi_bessel_yn(CELL *);
#endif
#endif

/* time functions */
CELL *bi_mktime(CELL *);
CELL *bi_strftime(CELL *);
CELL *bi_systime(CELL *);

/* other builtins */
CELL *bi_close(CELL *);
CELL *bi_system(CELL *);
CELL *bi_fflush(CELL *);

/********************************************
 * MACROS for defining bi_xxxx() functions
 *******************************************/

/*  EXAMPLE single parameter of double
CELL *
bi_acos(CELL *sp)
{
    TRACE_FUNC("bi_acos", sp);

#if  ! STDC_MATHERR
    if (sp->type != C_DOUBLE)
	cast1_to_d(sp);
    sp->dval = acos(sp->dval);
#else
    {
	double x;

	errno = 0;
	if (sp->type != C_DOUBLE)
	    cast1_to_d(sp);
	x = sp->dval;
	sp->dval = acos(sp->dval);
	if (errno)
	    fplib_err("acos", x, "domain error");
    }
#endif
    return_CELL("bi_acos", sp);
}


*/


#define FUNC_STR(name)             #name
#define BIFUNC_NAME(name)          #name
#define BIFUNC_STR(name)           BIFUNC_NAME(bi_ ## name)

#define FUNC_NAME(name,p)          name(p)
#define FUNC2_NAME(name,p1,p2)     name(p1,p2)

/* to catch errors for bessel_jn use jmp_bug
 * and return nan
 */
#if ! STDC_MATHERR
#define SAFE_FUNC2_NAME(res,name,p1,p2) \
  do {                              \
  jmp_buf sf_jmp;                   \
  if (setjmp(sf_jmp) == 0) {        \
      res = FUNC2_NAME(name,p1,p2); \
  } else {                          \
      res = log(-1);  /* return nan */ \
  }                                 \
  } while(0)
#else
#define SAFE_FUNC2_NAME(res,name,p1,p2) \
  do {                              \
      res = FUNC2_NAME(name,p1,p2); \
  } while(0)
#endif

#if ! STDC_MATHERR

/* for Arithmetic funcs like sin(x) */
#define FUNC_1P_DBL(name, msg)                  \
    CELL * bi_##name(CELL *sp) {                \
    TRACE_FUNC(BIFUNC_STR(name), sp);           \
    if (sp->type != C_DOUBLE) cast1_to_d(sp);   \
    sp->dval = FUNC_NAME(name,sp->dval);        \
    return_CELL(BIFUNC_STR(name), sp); }

/* different C function name to mawk function name */
#define FUNC_DIFF_1P_DBL(name, fn, msg)         \
    CELL * bi_##name(CELL *sp) {                \
    TRACE_FUNC(BIFUNC_STR(name), sp);           \
    if (sp->type != C_DOUBLE) cast1_to_d(sp);   \
    sp->dval = FUNC_NAME(fn,sp->dval);          \
    return_CELL(BIFUNC_STR(name), sp); }

/* for Arithmetic funcs like bessel_jn(x,y) */
#define FUNC_DIFF_2P_INT_DBL(name, fn, msg)       \
    CELL * bi_##name(CELL *sp) {                  \
    int param1;                                   \
    TRACE_FUNC(BIFUNC_STR(name), sp);             \
    sp--;                                         \
    if (TEST2(sp) != TWO_DOUBLES) cast2_to_d(sp); \
    param1 = (int) sp->dval;                      \
    SAFE_FUNC2_NAME(sp->dval,fn,param1,(sp + 1)->dval);  \
    return_CELL(BIFUNC_STR(name), sp); }

/* for Arithmetic funcs like ldexp(x,y) */
#define FUNC_DIFF_2P_DBL_INT(name, fn, msg)       \
    CELL * bi_##name(CELL *sp) {                  \
    int param2;                                   \
    TRACE_FUNC(BIFUNC_STR(name), sp);             \
    sp--;                                         \
    if (TEST2(sp) != TWO_DOUBLES) cast2_to_d(sp); \
    param2 = (int) (sp + 1)->dval;                      \
    SAFE_FUNC2_NAME(sp->dval,fn,sp->dval,param2);  \
    return_CELL(BIFUNC_STR(name), sp); }

/* for Arithmetic funcs like atan2(x,y) */
#define FUNC_2P_DBL(name, msg)                    \
    CELL * bi_##name(CELL *sp) {                  \
    TRACE_FUNC(BIFUNC_STR(name), sp);             \
    sp--;                                         \
    if (TEST2(sp) != TWO_DOUBLES) cast2_to_d(sp); \
    sp->dval = FUNC2_NAME(name,sp->dval,(sp + 1)->dval);  \
    return_CELL(BIFUNC_STR(name), sp); }

#else    /* STDC_MATHERR */

/* for Arithmetic funcs like sin(x) */
#define FUNC_1P_DBL(name, msg)                  \
CELL * bi_##name(CELL *sp) {                    \
    TRACE_FUNC(BIFUNC_STR(name), sp);           \
    { double x;                                 \
    errno = 0;                                  \
    if (sp->type != C_DOUBLE) cast1_to_d(sp);   \
    x = sp->dval;                               \
    sp->dval =  FUNC_NAME(name,sp->dval);       \
    if (errno)  fplib_err(FUNC_STR(name), x, msg);  \
    }                                           \
    return_CELL(BIFUNC_STR(name), sp); }
// 	    rt_error("ldexp(x,exp) : domain error");  <- rather than fplib() ??

/* different C function name to mawk function name */
#define FUNC_DIFF_1P_DBL(name, fn, msg)       \
CELL * bi_##name(CELL *sp) {                    \
    TRACE_FUNC(BIFUNC_STR(name), sp);           \
    { double x;                                 \
    errno = 0;                                  \
    if (sp->type != C_DOUBLE) cast1_to_d(sp);   \
    x = sp->dval;                               \
    sp->dval =  FUNC_NAME(fn,sp->dval);         \
    if (errno)  fplib_err(FUNC_STR(name), x, msg);  \
    }                                           \
    return_CELL(BIFUNC_STR(name), sp); }

/* for Arithmetic funcs like bessel_jn(x,y) */
#define FUNC_DIFF_2P_INT_DBL(name, fn, msg)       \
CELL * bi_##name(CELL *sp) {                      \
    int param1;                                   \
    TRACE_FUNC(BIFUNC_STR(name), sp);             \
    { double x;                                   \
    errno = 0;                                    \
    sp--;                                         \
    if (TEST2(sp) != TWO_DOUBLES) cast2_to_d(sp); \
    x = sp->dval;                                 \
    param1 = (int) sp->dval;                      \
    sp->dval = FUNC2_NAME(fn,param1,(sp + 1)->dval);  \
    if (errno)  fplib_err(FUNC_STR(name), x, msg);  \
    }                                               \
    return_CELL(BIFUNC_STR(name), sp); }

/* for Arithmetic funcs like ldexp(x,y) */
#define FUNC_DIFF_2P_DBL_INT(name, fn, msg)       \
CELL * bi_##name(CELL *sp) {                      \
    int param2;                                   \
    TRACE_FUNC(BIFUNC_STR(name), sp);             \
    { double x;                                   \
    errno = 0;                                    \
    sp--;                                         \
    if (TEST2(sp) != TWO_DOUBLES) cast2_to_d(sp); \
    x = sp->dval;                                 \
    param2 = (int) (sp + 1)->dval;                \
    SAFE_FUNC2_NAME(sp->dval,fn,sp->dval,param2);    \
    if (errno)  fplib_err(FUNC_STR(name), x, msg);  \
    }                                               \
    return_CELL(BIFUNC_STR(name), sp); }

/* for Arithmetic funcs like atan2(x,y) */
#define FUNC_DIFF_2P_DBL(name, fn, msg)           \
CELL * bi_##name(CELL *sp) {                      \
    TRACE_FUNC(BIFUNC_STR(name), sp);             \
    { double x;                                   \
    errno = 0;                                    \
    sp--;                                         \
    if (TEST2(sp) != TWO_DOUBLES) cast2_to_d(sp); \
    x = sp->dval;                                 \
    SAFE_FUNC2_NAME(sp->dval,fn,sp->dval,(sp + 1)->dval);  \
    if (errno)  fplib_err(FUNC_STR(name), x, msg);  \
    }                                               \
    return_CELL(BIFUNC_STR(name), sp); }

/* for Arithmetic funcs like atan2(x,y) */
#define FUNC_2P_DBL(name, msg)           \
CELL * bi_##name(CELL *sp) {                      \
    TRACE_FUNC(BIFUNC_STR(name), sp);             \
    { double x;                                   \
    errno = 0;                                    \
    sp--;                                         \
    if (TEST2(sp) != TWO_DOUBLES) cast2_to_d(sp); \
    x = sp->dval;                                 \
    SAFE_FUNC2_NAME(sp->dval,name,sp->dval,(sp + 1)->dval);  \
    if (errno)  fplib_err(FUNC_STR(name), x, msg);  \
    }                                               \
    return_CELL(BIFUNC_STR(name), sp); }

#endif


#endif /* BI_FUNCT_H  */
