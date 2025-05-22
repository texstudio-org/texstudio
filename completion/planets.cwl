# planets package
# Matthew Bertucci 2025/05/14 for v1.0.4

#include:xcolor
#include:pgfkeys
#include:tikz
#include:tikzlibrarydecorations.pathmorphing
#include:xstring

\planet[keyvals]

#keyvals:\planet
surface=#mercury,venus,earth,mars,jupiter,saturn,uranus,neptune,pluto,sun,moon,shaded jupiter,north pole,south pole,mars pole
color=#%color
rings
ring=%<radius%>
tilt=%<degrees%>
rotation
equator
axis
retrograde
phase=#new,first crescent,first half,waxing gibbous,full,waning gibbous,last half,last crescent,top half,bottom half
scale=%<factor%>
centerx=%<x-coord%>
centery=%<y-coord%>
center={%<(x,y)%>}
#endkeyvals
