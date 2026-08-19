# tikzphysics.surface tikzlibrary
# Matthew Bertucci 2026/08/13 for v1.0.0

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
physics wedge width=##L
physics wedge height=##L
physics wedge angle=%<degrees%>
physics wedge right angle at=#br,bl,top
physics ground width=##L
physics ground depth=##L
physics ceiling width=##L
physics ceiling depth=##L
physics wall thickness=##L
physics wall height=##L
#endkeyvals

#keyvals:\node#c
physicsplatform-left
physicsplatform-right
physicsplatform-both
physicswedge
physicsground
physicsceiling
physicswall-left
physicswall-right
#endkeyvals