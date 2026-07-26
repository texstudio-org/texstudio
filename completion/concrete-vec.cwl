# concrete-vec package
# Matthew Bertucci 2026/07/26 for v1.2

#include:kvoptions
#include:etoolbox
#include:pdfrender
#include:mathastext

#keyvals:\usepackage/concrete-vec#c
bold
nobold
boldwidth=##L
mathbold
nomathbold
math
nomath
greek=#lgr,euler,symbol,none
frenchmath
nofrenchmath
lmodern
nolmodern
#endkeyvals

\bd{arg}
\mathbold{arg}
\concretebold#*
\concretenobold#*
\setconcreteboldwidth{dimen}