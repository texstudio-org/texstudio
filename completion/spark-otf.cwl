# spark-otf package
# Matthew Bertucci 3/7/2022 for v0.05a

#include:ifxetex
#include:ifluatex
#include:xkeyval
#include:luacode

#keyvals:\usepackage/spark-otf#c
usefilenames#true,false
DefaultFeatures={%<features%>}
#endkeyvals

\sparkBarMedium#*
\sparkBarNarrow#*
\sparkBarExtranarrow#*
\sparkBarWide#*
\sparkBarExtrawide#*
\sparkDotLineMedium#*
\sparkDotLineThick#*
\sparkDotLineExtrathick#*
\sparkDotLineThin#*
\sparkDotLineExtrathin#*
\sparkDotMedium#*
\sparkDotSmall#*
\sparkDotExtralarge#*
\sparkDotExtrasmall#*

\sparkBar{values}
\sparkBar[type%keyvals]{values}
\sparkBar[type%keyvals][num1]{values}[num2]
\sparkBar*{values}
\sparkBar*[type%keyvals]{values}
\sparkBar*[type%keyvals][num1]{values}[num2]

#keyvals:\sparkBar,\sparkBar*
Extranarrow
Extrawide
Medium
Narrow
Wide
#endkeyvals

\sparkDot{values}
\sparkDot[type%keyvals]{values}
\sparkDot[type%keyvals][num1]{values}[num2]
\sparkDot*{values}
\sparkDot*[type%keyvals]{values}
\sparkDot*[type%keyvals][num1]{values}[num2]

#keyvals:\sparkDot,\sparkDot*
Extralarge
Extrasmall
Large
Medium
Small
#endkeyvals

\sparkDotline{values}
\sparkDotline[type%keyvals]{values}
\sparkDotline[type%keyvals][num1]{values}[num2]
\sparkDotline*{values}
\sparkDotline*[type%keyvals]{values}
\sparkDotline*[type%keyvals][num1]{values}[num2]

#keyvals:\sparkDotline,\sparkDotline*
Extrathick
Extrathin
Medium
Thick
Thin
#endkeyvals

\setSparkColor{rrggbb}{values}