# tkz-euclide package
# Matthew Bertucci 9/17/2021 for v3.06c

#include:tkz-base

\tkzGetPoint{point}#/tikzpicture
\tkzGetPoints{point1,point2,...}#/tikzpicture

\tkzDefMidPoint(point1,point2)#/tikzpicture
\tkzDefBarycentricPoint(point1=num1,point2=num2,...)#/tikzpicture
\tkzCentroid(point1=num1,point2=num2,point3=num3)#/tikzpicture
\tkzApolloniusCenter[options](point1,point2)#*/tikzpicture
\tkzDefApolloniusPoint[options](point1,point2)#*/tikzpicture
\tkzDefApolloniusRadius[options](point1,point2)#*/tikzpicture
\tkzInCenter(point1,point2,point3)#*/tikzpicture

\tkzDefIntSimilitudeCenter(point1,num1)(point2,num2)#/tikzpicture
\tkzExtSimilitudeCenter(point1,num1)(point2,num2)#/tikzpicture

\tkzDefTriangleCenter(point1,point2,point3)#/tikzpicture
\tkzDefTriangleCenter[options%keyvals](point1,point2,point3)#/tikzpicture

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

\tkzDefPointOnLine(point1,point2)#/tikzpicture
\tkzDefPointOnLine[options%keyvals](point1,point2)#/tikzpicture

#keyvals:\tkzDefPointOnLine#c
pos=
#endkeyvals

\tkzDefPointOnCircle#/tikzpicture
\tkzDefPointOnCircle[options%keyvals]#/tikzpicture

#keyvals:\tkzDefPointOnCircle#c
angle=
center=
radius=
#endkeyvals


\tkzDefPointBy(point)#/tikzpicture
\tkzDefPointBy[options%keyvals](point)#/tikzpicture
\tkzDefPointsBy(point1,point2,...){point1,point2,...}#/tikzpicture
\tkzDefPointsBy[options%keyvals](point1,point2,...){point1,point2,...}#/tikzpicture

#keyvals:\tkzDefPointBy#c,tkzDefPointsBy#c
translation=
homothety=
reflection=
symmetry=
projection=
rotation=
rotation in rad=
inversion=
#endkeyvals

\tkzCircumCenter(point1,point2,point3)#*/tikzpicture

\tkzDefPointWith(point1,point2)#/tikzpicture
\tkzDefPointWith[options%keyvals](point1,point2)#/tikzpicture

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

\tkzDefRandPointOn[options%keyvals]#/tikzpicture

#keyvals:\tkzDefRandPointOn#c
rectangle=
segment=
line=
circle=
circle through=
disk through=
#endkeyvals

\tkzDefLine(point1,point2)#/tikzpicture
\tkzDefLine[options%keyvals](point1,point2)#/tikzpicture

#keyvals:\tkzDefLine#c
mediator
perpendicular=through
parallel=through
bisector
K=
normed
#endkeyvals

\tkzDefEquilateral(point1,point2)#*/tikzpicture

\tkzDefTangent(point1,point2)#/tikzpicture
\tkzDefTangent[options%keyvals](point1,point2)#/tikzpicture

#keyvals:\tkzDefTangent#c
at=
from=
from with R=
#endkeyvals

\tkzDrawLine(point1,point2)#/tikzpicture
\tkzDrawLine[options%keyvals](point1,point2)#/tikzpicture

#keyvals:\tkzDrawLine#c
median
altitude
bisector
none
add=
#endkeyvals

\tkzDrawLines(point1,point2,...)#/tikzpicture
\tkzDrawLines[options](point1,point2,...)#/tikzpicture

\tkzDrawSegment(point1,point2)#/tikzpicture
\tkzDrawSegment[options%keyvals](point1,point2)#/tikzpicture

#keyvals:\tkzDrawSegment#c
add=
dim=
#endkeyvals

\tkzDrawSegments(pt1,pt2 pt3,pt4 ...)#/tikzpicture
\tkzDrawSegments[options](pt1,pt2 pt3,pt4 ...)#/tikzpicture

\tkzMarkSegment(point1,point2)#/tikzpicture
\tkzMarkSegment[options%keyvals](point1,point2)#/tikzpicture
\tkzMarkSegments(pt1,pt2 pt3,pt4 ...)#/tikzpicture
\tkzMarkSegments[options%keyvals](pt1,pt2 pt3,pt4 ...)#/tikzpicture

#keyvals:\tkzMarkSegment#c,\tkzMarkSegments#c
pos=
color=#%color
mark=
size=##L
#endkeyvals

\tkzLabelLine[options%keyvals](point1,point2){label%plain}#/tikzpicture

\tkzLabelSegment[options%keyvals](point1,point2){label%plain}#/tikzpicture
\tkzLabelSegments[options%keyvals](pt1,pt2 pt3,pt4 ...){label%plain}#/tikzpicture

#keyvals:\tkzLabelLine#c,\tkzLabelSegment#c,\tkzLabelSegments#c
pos=
#endkeyvals

