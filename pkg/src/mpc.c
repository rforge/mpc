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

static int max(int a, int b) {
	return (b<a) ? a : b;
}

void mpcFinalizer(SEXP ptr) {
/*	Rprintf("In MPC Finalizer!\n"); */
	mpc_t *z = (mpc_t *)R_ExternalPtrAddr(ptr);
	if (z) {
/* 		Rprintf("Gathered an external pointer in finalizer, clearing %p\n", z); */
		mpc_clear(*z);
		free(z);
		R_ClearExternalPtr(ptr);
	}
}

SEXP print_mpc(SEXP ptr) {
	mpc_ptr z = (mpc_ptr)R_ExternalPtrAddr(ptr);
	SEXP retVal;
	if (z) {
		char *mystring = mpc_get_str(10, 0, z, MPC_RNDNN);
		PROTECT(retVal = Rf_mkString(mystring));
		UNPROTECT(1);
		return retVal;
	}
	return R_NilValue;
}

/* Section 5.1 Initialization Functions */
SEXP R_mpc_get_prec(SEXP ptr) {
	mpc_ptr z = (mpc_ptr)R_ExternalPtrAddr(ptr);
	SEXP retVal;
	if (z) {
		mpfr_prec_t prec = mpc_get_prec(z);
		PROTECT(retVal = Rf_ScalarInteger(prec));
		UNPROTECT(1);
		return retVal;
	}
	return R_NilValue;
}

SEXP as_mpc_numeric(SEXP n, SEXP sprec) {
	/* INTEGER returns 32bit integer but mpfr_prec_t may be 64bit. */
	mpfr_prec_t prec = INTEGER(sprec)[0];
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	if (z == NULL) {
		Rf_error("Could not allocate memory for MPC type.");
	}
	mpc_init2(*z, prec);
	/* Here switch on class of n */
	/* double */
	/* TODO(mstokely): Support user defined rounding. */

	if (Rf_isNumeric(n)) {
		mpc_set_d(*z, REAL(n)[0], MPC_RNDNN);
	} else if (Rf_isComplex(n)) {
		mpc_set_d_d(*z, COMPLEX(n)[0].r, COMPLEX(n)[0].i, MPC_RNDNN);
	} else {
		Rf_error("Unsupported type coversion to MPC.");
	}
	char *mystring = mpc_get_str(10, 0, *z, MPC_RNDNN);

	/* Now, instead of making external pointers, lets return other types. */

	/* Lets just make it an external pointer with a class "MPC" */
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z, Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}

/* Section 5.7 Basic Arithmetic Functions */

SEXP R_mpc_add(SEXP e1, SEXP e2) {
	/* TODO switch on class of e2 here don't assume both mpc. */
	mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	if (z == NULL) {
		Rf_error("Could not allocate memory for MPC type.");
	}

	if (Rf_inherits(e2, "mpc")) {
		Rprintf("It's an mpc");
		mpc_t *z2 = (mpc_t *)R_ExternalPtrAddr(e2);
		/* TODO: both are mpc, set prec to max mpc_get_prec z1/z2 */
		mpc_init2(*z, mpc_get_prec(*z1));
		mpc_add(*z, *z1, *z2, MPC_RNDNN);
	} else if (Rf_isInteger(e2)) {
		Rprintf("It's an int : %d", INTEGER(e2)[0]);
		mpc_init2(*z, mpc_get_prec(*z1));
		Rprintf("AFter init");
		mpc_add_ui(*z, *z1, INTEGER(e2)[0], MPC_RNDNN);
	} else if (Rf_isNumeric(e2)) {
		Rprintf("It's a real : %f\n", REAL(e2)[0]);
		mpfr_t x;
		mpfr_init2(x, 53);
		mpfr_set_d(x, REAL(e2)[0], MPFR_RNDN);
/*	TODO support mpfr packge somehow.  Create one from a numeric. */
		/* Max of mpc precision z2 and 53 from e2. */
		Rprintf("Precision: %d\n", mpc_get_prec(*z1));
		mpc_init2(*z, mpc_get_prec(*z1));
		mpc_add_fr(*z, *z1, x, MPC_RNDNN);
	} else {
		Rprintf("It's unknown");
		free(z);
		Rf_error("Invalid second operand for mpc addition.");
	}
	Rprintf("Now building return value\n");
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z, Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}


