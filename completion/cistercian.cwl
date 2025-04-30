# cistercian package
# Matthew Bertucci 2025/04/15 for v0.3

#include:tikz
#include:etoolbox

\cistercianset{options%keyvals}
\cistercianreset
\cistercian{number}
\cistercian[options%keyvals]{number}

#keyvals:\cistercianset#c,\cistercian#c
height=##L
width=##L
stroke=##L
scale=%<factor%>
draw={%<TikZ keys%>}
line join=#round,bevel,miter
#endkeyvals

#keyvals:\pagenumbering#c
cistercian
#endkeyvals
