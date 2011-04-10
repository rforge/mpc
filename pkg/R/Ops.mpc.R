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

.equality.mpc <- function(e1, e2)
{
  # Ensure first operand is mpc type, second possibly not.
  if (!inherits(e1, "mpc")) {
    tmp <- e2
    e2 <- e1
    e1 <- tmp
  }
  stopifnot(inherits(e1, "mpc"))
  # mpc library can compare MPCs against integers or other MPCs,
  # but not floats or complex numbers, so convert if necessary.
  if ((is.numeric(e2) && !is.integer(e2)) || is.complex(e2)) {
    e2 <- mpc(e2, .Call("R_mpc_get_prec", e1, PACKAGE="mpc"))
  }
  return(.Call("R_mpc_cmp", e1, e2, PACKAGE="mpc") == 0)
}

Ops.mpc <- function (e1, e2) 
{
    switch(.Generic,
    "+" = {
             return(.Call("R_mpc_add", e1, e2, PACKAGE="mpc"))
       },
    "-" = {
       if (missing(e2)) {
          return(.Call("R_mpc_neg", e1, PACKAGE="mpc"))
       } else {
          return(.Call("R_mpc_sub", e1, e2, PACKAGE="mpc"))
       }
    },
    "*" = {
        stopifnot(inherits(e1, "mpc"))
        return(.Call("R_mpc_mul", e1, e2, PACKAGE="mpc"))
       },
    "/" = return(.Call("R_mpc_div", e1, e2, PACKAGE="mpc")),
    "^" = return(.Call("R_mpc_pow", e1, e2, PACKAGE="mpc")),
    "%%" = stop(.Generic, " not yet supported with mpc types."),
    "%/%" = stop(.Generic, " not yet supported with mpc types."),
    "&" = stop(.Generic, " not yet supported with mpc types."),
    "|" = stop(.Generic, " not yet supported with mpc types."),
    "!" = stop(.Generic, " not yet supported with mpc types."),
    "==" = return(.equality.mpc(e1, e2)),
    "!=" = return(!.equality.mpc(e1, e2)),
    "<" = stop(.Generic, " not yet supported with mpc types."),
    "<=" = stop(.Generic, " not yet supported with mpc types."),
    ">=" = stop(.Generic, " not yet supported with mpc types."),
    ">" = stop(.Generic, " not yet supported with mpc types."),
    NextMethod(.Generic))
}
