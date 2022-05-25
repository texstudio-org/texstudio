# fltpage package
# Matthew Bertucci 2022/05/24 for v0.3

#include:ifthen
#include:afterpage

#keyvals:\usepackage/fltpage#c
german
varioref
closeFloats
leftFloats
rightFloats
CaptionAfterwards
CaptionBefore
draft
oneside
twoside
noSeparatorLine
noHints
#endkeyvals

#ifOption:varioref
#include:varioref
#endif

\begin{FPfigure}
\end{FPfigure}
\begin{FPtable}
\end{FPtable}