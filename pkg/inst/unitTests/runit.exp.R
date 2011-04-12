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

test.exp <- function() {
  checkEquals(exp(3), Re(exp(mpc(3, 52))))
  checkEquals(3, Re(exp(log(mpc(3, 52)))))
  checkEquals(3, Re(exp(log(mpc(3, 500)))))
  checkEquals(3, Re(exp(log(mpc(3, 11)))))
  checkTrue(3 == Re(exp(log(mpc(3, 11)))))
  # With only 10 bits we should lose some accuracy through exp(log())
  checkTrue(3 != Re(exp(log(mpc(3, 10)))))
}
