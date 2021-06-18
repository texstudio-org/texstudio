# tkz-euclide package
# Matthew Bertucci 6/16/2021

#include:tkz-base

\tkzGetPoint{point}#/tikzpicture
\tkzGetPoints{point1,point2,...}#/tikzpicture

\tkzDefMidPoint(point1,point2)#/tikzpicture
\tkzDefBarycentricPoint(point1=num1,point2=num2,...)#/tikzpicture
\tkzCentroid(point1=num1,point2=num2,point3=num3)#/tikzpicture

\tkzDefIntSimilitudeCenter(point1,num1)(point2,num2)#/tikzpicture
\tkzExtSimilitudeCenter(point1,num1)(point2,num2)#/tikzpicture

\tkzDefTriangleCenter[local options%keyvals](point1,point2,point3)#/tikzpicture

#keyvals:\tkzDefTriangleCenter#c
ortho
centroid
circum
in
ex
euler
symmedian
spieker
nagel
mittenpunkt
feuerbach
#endkeyvals

\tkzDefPointOnLine[local options%keyvals](point1,point2)#/tikzpicture

#keyvals:\tkzDefPointOnLine#c
pos=
#endkeyvals

\tkzDefPointOnCircle[local options%keyvals]#/tikzpicture

#keyvals:\tkzDefPointOnCircle#c
angle=
center=
radius=
#endkeyvals

\tkzDefPointBy[local options%keyvals](point)#/tikzpicture
\tkzDefPointsBy[local options%keyvals](point1,point2,...){point1,point2,...}#/tikzpicture

#keyvals:\tkzDefPointBy#c
translation=
homothety=
reflection=
symmetry=
projection=
rotation=
rotation in rad=
inversion=
#endkeyvals

\tkzDefPointWith[local options%keyvals](point1,point2)#/tikzpicture

#keyvals:tkzDefPointWith#c
orthogonal
orthogonal normed
linear
linear normed
colinear=
colinear normed=
K=
#endkeyvals

\tkzGetVectxy(point1,point2){name}#/tikzpicture

\tkzDefRandPointOn[local options%keyvals]#/tikzpicture

#keyvals:\tkzDefRandPointOn#c
rectangle=
segment=
line=
circle=
circle through=
disk through=
#endkeyvals

\tkzDefLine[local options%keyvals](point1,point2)#/tikzpicture
\tkzDefLine[local options%keyvals](point1,point2,point3)#/tikzpicture

#keyvals:\tkzDefLine#c
mediator
perpendicular=through
parallel=through
bisector
K=
normed
#endkeyvals

\tkzDefTangent[local options%keyvals](point1,point2)#/tikzpicture
\tkzDefTangent[local options%keyvals](point1,radius)#/tikzpicture

#keyvals:\tkzDefTangent#c
at=
from=
from with R=
#endkeyvals

\tkzDrawLine[local options%keyvals](point1,point2)#/tikzpicture
\tkzDrawLine[local options%keyvals](point1,point2,point3)#/tikzpicture

#keyvals:\tkzDrawLine#c
median
altitude
bisector
none
add=
#endkeyvals

\tkzDrawSegment[local options%keyvals](point1,point2)#/tikzpicture

#keyvals:\tkzDrawSegment#c
add=
dim=
#endkeyvals

\tkzDrawSegments[local options](point1,point2 point3,point4 ...)#/tikzpicture

\tkzMarkSegment[local options%keyvals](point1,point2)#/tikzpicture
\tkzMarkSegments[local options%keyvals](point1,point2 point3,point4 ...)#/tikzpicture

#keyvals:\tkzMarkSegment#c,\tkzMarkSegments#c
pos=
color=#%color
mark=
size=##L
#endkeyvals

\tkzLabelLine[local options%keyvals](point1,point2){label%plain}#/tikzpicture

\tkzLabelSegment[local options%keyvals](point1,point2){label%plain}#/tikzpicture
\tkzLabelSegments[local options%keyvals](point1,point2 point3,point4 ...)#/tikzpicture

#keyvals:\tkzLabelLine#c,\tkzLabelSegment#c,\tkzLabelSegments#c
pos=
#endkeyvals

\tkzDefTriangle[local options%keyvals](point1,point2)#/tikzpicture
\tkzDrawTriangle[local options%keyvals](point1,point2)#/tikzpicture

#keyvals:\tkzDefTriangle#c,\tkzDrawTriangle#c
two angles=
equilateral
pythagore
school
gold
euclide
golden
cheops
#endkeyvals

\tkzDefSpcTriangle[local options%keyvals](point1,point2,point3)#/tikzpicture

