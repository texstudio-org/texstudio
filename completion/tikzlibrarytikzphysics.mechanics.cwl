# tikzphysics.mechanics tikzlibrary
# Matthew Bertucci 2026/09/08 for v1.2.0

#include:tikzlibrarycalc
#include:tikzlibrarytikzphysics.core

\physicsstringoverpulley{start}{pulley}{end}

#keyvals:\begin{tikzpicture}#c,\tikz#c,\node#c
block width=##L
block height=##L
pulley diameter=##L
pulley axle radius=##L
pulley axle color=#%color
string start solution=#1,2
string end solution=#1,2
string wrap=#clockwise,counterclockwise,shortest
string route=#surface-right,over,under,shortest
pre length=##L
post length=##L
amplitude=##L
segment length=##L
aspect=%<factor%>
support size=##L
pendulum length=##L
pendulum angle=%<degrees%>
#endkeyvals

#keyvals:\node#c
block
pulley
particle
disk
ring
#endkeyvals

#keyvals:\draw#c
spring
rope
force
velocity
acceleration
torque
rod
#endkeyvals
