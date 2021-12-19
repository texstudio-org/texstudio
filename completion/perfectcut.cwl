# perfectcut package
# Matthew Bertucci 12/13/2021 for v2.3

#include:calc
#include:graphicx
#include:scalerel

#ifOption:mathstyle
#include:mathstyle
#endif

#keyvals:\usepackage/perfectcut#c
nomathstyle
mathstyle
realVert
fixxits
#endkeyvals

\perfectcut{arg1}{arg2}#m
\perfectbra{arg}#m
\perfectket{arg}#m
\perfectcase{arg1}{arg2}#m
\perfectbrackets{arg}#m
\perfectparens{arg}#m

\perfectunary{option%keyvals}{delim1}{delim2}{arg}#*
\perfectbinary{option%keyvals}{delim1}{delim2}{delim3}{arg1}{arg2}#*

#keyvals:\perfectunary,\perfectbinary
IncreaseHeight
CurrentHeight
CurrentHeightPlusOne
#endkeyvals

\cutbarskip#*
\cutangleskip#*
\cutangleouterskip#*
\cutinterbarskip#*

\nthleft{n}{delim}
\nthmiddle{n}{delim}
\nthright{n}{delim}
\lenleft{length}{delim}
\lenmiddle{length}{delim}
\lenright{length}{delim}
\reallenleft{length}{delim}
\reallenmiddle{length}{delim}
\reallenright{length}{delim}

\ifcutdebug#S
\cutdebugtrue#S
\cutdebugfalse#S
\bugfix#S

# deprecated
\cutbraprimitive#S
\cutketprimitive#S
\cutprimitive#S