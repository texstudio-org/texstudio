# matchedsplit package
# Matthew Bertucci 2026/10/29 for v0.8.1

#include:amsmath
#include:xcolor

#keyvals:\usepackage/matchedsplit#c
overridesplit
overridealign
rainbow
colors={%<color1,color2,...%>}
#endkeyvals

\begin{matchedalign}#\math,array
\begin{matchedalign}[options%keyvals]#\math,array
\end{matchedalign}
\begin{matchedalign*}#\math,array
\begin{matchedalign*}[options%keyvals]#\math,array
\end{matchedalign*}
\begin{matchedsplit}#m\array
\begin{matchedsplit}[options%keyvals]#m\array
\end{matchedsplit}#m

#keyvals:\begin{matchedalign},\begin{matchedalign*},\begin{matchedsplit}
rainbow#true,false
colors={%<color1,color2,...%>}
#endkeyvals

msblue#B
msorange#B
msgreen#B
mspurple#B
msred#B
mscyan#B