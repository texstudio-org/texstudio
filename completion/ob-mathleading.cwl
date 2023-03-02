# ob-mathleading package
# Matthew Bertucci 2023/03/02 for v0.2

#include:amsmath
#include:etoolbox
#include:l3keys2e

#keyvals:\usepackage/ob-mathleading#c
default#true,false
mathleading=%<value%>
exception={%<envname1,envname2,...%>}
noallowdisplaybreaks#true,false
badm#true,false
#endkeyvals

\obmathleading{value}
\begin{obMathLeading}
\begin{obMathLeading}[value]
\end{obMathLeading}
