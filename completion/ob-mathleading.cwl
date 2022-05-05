# ob-mathleading package
# Matthew Bertucci 2022/05/05 for v0.1

#include:expl3
#include:amsmath
#include:xparse
#include:etoolbox
#include:l3keys2e

#keyvals:\usepackage/ob-mathleading#c
default#true,false
mathleading=%<value%>
exception={%<envname1,envname2,...%>}
noallowdisplaybreaks#true,false
#endkeyvals

\obmathleading{value}
\begin{obMathLeading}
\begin{obMathLeading}[value]
\end{obMathLeading}