# quantikz package
# Matthew Bertucci 12/28/2021 for v0.9.6

#include:tikz
# loads quantikz tikzlibrary

# from quantikz tikzlibrary
#include:xargs
#include:ifthen
#include:xstring
#include:xparse
#include:etoolbox
#include:mathtools
#include:pgfmath
#include:environ
# loads cd, decorations.pathreplacing, calc, positioning, fit, shapes.symbols, shapes.misc
# decorations.pathmorphing, backgrounds, decorations.markings, and math tikzlibraries

\begin{quantikz}#\math,array
\begin{quantikz}[options%keyvals]]#\math,array
\end{quantikz}

\gate{label}#/tikzcd,quantikz
\gate[options%keyvals]{label}#/tikzcd,quantikz
\gate[options%keyvals][width]{label}#/tikzcd,quantikz
\gate[options%keyvals][width][height]{label}#/tikzcd,quantikz

\phase{label}#/tikzcd,quantikz
\phase[TikZ options%keyvals]{label}#/tikzcd,quantikz

\lstick{text}#/tikzcd,quantikz
\lstick[options%keyvals]{text}#/tikzcd,quantikz
\rstick{text}#/tikzcd,quantikz
\rstick[options%keyvals]{text}#/tikzcd,quantikz

\qw#/tikzcd,quantikz
\cw#/tikzcd,quantikz
\push{label}#/tikzcd,quantikz
\alias{arg}#*/tikzcd,quantikz

\trash{label}#/tikzcd,quantikz
\trash[TikZ options%keyvals]{label}#/tikzcd,quantikz

\qwbundle{label}#/tikzcd,quantikz
\qwbundle[alternate]{%<label%>}#/tikzcd,quantikz
\qwbundle[alternate=2]{%<label%>}#/tikzcd,quantikz

\ctrl{number}#/tikzcd,quantikz
\octrl{number}#/tikzcd,quantikz
\targ{}#/tikzcd,quantikz
\targ[TikZ options%keyvals]{}#/tikzcd,quantikz
\control{}#/tikzcd,quantikz
\control[TikZ options%keyvals]{}#/tikzcd,quantikz
\ocontrol{}#/tikzcd,quantikz
\ocontrol[TikZ options%keyvals]{}#/tikzcd,quantikz
\targX{}#/tikzcd,quantikz
\targX[TikZ options%keyvals]{}#/tikzcd,quantikz
\swap{number}#/tikzcd,quantikz

\vqw{number}#/tikzcd,quantikz
\vcw{number}#/tikzcd,quantikz
\cwbend{number}#/tikzcd,quantikz

\ctrlbundle{number}#/tikzcd,quantikz
\ctrlbundle[1 or 2]{number}#/tikzcd,quantikz
\ctrlbundle[1 or 2][TikZ options%keyvals]{number}#/tikzcd,quantikz

\gateinput{text}#/tikzcd,quantikz
\gateinput[options%keyvals]{text}#/tikzcd,quantikz
\gateoutput{text}#/tikzcd,quantikz
\gateoutput[options%keyvals]{text}#/tikzcd,quantikz

\slice{title%text}#/tikzcd,quantikz
\slice[options%keyvals]{title%text}#/tikzcd,quantikz

\phantomgate{text%plain}#/tikzcd,quantikz
\hphantomgate{text%plain}#/tikzcd,quantikz
\ghost{text%plain}#/tikzcd,quantikz
\ghost[options]{text%plain}#*/tikzcd,quantikz
\ghost[options][width]{text%plain}#*/tikzcd,quantikz
\ghost[options][width][height]{text%plain}#*/tikzcd,quantikz

\midstick{text}#/tikzcd,quantikz
\midstick[options%keyvals]{text}#/tikzcd,quantikz

\linethrough#/tikzcd,quantikz

\meter{text}#/tikzcd,quantikz
\meter[TikZ options%keyvals]{text}#/tikzcd,quantikz
\measuretab{label}#/tikzcd,quantikz
\measuretab[TikZ options%keyvals]{label}#/tikzcd,quantikz
\meterD{label}#/tikzcd,quantikz
\meterD[TikZ options%keyvals]{label}#/tikzcd,quantikz
\measure{label}#/tikzcd,quantikz
\measure[TikZ options%keyvals]{label}#/tikzcd,quantikz

