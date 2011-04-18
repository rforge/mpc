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

/* 5.6 Projection and Decomposing Functions. */

/* Only supported for components that fit in a real. */
/* TODO(mstokely): Support larger components here with Rmpfr. */

SEXP R_mpc_real(SEXP e1) {
	if (Rf_inherits(e1, "mpc")) {
		mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
		if (mpfr_fits_sint_p(mpc_realref(*z1), GMP_RNDN)) {
			double y = mpfr_get_d(mpc_realref(*z1), GMP_RNDN);
			return Rf_ScalarReal(y);
		} else {
			Rf_error("Real part doesn't fit in numeric.");
		}
	} else {
		Rf_error("Invalid operand for MPC log.");
	}
	return R_NilValue;	/* Not reached */
}

SEXP R_mpc_imag(SEXP e1) {
	if (Rf_inherits(e1, "mpc")) {
		mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
		if (mpfr_fits_sint_p(mpc_imagref(*z1), GMP_RNDN)) {
			return Rf_ScalarReal(mpfr_get_d(mpc_imagref(*z1),
				GMP_RNDN));
		} else {
			Rf_error("Imaginary part doesn't fit in numeric.");
		}
	} else {
		Rf_error("Invalid operand for MPC log.");
	}
	return R_NilValue;	/* Not reached */
}

SEXP R_mpc_arg(SEXP e1) {
	mpfr_t x;
	if (Rf_inherits(e1, "mpc")) {
		mpc_t *z1 = (mpc_t *)R_ExternalPtrAddr(e1);
		mpc_arg(x, *z1, GMP_RNDN);
		if (mpfr_fits_sint_p(x, GMP_RNDN)) {
			return Rf_ScalarReal(mpfr_get_d(x, GMP_RNDN));
		} else {
			Rf_error("Arg doesn't fit in numeric.");
		}
	} else {
		Rf_error("Invalid operand for MPC log.");
	}
	return R_NilValue;	/* Not reached */
}
