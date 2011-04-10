% Copyright 2011 Google Inc.
%
% This library is free software; you can redistribute it and/or
% modify it under the terms of the GNU Lesser General Public
% License as published by the Free Software Foundation; either
% version 2.1 of the License, or (at your option) any later version.
%
% This library is distributed in the hope that it will be useful,
% but WITHOUT ANY WARRANTY; without even the implied warranty of
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
% Lesser General Public License for more details.
%
% You should have received a copy of the GNU Lesser General Public
% License along with this library; if not, write to the Free Software
% Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
% 02110-1301, USA
%
% http://mpc.r-forge.r-project.org/
\name{mpc-utils}
\alias{mpc-utils}
\alias{getPrec}
\alias{mpcVersion}
\alias{urandom.mpc}
\title{mpc -- Utilities for Getting Precision, Version, etc}
\description{
  This page documents utilities from package \pkg{mpc}.
}
\usage{
getPrec(z)
urandom.mpc(precision)
mpcVersion()
}
\arguments{
  \item{z}{An MPC object representing a complex number in arbitary
    precision floating point.}
  \item{precision}{The number of bits of precision that should be used
    to represent the returned complex number \eqn{z}.}
}
\value{
  \code{getPrec(z)} returns a \code{\link{integer}} vector of length 2
  where the first element contains the number of bits of precision
  of the real part of \code{z} and the second element contains the
  number of bits of precision of the imaginary part of \code{z}.
  
  \code{urandom.mpc(precision)} returns a uniformly distributed random
  complex \code{\link{mpc}} object in the unit square [0,1]*[0,1].

  \code{mpcVersion} returns the MPC library version as a string.
}
\seealso{
  \code{\link{mpc}}.
}
\examples{
library(mpc)

z1 <- mpc(3, 100)
getPrec(z1)  # 100 bits.

z2 <- mpc(3, 200)
getPrec(z2)  # 200 bits.

z3 <- z1 + z2
getPrec(z3)  # 200 bits

urandom.mpc(53)
urandom.mpc(53)

mpcVersion()
}
\keyword{utilities}
