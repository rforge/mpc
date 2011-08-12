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
#include <string.h>
#include <math.h>
#include <float.h>

#include "mpc.h"
#include "mpfr.h"
#define R_NO_REMAP   /* avoid collisions with stl definitions */

#include <Rinternals.h>
#include "Rmpc.h"

static gmp_randstate_t R_mpc_seed_state;
static int R_mpc_seed_init = 0;

static int max(int a, int b) {
	return (b < a) ? a : b;
}

void mpcFinalizer(SEXP ptr) {
	mpc_t *z = (mpc_t *)R_ExternalPtrAddr(ptr);
	if (z) {
		mpc_clear(*z);
		free(z);
		R_ClearExternalPtr(ptr);
	}
}

/* Rmpc_get_max_prec - return the maximum precision of two mpc_t.
 *
 * Reads in the precision used for storing the two provided mpc_t
 * variables and stores the maximum of the real and imaginary
 * precision through the provided pointers.
 *
 * Args:
 *   real_prec: Pointer to store the necessary precision for real part.
 *   imag_prec: Pointer to store the necessary precision for imaginary part.
 *   z1:        An mpc_t
 *   z2:        An mpc_t
 * Return value:
 *   None.
 */
void Rmpc_get_max_prec(mpfr_prec_t *real_prec,
    mpfr_prec_t *imag_prec, mpc_t z1, mpc_t z2) {
	mpfr_prec_t rp1, ip1, rp2, ip2;
	mpc_get_prec2(&rp1, &ip1, z1);
	mpc_get_prec2(&rp2, &ip2, z2);

	*real_prec = max(rp1, rp2);
	*imag_prec = max(ip1, ip2);
}

/* Rmpc_get_rounding - return the MPC rounding method based on R option.
 *
 * Args:
 *   None
 * Return value:
 *   An MPC rounding mode, e.g. MPC_RNDNN.
 */
int Rmpc_get_rounding() {
	const char *round_mode = CHAR(STRING_ELT(Rf_GetOption(
			Rf_install("mpc.rounding"), R_BaseEnv), 0));
	int real_round, imag_round;
	if (strlen(round_mode) != 9) {
		Rf_warning("Invalid mpc.rounding option, using MPC_RNDNN");
		return(MPC_RNDNN);
	}
	switch (round_mode[7]) {
	case 'N':
		real_round = GMP_RNDN;
		break;
	case 'Z':
		real_round = GMP_RNDZ;
		break;
	case 'U':
		real_round = GMP_RNDU;
		break;
	case 'D':
		real_round = GMP_RNDD;
		break;
	default:
		Rf_warning("Invalid mpc.rounding option, using MPC_RNDNN");
		return(MPC_RNDNN);
	}
	switch(round_mode[8]) {
	case 'N':
		imag_round = GMP_RNDN;
		break;
	case 'Z':
		imag_round = GMP_RNDZ;
		break;
	case 'U':
		imag_round = GMP_RNDU;
		break;
	case 'D':
		imag_round = GMP_RNDD;
		break;
	default:
		Rf_warning("Invalid mpc.rounding option, using MPC_RNDNN");
		return(MPC_RNDNN);
	}
	return (RNDC(real_round, imag_round));
}

SEXP print_mpc(SEXP ptr) {
	mpc_ptr z = (mpc_ptr)R_ExternalPtrAddr(ptr);
	SEXP retVal;
	Rprintf("Rounding: %s\n",
	    CHAR(STRING_ELT(Rf_GetOption(Rf_install("mpc.rounding"),
			R_BaseEnv), 0)));
	if (z) {
		char *mystring = mpc_get_str(10, 0, z, Rmpc_get_rounding());
		PROTECT(retVal = Rf_mkString(mystring));
		UNPROTECT(1);
		return retVal;
	}
	return R_NilValue;
}

/* Section 5.1 Initialization Functions */

/* R_mpc_get_prec - Return precision used for an MPC S3 object.
 *
 * Args:
 *   ptr -    An MPC S3 object.
 * Returns:
 *   Vector of length two for real and imaginary precision bits for MPC.
 */
