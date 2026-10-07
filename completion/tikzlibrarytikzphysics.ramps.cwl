# tikzphysics.ramps tikzlibrary
# Matthew Bertucci 2026/10/01 for v1.7.0

#include:tikzlibrarypatterns
#include:tikzlibrarycalc
#include:tikzlibraryangles
#include:tikzlibrarytikzphysics.core

#keyvals:\begin{tikzpicture}#c,\tikz#c,\node#c
ramp direction=#right,left
ramp run=##L
ramp rise=##L
ramp angle=%<degrees%>
ramp depth=##L
ramp wall height=##L
ramp wall width=##L
ramp guide length=##L
curved ramp radius=##L
curved ramp angle=%<degrees%>
curved ramp floor length=##L
curved ramp back extension=##L
track length=##L
track rise=##L
track rough start=%<factor%>
track rough end=%<factor%>
circular bowl radius=##L
circular bowl rough start=%<factor%>
circular bowl rough end=%<factor%>
loop track radius=##L
loop track rough start=%<factor%>
loop track rough end=%<factor%>
#endkeyvals

#keyvals:\node#c
ramp
curved-ramp
ramp-left
curved-ramp-left
track
circular bowl
loop track
#endkeyvals
