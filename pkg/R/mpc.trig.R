# Copyright 2018 Martin Maechler
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

# http://www.multiprecision.org/index.php?prog=mpc&page=html#Trigonometric-Functions

sin.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call(R_mpc_sin, x))
}

cos.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call(R_mpc_cos, x))
}

tan.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call(R_mpc_tan, x))
}

sinh.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call(R_mpc_sinh, x))
}

cosh.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call(R_mpc_cosh, x))
}

tanh.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call(R_mpc_tanh, x))
}

asin.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call(R_mpc_asin, x))
}

acos.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call(R_mpc_acos, x))
}

atan.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call(R_mpc_atan, x))
}

asinh.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call(R_mpc_asinh, x))
}

acosh.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call(R_mpc_acosh, x))
}

atanh.mpc <- function(x) {
        stopifnot(inherits(x, "mpc"))
        return(.Call(R_mpc_atanh, x))
}
