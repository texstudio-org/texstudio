# diagbox package
# Matthew Bertucci 9/19/2021 for v2.3

#include:pict2e
#include:calc
#include:array
#include:fp

\diagbox{left}{right}#/tabular
\diagbox[options%keyvals]{left}{right}#/tabular
\diagbox{left}{middle}{right}#/tabular

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
font=
linewidth=##l
linecolor=#%color
#endkeyvals

\backslashbox[width][trim%keyvals]{left}{right}#*
\slashbox[width][trim%keyvals]{left}{right}#*

#keyvals:\backslashbox,\slashbox
l
r
lr
rl
#endkeyvals
