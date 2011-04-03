/* Copyright(c) 2011 Murray M. Stokely
 *
 * This file is part of the R Multiple Precision Complex package, mpc.
 *
 * mpc is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
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

/* 5.8 Power Functions and Logarithm. */
/* Power functions implemented in Ops. */

/* http://www.multiprecision.org/index.php?prog=mpc&page=html#Power-Functions-and-Logarithm */

SEXP R_mpc_log(SEXP e1) {
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	if (Rf_inherits(e1, "mpc")) {
		mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
		mpc_init2(*z, mpc_get_prec(*z1));
		mpc_log(*z, *z1, MPC_RNDNN);
	} else {
		Rf_error("Invalid operand for MPC log.");
	}
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z, Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}

SEXP R_mpc_exp(SEXP e1) {
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	if (Rf_inherits(e1, "mpc")) {
		mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
		mpc_init2(*z, mpc_get_prec(*z1));
		mpc_exp(*z, *z1, MPC_RNDNN);
	} else {
		Rf_error("Invalid operand for MPC exp.");
	}
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z, Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}
