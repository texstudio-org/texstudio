# cistercian package
# Matthew Bertucci 2025/10/08 for v0.6

#include:tikz
#include:etoolbox
#include:BusyPanda

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
