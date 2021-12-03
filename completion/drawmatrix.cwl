# drawmatrix package
# Matthew Bertucci 11/30/2021 for v1.5.0

#include:tikz

\drawmatrix{label}
\drawmatrix[options%keyvals]{label}

\drawmatrixset{options%keyvals}

#keyvals:\drawmatrix#c,\drawmatrixset#c
label text=%<text%>
height=##L
width=##L
size=##L
lower
upper
lower banded
upper banded
banded
lower bandwidth=##L
upper bandwidth=##L
bandwidth=##L
diag
label base=%<text%>
label base anchor=%<anchor%>
exponent=%<text%>
fill=#%color
draw=#%color
line width=##L
ultra thin
very thin
thin
semithick
thick
very thick
ultra thick
line cap=#round,rect,butt
line join=#round,bevel,miter
miter limit=%<factor%>
dash pattern=%<pattern%>
dash phase=##L
dash=%<dash pattern%> phase %<dash phase%>
dash expand off
solid
dotted
densely dotted
loosely dotted
dashed
densely dashed
loosely dashed
dash dot
densely dash dot
loosely dash dot
dash dot dot
densely dash dot dot
loosely dash dot dot
bbox style={%<TikZ options%>}
bbox height=##L
bbox width=##L
bbox size=##L
offset height=##L
offset width=##L
offset=##L
scale=%<factor%>
x=##L
y=##L
label anchor=%<anchor%>
label pos=bbox.%<anchor%>
label pos=matrix.%<anchor%>
baseline=%<node.anchor%>
#endkeyvals

#keyvals:\drawmatrixset#c
every picture/.append style={%<TikZ options%>}
every bbox/.append style={%<TikZ options%>}
every drawmatrix/.append style={%<TikZ options%>}
every label/.append style={%<TikZ options%>}
every node/.append style={%<TikZ options%>}
externalize#true,false
#endkeyvals