SEXP R_mpc_sub(SEXP e1, SEXP e2) {
	/* TODO switch on class of e2 here don't assume both mpc. */
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	if (z == NULL) {
		Rf_error("Could not allocate memory for MPC type.");
	}

	if (Rf_inherits(e1, "mpc")) {
		Rprintf("It's an mpc");
		mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
		if (Rf_inherits(e2, "mpc")) {
			mpc_t *z2 = (mpc_t *)R_ExternalPtrAddr(e2);
			mpc_init2(*z, max(mpc_get_prec(*z1), mpc_get_prec(*z2)));
			mpc_sub(*z, *z1, *z2, MPC_RNDNN);
		} else if (Rf_isInteger(e2)) {
			mpc_init2(*z, mpc_get_prec(*z1));
			mpc_sub_ui(*z, *z1, INTEGER(e2)[0], MPC_RNDNN);
		} else if (Rf_isNumeric(e2)) {
			mpfr_t x;
			mpfr_init2(x, 53);
			mpfr_set_d(x, REAL(e2)[0], MPFR_RNDN);
/*	TODO support mpfr packge somehow.  Create one from a numeric. */
		/* Max of mpc precision z2 and 53 from e2. */
			Rprintf("Precision: %d\n", mpc_get_prec(*z1));
			mpc_init2(*z, max(mpc_get_prec(*z1), 53));
			mpc_sub_fr(*z, *z1, x, MPC_RNDNN);
		} else {
			Rf_error("Unsupported type for operand 2 of MPC subtraction.");
		}
	} else if (Rf_isInteger(e1)) {
		if (Rf_inherits(e2, "mpc")) {
			mpc_t *z2 = (mpc_t *)R_ExternalPtrAddr(e2);
			mpc_init2(*z, mpc_get_prec(*z2));
			mpc_ui_sub(*z, INTEGER(e1)[0], *z2, MPC_RNDNN);
		} else {
			Rf_error("Unsupported type for operands for MPC subtraction.");
		}
	} else if (Rf_isNumeric(e1)) {
		if (Rf_inherits(e2, "mpc")) {
			mpc_t *z2 = (mpc_t *)R_ExternalPtrAddr(e2);
			mpc_init2(*z, mpc_get_prec(*z2));
			mpfr_t x;
			mpfr_init2(x, 53);
			mpfr_set_d(x, REAL(e1)[0], MPFR_RNDN);
			mpc_fr_sub(*z, x, *z2, MPC_RNDNN);
		} else {
			Rf_error("Unsupported type for operands for MPC subtraction.");
		}
	} else {
		Rprintf("It's unknown");
		free(z);
		Rf_error("Invalid second operand for mpc subtraction.");
	}
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z, Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}

SEXP R_mpc_mul(SEXP e1, SEXP e2) {
	/* N.B. We always use signed integers for e2 given R's type system. */
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	if (Rf_inherits(e1, "mpc")) {
		mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
		if (Rf_inherits(e2, "mpc")) {
			mpc_t *z2 = (mpc_t *)R_ExternalPtrAddr(e2);
			mpc_init2(*z, max(mpc_get_prec(*z1), mpc_get_prec(*z2)));
			mpc_mul(*z, *z1, *z2, MPC_RNDNN);
		} else if (Rf_isInteger(e2)) {
			mpc_init2(*z, mpc_get_prec(*z1));
			mpc_mul_si(*z, *z1, INTEGER(e2)[0], MPC_RNDNN);
		} else if (Rf_isNumeric(e2)) {
			mpc_init2(*z, mpc_get_prec(*z1));
			mpfr_t x;
			mpfr_init2(x, 53);
			mpfr_set_d(x, REAL(e2)[0], MPFR_RNDN);
			mpc_mul_fr(*z, *z1, x, MPC_RNDNN);
		} else {
			Rf_error("Invalid second operand for mpc multiplication.");
		}
	} else {
		Rf_error("Invalid first operand for MPC multiplication.");
	}
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z, Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}

