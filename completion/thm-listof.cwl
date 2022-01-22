# thm-listof package
# Matthew Bertucci 1/21/2022 for v0.72

#include:thm-patch
#include:keyval
#include:kvsetkeys

\listoftheorems
\listoftheorems[options%keyvals]
\listtheoremname
\setlisttheoremstyle{options%keyvals}#*

#keyvals:\listoftheorems,\setlisttheoremstyle
title=%<title%>
ignore={%<thm1,thm2,...%>}
ignoreall
show={%<thm1,thm2,...%>}
showall
onlynamed={%<thm1,thm2,...%>}
swapnumber#true,false
numwidth=##L
#endkeyvals

\thmtformatoptarg{arg}#*
\showtheorems{thm1,thm2,...}#*
\ignoretheorems{thm1,thm2,...}#*
\onlynamedtheorems{thm1,thm2,...}#*