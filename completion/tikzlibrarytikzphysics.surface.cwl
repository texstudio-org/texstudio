# tikzphysics.surface tikzlibrary
# Matthew Bertucci 2026/09/08 for v1.2.0

#include:tikzlibrarypatterns
#include:tikzlibrarycalc
#include:tikzlibrarytikzphysics.core

#keyvals:\begin{tikzpicture}#c,\tikz#c,\node#c
platform width=##L
platform depth=##L
strip width=##L
wall angle=%<degrees%>
left wall angle=%<degrees%>
right wall angle=%<degrees%>
wedge width=##L
wedge height=##L
wedge angle=%<degrees%>
wedge right angle at=#br,bl,top
surface guide length=##L
ground width=##L
ground depth=##L
ceiling width=##L
ceiling depth=##L
wall thickness=##L
wall height=##L
#endkeyvals

#keyvals:\node#c
platform
platform-left
platform-right
platform-both
platform-left-up
platform-right-up
wedge
ground
ceiling
wall-left
wall-right
#endkeyvals