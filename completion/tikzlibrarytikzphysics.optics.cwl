# tikzphysics.optics tikzlibrary
# Matthew Bertucci 2026/08/13 for v1.0.0

#include:tikzlibrarypatterns
#include:tikzlibrarycalc
#include:tikzlibrarytikzphysics.core

#keyvals:\begin{tikzpicture}#c,\tikz#c,\node#c
physics lens radius=##L
physics lens thickness=##L
physics lens aperture angle=%<degrees%>
#endkeyvals

#keyvals:\node#c
physicslens
#endkeyvals