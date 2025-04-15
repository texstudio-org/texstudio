# cistercian package
# Matthew Bertucci 2025/04/14 for v0.2

#include:tikz

\cistercianset{options%keyvals}
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
