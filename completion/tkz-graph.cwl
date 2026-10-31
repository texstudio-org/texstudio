# tkz-graph package
# Matthew Bertucci 2026/10/24 for v2.20c

#include:ifthen
#include:tikz

#keyvals:\usepackage/tkz-graph#c
noshortnames
#endkeyvals

\Vertex{name}
\Vertex[options%keyvals]{name}
\Vertices{type}{vertex1,vertex2,...}
\Vertices[options%keyvals]{type}{vertex1,vertex2,...}

\EA(vertex1){vertex2}
\EA[options%keyvals](vertex1){vertex2}
\WE(vertex1){vertex2}
\WE[options%keyvals](vertex1){vertex2}
\NO(vertex1){vertex2}
\NO[options%keyvals](vertex1){vertex2}
\SO(vertex1){vertex2}
\SO[options%keyvals](vertex1){vertex2}
\NOEA(vertex1){vertex2}
\NOEA[options%keyvals](vertex1){vertex2}
\NOWE(vertex1){vertex2}
\NOWE[options%keyvals](vertex1){vertex2}
\SOEA(vertex1){vertex2}
\SOEA[options%keyvals](vertex1){vertex2}
\SOWE(vertex1){vertex2}
\SOWE[options%keyvals](vertex1){vertex2}

#keyvals:\Vertex,\Vertices,\EA,\WE,\NO,\SO,\NOEA,\NOWE,\SOEA,\SOWE
x=%<number%>
y=%<number%>
a=%<number%>
d=%<number%>
Node#true,false
position=
unit=%<number%>
dir=
style={%<TikZ keys%>}
empty#true,false
NoLabel#true,false
LabelOut#true,false
L=%<text%>
Math#true,false
Ldist=##L
Lpos=%<degrees%>
#endkeyvals

#keyvals:\Vertices
rotation=%<degrees%>
clockwise#true,false
#endkeyvals

\SetGraphUnit{number}

\SetVertexNoLabel
\SetVertexMath
\SetVertexLabel
\SetVertexLabelOut
\SetVertexLabelIn

\Edge(vertex1)(vertex2)
\Edge[options%keyvals](vertex1)(vertex2)
\Edges(vertex1,vertex2,...)
\Edges[options%keyvals](vertex1,vertex2,...)

#keyvals:\Edge,\Edges
color=#%color
lw=##L
double=#%color
dd=##L
label=##l
labeltext=#%color
labelcolor=#%color
labelstyle={%<TikZ keys%>}
style={%<TikZ keys%>}
local#true,false
->
<-
<->
-
arrow={%<spec%>}
#endkeyvals

\Loop(vertex)
\Loop[options%keyvals](vertex)
\grLoop(vertex)#*
\grLoop[options%keyvals](vertex)#*

#keyvals:\Loop,\grLoop
dir=#EA,WE,NO,SO,NOEA,NOWE,SOEA,SOWE
color=#%color
lw=##L
label=##l
labelstyle={%<TikZ keys%>}
style={%<TikZ keys%>}
#endkeyvals

\GraphInit[options%keyvals]
\GraphUnit#*

#keyvals:\GraphInit
vstyle=#Empty,Hasse,Simple,Classic,Normal,Shade,Dijkstra,Welsh,Art,Shade Art,%tkzgraphstyle
unit=%<number%>
#endkeyvals

\tkzDefGraphStyle{name%specialDef}{code}#s#%tkzgraphstyle

\tkzSetUpGraph[options%keyvals]

#keyvals:\tkzSetUpGraph
vertex shape=%<shape%>
vertex line width=##L
vertex line=#%color
vertex text=#%color
vertex fill=#%color
light fill=#%color
dark fill=#%color
ball color=#%color
inner sep=##L
outer sep=##L
small size=##L
medium size=##L
big size=##L
edge color=#%color
edge width=##L
edge fill=#%color
art color=#%color
double distance=##L
label text=#%color
label fill=#%color
unit=%<number%>
directed
arrow tip=%<type%>
#endkeyvals

\tkzHighlightPath{list}
\tkzHighlightPath[options%keyvals]{list}

#keyvals:\tkzHighlightPath
color=#%color
lw=##L
style={%<TikZ keys%>}
cycle#true,false
#endkeyvals

