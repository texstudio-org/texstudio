# tkz-graph package
# Matthew Bertucci 6/21/2021

#include:tikz

\Vertex[local options%keyvals]{name}#/tikzpicture

#keyvals:\Vertex
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

\EA[local options%keyvals](vertex1){vertex2}#/tikzpicture
\WE[local options%keyvals](vertex1){vertex2}#/tikzpicture
\NO[local options%keyvals](vertex1){vertex2}#/tikzpicture
\SO[local options%keyvals](vertex1){vertex2}#/tikzpicture
\NOEA[local options%keyvals](vertex1){vertex2}#/tikzpicture
\NOWE[local options%keyvals](vertex1){vertex2}#/tikzpicture
\SOEA[local options%keyvals](vertex1){vertex2}#/tikzpicture
\SOWE[local options%keyvals](vertex1){vertex2}#/tikzpicture

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

\Vertices[local options]{type%keyvals}{vertex1,vertex2,...}#/tikzpicture

#keyvals:\Vertices
line
tr1
tr2
tr3
tr4
square
circle
#endkeyvals

\SetVertexNoLabel#/tikzpicture
\SetVertexMath#/tikzpicture
\SetVertexLabel#/tikzpicture
\SetVertexLabelOut#/tikzpicture
\SetVertexLabelIn#/tikzpicture

\Edge[local options%keyvals](vertex1)(vertex2)#/tikzpicture

#keyvals:\Edge
local
color=#%color
lw=##L
label=##l
labeltext=
labelcolor=#%color
labelstyle=
style=
#endkeyvals

\Loop[local options%keyvals](vertex)#/tikzpicture

#keyvals:\Loop
color=#%color
lw=##L
label=##l
labelstyle=
style=
#endkeyvals

\Edges[local options%keyvals](vertex1,vertex2,...)#/tikzpicture

#keyvals:\Loop
color=#%color
lw=##L
label=##l
labelstyle=
style=
dir=#EA,WE,NO,SO,NOEA,NOWE,SOEA,SOWE
dist=##L
#endkeyvals

\GraphInit[local options%keyvals]#/tikzpicture

#keyvals:\GraphInit
vstyle=#Empty,Hasse,Simple,Classic,Normal,Shade,Dijkstra,Welsh,Art,Shade Art
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

\SetVertexSimple[local options%keyvals]#/tikzpicture

#keyvals:\SetVertexSimple
Shape=
MinSize=##L
LineWidth=##L
LineColor=#%color
FillColor=#%color
#endkeyvals

\SetVertexNormal[local options%keyvals]#/tikzpicture

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

\SetUpEdge[local options%keyvals]#/tikzpicture

#keyvals:\SetUpEdge
color=#%color
label=##l
labelstyle=
labeltext=#%color
labelcolor=#%color
style=
lw=##L
#endkeyvals

\SetUpVertex[local options%keyvals]#/tikzpicture

#keyvals:\SetUpVertex
Lpos=
Ldist=##L
style=
NoLabel
LabelOut
#endkeyvals

\SetGraphShadeColor{vertexcolor}{color1}{color2}#/tikzpicture
\SetGraphArtColor{vertexcolor}{edgecolor}#/tikzpicture
\SetGraphColor{vertexcolor}{edgecolor}#/tikzpicture

\grProb[local options%keyvals]{left-vertex}{right-vertex}{toplabel}{bottomlabel}{leftlabel}{rightlabel}#/tikzpicture
\grProbThree[local options%keyvals]{right-vertex}{up-vertex}{down-vertex}{rr/ru/rd}{uu/ud/ur}{dd/dr/du}#/tikzpicture

#keyvals:\grProb,\grProbThree
unit=##L
LposA=
LposB=
Ldist=##L
LoopDist=##L
#endkeyvals

\AddVertexColor{color}{vertex1,vertex2,...}#/tikzpicture

\SetVertexArt#/tikzpicture