# leporello class
# Matthew Bertucci 2025/08/19 for v0.9.2

#include:geometry
#include:graphicx
#include:l3draw

\leporelloset{options%keyvals}

#keyvals:\leporelloset,\documentclass/leporello#c
columns={%<list of dimensions%>}
two columns
three columns
four columns
four columns wrap
five columns
six columns
layout height=##L
auto typeset
show frames
show ids
prepress
info area=##L
bleed=##L
#endkeyvals

\leporellobleed#*
\leporelloboxwidth#*

\begin{leporellocolumn}{string}
\end{leporellocolumn}

\begin{leporellobox}
\begin{leporellobox}[options%keyvals]
\end{leporellobox}

#keyvals:\begin{leporellobox},\leporellosetstyle
name=%<string%>
parent=%<string%>
align parent={%<tuple of poles%>}
align self={%<tuple of poles%>}
offset={%<tuple of dimensions%>}
width=##L
height=##L
stretch
padding left=##L
padding right=##L
padding top=##L
padding bottom=##L
padding={%<keyvals%>}
no padding
pre=%<code%>
background color=#none,%color
background code=%<code%>
bleed={%<list of values%>}
store width=%<macro%>
store height=%<macro%>
flow into=%<string%>
%leporellostyle
#endkeyvals

\leporellotypesetcolumns{list of strings}
\leporellotypesetcolumns[options%keyvals]{list of strings}

#keyvals:\leporellotypesetcolumns
reverse layout
reverse order
reverse pagination
continuous pagination
#endkeyvals

\leporelloboxbreak

\leporelloimage{imagefile}#g
\leporelloimage[options%keyvals]{imagefile}#g

#keyvals:\leporelloimage
clip width=##L
clip height=##L
scale=%<factor%>
width=##L
height=##L
offset={%<tuple of dimensions%>}
ignore padding={%<list of values%>}
fill bleed
#endkeyvals

\leporellocolordefine{string%specialDef}{model}{list of values}#s#%color
\leporellocolorselect{color}
\leporellosetstyle{string%specialDef}{keyvals}#s#%leporellostyle
\leporellojustified