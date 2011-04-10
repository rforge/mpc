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

getPrec <- function(z) {
  stopifnot(inherits(z, "mpc"))
  return(.Call("R_mpc_get_prec", z, PACKAGE="mpc"))
}

urandom.mpc <- function(precision) {
  stopifnot(is.numeric(precision))
  return(.Call("R_mpc_urandom", as.integer(precision), PACKAGE="mpc"))
}

mpcVersion <- function() .Call("R_mpc_get_version", PACKAGE="mpc")
