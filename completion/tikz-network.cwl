# tikz-network package
# Matthew Bertucci 9/3/2021 for v1.1

#include:tikz
#include:etex
#include:datatool
#include:graphicx
#include:trimspaces
#include:xifthen

\Vertex[options%keyvals]{name}

#keyvals:\Vertex
x=
y=
size=
color=#%color
opacity=
shape=
label=
fontsize=
fontcolor=#%color
fontscale=
position=
distance=
style=
layer=
NoLabel#true,false
IdAsLabel#true,false
Math#true,false
RGB#true,false
Pseudo#true,false
#endkeyvals

\Edge[options%keyvals](vertex1)(vertex2)

#keyvals:\Edge
lw=##L
color=#%color
opacity=
bend=
label=
fontsize=
fontcolor=#%color
fontscale=
position=
distance=
style=
path={%<vertex list%>}
loopsize=##L
loopposition=
loopshape=
Direct#true,false
Math#true,false
RGB#true,false
NotInBG#true,false
#endkeyvals

\Text[options%keyvals]{text}

#keyvals:\Text
x=
y=
fontsize=
color=#%color
opacity=
position=
distance=##L
rotation=
anchor=
width=##L
style=
layer=
RGB#true,false
#endkeyvals

\Vertices[options%keyvals]{file}

#keyvals:\Vertices
size=
color=#%color
opacity=
style=
layer=
NoLabel#true,false
IdAsLabel#true,false
Math#true,false
RGB#true,false
Pseudo#true,false
#endkeyvals

\Edges[options%keyvals]{file}

#keyvals:\Edges
lw=##L
color=#%color
opacity=
style=
vertices=%<file%>
layer=
Direct#true,false
Math#true,false
NoLabel#true,false
RGB#true,false
NotInBG#true,false
#endkeyvals

#keyvals:\begin{tikzpicture}#c
multilayer
multilayer=3d
#endkeyvals

\begin{Layer}
\end{Layer}

\Plane[options%keyvals]

#keyvals:\Plane
x=
y=
width=##L
height=##L
color=#%color
opacity=
grid=
image=%<file%>
style=
layer=
RGB#true,false
NoFill#true,false
NoBorder#true,false
ImageAndFill#true,false
InBG#true,false
#endkeyvals

\SetDefaultUnit{unit}#*
\SetDistanceScale{number}#*
\SetLayerDistance{length}#*
\SetCoordinates[specs%keyvals]#*

#keyvals:\SetCoordinates
xAngle=
yAngle=
zAngle=
xLength=
yLength=
zLength=
#endkeyvals

\SetVertexStyle[options%keyvals]

#keyvals:\SetVertexStyle
Shape=
InnerSep=##L
OuterSep=##L
MinSize=
FillColor=#%color
FillOpacity=
LineWidth=##L
LineColor=#%color
LineOpacity=
TextFont=
TextColor=#%color
TextOpacity=
TextRotation=
#endkeyvals

\SetEdgeStyle[options%keyvals]

#keyvals:\SetEdgeStyle
LineWidth=##L
Color=#%color
Opacity=
Arrow=
TextFont=
TextOpacity=
TextFillColor=#%color
TextFillOpacity=
InnerSep=##L
OuterSep=##L
TextRotation=
#endkeyvals

\EdgesNotInBG#*
\EdgesInBG#*

\SetTextStyle[options%keyvals]

#keyvals:\SetTextStyle
TextFont=
TextOpacity=
TextColor=#%color
InnerSep=##L
OuterSep=##L
TextRotation=
#endkeyvals

\SetPlaneStyle[options%keyvals]

#keyvals:\SetPlaneStyle
LineWidth=##L
LineColor=#%color
LineOpacity=
FillColor=#%color
FillOpacity=
GridLineWidth=##L
GridColor=#%color
GridOpacity=
#endkeyvals

\SetPlaneWidth{width}#*
\SetPlaneHeight{height}#*