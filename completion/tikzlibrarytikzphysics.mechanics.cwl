# tikzphysics.mechanics tikzlibrary
# Matthew Bertucci 2026/09/04 for v1.1.0

#include:tikzlibrarycalc
#include:tikzlibrarytikzphysics.core

\physicsstringoverpulley{start}{pulley}{end}
#keyvals:\begin{tikzpicture}#c,\tikz#c,\node#c
physics block width=##L
physics block height=##L
physics pulley diameter=##L
physics pulley axle radius=##L
physics pulley axle color=#%color
physics string start solution=#1,2
physics string end solution=#1,2
physics string wrap=#clockwise,counterclockwise,shortest
physics string route=#surface-right,over,under,shortest
pre length=##L
post length=##L
amplitude=##L
segment length=##L
aspect=%<factor%>
#endkeyvals

#keyvals:\node#c
block
pulley
spring
#endkeyvals