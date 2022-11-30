# cd tikzlibrary
# 2022/11/25 for v1.0

#include:tikzlibrarymatrix
#include:tikzlibraryquotes
#include:tikzlibraryarrows.meta

\begin{tikzcd}#\array,math
\begin{tikzcd}[options%keyvals]#\array,math
\end{tikzcd}
\arrow[%<options%>]#/tikzcd
\arrow[%<options%>]{%<direction%>}{%<label%>}#*/tikzcd
\arrow[%<options%>]{%<direction%>}[%<label options%>]{%<label%>}#*/tikzcd
\ar[%<options%>]#*/tikzcd
\rar[%<options%>]#*/tikzcd
\rar[%<options%>]{%<label%>}#*/tikzcd
\lar[%<options%>]#*/tikzcd
\lar[%<options%>]{%<label%>}#*/tikzcd
\dar[%<options%>]#*/tikzcd
\dar[%<options%>]{%<label%>}#*/tikzcd
\uar[%<options%>]#*/tikzcd
\uar[%<options%>]{%<label%>}#*/tikzcd
\drar[%<options%>]#*/tikzcd
\drar[%<options%>]{%<label%>}#*/tikzcd
\urar[%<options%>]#*/tikzcd
\urar[%<options%>]{%<label%>}#*/tikzcd
\dlar[%<options%>]#*/tikzcd
\dlar[%<options%>]{%<label%>}#*/tikzcd
\ular[%<options%>]#*/tikzcd
\ular[%<options%>]{%<label%>}#*/tikzcd
\tikzcdset{options%keyvals}
\tikzcd#S
\endtikzcd#S

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
#endkeyvals

## appearance of diagrams
#keyvals:\tikzcdset#c,\begin{tikzcd}#c
every diagram
diagrams={%<options%>}
every matrix
every cell
cells={%<options%>}
row sep=##L
column sep=##L
sep=##L
cramped
math mode#true,false
background color=#%color
every arrow
arrows={%<options%>}
arrow style=#Latin Modern,math font,tikz
every label
labels={%<options%>}
center yshift=##L
ampersand replacement=%<macro%>
#endkeyvals

## shared cd keys
#keyvals:\arrow#c,\ar#c,\rar#c,\lar#c,\dar#c,\uar#c,\drar#c,\urar#c,\dlar#c,\ular#c,\tikzcdset#c,\begin{tikzcd}#c
shorten=##L
crossing over
crossing over clearance=##L
marking
description
# some useful shared TikZ keys
%color
color=#%color
in=%<degrees%>
out=%<degrees%>
font=%<font commands%>
line width=##L
#endkeyvals

## arrow keys
#keyvals:\arrow#c,\ar#c,\rar#c,\lar#c,\dar#c,\uar#c,\drar#c,\urar#c,\dlar#c,\ular#c
from=
to=
phantom
shift left=##L
shift right=##L
shift={%<coordinate%>}
xshift=##L
yshift=##L
start anchor=%<anchor%>
start anchor={[%<coord transforms%>]%<anchor%>}
end anchor=%<anchor%>
end anchor={[%<coord transforms%>]%<anchor%>}
# some useful TikZ keys for arrows
bend left
bend left=%<degrees%>
bend right
bend right=%<degrees%>
near start
near end
very near start
very near end
above
below
left
right
swap
to path={%<path spec%>}
#endkeyvals

\tikzcdmatrixname#*