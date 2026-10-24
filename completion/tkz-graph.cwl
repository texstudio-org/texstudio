# tkz-graph package
# Matthew Bertucci 2026/10/24 for v2.20c

#include:ifthen
#include:tikz

#keyvals:\usepackage/tkz-graph#c
noshortnames
#endkeyvals

\Vertex{name}#/tikzpicture
\Vertex[options%keyvals]{name}#/tikzpicture
\Vertices{type}{vertex1,vertex2,...}#/tikzpicture
\Vertices[options%keyvals]{type}{vertex1,vertex2,...}#/tikzpicture

#keyvals:\Vertex,\Vertices
x=
y=
a=
d=
Node
position=
dir=
NoLabel
LabelOut
L=##l
Math
Ldist=##L
Lpos=
#endkeyvals

\EA(vertex1){vertex2}#/tikzpicture
\EA[options%keyvals](vertex1){vertex2}#/tikzpicture
\WE(vertex1){vertex2}#/tikzpicture
\WE[options%keyvals](vertex1){vertex2}#/tikzpicture
\NO(vertex1){vertex2}#/tikzpicture
\NO[options%keyvals](vertex1){vertex2}#/tikzpicture
\SO(vertex1){vertex2}#/tikzpicture
\SO[options%keyvals](vertex1){vertex2}#/tikzpicture
\NOEA(vertex1){vertex2}#/tikzpicture
\NOEA[options%keyvals](vertex1){vertex2}#/tikzpicture
\NOWE(vertex1){vertex2}#/tikzpicture
\NOWE[options%keyvals](vertex1){vertex2}#/tikzpicture
\SOEA(vertex1){vertex2}#/tikzpicture
\SOEA[options%keyvals](vertex1){vertex2}#/tikzpicture
\SOWE(vertex1){vertex2}#/tikzpicture
\SOWE[options%keyvals](vertex1){vertex2}#/tikzpicture

#keyvals:\EA,\WE,\NO,\SO,\NOEA,\NOWE,\SOEA,\SOWE
x=
y=
a=
d=
Node
position=
dir=
NoLabel
LabelOut
L=
Math
Ldist=##L
Lpos=
unit=
#endkeyvals

\SetGraphUnit{number}#/tikzpicture

\SetVertexNoLabel#/tikzpicture
\SetVertexMath#/tikzpicture
\SetVertexLabel#/tikzpicture
\SetVertexLabelOut#/tikzpicture
\SetVertexLabelIn#/tikzpicture

\Edge(vertex1)(vertex2)#/tikzpicture
\Edge[options%keyvals](vertex1)(vertex2)#/tikzpicture
\Edges(vertex1,vertex2,...)#/tikzpicture
\Edges[options%keyvals](vertex1,vertex2,...)#/tikzpicture

#keyvals:\Edge,\Edges
color=#%color
lw=##L
double=#%color
dd=##L
label=##l
labeltext=
labelcolor=#%color
labelstyle=
style=
local#true,false
->
<-
<->
-
arrow={%<spec%>}
#endkeyvals

\Loop(vertex)#/tikzpicture
\Loop[options%keyvals](vertex)#/tikzpicture
\grLoop(vertex)#*/tikzpicture
\grLoop[options%keyvals](vertex)#*/tikzpicture

#keyvals:\Loop,\grLoop
dir=#EA,WE,NO,SO,NOEA,NOWE,SOEA,SOWE
color=#%color
lw=##L
label=##l
labelstyle=
style=
#endkeyvals

\GraphInit[options%keyvals]#/tikzpicture
\GraphUnit#*

#keyvals:\GraphInit
vstyle=#Empty,Hasse,Simple,Classic,Normal,Shade,Dijkstra,Welsh,Art,Shade Art,%tkzgraphstyle
unit=%<number%>
#endkeyvals

\tkzDefGraphStyle{name%specialDef}{code}#s#%tkzgraphstyle

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

\SetVertexSimple#/tikzpicture
\SetVertexSimple[options%keyvals]#/tikzpicture

#keyvals:\SetVertexSimple
Shape=
MinSize=##L
LineWidth=##L
LineColor=#%color
FillColor=#%color
#endkeyvals

\SetVertexNormal[options%keyvals]#/tikzpicture

#keyvals:\SetVertexNormal
color=#%color
label=##l
labelstyle=
labeltext=#%color
labelcolor=#%color
style=
lw=##L
Shape=
LineWidth=##L
FillColor=#%color
#endkeyvals

\SetUpVertex[options%keyvals]#/tikzpicture

#keyvals:\SetUpVertex
Lpos=
Ldist=##L
style=
NoLabel
LabelOut
#endkeyvals

\SetUpEdge[options%keyvals]#/tikzpicture

#keyvals:\SetUpEdge
color=#%color
label=##l
labelstyle=
labeltext=#%color
labelcolor=#%color
style=
lw=##L
#endkeyvals

\SetGraphShadeColor{vertexcolor}{color1}{color2}#/tikzpicture
\SetGraphArtColor{vertexcolor}{edgecolor}#/tikzpicture
\SetGraphColor{vertexcolor}{edgecolor}#/tikzpicture

\grProb{left-vertex}{right-vertex}{toplabel}{bottomlabel}{leftlabel}{rightlabel}#/tikzpicture
\grProb[options%keyvals]{left-vertex}{right-vertex}{toplabel}{bottomlabel}{leftlabel}{rightlabel}#/tikzpicture
\grProbThree{right-vertex}{up-vertex}{down-vertex}{rr/ru/rd}{uu/ud/ur}{dd/dr/du}#/tikzpicture
\grProbThree[options%keyvals]{right-vertex}{up-vertex}{down-vertex}{rr/ru/rd}{uu/ud/ur}{dd/dr/du}#/tikzpicture

#keyvals:\grProb,\grProbThree
unit=##L
LposA=
LposB=
Ldist=##L
LoopDist=##L
#endkeyvals

\AddVertexColor{color}{vertex1,vertex2,...}#/tikzpicture

\SetVertexArt#*/tikzpicture
