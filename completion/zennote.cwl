# zennote package
# Matthew Bertucci 2023/01/16 for v1.0.0

#include:tcolorbox
#include:tcolorboxlibrarymost

\titlebox{settings%keyvals}

#keyvals:\titlebox
top-left={%<text%>}
top-right={%<text%>}
bottom-left={%<text%>}
bottom-right={%<text%>}
notenumber=%<integer%>
topic={%<text%>}
type={%<text%>}
#endkeyvals

\begin{noteframe}
\begin{noteframe}[options%keyvals]
\end{noteframe}

#keyvals:\begin{noteframe}
color=#%color
style=#zero,one,two
title={%<text%>}
#endkeyvals

\thenotenumber#*