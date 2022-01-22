# vwcol package
# Matthew Bertucci 1/8/2021 for v0.2

#include:calc
#include:color
#include:environ
#include:keyval
#include:ragged2e

#keyvals:\usepackage/vwcol#c
quiet
#endkeyvals

\begin{vwcol}
\begin{vwcol}[options%keyvals]
\end{vwcol}

\vwcolsetup{options%keyvals}

#keyvals:\begin{vwcol},\vwcolsetup
widths={%<ratio1,ratio2,...%>}
sep=%<factor%>
sidesep#true,false
presep#true,false
postsep#true,false
rule=##L
siderule#true,false
prerule#true,false
postrule#true,false
rulecolor=#%color
justify=#ragged,flush,raggedleft,center
indent=##L
quiet
lines=%<integer%>
maxrecursion=%<integer%>
#endkeyvals
