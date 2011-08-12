# Copyright 2011 Google Inc.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA
#
# http://mpc.r-forge.r-project.org/

mpc <- function(z, precision) {
  stopifnot(is.numeric(precision))
  if (length(z) == 1) {
    .Call("R_mpc", z, as.integer(precision), PACKAGE="mpc")
  } else {
    unlist(sapply(z, .Call("R_mpc", z, as.integer(precision), PACKAGE="mpc")))
  }
}

as.mpc <- function(z, precision) {
  stopifnot(is.numeric(precision))
  stopifnot(is.numeric(z) || is.complex(z))
  .Call("R_mpc", z, as.integer(precision), PACKAGE="mpc")
}

is.mpc <- function(z) {
  return(inherits(z, "mpc"))
}

as.complex.mpc <- function(x, ...) {
  complex(1, Re.mpc(x), Im.mpc(x))
}

as.double.mpc <- function(x, ...) {
  stopifnot(Im.mpc(x) == 0)
  as.numeric(Re.mpc(x))
}

print.mpc <-function(x, ...) {
  print(.Call("print_mpc", x, PACKAGE="mpc"))
}

summary.mpc <- function(object, ...) {
  precision <- .Call("R_mpc_get_prec", object, PACKAGE="mpc")
  cat("Output: ",
      .Call("print_mpc", object, PACKAGE="mpc"),
      "\nReal Precision: ", precision[1],
      "Imaginary Precision: ", precision[2],
      "\n")
}

Conj.mpc <- function(z) {
  .Call("R_mpc_conj", z)
}

# 5.6 Projection and Decomposing Functions.

Re.mpc <- function(z) {
  stopifnot(inherits(z, "mpc"))
  .Call("R_mpc_real", z, PACKAGE="mpc")
}

Im.mpc <- function(z) {
  stopifnot(inherits(z, "mpc"))
  .Call("R_mpc_imag", z, PACKAGE="mpc")
}

Arg.mpc <- function(z) {
  stopifnot(inherits(z, "mpc"))
  .Call("R_mpc_arg", z, PACKAGE="mpc")
}

# 5.8 Power and Logarithm Functions.
log.mpc <- function(x, base=exp(1)) {
  stopifnot(is.numeric(base) || is.mpc(base))
  result <- .Call("R_mpc_log", x, PACKAGE="mpc")
  if (base == exp(1)) {
    return(result)
  } else {
    return(result / log(base))
  }
}

exp.mpc <- function(x) { 
  .Call("R_mpc_exp", x, PACKAGE="mpc")
}

# Utilities for testing

#ulp <- function(x, y) {
#  stopifnot(is.numeric(x), is.numeric(y))
#  stopifnot(length(x) == length(y))
#  return(.Call("R_ulp", x, y, PACKAGE="mpc"))
#}
