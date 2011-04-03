# Copyright(c) 2011 Murray M. Stokely
#
# This file is part of the R Multiple Precision Complex package, mpc.
#
# mpc is free software: you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# http://mpc.r-forge.r-project.org/

mpc <- function(z, precision) {
  stopifnot(is.numeric(precision))
  .Call("as_mpc_numeric", z, as.integer(precision), PACKAGE="mpc")
}

as.mpc <- function(z, precision=52) {
  stopifnot(is.numeric(precision))
  stopifnot(is.numeric(z) || is.complex(z))
  .Call("as_mpc_numeric", z, as.integer(precision), PACKAGE="mpc")
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
  cat("Output: ",
      .Call("print_mpc", object, PACKAGE="mpc"),
      "\nPrecision: ", .Call("R_mpc_get_prec", object, PACKAGE="mpc"), "\n")
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