\gategroup{text}#/tikzcd,quantikz
\gategroup[options%keyvals]{text}#/tikzcd,quantikz

\wave#/tikzcd,quantikz
\wave[TikZ options%keyvals]#/tikzcd,quantikz

\makeebit{text}#/tikzcd,quantikz
\makeebit[angle]{text}#/tikzcd,quantikz
\makeebit[angle][TikZ options%keyvals]{text}#/tikzcd,quantikz

\ket{arg%formula}
\bra{arg%formula}
\proj{arg%formula}
\braket{left%formula}{right%formula}

#keyvals:\begin{quantikz}#c,\begin{tikzcd}#c
slice all
remove end slices=%<integer%>
slice titles=%<text%>
slice style={%<TikZ options%>}
slice label style={%<TikZ options%>}
vertical slice labels
align equals at=%<wire number%>
thin lines
transparent
#endkeyvals

#keyvals:\gate#c,\lstick#c,\rstick#c,\gateinput#c,\gateoutput#c,\slice#c,\midstick#c,\gategroup#c
wires=%<integer%>
style={%<TikZ options%>}
label style={%<TikZ options%>}
cwires=%<integer%>
nwires=%<integer%>
bundle=%<integer%>
disable auto height
brackets=#none,left,right,both
%<integer%>
steps=%<integer%>
background
swap
#endkeyvals

\myl#*
\myh#*
\myd#*
\theaaa#*
\IfInList{item}{list}#*
\ifnodedefined{node}{true}{false}#*
\MathAxis#*
\DisableMinSize#*
\quantwires#*
\dotikzset#*
\undotikzset#*
\sliceallr#*
\sliceallvr#*
\DivideRowsCols#*
\setmiddle{row num}#*
\vqwexplicit{from}{to}#*
\vqbundleexplicit{from}{to}#*
\vcwhexplicit{from}{to}#*
\vqwexplicitcenter{from}{to}#*
\resetstyles#*
\maketransparent#*
\row#*
\col#*

# from cd tikzlibrary
\begin{tikzcd}#\array,math
\begin{tikzcd}[options%keyvals]#\array,math
\end{tikzcd}
\arrow[%<options%>]#/tikzcd,quantikz
\arrow[%<options%>]{%<direction%>}{%<label%>}#*/tikzcd,quantikz
\arrow[%<options%>]{%<direction%>}[%<label options%>]{%<label%>}#*/tikzcd,quantikz
\ar[%<options%>]#*/tikzcd,quantikz
\rar[%<options%>]#*/tikzcd,quantikz
\rar[%<options%>]{%<label%>}#*/tikzcd,quantikz
\lar[%<options%>]#*/tikzcd,quantikz
\lar[%<options%>]{%<label%>}#*/tikzcd,quantikz
\dar[%<options%>]#*/tikzcd,quantikz
\dar[%<options%>]{%<label%>}#*/tikzcd,quantikz
\uar[%<options%>]#*/tikzcd,quantikz
\uar[%<options%>]{%<label%>}#*/tikzcd,quantikz
\drar[%<options%>]#*/tikzcd,quantikz
\drar[%<options%>]{%<label%>}#*/tikzcd,quantikz
\urar[%<options%>]#*/tikzcd,quantikz
\urar[%<options%>]{%<label%>}#*/tikzcd,quantikz
\dlar[%<options%>]#*/tikzcd,quantikz
\dlar[%<options%>]{%<label%>}#*/tikzcd,quantikz
\ular[%<options%>]#*/tikzcd,quantikz
\ular[%<options%>]{%<label%>}#*/tikzcd,quantikz
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
#keyvals:\tikzcdset#c,\begin{tikzcd}#c,\begin{quantikz}#c
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
#keyvals:\arrow#c,\ar#c,\rar#c,\lar#c,\dar#c,\uar#c,\drar#c,\urar#c,\dlar#c,\ular#c,\tikzcdset#c,\begin{tikzcd}#c,\begin{quantikz}#c
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