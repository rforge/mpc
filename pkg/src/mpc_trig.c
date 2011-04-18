/* Copyright 2011 Google Inc.
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

#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"
#include "mpfr.h"
#define R_NO_REMAP   /* avoid collisions with stl definitions */

#include <Rinternals.h>

#include "Rmpc.h"

/* TODO(mstokely): Replace all of the duplicate functions with a
 * function table or something to replace just the 1 line that differs
 * in each one. */

/* 5.9 Trigonometric Functions */
/* http://www.multiprecision.org/index.php?prog=mpc&page=html#Trigonometric-Functions */

SEXP R_mpc_sin(SEXP x) {
	if (!Rf_inherits(x, "mpc")) {
		Rf_error("Invalid operand for sin.mpc");
	}
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(x);
	mpc_init2(*z, mpc_get_prec(*z1));
	mpc_sin(*z, *z1, MPC_RNDNN);
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}


SEXP R_mpc_cos(SEXP x) {
	if (!Rf_inherits(x, "mpc")) {
		Rf_error("Invalid operand for sin.mpc");
	}
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(x);
	mpc_init2(*z, mpc_get_prec(*z1));
	mpc_cos(*z, *z1, MPC_RNDNN);
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}


SEXP R_mpc_tan(SEXP x) {
	if (!Rf_inherits(x, "mpc")) {
		Rf_error("Invalid operand for sin.mpc");
	}
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(x);
	mpc_init2(*z, mpc_get_prec(*z1));
	mpc_tan(*z, *z1, MPC_RNDNN);
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}


SEXP R_mpc_sinh(SEXP x) {
	if (!Rf_inherits(x, "mpc")) {
		Rf_error("Invalid operand for sin.mpc");
	}
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(x);
	mpc_init2(*z, mpc_get_prec(*z1));
	mpc_sinh(*z, *z1, MPC_RNDNN);
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}


SEXP R_mpc_cosh(SEXP x) {
	if (!Rf_inherits(x, "mpc")) {
		Rf_error("Invalid operand for sin.mpc");
	}
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(x);
	mpc_init2(*z, mpc_get_prec(*z1));
	mpc_cosh(*z, *z1, MPC_RNDNN);
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}


SEXP R_mpc_tanh(SEXP x) {
	if (!Rf_inherits(x, "mpc")) {
		Rf_error("Invalid operand for sin.mpc");
	}
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(x);
	mpc_init2(*z, mpc_get_prec(*z1));
	mpc_tanh(*z, *z1, MPC_RNDNN);
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}


SEXP R_mpc_asin(SEXP x) {
	if (!Rf_inherits(x, "mpc")) {
		Rf_error("Invalid operand for sin.mpc");
	}
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(x);
	mpc_init2(*z, mpc_get_prec(*z1));
	mpc_asin(*z, *z1, MPC_RNDNN);
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}


SEXP R_mpc_acos(SEXP x) {
	if (!Rf_inherits(x, "mpc")) {
		Rf_error("Invalid operand for sin.mpc");
	}
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(x);
	mpc_init2(*z, mpc_get_prec(*z1));
	mpc_acos(*z, *z1, MPC_RNDNN);
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}


SEXP R_mpc_atan(SEXP x) {
	if (!Rf_inherits(x, "mpc")) {
		Rf_error("Invalid operand for sin.mpc");
	}
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(x);
	mpc_init2(*z, mpc_get_prec(*z1));
	mpc_atan(*z, *z1, MPC_RNDNN);
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}


SEXP R_mpc_asinh(SEXP x) {
	if (!Rf_inherits(x, "mpc")) {
		Rf_error("Invalid operand for sin.mpc");
	}
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(x);
	mpc_init2(*z, mpc_get_prec(*z1));
	mpc_asinh(*z, *z1, MPC_RNDNN);
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}


SEXP R_mpc_acosh(SEXP x) {
	if (!Rf_inherits(x, "mpc")) {
		Rf_error("Invalid operand for sin.mpc");
	}
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(x);
	mpc_init2(*z, mpc_get_prec(*z1));
	mpc_acosh(*z, *z1, MPC_RNDNN);
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}


SEXP R_mpc_atanh(SEXP x) {
	if (!Rf_inherits(x, "mpc")) {
		Rf_error("Invalid operand for sin.mpc");
	}
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(x);
	mpc_init2(*z, mpc_get_prec(*z1));
	mpc_atanh(*z, *z1, MPC_RNDNN);
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}
