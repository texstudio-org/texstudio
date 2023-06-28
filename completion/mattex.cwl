# mattex package
# Matthew Bertucci 1/18/2022 for v0.1

#include:pgfkeys
#include:xstring
#include:siunitx
#include:array
#include:collcell

\Mset{varname}{significand}{error}{exponent}
\Mset{varname}{significand}{error}
\Mset{varname}{significand}
\Mval{varname}
\Merr{varname}
\Mnum{varname}
\MSI{varname}{unit}

\M{varname}#*
\Mvallit{varname}#*
\Merrlit{varname}#*

\preparematrix{varname}{rows}{columns}
\usematrix
\header
\noheader

# not documented
\mtdirectory#*
\tabMval{varname}#*
\tabMnum{varname}#*
\tabMerr{varname}#*