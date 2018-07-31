#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

#include "Rmpc.h"

static const R_CallMethodDef CallEntries[] = {
    {"print_mpc",         (DL_FUNC) &print_mpc,         1},
    {"R_mpc",             (DL_FUNC) &R_mpc,             2},
    {"R_mpc_acos",        (DL_FUNC) &R_mpc_acos,        1},
    {"R_mpc_acosh",       (DL_FUNC) &R_mpc_acosh,       1},
    {"R_mpc_add",         (DL_FUNC) &R_mpc_add,         2},
    {"R_mpc_arg",         (DL_FUNC) &R_mpc_arg,         1},
    {"R_mpc_asin",        (DL_FUNC) &R_mpc_asin,        1},
    {"R_mpc_asinh",       (DL_FUNC) &R_mpc_asinh,       1},
    {"R_mpc_atan",        (DL_FUNC) &R_mpc_atan,        1},
    {"R_mpc_atanh",       (DL_FUNC) &R_mpc_atanh,       1},
    {"R_mpc_cmp",         (DL_FUNC) &R_mpc_cmp,         2},
    {"R_mpc_conj",        (DL_FUNC) &R_mpc_conj,        1},
    {"R_mpc_cos",         (DL_FUNC) &R_mpc_cos,         1},
    {"R_mpc_cosh",        (DL_FUNC) &R_mpc_cosh,        1},
    {"R_mpc_div",         (DL_FUNC) &R_mpc_div,         2},
    {"R_mpc_exp",         (DL_FUNC) &R_mpc_exp,         1},
    {"R_mpc_get_prec",    (DL_FUNC) &R_mpc_get_prec,    1},
    {"R_mpc_get_version", (DL_FUNC) &R_mpc_get_version, 0},
    {"R_mpc_imag",        (DL_FUNC) &R_mpc_imag,        1},
    {"R_mpc_log",         (DL_FUNC) &R_mpc_log,         1},
    {"R_mpc_mul",         (DL_FUNC) &R_mpc_mul,         2},
    {"R_mpc_neg",         (DL_FUNC) &R_mpc_neg,         1},
    {"R_mpc_pow",         (DL_FUNC) &R_mpc_pow,         2},
    {"R_mpc_real",        (DL_FUNC) &R_mpc_real,        1},
    {"R_mpc_sin",         (DL_FUNC) &R_mpc_sin,         1},
    {"R_mpc_sinh",        (DL_FUNC) &R_mpc_sinh,        1},
    {"R_mpc_sub",         (DL_FUNC) &R_mpc_sub,         2},
    {"R_mpc_tan",         (DL_FUNC) &R_mpc_tan,         1},
    {"R_mpc_tanh",        (DL_FUNC) &R_mpc_tanh,        1},
    {"R_mpc_urandom",     (DL_FUNC) &R_mpc_urandom,     1},
    {NULL, NULL, 0}
};

void R_init_mpc(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
