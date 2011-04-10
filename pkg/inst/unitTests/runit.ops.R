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

test.cmp <- function() {
  checkTrue(as.integer(10) == mpc(10, 52))
  checkTrue(mpc(10,52) == mpc(10, 32))
  checkTrue(10 == mpc(10,52))
  checkTrue(mpc(10,52) == 10)
  checkTrue(mpc(10,52) != 10.1)
}

test.conv <- function() {
  options("mpc.rounding"="MPC_RNDNN")
  checkTrue(as.numeric(mpc("3.143", 3)) == 3)
  options("mpc.rounding"="MPC_RNDUU")
  checkTrue(as.numeric(mpc("3.143", 3)) != 3)
  checkTrue(as.numeric(mpc("3.143", 3)) == 3.5)
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
