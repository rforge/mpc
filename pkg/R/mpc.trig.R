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

# http://www.multiprecision.org/index.php?prog=mpc&page=html#Trigonometric-Functions

sin.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call("R_mpc_sin", x, PACKAGE="mpc"))
}

cos.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call("R_mpc_cos", x, PACKAGE="mpc"))
}

tan.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call("R_mpc_tan", x, PACKAGE="mpc"))
}

sinh.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call("R_mpc_sinh", x, PACKAGE="mpc"))
}

cosh.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call("R_mpc_cosh", x, PACKAGE="mpc"))
}

tanh.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call("R_mpc_tanh", x, PACKAGE="mpc"))
}

asin.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call("R_mpc_asin", x, PACKAGE="mpc"))
}

acos.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call("R_mpc_acos", x, PACKAGE="mpc"))
}

atan.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call("R_mpc_atan", x, PACKAGE="mpc"))
}

asinh.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call("R_mpc_asinh", x, PACKAGE="mpc"))
}

acosh.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call("R_mpc_acosh", x, PACKAGE="mpc"))
}

atanh.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call("R_mpc_atanh", x, PACKAGE="mpc"))
}