SEXP R_mpc_get_prec(SEXP ptr) {
	mpc_ptr z = (mpc_ptr)R_ExternalPtrAddr(ptr);
	SEXP retVal;
	if (z) {
		PROTECT(retVal = Rf_allocVector(INTSXP, 2));
		mpfr_prec_t real_prec, imag_prec;
		mpc_get_prec2(&real_prec, &imag_prec, z);
		INTEGER(retVal)[0] = real_prec;
		INTEGER(retVal)[1] = imag_prec;
		UNPROTECT(1);
		return retVal;
	}
	return R_NilValue;
}

/* MakeMPC - Create an MPC ExternalPtr object for R based on a C mpc_t.
 *
 * Args:
 *   z -    An mpc_t pointer.
 * Returns:
 *   An S3 object of type "mpc" containing the external pointer to z.
 */
SEXP MakeMPC(mpc_t *z) {
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}

/* R_mpc - Create an MPC S3 object for arbitrary precision complex numbers.
 *
 * We currently use external pointers for performance reasons, which
 * means that we can't allocVector a list of length(n) MPC objects,
 * and instead must instantiate them one at a time, that a caller can
 * put into a list if they want, but not a vector.
 *
 * Args:
 *   n -   An integer, numeric, or complex number to convert to an MPC.
 *   sprec  - The number of bits of precision to use, e.g. 52 for doubles.
 */
SEXP R_mpc(SEXP n, SEXP sprec) {
	/* TODO: INTEGER returns 32bit integer but mpfr_prec_t may be
	 * 64bit. This is based on how mpfr was compiled. Therefore we
	 * could add this as a configure check? */
	mpfr_prec_t prec = INTEGER(sprec)[0];
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	if (z == NULL) {
		Rf_error("Could not allocate memory for MPC type.");
	}
	mpc_init2(*z, prec);

	if (Rf_isNumeric(n)) {
		mpc_set_d(*z, REAL(n)[0], Rmpc_get_rounding());
	} else if (Rf_isComplex(n)) {
		mpc_set_d_d(*z, COMPLEX(n)[0].r, COMPLEX(n)[0].i,
		    Rmpc_get_rounding());
	} else if (Rf_isString(n)) {
		mpc_set_str(*z, CHAR(STRING_ELT(n, 0)), 10,
		    Rmpc_get_rounding());
	} else {
		Rf_error("Unsupported type conversion to MPC.");
	}
	return(MakeMPC(z));
}


/* Section 5.7 Basic Arithmetic Functions */

SEXP R_mpc_add(SEXP e1, SEXP e2) {
	mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	if (z == NULL) {
		Rf_error("Could not allocate memory for MPC type.");
	}

	if (Rf_inherits(e2, "mpc")) {
		mpc_t *z2 = (mpc_t *)R_ExternalPtrAddr(e2);
		mpfr_prec_t real_prec, imag_prec;
		Rmpc_get_max_prec(&real_prec, &imag_prec, *z1, *z2);
		mpc_init3(*z, real_prec, imag_prec);
		mpc_add(*z, *z1, *z2, Rmpc_get_rounding());
	} else if (Rf_isInteger(e2)) {
		mpc_init2(*z, mpc_get_prec(*z1));
		mpc_add_ui(*z, *z1, INTEGER(e2)[0], Rmpc_get_rounding());
	} else if (Rf_isNumeric(e2)) {
		mpfr_t x;
		mpfr_init2(x, 53);
                // We use GMP_RNDN rather than MPFR_RNDN for compatibility
                // with mpfr 2.4.x and earlier as well as more modern versions.
		mpfr_set_d(x, REAL(e2)[0], GMP_RNDN);
		/* Max of mpc precision z2 and 53 from e2. */
		Rprintf("Precision: %d\n", mpc_get_prec(*z1));
		mpc_init2(*z, max(mpc_get_prec(*z1), 53));
		mpc_add_fr(*z, *z1, x, Rmpc_get_rounding());
	} else {
		/* TODO(mstokely): Add support for mpfr types here. */
		free(z);
		Rf_error("Invalid second operand for mpc addition.");
	}
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}


