# 12many package
# Matthew Bertucci 12/14/2021 for v0.3

#include:calc
#include:keyval

\nto{num1}{num2}
\ito{num}
\oto{num}
\setOTMstyle{style}
\setOTMstyle[params%keyvals]{style}

#keyvals:\usepackage/12many#c
set
dots
nude
laue
#endkeyvals

#keyvals:\setOTMstyle/set
var=%<variable name%>
naturals=%<symbol%>
where=%<symbol%>
#endkeyvals

#keyvals:\setOTMstyle/dots
dots=%<symbol%>
#endkeyvals

#keyvals:\setOTMstyle/nude
dots=%<symbol%>
#endkeyvals

#keyvals:\setOTMstyle/laue
setminus=%<symbol%>
setplus=%<symbol%>
ybelow=##L
strokewidth=##L
innersidegap=##L
outersidegap=##L
#endkeyvals

\newOTMstyle{name}{definition}#*
\newOTMstyle[params]{name}{definition}#*
\getOTMparameter{param}#*
\renewOTMstyle{name}{definition}#*
\newOTMstyle[params]{name}{definition}#*
\newOTMparameter{style}{param}{value}#*