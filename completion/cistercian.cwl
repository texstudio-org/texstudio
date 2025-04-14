# cistercian package
# Matthew Bertucci 2025/04/14 for v0.1

#include:tikz

\cistercian{number}
\cistercian[options%keyvals]{number}

#keyvals:\cistercian#c
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