SEXP R_mpc_sub(SEXP e1, SEXP e2) {
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	if (z == NULL) {
		Rf_error("Could not allocate memory for MPC type.");
	}

	if (Rf_inherits(e1, "mpc")) {
		Rprintf("It's an mpc");
		mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
		if (Rf_inherits(e2, "mpc")) {
			mpc_t *z2 = (mpc_t *)R_ExternalPtrAddr(e2);
			mpc_init2(*z, max(mpc_get_prec(*z1),
				mpc_get_prec(*z2)));
			mpc_sub(*z, *z1, *z2, Rmpc_get_rounding());
		} else if (Rf_isInteger(e2)) {
			mpc_init2(*z, mpc_get_prec(*z1));
			mpc_sub_ui(*z, *z1, INTEGER(e2)[0],
			    Rmpc_get_rounding());
		} else if (Rf_isNumeric(e2)) {
			mpfr_t x;
			mpfr_init2(x, 53);
			mpfr_set_d(x, REAL(e2)[0], GMP_RNDN);
			Rprintf("Precision: %d\n", mpc_get_prec(*z1));
			mpc_init2(*z, max(mpc_get_prec(*z1), 53));
			mpc_sub_fr(*z, *z1, x, Rmpc_get_rounding());
		} else {
			Rf_error("Unsupported type for operand 2 of MPC subtraction.");
		}
	} else if (Rf_isInteger(e1)) {
		if (Rf_inherits(e2, "mpc")) {
			mpc_t *z2 = (mpc_t *)R_ExternalPtrAddr(e2);
			mpc_init2(*z, mpc_get_prec(*z2));
			mpc_ui_sub(*z, INTEGER(e1)[0], *z2,
			    Rmpc_get_rounding());
		} else {
			Rf_error("Unsupported type for operands for MPC subtraction.");
		}
	} else if (Rf_isNumeric(e1)) {
		if (Rf_inherits(e2, "mpc")) {
			mpc_t *z2 = (mpc_t *)R_ExternalPtrAddr(e2);
			mpc_init2(*z, mpc_get_prec(*z2));
			mpfr_t x;
			mpfr_init2(x, 53);
			mpfr_set_d(x, REAL(e1)[0], GMP_RNDN);
			mpc_fr_sub(*z, x, *z2, Rmpc_get_rounding());
		} else {
			Rf_error("Unsupported type for operands for MPC subtraction.");
		}
	} else {
		/* TODO(mstokely): Add support for mpfr types here. */
		Rprintf("It's unknown");
		free(z);
		Rf_error("Invalid second operand for mpc subtraction.");
	}
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
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
			mpc_init2(*z, max(mpc_get_prec(*z1),
				mpc_get_prec(*z2)));
			mpc_mul(*z, *z1, *z2, Rmpc_get_rounding());
		} else if (Rf_isInteger(e2)) {
			mpc_init2(*z, mpc_get_prec(*z1));
			mpc_mul_si(*z, *z1, INTEGER(e2)[0],
			    Rmpc_get_rounding());
		} else if (Rf_isNumeric(e2)) {
			mpc_init2(*z, mpc_get_prec(*z1));
			mpfr_t x;
			mpfr_init2(x, 53);
			mpfr_set_d(x, REAL(e2)[0], GMP_RNDN);
			mpc_mul_fr(*z, *z1, x, Rmpc_get_rounding());
		} else {
			Rf_error("Invalid second operand for mpc multiplication.");
		}
	} else {
		Rf_error("Invalid first operand for MPC multiplication.");
	}
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
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
			mpc_init2(*z, max(mpc_get_prec(*z1),
				mpc_get_prec(*z2)));
			mpc_div(*z, *z1, *z2, Rmpc_get_rounding());
		} else if (Rf_isInteger(e2)) {
			mpc_init2(*z, mpc_get_prec(*z1));
			mpc_div_ui(*z, *z1, INTEGER(e2)[0],
			    Rmpc_get_rounding());
		} else if (Rf_isNumeric(e2)) {
			mpc_init2(*z, mpc_get_prec(*z1));
			mpfr_t x;
			mpfr_init2(x, 53);
			mpfr_set_d(x, REAL(e2)[0], GMP_RNDN);
			mpc_div_fr(*z, *z1, x, Rmpc_get_rounding());
		} else {
			Rf_error("Invalid second operand for mpc division.");
		}
	} else if (Rf_isInteger(e1)) {
		if (Rf_inherits(e2, "mpc")) {
			/* TODO: sign issue here.  mpc_ui_div is
			 * unsigned, mult -1 if needed by asnwer? */
			mpc_t *z2 = (mpc_t *)R_ExternalPtrAddr(e2);
			mpc_init2(*z, mpc_get_prec(*z2));
			mpc_ui_div(*z, INTEGER(e1)[0], *z2,
			    Rmpc_get_rounding());
		} else {
			Rf_error("Invalid second operand for mpc division.");
		}
	} else if (Rf_isNumeric(e1)) {
		if (Rf_inherits(e2, "mpc")) {
			mpc_t *z2 = (mpc_t *)R_ExternalPtrAddr(e2);
			mpfr_t x;
			mpfr_init2(x, 53);
			mpfr_set_d(x, REAL(e2)[0], GMP_RNDN);
			mpc_fr_div(*z, x, *z2, Rmpc_get_rounding());

		} else {
			Rf_error("Invalid second operand for mpc division.");
		}
	} else {
		Rf_error("Invalid operands for mpc division.");
	}
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}

