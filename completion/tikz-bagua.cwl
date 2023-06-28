# tikz-bagua package
# Matthew Bertucci 2022/08/14 for v1.01

#include:tikz
#include:xstring
#include:bitset
#include:xintexpr

\taiji
\taiji[scale]
\taiji*
\taiji*[scale]
\xtaiji
\xtaiji[scale]
\xtaiji*
\xtaiji*[scale]
\drawliangyi{0 or 1}#*
\drawliangyi[yshift]{0 or 1}#*
\liangyi{0 or 1}
\liangyi{0 or 1}[scale]
\sixiang{binary}
\sixiang{binary}[scale]
\sixiang*{decimal}
\sixiang*{decimal}[scale]
\bagua{binary}
\bagua{binary}[scale]
\bagua*{decimal}
\bagua*{decimal}[scale]
\Bagua{binary}
\Bagua{binary}[scale]
\Bagua[8]{%<octal%>}
\Bagua[8]{%<octal%>}[%<scale%>]
\Bagua*{decimal}
\Bagua*{decimal}[scale]
