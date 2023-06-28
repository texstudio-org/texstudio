# quantikz tikzlibrary
# 2022/12/06 for v0.9.6

#include:xargs
#include:ifthen
#include:xstring
#include:etoolbox
#include:mathtools
#include:pgfmath
#include:environ
#include:tikzlibrarycd
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarycalc
#include:tikzlibrarypositioning
#include:tikzlibraryfit
#include:tikzlibraryshapes.symbols
#include:tikzlibraryshapes.misc
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibrarybackgrounds
#include:tikzlibrarydecorations.markings
#include:tikzlibrarymath

\begin{quantikz}#\math,array
\begin{quantikz}[options%keyvals]#\math,array
\end{quantikz}

\gate{label}#/tikzcd,quantikz
\gate[options%keyvals]{label}#/tikzcd,quantikz
\gate[options%keyvals][width]{label}#/tikzcd,quantikz
\gate[options%keyvals][width][height]{label}#/tikzcd,quantikz

\phase{label}#/tikzcd,quantikz
\phase[TikZ keys%keyvals]{label}#/tikzcd,quantikz

\lstick{text}#/tikzcd,quantikz
\lstick[options%keyvals]{text}#/tikzcd,quantikz
\rstick{text}#/tikzcd,quantikz
\rstick[options%keyvals]{text}#/tikzcd,quantikz

\qw#/tikzcd,quantikz
\cw#/tikzcd,quantikz
\push{label}#/tikzcd,quantikz
\alias{arg}#*/tikzcd,quantikz

\trash{label}#/tikzcd,quantikz
\trash[TikZ keys%keyvals]{label}#/tikzcd,quantikz

\qwbundle{label}#/tikzcd,quantikz
\qwbundle[alternate]{%<label%>}#/tikzcd,quantikz
\qwbundle[alternate=2]{%<label%>}#/tikzcd,quantikz

\ctrl{number}#/tikzcd,quantikz
\octrl{number}#/tikzcd,quantikz
\targ{}#/tikzcd,quantikz
\targ[TikZ keys%keyvals]{}#/tikzcd,quantikz
\control{}#/tikzcd,quantikz
\control[TikZ keys%keyvals]{}#/tikzcd,quantikz
\ocontrol{}#/tikzcd,quantikz
\ocontrol[TikZ keys%keyvals]{}#/tikzcd,quantikz
\targX{}#/tikzcd,quantikz
\targX[TikZ keys%keyvals]{}#/tikzcd,quantikz
\swap{number}#/tikzcd,quantikz

\vqw{number}#/tikzcd,quantikz
\vcw{number}#/tikzcd,quantikz
\cwbend{number}#/tikzcd,quantikz

\ctrlbundle{number}#/tikzcd,quantikz
\ctrlbundle[1 or 2]{number}#/tikzcd,quantikz
\ctrlbundle[1 or 2][TikZ keys%keyvals]{number}#/tikzcd,quantikz

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
\meter[TikZ keys%keyvals]{text}#/tikzcd,quantikz
\measuretab{label}#/tikzcd,quantikz
\measuretab[TikZ keys%keyvals]{label}#/tikzcd,quantikz
\meterD{label}#/tikzcd,quantikz
\meterD[TikZ keys%keyvals]{label}#/tikzcd,quantikz
\measure{label}#/tikzcd,quantikz
\measure[TikZ keys%keyvals]{label}#/tikzcd,quantikz

\gategroup{text}#/tikzcd,quantikz
\gategroup[options%keyvals]{text}#/tikzcd,quantikz

\wave#/tikzcd,quantikz
\wave[TikZ keys%keyvals]#/tikzcd,quantikz

\makeebit{text}#/tikzcd,quantikz
\makeebit[angle]{text}#/tikzcd,quantikz
\makeebit[angle][TikZ keys%keyvals]{text}#/tikzcd,quantikz

\ket{arg%formula}
\bra{arg%formula}
\proj{arg%formula}
\braket{left%formula}{right%formula}

#keyvals:\begin{quantikz}#c,\begin{tikzcd}#c
slice all
remove end slices=%<integer%>
slice titles=%<text%>
slice style={%<TikZ keys%>}
slice label style={%<TikZ keys%>}
vertical slice labels
align equals at=%<wire number%>
thin lines
transparent
#endkeyvals

#keyvals:\gate#c,\lstick#c,\rstick#c,\gateinput#c,\gateoutput#c,\slice#c,\midstick#c,\gategroup#c
wires=%<integer%>
style={%<TikZ keys%>}
label style={%<TikZ keys%>}
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

# not documented
\myl#S
\myh#S
\myd#S
\theaaa#S
\IfInList{item}{list}#S
\ifnodedefined{node}{true}{false}#S
\MathAxis#S
\DisableMinSize#S
\quantwires#S
\dotikzset#S
\undotikzset#S
\sliceallr#S
\sliceallvr#S
\DivideRowsCols#S
\setmiddle{row num}#S
\vqwexplicit{from}{to}#S
\vqbundleexplicit{from}{to}#S
\vcwexplicit{from}{to}#S
\vcwhexplicit{from}{to}#S
\vqwexplicitcenter{from}{to}#S
\resetstyles#S
\maketransparent#S
\row#S
\col#S

## list tikz-cd cmds here with #/tikzcd,quantikz
\arrow[%<options%>]#/tikzcd,quantikz
\ar[%<options%>]#*/tikzcd,quantikz
\rar[%<options%>]#*/tikzcd,quantikz
\lar[%<options%>]#*/tikzcd,quantikz
\dar[%<options%>]#*/tikzcd,quantikz
\uar[%<options%>]#*/tikzcd,quantikz
\drar[%<options%>]#*/tikzcd,quantikz
\urar[%<options%>]#*/tikzcd,quantikz
\dlar[%<options%>]#*/tikzcd,quantikz
\ular[%<options%>]#*/tikzcd,quantikz

#keyvals:\begin{quantikz}#c
# from tikz-cd
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
# shared with arrow cmds
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
# shared cd keys
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