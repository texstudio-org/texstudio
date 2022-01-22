# axessibility package
# Matthew Bertucci 1/20/2022 for v3.0

#include:amsmath
#include:amssymb
#include:xstring
#include:tagpdf

#ifOption:accsupp
#include:accsupp
\begin{tempenv}#S\math
\end{tempenv}#S
#endif

#keyvals:\usepackage/axessibility#c
accsupp
tagpdf
#endkeyvals

\iftagpdfopt#*
\tagpdfopttrue#*
\tagpdfoptfalse#*

\doreplacement{true or false}
\auxiliaryspace#*
\wrap{arg}
\wrapml{arg}
\wrapmlstar{arg}
\wrapmlalt{arg}