# tikzphysics.surface tikzlibrary
# Matthew Bertucci 2026/09/04 for v1.1.0

#include:tikzlibrarypatterns
#include:tikzlibrarycalc
#include:tikzlibrarytikzphysics.core

#keyvals:\begin{tikzpicture}#c,\tikz#c,\node#c
physics platform width=##L
physics platform depth=##L
physics strip width=##L
physics wall angle=%<degrees%>
physics left wall angle=%<degrees%>
physics right wall angle=%<degrees%>
wedge width=##L
wedge height=##L
wedge angle=%<degrees%>
wedge right angle at=#br,bl,top
physics ground width=##L
physics ground depth=##L
physics ceiling width=##L
physics ceiling depth=##L
physics wall thickness=##L
physics wall height=##L
#endkeyvals

#keyvals:\node#c
platform
platform-left
platform-right
platform-both
wedge
ground
ceiling
wall-left
wall-right
#endkeyvals