SEXP R_mpc_neg(SEXP e1) {
	/* Garbage collector will be confused if we just call
	 * mpc_neg(*z, *z, ...) */
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	if (Rf_inherits(e1, "mpc")) {
		mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
		mpc_init2(*z, mpc_get_prec(*z1));
		mpc_neg(*z, *z1, Rmpc_get_rounding());
	} else {
		Rf_error("Invalid operands for mpc negation.");
	}
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
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
			mpc_init2(*z, max(mpc_get_prec(*z1),
				mpc_get_prec(*z2)));
			mpc_pow(*z, *z1, *z2, Rmpc_get_rounding());
		} else if (Rf_isInteger(e2)) {
			mpc_init2(*z, mpc_get_prec(*z1));
			mpc_pow_si(*z, *z1, INTEGER(e2)[0],
			    Rmpc_get_rounding());
		} else if (Rf_isNumeric(e2)) {
			mpc_init2(*z, mpc_get_prec(*z1));
			mpc_pow_d(*z, *z1, REAL(e2)[0], Rmpc_get_rounding());
		} else {
			Rf_error("Invalid second operand for mpc power.");
		}
	} else {
		Rf_error("Invalid first operand for MPC power.");
	}
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}

/* R_mpc_cmp - Comparison function for MPC objects.
 *
 * Ops.mpc.R includes code to coerce complex numbers or numerics from
 * e2 into MPC objects for this comparison since the MPC library only
 * supports comparison against other MPC objects or integers.
 *
 * Arguments:
 *  e1:    SEXP for an mpc type.
 *  e2:    SEXP for an mpc type, or integer.
 * Return value:
 *  True if e1 == e2.
 */
SEXP R_mpc_cmp(SEXP e1, SEXP e2) {
	if (Rf_inherits(e1, "mpc")) {
		mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
		if (Rf_inherits(e2, "mpc")) {
			mpc_t *z2 = (mpc_t *)R_ExternalPtrAddr(e2);
			return(Rf_ScalarInteger(mpc_cmp(*z1, *z2)));
		} else if (Rf_isInteger(e2)) {
			return(Rf_ScalarInteger(mpc_cmp_si(*z1,
				    INTEGER(e2)[0])));
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
	mpc_conj(*z, *z1, Rmpc_get_rounding());
	SEXP retVal = PROTECT(R_MakeExternalPtr((void *)z,
		Rf_install("mpc ptr"), R_NilValue));
	Rf_setAttrib(retVal, R_ClassSymbol, Rf_mkString("mpc"));
	R_RegisterCFinalizerEx(retVal, mpcFinalizer, TRUE);
	UNPROTECT(1);
	return retVal;
}

//SEXP R_ulp(SEXP y, SEXP z)
//{
//        int n;
//        double f;
//        f = frexp(REAL(y)[0], &n);
//        f = fabs(f - ldexp(REAL(z)[0], -n));
//        f = ldexp(f, DBL_MANT_DIG - 1);
//        return Rf_ScalarReal(f);
//}

SEXP R_mpc_urandom(SEXP sprec)
{
	mpfr_prec_t prec = INTEGER(sprec)[0];
	mpc_t *z = (mpc_t *)malloc(sizeof(mpc_t));
	if (z == NULL) {
		Rf_error("Could not allocate memory for MPC type.");
	}
	mpc_init2(*z, prec);

	if (!R_mpc_seed_init) {
		gmp_randinit_default(R_mpc_seed_state);
		R_mpc_seed_init = 1;
	}
	mpc_urandom((mpc_ptr)z, R_mpc_seed_state);
	return(MakeMPC(z));
}

SEXP R_mpc_get_version()
{
	return Rf_mkString(mpc_get_version());
}
