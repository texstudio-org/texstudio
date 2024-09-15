# suanpan-l3 package
# Matthew Bertucci 2024/09/10 for v1.2.2

#include:tikz

\begin{suanpan}
\begin{suanpan}[options%keyvals]
\end{suanpan}

\rod{num}{val}
\rod*{num}{val}
\rods{val list}
\bid{num}{pos list}{fill color}[draw color]
\bids{num}{val}{color}
\bids*{num}{val}{color}
\rodmark{marker list}
\rodmark[start]{marker list}
\mkframe
\lrframe{first num}{last num}

\suanpanset{options%keyvals}

#keyvals:\usepackage/suanpan-l3#c,\begin{suanpan},\suanpanset
draft
empty#true,false
linewd=##L
bidh=##L
bidd=##L
rodd=##L
framew=##L
rodsep=##L
bidsep=##L
scale=%<factor%>
framedraw=#%color
roddraw=#%color
rodfill=#%color
outerdraw=#%color
outerfill=#%color
innerdraw=#%color
innerfill=#%color
font=%<font commands%>
#endkeyvals