#keyvals:\tkzDefSpcTriangle#c
in
incentral
ex
excentral
intouch
contact
centroid
medial
orthic
feuerbach
euler
tangential
name=
#endkeyvals

\tkzDefSquare(point1,point2)#/tikzpicture
\tkzDrawSquare[local options](point1,point2)#/tikzpicture
\tkzDefParallelogram(point1,point2,point3)#/tikzpicture

\tkzDefGoldRectangle(point1,point2)
\tkzDrawGoldRectangle[local options](point1,point2)#/tikzpicture

\tkzDrawPolygon[local options](point1,point2,...)#/tikzpicture
\tkzDrawPolySeg[local options](point1,point2,...)#/tikzpicture
\tkzClipPolygon[local options](point1,point2,...)#/tikzpicture
\tkzFillPolygon[local options](point1,point2,...)#/tikzpicture

\tkzDefRegPolygon[local options%keyvals](point1,point2)#/tikzpicture

#keyvals:\tkzDefRegPolygon#c
name=
sides=
center
side
#endkeyvals

\tkzDefCircle[local options%keyvals](point1,point2)#/tikzpicture
\tkzDefCircle[local options%keyvals](point1,point2,point3)#/tikzpicture

#keyvals:\tkzDefCircle#c
through
diameter
circum
in
ex
euler
nine
spieker
apollonius
orthogonal
orthogonal through
K=
#endkeyvals

\tkzDrawCircle[local options%keyvals](point1,point2)#/tikzpicture
\tkzDrawCircles[local options%keyvals](point1,point2 point3,point4)#/tikzpicture

#keyvals:\tkzDrawCircle#c
through
diameter
R
#endkeyvals

\tkzDrawSemiCircle[local options%keyvals](point1,point2)#/tikzpicture

#keyvals:\tkzDrawSemiCircle#c
through
diameter
#endkeyvals

\tkzFillCircle[local options%keyvals](point1,point2)#/tikzpicture
\tkzClipCircle[local options%keyvals](point1,point2)#/tikzpicture
\tkzClipCircle[local options%keyvals](point1,radius)#/tikzpicture
\tkzLabelCircle[local options%keyvals](point1,point2)(angle){label%plain}#/tikzpicture

#keyvals:\tkzFillCircle#c,\tkzClipCircle#c,\tkzLabelCircle#c
radius
R
#endkeyvals

\tkzInterLL(point1,point2)(point3,point4)#/tikzpicture

\tkzInterLC[local options%keyvals](point1,point2)(point3,point4)#/tikzpicture
\tkzInterLC[local options%keyvals](point1,point2)(point3,radius)#/tikzpicture
\tkzInterLC[local options%keyvals](point1,point2)(point3,point4,point5)#/tikzpicture
\tkzInterCC[local options%keyvals](point1,point2)(point3,point4)#/tikzpicture
\tkzInterCC[local options%keyvals](point1,radius1)(point2,radius2)#/tikzpicture
\tkzInterCC[local options%keyvals](point1,point2,point3)(point4,point5,point6)#/tikzpicture
\tkzInterCCN(point1,point2)(point3,point4)#/tikzpicture
\tkzInterCCR(point1,radius1)(point2,radius2)#/tikzpicture

#keyvals:\tkzInterLC#c,\tkzInterCC#c
N
R
with nodes
#endkeyvals

\tkzLengthResult#/tikzpicture
\tkzPointResult#/tikzpicture
\tkzAngleResult#/tikzpicture
\tkzLength#/tikzpicture

\tkzFillAngle[local options%keyvals](point1,point2,point3)#/tikzpicture
\tkzFillAngles[local options%keyvals](point1,point2,point3)(point4,point5,point6)...#/tikzpicture

#keyvals:\tkzFillAngle#c,\tkzFillAngles#c
size=##L
#endkeyvals

\tkzMarkAngle[local options%keyvals](point1,point2,point3)#/tikzpicture
\tkzMarkAngles[local options%keyvals](point1,point2,point3)(point4,point5,point6)...#/tikzpicture

#keyvals:\tkzMarkAngle#c,\tkzMarkAngles#c
arc=
size=##L
mark=
mksize=##L
mkcolor=#%color
mkpos=
#endkeyvals

\tkzLabelAngle[local options%keyvals](point1,point2,point3)#/tikzpicture
\tkzLabelAngles[local options%keyvals](point1,point2,point3)(point4,point5,point6)...#/tikzpicture

#keyvals:\tkzLabelAngle#c,\tkzLabelAngles#c
pos=
#endkeyvals

