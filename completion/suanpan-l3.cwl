# suanpan-l3 package
# Matthew Bertucci 2026/08/04 for v2.0.0

#include:l3draw
#include:tikz
#include:tikzlibraryshadings

\begin{suanpan}
\begin{suanpan}[options%keyvals]
\end{suanpan}

\rod{num}{val}
\rod*{num}{val}
\rods{val list}[counting point string]
\rods{val list}
\bead{num}{pos list}{fill color}
\bead{num}{pos list}{fill color}[draw color]
\beads{num}{val}{color}
\beads*{num}{val}{color}
\rodmark{marker list}
\rodmark[start]{marker list}
\mkframe
\lrframe{first num}{last num}

\suanpanset{options%keyvals}

#keyvals:\usepackage/suanpan-l3#c,\begin{suanpan},\suanpanset
draft
empty#true,false
numrods=%<integer%>
linewd=##L
beadh=##L
beadd=##L
rodd=##L
framew=##L
rodsep=##L
beadsep=##L
scale=%<factor%>
framedraw=#%color
roddraw=#%color
rodfill=#%color
outerdraw=#%color
outerfill=#%color
innerdraw=#%color
innerfill=#%color
font=%<font commands%>
beadspot=%<number%>
#endkeyvals
