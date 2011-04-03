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

#define R_NO_REMAP   /* avoid collisions with stl definitions */

#include <Rinternals.h>

void mpcFinalizer(SEXP ptr);
