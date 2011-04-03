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
    "==" = return(.Call("R_mpc_cmp", e1, e2, PACKAGE="mpc") == 0),
    "!=" = stop(.Generic, " not yet supported with mpc types."),
    "<" = stop(.Generic, " not yet supported with mpc types."),
    "<=" = stop(.Generic, " not yet supported with mpc types."),
    ">=" = stop(.Generic, " not yet supported with mpc types."),
    ">" = stop(.Generic, " not yet supported with mpc types."),
    NextMethod(.Generic))
}