\tkzAdjacencyMatrix#m
\tkzAdjacencyMatrix[options%keyvals]#m

#keyvals:\tkzAdjacencyMatrix
directed#true,false
order={%<list%>}
#endkeyvals

\tkzGraphFromMatrix{list of vertices}{matrix}
\tkzGraphFromMatrix[options%keyvals]{list of vertices}{matrix}
\grProbMatrix{list of states}{transition matrix}
\grProbMatrix[options%keyvals]{list of states}{transition matrix}

#keyvals:\tkzGraphFromMatrix,\grProbMatrix
placed#true,false
unit=%<number%>
rotation=%<degrees%>
clockwise#true,false
directed#true,false
weighted#true,false
style={%<TikZ keys%>}
bend=%<degrees%>
loop distance=##L
#endkeyvals

\VertexInnerSep#*
\VertexOuterSep#*
\VertexDistance#*
\VertexShape#*
\VertexLineWidth#*
\VertexLineColor#*
\VertexLightFillColor#*
\VertexDarkFillColor#*
\VertexTextColor#*
\VertexFillColor#*
\VertexBallColor#*
\VertexBigMinSize#*
\VertexInterMinSize#*
\VertexSmallMinSize#*
\EdgeFillColor#*
\EdgeArtColor#*
\EdgeColor#*
\EdgeDoubleDistance#*
\EdgeLineWidth#*

\SetVertexSimple[options%keyvals]

#keyvals:\SetVertexSimple
Shape=%<shape%>
MinSize=##L
LineWidth=##L
LineColor=#%color
FillColor=#%color
InnerSep=##L
OuterSep=##L
#endkeyvals

\SetVertexNormal[options%keyvals]

#keyvals:\SetVertexNormal
Shape=%<shape%>
MinSize=##L
LineWidth=##L
LineColor=#%color
FillColor=#%color
TextColor=#%color
InnerSep=##L
OuterSep=##L
#endkeyvals

\SetVertexShade[options%keyvals]
\SetVertexArt[options%keyvals]

#keyvals:\SetVertexShade,\SetVertexArt
Shape=%<shape%>
MinSize=##L
LineWidth=##L
LineColor=#%color
BallColor=#%color
InnerSep=##L
OuterSep=##L
#endkeyvals

\SetUpVertex[options%keyvals]

#keyvals:\SetUpVertex
Lpos=%<degrees%>
Ldist=##L
Style={%<TikZ keys%>}
NoLabel#true,false
LabelOut#true,false
Math#true,false
Unit=%<number%>
MinSize=##L
LineWidth=##L
LineColor=#%color
FillColor=#%color
TextColor=#%color
InnerSep=##L
OuterSep=##L
#endkeyvals

\SetUpEdge[options%keyvals]

#keyvals:\SetUpEdge
color=#%color
lw=##L
label=%<text%>
labeltext=#%color
labelcolor=#%color
labelstyle={%<TikZ keys%>}
style={%<TikZ keys%>}
#endkeyvals

\SetGraphShadeColor{ball color}{edge color}{double color}
\SetGraphArtColor{ball color}{edge color}
\SetGraphColor{fill color}{edge color}

\SetVertexLabeledSmall
\SetVertexNotLabeledSmall
\SetVertexForPresentation{ball color}{edge color}{double color}

\tkzSetUpColors[options%keyvals]

#keyvals:\tkzSetUpColors
background=#%color
text=#%color
#endkeyvals

\grProb{left-vertex}{right-vertex}{toplabel%formula}{bottomlabel%formula}{leftlabel%formula}{rightlabel%formula}
\grProb[options%keyvals]{left-vertex}{right-vertex}{toplabel%formula}{bottomlabel%formula}{leftlabel%formula}{rightlabel%formula}
\grProbThree{right-vertex}{up-vertex}{down-vertex}{rr/ru/rd}{uu/ud/ur}{dd/dr/du}
\grProbThree[options%keyvals]{right-vertex}{up-vertex}{down-vertex}{rr/ru/rd}{uu/ud/ur}{dd/dr/du}

#keyvals:\grProb,\grProbThree
unit=##L
LposA=%<degrees%>
LposB=%<degrees%>
Ldist=##L
LoopDist=##L
#endkeyvals

\AddVertexColor{color}{vertex1,vertex2,...}
