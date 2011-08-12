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
\name{mpc}
\alias{mpc}
\alias{Arg.mpc}
\alias{Conj.mpc}
\alias{Im.mpc}
\alias{Ops.mpc}
\alias{Re.mpc}
\alias{acos.mpc}
\alias{acosh.mpc}
\alias{as.complex.mpc}
\alias{as.double.mpc}
\alias{as.mpc}
\alias{asin.mpc}
\alias{asinh.mpc}
\alias{atan.mpc}
\alias{atanh.mpc}
\alias{cos.mpc}
\alias{cosh.mpc}
\alias{exp.mpc}
\alias{is.mpc}
\alias{log.mpc}
\alias{print.mpc}
\alias{sin.mpc}
\alias{sinh.mpc}
\alias{summary.mpc}
\alias{tan.mpc}
\alias{tanh.mpc}
\title{Arbitrarily High Precision Complex Number Arithmetic}
\description{
  A class for arbitrarily high precision complex number arithmetic.
}
\usage{
mpc(z, precision)
}
\arguments{
  \item{z}{A numeric value representing the real part of a complex
    number, or a complex value.}
  \item{precision}{The number of bits of precision that should be used
    to represent \eqn{z}.}
}
\value{
    An object of (S3) class mpc, which the user should use as a normal
    numeric value.  Currently, the implementation does not support use
    as a numeric vector.
}
\details{
  MPC supports 16 possible rounding modes for complex arithmetic which
  are specified through the \code{mpc.rounding} option.  The default
  rounding option, \code{MPC_RNDNN}, rounds both the real and imaginary
  parts to the nearest representable number as specified in the IEEE
  Floating Point standard.
  
  %% The following is direct from the MPC manual
  A complex rounding mode is of the form \code{MPC_RNDxy} where \code{x}
  and \code{y} are one of \code{N} (to nearest), \code{Z} (towards
  zero), \code{U} (towards plus infinity), \code{D} (towards minus
  infinity). The first letter refers to the rounding mode for the real
  part, and the second one for the imaginary part. For example
  \code{MPC_RNDZU} indicates to round the real part towards zero, and
  the imaginary part towards plus infinity.
}
\seealso{
  \code{\link{complex}}.
}
\references{
  Andeas Enge, Micka\"el Gastineau, Philippe Th\'eveny, and Paul Zimmermann,
  \emph{mpc --- A library for multiprecision complex arithmetic with
  exact rounding},
  see \url{http://www.multiprecision.org}.
}
\examples{
library(mpc)

summary(mpc(3,100) / mpc (3,100))

options("mpc.rounding" = "MPC_RNDUU")
summary(mpc(3,3) / mpc(3.01,3))
}
\keyword{complex}
