% Copyright(c) 2011 Murray M. Stokely
%
% This file is part of the R Multiple Precision Complex package, mpc.
%
% mpc is free software: you can redistribute it and/or modify it under
% the terms of the GNU Lesser General Public License as published by
% the Free Software Foundation, either version 3 of the License, or
% (at your option) any later version.
%
% http://mpc.r-forge.r-project.org/
\name{mpc}
\alias{mpc}
\title{Arbitrarily High Precision Complex Number Arithmetic}
\description{
  A class for arbitrarily high precision complex number arithmetic.
}
\usage{
mpc(z, precision)
Re(z)
Im(z)
Mod(z)
Arg(z)
Conj(z)
}
\arguments{
  \item{z}{A numeric value representing the real part of a complex
    number, or a complex value.}
  \item{precision}{The number of bits of precision that should be used
    to represent \eqn{z}.}
}
\seealso{
  \code{\link{complex}}.
}
\examples{
library(mpc)

summary(mpc(3,100) / mpc (3,100))
}
\keyword{complex}
