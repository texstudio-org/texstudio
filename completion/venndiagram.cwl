# venndiagram package
# Matthew Bertucci 2021/09/21 for v1.2

#include:xkeyval
#include:tikz
#include:etoolbox

\begin{venndiagram3sets}
\begin{venndiagram3sets}[options%keyvals]
\end{venndiagram3sets}
\begin{venndiagram2sets}
\begin{venndiagram2sets}[options%keyvals]
\end{venndiagram2sets}

#keyvals:\begin{venndiagram3sets},\begin{venndiagram2sets}
shade=#%color
labelA=%<label text%>
labelB=%<label text%>
labelOnlyA=%<label text%>
labelOnlyB=%<label text%>
radius=##L
hgap=##L
vgap=##L
overlap=##L
showframe#true,false
tikzoptions={%<TikZ options%>}
#endkeyvals

#keyvals:\begin{venndiagram3sets}
labelC=%<label text%>
labelOnlyC=%<label text%>
labelOnlyAB=%<label text%>
labelOnlyAC=%<label text%>
labelOnlyBC=%<label text%>
labelABC=%<label text%>
labelNotABC=%<label text%>
#endkeyvals

#keyvals:\begin{venndiagram2sets}
labelAB=%<label text%>
labelNotAB=%<label text%>
#endkeyvals

\fillA#/venndiagram3sets,venndiagram2sets
\fillB#/venndiagram3sets,venndiagram2sets
\fillC#/venndiagram3sets
\fillAll#/venndiagram3sets,venndiagram2sets
\fillNotABC#/venndiagram3sets
\fillOnlyA#/venndiagram3sets,venndiagram2sets
\fillOnlyB#/venndiagram3sets,venndiagram2sets
\fillOnlyC#/venndiagram3sets
\fillNotA#/venndiagram3sets,venndiagram2sets
\fillNotB#/venndiagram3sets,venndiagram2sets
\fillNotC#/venndiagram3sets
\fillNotAorB#/venndiagram2sets
\fillNotAorNotB#/venndiagram2sets
\fillANotB#/venndiagram3sets,venndiagram2sets
\fillBNotA#/venndiagram3sets,venndiagram2sets
\fillANotC#/venndiagram3sets
\fillCNotA#/venndiagram3sets
\fillBNotC#/venndiagram3sets
\fillCNotB#/venndiagram3sets
\fillACapB#/venndiagram3sets,venndiagram2sets
\fillBCapA#*/venndiagram3sets,venndiagram2sets
\fillACapC#/venndiagram3sets
\fillCCapA#*/venndiagram3sets,venndiagram2sets
\fillBCapC#/venndiagram3sets
\fillCCapB#*/venndiagram3sets,venndiagram2sets
\fillACapBNotC#/venndiagram3sets
\fillBCapANotC#*/venndiagram3sets
\fillACapCNotB#/venndiagram3sets
\fillCCapANotB#*/venndiagram3sets
\fillBCapCNotA#/venndiagram3sets
\fillCCapBNotA#*/venndiagram3sets
\fillACapBCapC#/venndiagram3sets
\fillACapCCapB#*/venndiagram3sets
\fillBCapACapC#*/venndiagram3sets
\fillBCapCCapA#*/venndiagram3sets
\fillCCapACapB#*/venndiagram3sets
\fillCCapBCapA#*/venndiagram3sets

\setpostvennhook{code}
\ifvennoldpgf#*
\vennoldpgftrue#*
\vennoldpgffalse#*
\ifvennshowframe#*
\vennshowframetrue#*
\vennshowframefalse#*