\tkzDefTriangle[options%keyvals](point1,point2)#/tikzpicture
\tkzDrawTriangle[options%keyvals](point1,point2)#/tikzpicture

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

\tkzDefSpcTriangle[options%keyvals](point1,point2,point3)#/tikzpicture

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
\tkzDrawSquare(point1,point2)#/tikzpicture
\tkzDrawSquare[options](point1,point2)#/tikzpicture
\tkzDefParallelogram(point1,point2,point3)#/tikzpicture

\tkzDefGoldRectangle(point1,point2)
\tkzDrawGoldRectangle(point1,point2)#/tikzpicture
\tkzDrawGoldRectangle[options](point1,point2)#/tikzpicture
\tkzDrawRectangle(point1,point2)#/tikzpicture
\tkzDrawRectangle[options](point1,point2)#/tikzpicture
\tkzDrawPolygon(point1,point2,...)#/tikzpicture
\tkzDrawPolygon[options](point1,point2,...)#/tikzpicture
\tkzDrawPolySeg(point1,point2,...)#/tikzpicture
\tkzDrawPolySeg[options](point1,point2,...)#/tikzpicture
\tkzClipPolygon(point1,point2,...)#/tikzpicture
\tkzClipPolygon[options](point1,point2,...)#/tikzpicture
\tkzClipOutPolygon(point1,point2,...)#*/tikzpicture
\tkzFillPolygon(point1,point2,...)#/tikzpicture
\tkzFillPolygon[options](point1,point2,...)#/tikzpicture
\tkzLabelRegPolygon[options](point){label1,label2,...}#/tikzpicture

\tkzDefRegPolygon(point1,point2)#/tikzpicture
\tkzDefRegPolygon[options%keyvals](point1,point2)#/tikzpicture

#keyvals:\tkzDefRegPolygon#c
name=
sides=
center
side
#endkeyvals

\tkzDefCircle(point1,point2)#/tikzpicture
\tkzDefCircle[options%keyvals](point1,point2)#/tikzpicture

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

\tkzDefExCircle(point1,point2,point3)#/tikzpicture

\tkzDrawCircle(point1,point2)#/tikzpicture
\tkzDrawCircle[options%keyvals](point1,point2)#/tikzpicture
\tkzDrawCircles(pt1,pt2 pt3,pt4 ...)#/tikzpicture
\tkzDrawCircles[options%keyvals](pt1,pt2 pt3,pt4 ...)#/tikzpicture

#keyvals:\tkzDrawCircle#c,\tkzDrawCircles#c
through
diameter
R
#endkeyvals

\tkzDrawSemiCircle(point1,point2)#/tikzpicture
\tkzDrawSemiCircle[options%keyvals](point1,point2)#/tikzpicture

#keyvals:\tkzDrawSemiCircle#c
through
diameter
#endkeyvals

\tkzFillCircle(point1,point2)#/tikzpicture
\tkzFillCircle[options%keyvals](point1,point2)#/tikzpicture
\tkzClipCircle(point1,point2)#/tikzpicture
\tkzClipCircle[options%keyvals](point1,point2)#/tikzpicture
\tkzLabelCircle(point1,point2)(angle){label%plain}#/tikzpicture
\tkzLabelCircle[options%keyvals](point1,point2)(angle){label%plain}#/tikzpicture

#keyvals:\tkzFillCircle#c,\tkzClipCircle#c,\tkzLabelCircle#c
radius
R
#endkeyvals

\tkzInterLL(point1,point2)(point3,point4)#/tikzpicture
\tkzInterLC(point1,point2)(point3,point4)#/tikzpicture
\tkzInterLC[options%keyvals](point1,point2)(point3,point4)#/tikzpicture
\tkzInterCC(point1,point2)(point3,point4)#/tikzpicture
\tkzInterCC[options%keyvals](point1,point2)(point3,point4)#/tikzpicture
\tkzInterCCN(point1,point2)(point3,point4)#/tikzpicture
\tkzInterCCR(point1,radius1)(point2,radius2)#/tikzpicture

#keyvals:\tkzInterLC#c,\tkzInterCC#c
N
R
with nodes
#endkeyvals

\tkzLengthResult#*/tikzpicture
\tkzPointResult#*/tikzpicture
\tkzAngleResult#*/tikzpicture
\tkzLength#*/tikzpicture

\tkzFillAngle(point1,point2,point3)#/tikzpicture
\tkzFillAngle[options%keyvals](point1,point2,point3)#/tikzpicture
\tkzFillAngles(%<point1,point2,point3%>)(%<point4,point5,point6%>)%<...%>#/tikzpicture
\tkzFillAngles[%<options%>](%<point1,point2,point3%>)(%<point4,point5,point6%>)%<...%>#/tikzpicture

#keyvals:\tkzFillAngle#c,\tkzFillAngles#c
size=##L
#endkeyvals

