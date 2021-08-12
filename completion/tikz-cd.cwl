# tikz-cd package
# Fernando Muro, 5 Nov 2017
# muzimuzhi, 23 Jan 2020, tikz-cd v0.9f
# Matthew Bertucci, 7/29/2021, v1.0

#include:tikz
\begin{tikzcd}#\array,math
\begin{tikzcd}[options]#\array,math
\end{tikzcd}
\arrow[options%keyvals]#/tikzcd
\arrow[options%keyvals]{direction}%<labels%>#*/tikzcd
\ar[options%keyvals]#/tikzcd
\rar[options%keyvals]%<labels%>#*/tikzcd
\lar[options%keyvals]%<labels%>#*/tikzcd
\dar[options%keyvals]%<labels%>#*/tikzcd
\uar[options%keyvals]%<labels%>#*/tikzcd
\drar[options%keyvals]%<labels%>#*/tikzcd
\urar[options%keyvals]%<labels%>#*/tikzcd
\dlar[options%keyvals]%<labels%>#*/tikzcd
\ular[options%keyvals]%<labels%>#*/tikzcd
\tikzcdset{options%keyvals}

## arrow types
#keyvals:\arrow#c,\ar#c,\rar#c,\lar#c,\dar#c,\uar#c,\drar#c,\urar#c,\dlar#c,\ular#c
to head
rightarrow
leftarrow
leftrightarrow
Rightarrow
Leftarrow
Leftrightarrow
maps to
mapsto
mapsfrom
Mapsto
Mapsfrom
hook
hook'
hookrightarrow
hookleftarrow
dashed
dashrightarrow
dashleftarrow
tail
rightarrowtail
leftarrowtail
squiggly
rightsquigarrow
leftsquigarrow
leftrightsquigarrow
two heads
twoheadrightarrow
twoheadleftarrow
no head
no tail
dash
equal
harpoon
harpoon'
rightharpoonup
rightharpoondown
leftharpoonup
leftharpoondown
crossing over
#endkeyvals

## appearance of diagrames
#keyvals:\tikzcdset,\begin{tikzcd}#c
every diagram
diagrams=%<options%>
every matrix
every cell
cells=%<options%>
row sep=
column sep=
sep=
cramped
math mode#true,false
background color=#%color
every arrow
arrows=%<options%>
arrow style=Latin Modern,math font,tikz
from=
to=
phantom
shift left=##L
shift right=##L
shift={%<coordinate%>}
xshift=##L
yshift=##L
start anchor=
end anchor=
shorten=##L
crossing over
crossing over clearance=##L
every label
labels=%<options%>
marking
description
center yshift=##L
#endkeyvals
