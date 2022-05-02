# puyotikz package
# Matthew Bertucci 4/14/2022 for v1.0.1

#include:pythontex
#include:tikz
#include:keyval

\begin{puyotikz}#\pictureHighlight
\begin{puyotikz}[scale]
\end{puyotikz}

\puyosmallscale
\puyobigscale
\puyoboard{board string}{next puyos string}
\puyoboard[options%keyvals]{board string}{next puyos string}
\puyomarker{marker string}
\puyogrid{board string}
\puyogrid[options%keyvals]{board string}

#keyvals:\puyoboard,\puyogrid
ncols=%<number%>
nrows=%<number%>
nhidrows=%<number%>
showlabels=#True,False
#endkeyvals

\puyocolor{name}{r,g,b}#*
redpuyo#B
greenpuyo#B
bluepuyo#B
yellowpuyo#B
purplepuyo#B
graypuyo#B
darkredpuyo#B
darkgreenpuyo#B
darkbluepuyo#B
darkyellowpuyo#B
darkpurplepuyo#B
darkgraypuyo#B