\tkzMarkAngle(point1,point2,point3)#/tikzpicture
\tkzMarkAngle[options%keyvals](point1,point2,point3)#/tikzpicture
\tkzMarkAngles(%<point1,point2,point3%>)(%<point4,point5,point6%>)%<...%>#/tikzpicture
\tkzMarkAngles[%<options%>](%<point1,point2,point3%>)(%<point4,point5,point6%>)%<...%>#/tikzpicture

#keyvals:\tkzMarkAngle#c,\tkzMarkAngles#c
arc=
size=##L
mark=
mksize=##L
mkcolor=#%color
mkpos=
#endkeyvals

\tkzLabelAngle(point1,point2,point3)#/tikzpicture
\tkzLabelAngle[options%keyvals](point1,point2,point3)#/tikzpicture
\tkzLabelAngles(%<point1,point2,point3%>)(%<point4,point5,point6%>)%<...%>#/tikzpicture
\tkzLabelAngles[%<options%>](%<point1,point2,point3%>)(%<point4,point5,point6%>)%<...%>#/tikzpicture

#keyvals:\tkzLabelAngle#c,\tkzLabelAngles#c
pos=
#endkeyvals

\tkzMarkRightAngle(point1,point2,point3)#/tikzpicture
\tkzMarkRightAngle[options%keyvals](point1,point2,point3)#/tikzpicture
\tkzMarkRightAngles(%<point1,point2,point3%>)(%<point4,point5,point6%>)%<...%>#/tikzpicture
\tkzMarkRightAngles[%<options%>](%<point1,point2,point3%>)(%<point4,point5,point6%>)%<...%>#/tikzpicture

#keyvals:\tkzMarkRightAngle#c,\tkzMarkRightAngles#c
german
size=
#endkeyvals

\tkzGetAngle(name)#*/tikzpicture

\tkzFindAngle(point1,point2,point3)#*/tikzpicture

\tkzFindSlope(point1,point2){name}#*/tikzpicture
\tkzFindSlopeAngle(point1,point2)#*/tikzpicture


\tkzDrawSector(point1,point2)(point3)#/tikzpicture
\tkzDrawSector[options%keyvals](point1,point2)(point3)#/tikzpicture
\tkzFillSector(point1,point2)(point3)#/tikzpicture
\tkzFillSector[options%keyvals](point1,point2)(point3)#/tikzpicture

#keyvals:\tkzDrawSector#c,\tkzFillSector#c
towards
rotate
R
R with nodes
#endkeyvals

\tkzClipSector[options%keyvals](point1,point2)(point3)#/tikzpicture
\tkzClipSector(point1,point2)(point3)#/tikzpicture

#keyvals:\tkzClipSector#c
towards
rotate
R
#endkeyvals

\tkzDrawBisector(point1,point2,point3)#/tikzpicture

\tkzDrawArc(point1,point2)(point3)#/tikzpicture
\tkzDrawArc[options%keyvals](point1,point2)(point3)#/tikzpicture

#keyvals:\tkzDrawArc#c
towards
rotate
R
R with nodes
angles
#endkeyvals

\tkzDuplicateSegment(point1,point2)(point3,point4){point5}#/tikzpicture

\tkzpttocm(number){name}#*/tikzpicture
\tkzcmtopt(number){name}#*/tikzpicture

\tkzGetPointCoord(point){name}#*/tikzpicture

\tkzCompass(point1,point2)#/tikzpicture
\tkzCompass[options%keyvals](point1,point2)#/tikzpicture
\tkzCompasss(pt1,pt2 pt3,pt4 ...)#/tikzpicture
\tkzCompasss[options%keyvals](pt1,pt2 pt3,pt4 ...)#/tikzpicture

#keyvals:\tkzCompass#c,\tkzCompasss#c
delta=
length=
#endkeyvals

\tkzSetUpCompass[options%keyvals]#/tikzpicture

#keyvals:\tkzSetUpCompass#c
line width=##L
color=#%color
style=
#endkeyvals

\tkzShowLine(point1,point2)#/tikzpicture
\tkzShowLine[options%keyvals](point1,point2)#/tikzpicture

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

\tkzShowTransformation(point1,point2)#/tikzpicture
\tkzShowTransformation[options%keyvals](point1,point2)#/tikzpicture

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

\tkzDefEquiPoints(point1,point2)#/tikzpicture
\tkzDefEquiPoints[options%keyvals](point1,point2)#/tikzpicture

#keyvals:\tkzDefEquiPoints#c
dist=##L
from=
show
/compass/delta=
#endkeyvals

\tkzProtractor(point1,point2)#/tikzpicture
\tkzProtractor[options%keyvals](point1,point2)#/tikzpicture

#keyvals:\tkzProtractor#c
lw=##L
scale=
return
#endkeyvals

\tkzSetUpLine[options%keyvals]#/tikzpicture

#keyvals:\tkzSetUpLine#c
color=#%color
line width=##L
style=
add=
#endkeyvals

\tkzRadius#*/tikzpicture
\tkzVecKOrth(point1,point2)#*/tikzpicture
\tkzVecKOrth[option](point1,point2)#*/tikzpicture