\tkzMarkRightAngle[local options%keyvals](point1,point2,point3)#/tikzpicture
\tkzMarkRightAngles[local options%keyvals](point1,point2,point3)(point4,point5,point6)...#/tikzpicture

#keyvals:\tkzMarkRightAngle#c,\tkzMarkRightAngles#c
german
size=
#endkeyvals

\tkzGetAngle(name)#/tikzpicture

\tkzFindAngle(point1,point2,point3)#/tikzpicture

\tkzFindSlope(point1,point2){name}#/tikzpicture
\tkzFindSlopeAngle(point1,point2)#/tikzpicture

\tkzDrawSector[local options%keyvals](point1,point2)(point3)#/tikzpicture
\tkzDrawSector[local options%keyvals](point1,point2)(angle)#/tikzpicture
\tkzDrawSector[local options%keyvals](point,radius)(angle1,angle2)#/tikzpicture
\tkzDrawSector[local options%keyvals](point,radius)(point1,point2)#/tikzpicture
\tkzFillSector[local options%keyvals](point1,point2)(point3)#/tikzpicture
\tkzFillSector[local options%keyvals](point1,point2)(angle)#/tikzpicture
\tkzFillSector[local options%keyvals](point,radius)(angle1,angle2)#/tikzpicture
\tkzFillSector[local options%keyvals](point,radius)(point1,point2)#/tikzpicture

#keyvals:\tkzDrawSector#c,\tkzFillSector#c
towards
rotate
R
R with nodes
#endkeyvals

\tkzClipSector[local options%keyvals](point1,point2)(point3)#/tikzpicture
\tkzClipSector[local options%keyvals](point1,point2)(angle)#/tikzpicture
\tkzClipSector[local options%keyvals](point,radius)(angle1,angle2)#/tikzpicture

#keyvals:\tkzClipSector#c
towards
rotate
R
#endkeyvals

\tkzDrawArc[local options%keyvals](point1,point2)(point3)#/tikzpicture
\tkzDrawArc[local options%keyvals](point1,point2)(angle)#/tikzpicture
\tkzDrawArc[local options%keyvals](point,radius)(angle1,angle2)#/tikzpicture
\tkzDrawArc[local options%keyvals](point,radius)(point1,point2)#/tikzpicture
\tkzDrawArc[local options%keyvals](point,point2)(angle1,angle2)#/tikzpicture

#keyvals:\tkzDrawArc#c
towards
rotate
R
R with nodes
angles
#endkeyvals

\tkzDuplicateSegment(point1,point2)(point3,point4){point5}#/tikzpicture

\tkzCalcLength[local options%keyvals](point1,point2){name}#/tikzpicture

#keyvals:\tkzCalcLength#c
cm
#endkeyvals

\tkzpttocm(number){name}#/tikzpicture
\tkzcmtopt(number){name}#/tikzpicture

\tkzGetPointCoord(point){name}#/tikzpicture

\tkzCompass[local options%keyvals](point1,point2)#/tikzpicture
\tkzCompasss[local options%keyvals](point1,point2 point3,point4 ...)#/tikzpicture

#keyvals:\tkzCompass#c,\tkzCompasss#c
delta=
length=
#endkeyvals

\tkzSetUpCompass[local options%keyvals]#/tikzpicture

#keyvals:\tkzSetUpCompass#c
line width=##L
color=#%color
style=
#endkeyvals

\tkzShowLine[local options%keyvals](point1,point2)#/tikzpicture
\tkzShowLine[local options%keyvals](point1,point2,point3)#/tikzpicture

#keyvals:\tkzShowLine#c
mediator
perpendicular
orthogonal
bisector
K=
length=
ratio=
gap=
size=
#endkeyvals

\tkzShowTransformation[local options%keyvals](point1,point2)#/tikzpicture
\tkzShowTransformation[local options%keyvals](point1,point2,point3)#/tikzpicture

#keyvals:\tkzShowTransformation#c
reflection=over
symmetry=center
projection=onto
translation=from
K=
length=
ratio=
gap=
size=
#endkeyvals

\tkzDefEquiPoints[local options%keyvals](point1,point2)#/tikzpicture

#keyvals:\tkzDefEquiPoints#c
dist=##L
from=
show
/compass/delta=
#endkeyvals

\tkzProtractor[local options%keyvals](point1,point2)#/tikzpicture

#keyvals:\tkzProtractor#c
lw=##L
scale=
return
#endkeyvals

\tkzSetUpLine[local options%keyvals]#/tikzpicture

#keyvals:\tkzSetUpLine#c
color=#%color
line width=##L
style=
add=
#endkeyvals