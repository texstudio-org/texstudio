# tikzphysics.ramps tikzlibrary
# Matthew Bertucci 2026/09/04 for v1.1.0

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
#endkeyvals

#keyvals:\node#c
ramp
curved-ramp
ramp-left
curved-ramp-left
#endkeyvals
