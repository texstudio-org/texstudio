# diagbox package
# Matthew Bertucci 9/19/2021 for v2.3

#include:keyval
#include:pict2e
#include:calc
#include:array
#include:fp

\diagbox{left%text}{right%text}#t
\diagbox[options%keyvals]{left%text}{right%text}#t
\diagbox{left%text}{middle%text}{right%text}#t

#keyvals:\diagbox
width=##l
height=##l
dir=#NW,NE,SW,SE
innerwidth=##l
innerleftsep=##l
innerrightsep=##l
outerleftsep=##l
outerrightsep=##l
leftsep=##l
rightsep=##l
trim=#l,r,lr,rl
font=%<font commands%>
linewidth=##l
linecolor=#%color
#endkeyvals

\backslashbox{left%text}{right%text}#*
\backslashbox[width]{left%text}{right%text}#*
\backslashbox[width][trim%keyvals]{left%text}{right%text}#*
\slashbox{left%text}{right%text}#*
\slashbox[width]{left%text}{right%text}#*
\slashbox[width][trim%keyvals]{left%text}{right%text}#*

#keyvals:\backslashbox,\slashbox
l
r
lr
rl
#endkeyvals
