# polynomial package
# Matthew Bertucci 2/1/2022 for v1.1

#include:keyval

\polynomial{coeff1,coeff2,...}#m
\polynomial[options%keyvals]{coeff1,coeff2,...}#m
\polynomialfrac{numerator coeffs}{denominator coeffs}#m
\polynomialfrac[options%keyvals]{numerator coeffs}{denominator coeffs}#m
\polynomialstyle{options%keyvals}

#keyvals:\polynomial,\polynomialfrac,\polynomialstyle
falling#true,false
reciprocal#true,false
var=%<variable symbol%>
start=%<integer%>
step=%<integer%>
add=%<addition symbol%>
sub=%<subtraction symbol%>
firstsub=%<symbol%>
#endkeyvals