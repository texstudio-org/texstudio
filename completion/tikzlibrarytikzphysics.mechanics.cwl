# tikzphysics.mechanics tikzlibrary
# Matthew Bertucci 2026/08/13 for v1.0.0

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
#endkeyvals

#keyvals:\node#c
physicsblock
physicspulley
#endkeyvals