SEXP R_mpc_div(SEXP e1, SEXP e2) {
	/* N.B. We always use signed integers for e2 given R's type system. */
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	if (Rf_inherits(e1, "mpc")) {
		mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
		if (Rf_inherits(e2, "mpc")) {
			mpc_t *z2 = (mpc_t *)R_ExternalPtrAddr(e2);
			mpc_init2(*z, max(mpc_get_prec(*z1), mpc_get_prec(*z2)));
			mpc_div(*z, *z1, *z2, MPC_RNDNN);
		} else if (Rf_isInteger(e2)) {
			mpc_init2(*z, mpc_get_prec(*z1));
			mpc_div_ui(*z, *z1, INTEGER(e2)[0], MPC_RNDNN);
		} else if (Rf_isNumeric(e2)) {
			mpc_init2(*z, mpc_get_prec(*z1));
			mpfr_t x;
			mpfr_init2(x, 53);
			mpfr_set_d(x, REAL(e2)[0], MPFR_RNDN);
			mpc_div_fr(*z, *z1, x, MPC_RNDNN);
		} else {
			Rf_error("Invalid second operand for mpc division.");
		}
	} else if (Rf_isInteger(e1)) {
		if (Rf_inherits(e2, "mpc")) {
			/* TODO: sign issue here.  mpc_ui_div is unsigned, mult -1 if needed by asnwer? */
			mpc_t *z2 = (mpc_t *)R_ExternalPtrAddr(e2);
			mpc_init2(*z, mpc_get_prec(*z2));
			mpc_ui_div(*z, INTEGER(e1)[0], *z2, MPC_RNDNN);
		} else {
			Rf_error("Invalid second operand for mpc division.");
		}
	} else if (Rf_isNumeric(e1)) {
		if (Rf_inherits(e2, "mpc")) {
			mpc_t *z2 = (mpc_t *)R_ExternalPtrAddr(e2);
			mpfr_t x;
			mpfr_init2(x, 53);
			mpfr_set_d(x, REAL(e2)[0], MPFR_RNDN);
			mpc_fr_div(*z, x, *z2, MPC_RNDNN);

		} else {
			Rf_error("Invalid second operand for mpc division.");
		}
	} else {
		Rf_error("Invalid operands for mpc division.");
	}
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z, Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}

SEXP R_mpc_neg(SEXP e1) {
	/* Garbage collector will be confused if we just call mpc_neg(*z, *z, ...) */
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	if (Rf_inherits(e1, "mpc")) {
		mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
		mpc_init2(*z, mpc_get_prec(*z1));
		mpc_neg(*z, *z1, MPC_RNDNN);
	} else {
		Rf_error("Invalid operands for mpc negation.");
	}
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z, Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}

/* 5.8 Power Functions and Logarithm. */

SEXP R_mpc_pow(SEXP e1, SEXP e2) {
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	if (Rf_inherits(e1, "mpc")) {
		mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
		if (Rf_inherits(e2, "mpc")) {
			mpc_t *z2 = (mpc_t *)R_ExternalPtrAddr(e2);
			mpc_init2(*z, max(mpc_get_prec(*z1), mpc_get_prec(*z2)));
			mpc_pow(*z, *z1, *z2, MPC_RNDNN);
		} else if (Rf_isInteger(e2)) {
			mpc_init2(*z, mpc_get_prec(*z1));
			mpc_pow_si(*z, *z1, INTEGER(e2)[0], MPC_RNDNN);
		} else if (Rf_isNumeric(e2)) {
			mpc_init2(*z, mpc_get_prec(*z1));
			mpc_pow_d(*z, *z1, REAL(e2)[0], MPC_RNDNN);
		} else {
			Rf_error("Invalid second operand for mpc power.");
		}
	} else {
		Rf_error("Invalid first operand for MPC power.");
	}
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z, Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}

SEXP R_mpc_cmp(SEXP e1, SEXP e2) {
	if (Rf_inherits(e1, "mpc")) {
		mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
		if (Rf_inherits(e2, "mpc")) {
			mpc_t *z2 = (mpc_t *)R_ExternalPtrAddr(e2);
			return(Rf_ScalarInteger(mpc_cmp(*z1, *z2)));
		} else if (Rf_isInteger(e2)) {
			return(Rf_ScalarInteger(mpc_cmp_si(*z1, INTEGER(e2)[0])));
		} else {
			Rf_error("Invalid operand for mpc cmp.");
		}
	} else {
		Rf_error("Invalid operand for mpc cmp.");
	}
}

SEXP R_mpc_conj(SEXP x) {
	if (!Rf_inherits(x, "mpc")) {
		Rf_error("Invalid operand for conj.mpc");
	}
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(x);
	mpc_init2(*z, mpc_get_prec(*z1));
	mpc_conj(*z, *z1, MPC_RNDNN);
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z, Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}
