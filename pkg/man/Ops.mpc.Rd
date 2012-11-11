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
\name{mpc operators}
\alias{Ops.mpc}
\alias{+.mpc}
\alias{-.mpc}
\alias{*.mpc}
\alias{/.mpc}
\alias{^.mpc}
\alias{==.mpc}
\title{Basic Arithmetic Operators for Arbitrarily High Precision Complex Numbers}
\description{
  Addition, subtraction, multiplication, division, power, and equality
  functions for MPC types.
}
\usage{
\method{+}{mpc}(e1, e2)
\method{-}{mpc}(e1, e2)
\method{*}{mpc}(e1, e2)
\method{/}{mpc}(e1, e2)
\method{^}{mpc}(e1, e2)
\method{==}{mpc}(e1, e2)
}
\arguments{
  \item{x, y}{MPC complex numbers.}
}
\value{
  An object of (S3) class mpc, which the user should use as a normal
  numeric value.  The precision of the resulting complex number is the
  maximum of the precision used for x and y.  Currently, the
  implementation does not support use as a numeric vector.
}
\details{
  The operations work when both operands are an MPC complex number, but
  some binary operations between MPC complex numbers and other types are
  not yet implemented.
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
summary(mpc(3) + mpc(3,50))
}
\keyword{complex}
