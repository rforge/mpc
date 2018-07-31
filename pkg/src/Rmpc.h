/* Copyright 2018 Martin Maechler
 * Copyright 2011 Google Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA
 *
 * http://mpc.r-forge.r-project.org/
 */
#include "mpc.h"

#define R_NO_REMAP   /* avoid collisions with stl definitions */

#include <Rinternals.h>

void mpcFinalizer(SEXP ptr);

// mpc.c :
SEXP print_mpc(SEXP ptr);
SEXP R_mpc_get_prec(SEXP ptr);
SEXP MakeMPC(mpc_t *z);
SEXP R_mpc(SEXP n, SEXP sprec);
SEXP R_mpc_add(SEXP e1, SEXP e2);
SEXP R_mpc_sub(SEXP e1, SEXP e2);
SEXP R_mpc_mul(SEXP e1, SEXP e2);
SEXP R_mpc_div(SEXP e1, SEXP e2);
SEXP R_mpc_neg(SEXP e1);
SEXP R_mpc_pow(SEXP e1, SEXP e2);
SEXP R_mpc_cmp(SEXP e1, SEXP e2);
SEXP R_mpc_conj(SEXP x);
SEXP R_mpc_urandom(SEXP sprec);
SEXP R_mpc_get_version();

// mpc_log.c:
SEXP R_mpc_log(SEXP e1);
SEXP R_mpc_exp(SEXP e1);

// mpc_proj.c:
SEXP R_mpc_real(SEXP e1);
SEXP R_mpc_imag(SEXP e1);
SEXP R_mpc_arg(SEXP e1);

// mpc_trig.c:
SEXP R_mpc_sin(SEXP x);
SEXP R_mpc_cos(SEXP x);
SEXP R_mpc_tan(SEXP x);
SEXP R_mpc_sinh(SEXP x);
SEXP R_mpc_cosh(SEXP x);
SEXP R_mpc_tanh(SEXP x);
SEXP R_mpc_asin(SEXP x);
SEXP R_mpc_acos(SEXP x);
SEXP R_mpc_atan(SEXP x);
SEXP R_mpc_asinh(SEXP x);
SEXP R_mpc_acosh(SEXP x);
SEXP R_mpc_atanh(SEXP x);
