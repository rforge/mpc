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

test.cmp <- function() {
  checkTrue(as.integer(10) == mpc(10, 52))
  checkTrue(mpc(10,52) == mpc(10, 32))
  checkTrue(10 == mpc(10,52))
  checkTrue(mpc(10,52) == 10)
  checkTrue(mpc(10,52) != 10.1)
}

test.ops <- function() {
  checkTrue(1 == mpc(3,52) / mpc(3,52))
  checkTrue(2 == mpc(6,52) / mpc(3,52))
  checkTrue(1.5 == mpc(3,52) / mpc(2,52))

  checkTrue(-1 == -mpc(3,52) / as.integer(3))
  checkTrue(-1 != -mpc(3,52) / 3.1)

  checkTrue(2^2 == mpc(2,52) ^ mpc(2,52))

  checkEquals(2, Re(mpc(2,10)))
  checkEquals(0, Im(mpc(3000, 100)))

  checkEquals(2.1, Im(mpc(3+2.1i, 52)))
  checkEquals(3, Re(mpc(3+2.1i, 52)))

  checkEquals(Arg(1+1i) * 4, pi)
  checkEquals(Im(Conj(mpc(1+1i, 52))), -1)

  checkEquals(as.complex(mpc(3,10)), 3+0i)
  checkEquals(as.numeric(mpc(3+0i, 10)), 3)
}
