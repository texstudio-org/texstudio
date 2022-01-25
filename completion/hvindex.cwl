# hvindex package
# Matthew Bertucci 11/24/2021 for v0.04

#include:xkeyval

#keyvals:\usepackage/hvindex#c
makeidx
#endkeyvals

#ifOption:makeidx
#include:makeidx
#endif

\Index{entry}
\ttIndex{entry}
\bfIndex{entry}
\sfIndex{entry}
\scIndex{entry}
\itIndex{entry}
\sIndex{%<entry%>|%<see%>}
\saIndex{%<entry%>|%<see also%>}
\iBraceL#*
\iBraceR#*
\IVert#*
\IndexNIL#*
\hvIDXfontDefault{arg}#*
\hvIDXfont{arg}#*
\IndexXi#*
\IndexXXi#*
\IndexXXii#*
\IndexXXiii#*
\hvBraceLeft#*
\hvBraceRight#*
