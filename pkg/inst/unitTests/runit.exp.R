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

test.exp <- function() {
  checkEquals(exp(3), Re(exp(mpc(3, 52))))
  checkEquals(3, Re(exp(log(mpc(3, 52)))))
  checkEquals(3, Re(exp(log(mpc(3, 500)))))
  checkEquals(3, Re(exp(log(mpc(3, 11)))))
  checkTrue(3 == Re(exp(log(mpc(3, 11)))))
  # With only 10 bits we should lose some accuracy through exp(log())
  checkTrue(3 != Re(exp(log(mpc(3, 10)))))
}
