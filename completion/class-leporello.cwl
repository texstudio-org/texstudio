# leporello class
# Matthew Bertucci 2025/08/26 for v1.0.0

#include:graphicx
#include:l3draw

\leporelloset{options%keyvals}
\leporelloset[prefix]{options%keyvals}

#keyvals:\documentclass/leporello#c
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

#keyvals:\leporelloset#c,\leporellosetstyle#c
global/columns={%<list of dimensions%>}
global/two columns
global/three columns
global/four columns
global/four columns wrap
global/five columns
global/six columns
global/layout height=##L
global/auto typeset
global/show frames
global/show ids
global/prepress
global/info area=##L
global/bleed=##L
#endkeyvals

\leporellobleed#*
\leporelloboxwidth#*

\begin{leporellocolumn}{string}
\end{leporellocolumn}

\begin{leporellobox}
\begin{leporellobox}[options%keyvals]
\end{leporellobox}

#keyvals:\begin{leporellobox}
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

#keyvals:\leporelloset#c,\leporellosetstyle#c
box/name=%<string%>
box/parent=%<string%>
box/align parent={%<tuple of poles%>}
box/align self={%<tuple of poles%>}
box/offset={%<tuple of dimensions%>}
box/width=##L
box/height=##L
box/stretch
box/padding left=##L
box/padding right=##L
box/padding top=##L
box/padding bottom=##L
box/padding={%<keyvals%>}
box/no padding
box/pre=%<code%>
box/background color=#none,%color
box/background code=%<code%>
box/bleed={%<list of values%>}
box/store width=%<macro%>
box/store height=%<macro%>
box/flow into=%<string%>
#endkeyvals

\leporellotypesetcolumns{list of strings}
\leporellotypesetcolumns[options%keyvals]{list of strings}

#keyvals:\leporellotypesetcolumns
reverse layout
reverse order
reverse pagination
continuous pagination
%leporellostyle
#endkeyvals

#keyvals:\leporelloset#c,\leporellosetstyle#c
typeset/reverse layout
typeset/reverse order
typeset/reverse pagination
typeset/continuous pagination
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
%leporellostyle
#endkeyvals

#keyvals:\leporelloset#c,\leporellosetstyle#c
image/clip width=##L
image/clip height=##L
image/scale=%<factor%>
image/width=##L
image/height=##L
image/offset={%<tuple of dimensions%>}
image/ignore padding={%<list of values%>}
image/fill bleed
#endkeyvals

\leporellocolordefine{string%specialDef}{model}{list of values}#s#%color
\leporellocolorselect{color}
\leporellosetstyle{string%specialDef}{keyvals}#s#%leporellostyle
\leporellosetstyle[prefix]{string%specialDef}{keyvals}#s#%leporellostyle

\leporellonote{code}
\leporellonote[integer]{code}
\leporelloprintnotes

#keyvals:\leporelloset#c,\leporellosetstyle#c
notes/mark cmd=%<command%>
notes/list style=%<envname%>
%leporellostyle
#endkeyvals
