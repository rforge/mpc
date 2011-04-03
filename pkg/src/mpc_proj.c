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

/* 5.6 Projection and Decomposing Functions. */

/* Only supported for components that fit in a real. */
/* TODO(mstokely): Support larger components here. */

SEXP R_mpc_real(SEXP e1) {
	if (Rf_inherits(e1, "mpc")) {
		mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
		if (mpfr_fits_uint_p(mpc_realref(*z1), MPFR_RNDN)) {
			double y = mpfr_get_d(mpc_realref(*z1), MPFR_RNDN);
			return Rf_ScalarReal(y);
		} else {
			Rf_error("Real part doesn't fit in numeric.");
		}
	} else {
		Rf_error("Invalid operand for MPC log.");
	}
}

SEXP R_mpc_imag(SEXP e1) {
	if (Rf_inherits(e1, "mpc")) {
		mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
		if (mpfr_fits_uint_p(mpc_imagref(*z1), MPFR_RNDN)) {
			return Rf_ScalarReal(mpfr_get_d(mpc_imagref(*z1),
				MPFR_RNDN));
		} else {
			Rf_error("Imaginary part doesn't fit in numeric.");
		}
	} else {
		Rf_error("Invalid operand for MPC log.");
	}
}

SEXP R_mpc_arg(SEXP e1) {
	mpfr_t x;
	if (Rf_inherits(e1, "mpc")) {
		mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
		mpc_arg(x, *z1, MPFR_RNDN);
		if (mpfr_fits_uint_p(x, MPFR_RNDN)) {
			return Rf_ScalarReal(mpfr_get_d(x, MPFR_RNDN));
		} else {
			Rf_error("Arg doesn't fit in numeric.");
		}
	} else {
		Rf_error("Invalid operand for MPC log.");
	}
}
