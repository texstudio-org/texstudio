# crop package
# Matthew Bertucci 12/13/2021 for v1.10

#include:ifluatex
#include:color
#include:graphics

#keyvals:\usepackage/crop#c
a0
a1
a2
a3
a4
a5
a6
b0
b1
b2
b3
b4
b5
b6
letter
legal
executive
width=##L
height=##L
center
landscape
dvips
pdftex
pdflatex
luatex
lualatex
vtex
nodriver
mirror
rotate
invert
notext
#endkeyvals

\crop
\crop[options%keyvals]

#keyvals:\crop,\usepackage/crop#c
cam
cross
frame
off
odd
even
axes
noaxes
info
noinfo
font=%<font csname%>
color=#%color
mount1
mount1=%<integer%>
mount2
mount2=%<integer%>
horigin=##L
vorigin=##L
graphics
nographics
#endkeyvals

\cropdef{ul-macro}{ur-macro}{ll-macro}{lr-macro}{mode name}#*
\cropdef[page-info macro]{ul-macro}{ur-macro}{ll-macro}{lr-macro}{mode name}#*

\stockwidth#*
\stockheight#*