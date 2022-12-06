# planets package
# Matthew Bertucci 9/1/2021 for v1.0.2

#include:xcolor
#include:pgfkeys
#include:tikz
#include:tikzlibrarydecorations.pathmorphing
#include:xstring

\planet[keyvals]

#keyvals:\planet
surface=#mercury,venus,earth,mars,jupiter,saturn,uranus,neptune,pluto,sun,moon
rings
ring=%<radius%>
tilt=%<degrees%>
rotation
retrograde
phase=#new,first crescent,first half,waxing gibbous,full,waning gibbous,last half,last crescent
scale=
centerx=%<x-coord%>
centery=%<y-coord%>
center={%<(x,y)%>}
#endkeyvals
