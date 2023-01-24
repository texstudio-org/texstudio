# tkz-euclide package
# Matthew Bertucci 2023/01/24 for v5.01c

#include:tikz
#include:tikzlibraryangles
#include:tikzlibrarybackgrounds
#include:tikzlibrarycalc
#include:tikzlibrarydecorations
#include:tikzlibrarydecorations.markings
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarydecorations.shapes
#include:tikzlibrarydecorations.text
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibraryintersections
#include:tikzlibrarymath
#include:tikzlibraryplotmarks
#include:tikzlibrarypositioning
#include:tikzlibraryquotes
#include:tikzlibraryshapes.misc
#include:tikzlibrarythrough
#include:xfp
#include:xpatch

#keyvals:\usepackage/tkz-euclide#c
lua
#endkeyvals

#ifOption:lua
#include:luacode
# from tkz-tools-lua-angles.tex
\tkzmathanglebetweenpoints{arg1}{arg2}#*
# from tkz-tools-lua-math.tex
\tkzSqrt{arg}#*
\tkzExp{arg}#*
\tkzLog{arg}#*
\tkzSin{arg}#*
\tkzCos{arg}#*
#endif

### II. Setting ###

## Definition of a point: \tkzDefPoint or \tkzDefPoints ##
\tkzDefPoint(%<x%>,%<y%>){%<ref%>}
\tkzDefPoint[%<options%>](%<x%>,%<y%>){%<ref%>}
\tkzDefPoint(%<angle%>:%<radius%>){%<ref%>}
\tkzDefPoint[%<options%>](%<angle%>:%<radius%>){%<ref%>}
	
#keyvals:\tkzDefPoint#c,\tkzDefPoints#c
label=%<text%>
shift=(%<x%>,%<y%>)
shift=(%<angle%>:%<radius%>)
#endkeyvals

\tkzDefShiftPoint[%<point%>](%<x%>,%<y%>){%<ref%>}
\tkzDefShiftPoint[%<point%>](%<angle%>:%<radius%>){%<ref%>}
\tkzDefShiftPointCoord[point1](angle:radius){point2}#*

\tkzDefPoints{x1/y1/name1,x2/y2/name2,...}
\tkzDefPoints[options%keyvals]{x1/y1/name1,x2/y2/name2,...}

### III. Calculating ###

## Auxiliary tools ##
\tkzGetPoint{ref}
\tkzGetPoints{ref1}{ref2}
\tkzGetFirstPoint{ref1}
\tkzGetSecondPoint{ref2}
\tkzGetThirdPoint{ref3}#*
\tkzGetLength{csname}

## Special Points ##
\tkzDefMidPoint(point1,point2)
\tkzDefBarycentricPoint(point1=num1,point2=num2,...)

\tkzDefSimilitudeCenter(O,A)(O',B)
\tkzDefSimilitudeCenter[options%keyvals](O,A)(O',B)

#keyvals:\tkzDefSimilitudeCenter#c
ext
int
#endkeyvals

\tkzDefHarmonic(A,B,C)
\tkzDefHarmonic[options%keyvals](pt1,pt2,pt3)

#keyvals:\tkzDefHarmonic#c
both
ext
int
#endkeyvals

\tkzDefGoldenRatio(point1,point2)

\tkzDefEquiPoints(point1,point2)
\tkzDefEquiPoints[options%keyvals](point1,point2)

#keyvals:\tkzDefEquiPoints#c
dist=##L
from=%<point%>
show#true,false
/tkzcompass/delta=%<number%>
#endkeyvals

\tkzDefMidArc(A,B,C)

## Special points relating to a triangle ##
\tkzDefTriangleCenter(point1,point2,point3)
\tkzDefTriangleCenter[options%keyvals](point1,point2,point3)

#keyvals:\tkzDefTriangleCenter#c
ortho
orthic
centroid
median
circum
in
ex
euler
gergonne
symmedian
lemoine
grebe
spieker
nagel
mittenpunkt
feuerbach
#endkeyvals

## Projection of excenters ##
\tkzDefProjExcenter(A,B,C)(a,b,c){X,Y,Z}
\tkzDefProjExcenter[options%keyvals](A,B,C)(a,b,c){X,Y,Z}

#keyvals:\tkzDefProjExcenter#c
name=%<name%>
#endkeyvals

## Point on line or circle ##
\tkzDefPointOnLine(point1,point2)
\tkzDefPointOnLine[options%keyvals](point1,point2)

#keyvals:\tkzDefPointOnLine#c
pos=%<number%>
#endkeyvals

\tkzDefPointOnCircle[options%keyvals]

#keyvals:\tkzDefPointOnCircle#c
through=center %<point1%> angle %<degrees%> point %<point2%>
R=center %<point%> angle %<degrees%> radius %<radius%>
through in rad=center %<point1%> angle %<radians%> point %<point2%>
R in rad=center %<point%> angle %<radians%> radius %<radius%>
#endkeyvals

## Definition of points by transformation : \tkzDefPointBy ##
\tkzDefPointBy(point)
\tkzDefPointBy[options%keyvals](point)
\tkzDefPointsBy(point1,point2,...){point1,point2,...}
\tkzDefPointsBy[options%keyvals](point1,point2,...){point1,point2,...}

#keyvals:\tkzDefPointBy#c,\tkzDefPointsBy#c
translation=from %<point1%> to %<point2%>
homothety=center %<point%> ratio %<number%>
reflection=over %<point1%>--%<point2%>
symmetry=center %<point%>
projection=onto %<point1%>--%<point2%>
rotation=center %<point%> angle %<degrees%>
rotation in rad=center %<point%> angle %<radians%>
inversion=center %<point1%> through %<point2%>
inversion negative=center %<point1%> through %<point2%>
#endkeyvals

## Defining points using a vector ##
\tkzDefPointWith(point1,point2)
\tkzDefPointWith[options%keyvals](point1,point2)

#keyvals:\tkzDefPointWith#c
orthogonal
orthogonal normed
linear
linear normed
colinear=at %<point%>
colinear normed=at %<point%>
K=%<number%>
#endkeyvals

\tkzGetVectxy(point1,point2){text%plain}

## The straight lines ##

\tkzDefLine(point1,point2)
\tkzDefLine[options%keyvals](point1,point2)

#keyvals:\tkzDefLine#c
mediator
perpendicular=through %<point%>
orthogonal=through %<point%>
parallel=through %<point%>
bisector
bisector out
symmedian
altitude
euler
tangent at=%<point%>
tangent from=%<point%>
K=%<number%>
normed#true,false
#endkeyvals

\tkzDefTangent(point1,point2)
\tkzDefTangent[options%keyvals](point1,point2)

#keyvals:\tkzDefTangent#c
at=%<point%>
from=%<point%>
from with R=%<point%>
#endkeyvals

## Triangles ##
\tkzDefTriangle[options%keyvals](point1,point2)

#keyvals:\tkzDefTriangle#c
two angles=%<angle1%> and %<angle2%>
equilateral
isosceles right
pythagore
pythagoras
egyptian
school
gold
euclid
golden
cheops
swap
#endkeyvals

## Specific triangles with \tkzDefSpcTriangle ##
\tkzDefSpcTriangle[options%keyvals](point1,point2,point3){ref1,ref2,ref3}

#keyvals:\tkzDefSpcTriangle#c
orthic
centroid
medial
in
incentral
ex
excentral
extouch
intouch
contact
euler
symmedial
tangential
feuerbach
name=%<name%>
ortho
#endkeyvals

\tkzPermute(A,B,C)

## Definition of polygons ##
\tkzDefSquare(point1,point2)
\tkzDefRectangle(point1,point2)
\tkzDefParallelogram(point1,point2,point3)
\tkzDefGoldenRectangle(point1,point2)
\tkzDefGoldRectangle(point1,point2)#*

\tkzDefRegPolygon(point1,point2)
\tkzDefRegPolygon[options%keyvals](point1,point2)

#keyvals:\tkzDefRegPolygon#c
name=%<name%>
sides=%<integer%>
center
side
#endkeyvals

## The Circles ##
\tkzDefCircle(point1,point2)
\tkzDefCircle[options%keyvals](point1,point2)

#keyvals:\tkzDefCircle#c
R
diameter
circum
in
ex
euler
nine
spieker
apollonius
orthogonal from=%<point%>
orthogonal through=%<point1%> and %<point2%>
K=%<number%>
#endkeyvals

## Definition of circle by transformation; \tkzDefCircleBy ##
\tkzDefCircleBy(point1,point2)
\tkzDefCircleBy[options%keyvals](point1,point2)

#keyvals:\tkzDefCircleBy#c
translation=from %<point1%> to %<point2%>
homothety=center %<point%> ratio %<number%>
reflection=over %<point1%>--%<point2%>
symmetry=center %<point%>
projection=onto %<point1%>--%<point2%>
rotation=center %<point%> angle %<degrees%>
inversion=center %<point1%> through %<point2%>
#endkeyvals

## Intersections ##
\tkzInterLL(point1,point2)(point3,point4)

\tkzInterLC(point1,point2)(point3,point4)
\tkzInterLC[options%keyvals](point1,point2)(point3,point4)
\tkzInterCC(point1,point2)(point3,point4)
\tkzInterCC[options%keyvals](point1,point2)(point3,point4)

#keyvals:\tkzInterLC#c,\tkzInterCC#c
N
R
with nodes
#endkeyvals

\tkzTestInterCC(O,A)(O',B)
\iftkzFlagCC#*
\tkzFlagCCtrue#*
\tkzFlagCCfalse#*
\tkzInterCCN(point1,point2)(point3,point4)
\tkzInterCCR(point1,radius1)(point2,radius2)

## The angles ##
\tkzGetAngle(csname)
\tkzAngleResult
\tkzFindAngle(point1,point2,point3)
\tkzFindSlopeAngle(point1,point2)

## Random point definition ##
\tkzDefRandPointOn[options%keyvals]

#keyvals:\tkzDefRandPointOn#c
rectangle=%<point1%> and %<point2%>
segment=%<point1%>--%<point2%>
line=%<point1%>--%<point2%>
circle=center %<point%> radius %<number%>
circle through=center %<point1%> through %<point2%>
disk through=center %<point1%> through %<point2%>
#endkeyvals

### IV. Drawing and Filling ###

## Drawing ##
\tkzDrawPoint(name)
\tkzDrawPoint[options%keyvals](name)
\tkzDrawPoints(name1,name2,...)
\tkzDrawPoints[options%keyvals](name1,name2,...)

#keyvals:\tkzDrawPoint#c,\tkzDrawPoints#c
shape=#circle,cross,cross out
size=%<number%>
color=#%color
%color
fill=#%color
draw=#%color
opacity=%<factor%>
ultra thin
very thin
thin
semithick
thick
very thick
ultra thick
#endkeyvals

## Drawing the lines ##
\tkzDrawLine(point1,point2)
\tkzDrawLine[options%keyvals](point1,point2)
\tkzDrawLines(point1,point2,...)
\tkzDrawLines[options%keyvals](point1,point2,...)

#keyvals:\tkzDrawLine#c,\tkzDrawLines#c
add=%<num1%> and %<num2%>
color=#%color
%color
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
style={%<TikZ options%>}
->
<-
<->
ultra thin
very thin
thin
semithick
thick
very thick
ultra thick
line width=##L
double
double distance=##L
#endkeyvals

## Drawing a segment ##
\tkzDrawSegment(point1,point2)
\tkzDrawSegment[options%keyvals](point1,point2)
\tkzDrawSegments(pt1,pt2 pt3,pt4 ...)
\tkzDrawSegments[options%keyvals](pt1,pt2 pt3,pt4 ...)

#keyvals:\tkzDrawSegment#c,\tkzDrawSegments#c
add=%<num1%> and %<num2%>
dim={%<label%>,%<dim%>,%<option%>}
color=#%color
%color
opacity=%<factor%>
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
style={%<TikZ options%>}
->
<-
<->
ultra thin
very thin
thin
semithick
thick
very thick
ultra thick
line width=##L
double
double distance=##L
#endkeyvals

\tkzDrawPolygon(point1,point2,...)
\tkzDrawPolygon[options%keyvals](point1,point2,...)
\tkzDrawPolySeg(point1,point2,...)
\tkzDrawPolySeg[options%keyvals](point1,point2,...)

#keyvals:\tkzDrawPolygon#c,\tkzDrawPolySeg#c
color=#%color
%color
fill=#%color
draw=#%color
opacity=%<factor%>
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
style={%<TikZ options%>}
->
<-
<->
ultra thin
very thin
thin
semithick
thick
very thick
ultra thick
line width=##L
line join=#round,bevel,miter
double
double distance=##L
#endkeyvals

## Draw a circle with \tkzDrawCircle ##
\tkzDrawCircle(point1,point2)
\tkzDrawCircle[options%keyvals](point1,point2)
\tkzDrawCircles(pt1,pt2 pt3,pt4 ...)
\tkzDrawCircles[options%keyvals](pt1,pt2 pt3,pt4 ...)

#keyvals:\tkzDrawCircle#c,\tkzDrawCircles#c
through
R
color=#%color
%color
fill=#%color
opacity=%<factor%>
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
line width=##L
ultra thin
very thin
thin
semithick
thick
very thick
ultra thick
double
double distance=##L
#endkeyvals

\tkzDrawSemiCircle(point1,point2)
\tkzDrawSemiCircle[options%keyvals](point1,point2)
\tkzDrawSemiCircles(pt1,pt2 pt3,pt4 ...)
\tkzDrawSemiCircles[options%keyvals](pt1,pt2 pt3,pt4 ...)

#keyvals:\tkzDrawSemiCircle#c,\tkzDrawSemiCircles#c
through
diameter
color=#%color
%color
fill=#%color
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
line width=##L
ultra thin
very thin
thin
semithick
thick
very thick
ultra thick
double
double distance=##L
#endkeyvals

## Drawing arcs ##
\tkzDrawArc(point1,point2)(point3)
\tkzDrawArc[options%keyvals](point1,point2)(point3)

#keyvals:\tkzDrawArc#c
towards
rotate
R
R with nodes
angles
delta=%<number%>
reverse
color=#%color
%color
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
line width=##L
style={%<TikZ options%>}
line width=##L
ultra thin
very thin
thin
semithick
thick
very thick
ultra thick
double
double distance=##L
#endkeyvals

## Drawing a sector or sectors ##
\tkzDrawSector(point1,point2)(point3)
\tkzDrawSector[options%keyvals](point1,point2)(point3)

#keyvals:\tkzDrawSector#c,\tkzFillSector#c
towards
rotate
R
R with nodes
fill=#%color
opacity=%<factor%>
color=#%color
%color
draw=#%color
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
line width=##L
style={%<TikZ options%>}
line width=##L
ultra thin
very thin
thin
semithick
thick
very thick
ultra thick
double
double distance=##L
#endkeyvals

\tkzFillCircle(point1,point2)
\tkzFillCircle[options%keyvals](point1,point2)
\tkzFillCircles(pt1,pt2 pt3,pt4 ...)
\tkzFillCircles[options%keyvals](pt1,pt2 pt3,pt4 ...)

#keyvals:\tkzFillCircle#c,\tkzFillCircles#c
radius
R
color=#%color
%color
fill=#%color
opacity=%<factor%>
#endkeyvals

\tkzFillPolygon(point1,point2,...)
\tkzFillPolygon[options%keyvals](point1,point2,...)

#keyvals:\tkzFillPolygon#c
color=#%color
%color
opacity=%<factor%>
fill=#%color
#endkeyvals

\tkzFillSector(point1,point2)(point3)
\tkzFillSector[options%keyvals](point1,point2)(point3)

\tkzFillAngle(point1,point2,point3)
\tkzFillAngle[options%keyvals](point1,point2,point3)
\tkzFillAngles(%<point1,point2,point3%>)(%<point4,point5,point6%>)%<...%>
\tkzFillAngles[%<options%>](%<point1,point2,point3%>)(%<point4,point5,point6%>)%<...%>

#keyvals:\tkzFillAngle#c,\tkzFillAngles#c
size=%<number%>
color=#%color
%color
opacity=%<factor%>
fill=#%color
left color=#%color
right color=#%color
#endkeyvals

## Controlling Bounding Box ##
\tkzInit[options%keyvals]

#keyvals:\tkzInit#c
xmin=%<number%>
xmax=%<number%>
xstep=%<number%>
ymin=%<number%>
ymax=%<number%>
ystep=%<number%>
#endkeyvals

\tkzClip
\tkzClip[options%keyvals]

#keyvals:\tkzClip#c
space=%<number%>
#endkeyvals

\tkzShowBB
\tkzShowBB[options%keyvals]

#keyvals:\tkzShowBB#c
line width=##L
fill=#%color
opacity=%<factor%>
color=#%color
%color
#endkeyvals

\tkzClipBB

## Clipping different objects ##
\tkzClipPolygon(point1,point2,...)
\tkzClipPolygon[options%keyvals](point1,point2,...)

#keyvals:\tkzClipPolygon#c
out
#endkeyvals

\tkzClipCircle(point1,point2)
\tkzClipCircle[options%keyvals](point1,point2)

#keyvals:\tkzClipCircle#c
out
#endkeyvals

\tkzClipSector[options%keyvals](point1,point2)(point3)
\tkzClipSector(point1,point2)(point3)

#keyvals:\tkzClipSector#c
towards
rotate
R
#endkeyvals

### V. Marking ###

\tkzMarkSegment(point1,point2)
\tkzMarkSegment[options%keyvals](point1,point2)
\tkzMarkSegments(pt1,pt2 pt3,pt4 ...)
\tkzMarkSegments[options%keyvals](pt1,pt2 pt3,pt4 ...)

\tkzMarkArc(point1,point2,point3)
\tkzMarkArc[options%keyvals](point1,point2,point3)

#keyvals:\tkzMarkSegment#c,\tkzMarkSegments#c,\tkzMarkArc#c
pos=%<number%>
color=#%color
%color
mark=%<mark%>
size=##L
line width=##L
ultra thin
very thin
thin
semithick
thick
very thick
ultra thick
#endkeyvals

\tkzMarkAngle(point1,point2,point3)
\tkzMarkAngle[options%keyvals](point1,point2,point3)
\tkzMarkAngles(%<point1,point2,point3%>)(%<point4,point5,point6%>)%<...%>
\tkzMarkAngles[%<options%>](%<point1,point2,point3%>)(%<point4,point5,point6%>)%<...%>

#keyvals:\tkzMarkAngle#c,\tkzMarkAngles#c
arc=#l,ll,lll
size=##L
mark=%<mark%>
mksize=##L
mkcolor=#%color
color=#%color
mkpos=%<number%>
#endkeyvals

\tkzMarkRightAngle(point1,point2,point3)
\tkzMarkRightAngle[options%keyvals](point1,point2,point3)
\tkzMarkRightAngles(%<point1,point2,point3%>)(%<point4,point5,point6%>)%<...%>
\tkzMarkRightAngles[%<options%>](%<point1,point2,point3%>)(%<point4,point5,point6%>)%<...%>

#keyvals:\tkzMarkRightAngle#c,\tkzMarkRightAngles#c
german
size=%<number%>
fill=#%color
opacity=%<factor%>
draw=#%color
color=#%color
%color
line width=##L
#endkeyvals

\tkzPicAngle(A,O,B)
\tkzPicAngle[TikZ options](A,O,B)
\tkzPicRightAngle(A,O,B)
\tkzPicRightAngle[TikZ options](A,O,B)

### VI. Labelling ###

## Labelling ##
\tkzLabelPoint(point){label}
\tkzLabelPoint[options%keyvals](point){label}
\tkzLabelPoints(point1,point2,...)
\tkzLabelPoints[options%keyvals](point1,point2,...)
\tkzAutoLabelPoints(point1,point2,...)
\tkzAutoLabelPoints[options%keyvals](point1,point2,...)

#keyvals:\tkzLabelPoint#c,\tkzLabelPoints#c,\tkzAutoLabelPoints#c
left
right
above
below
above right
above left
below right
below left
color=#%color
%color
font=%<font commands%>
label=%<text%>
centered
#endkeyvals

#keyvals:\tkzAutoLabelPoints#c
center=%<point%>
dist=%<number%>
#endkeyvals

## Label for a segment ##
\tkzLabelSegment(point1,point2){label}
\tkzLabelSegment[options%keyvals](point1,point2){label}
\tkzLabelSegments(pt1,pt2 pt3,pt4 ...){label}
\tkzLabelSegments[options%keyvals](pt1,pt2 pt3,pt4 ...){label}

#keyvals:\tkzLabelLine#c,\tkzLabelSegment#c,\tkzLabelSegments#c
pos=%<number%>
swap
auto
below=##L
above=##L
left=##L
right=##L
below left=##L
below right=##L
above left=##L
above right=##L
sloped
midway
near start
near end
very near start
very near end
at start
at end
color=#%color
%color
#endkeyvals

## Add labels on a straight line \tkzLabelLine ##
\tkzLabelLine(point1,point2){label}
\tkzLabelLine[options%keyvals](point1,point2){label}

\tkzLabelAngle(point1,point2,point3)
\tkzLabelAngle[options%keyvals](point1,point2,point3)
\tkzLabelAngles(%<point1,point2,point3%>)(%<point4,point5,point6%>)%<...%>
\tkzLabelAngles[%<options%>](%<point1,point2,point3%>)(%<point4,point5,point6%>)%<...%>

#keyvals:\tkzLabelAngle#c,\tkzLabelAngles#c
pos=%<number%>
circle
draw
fill=#%color
font=%<font commands%>
#endkeyvals

\tkzLabelCircle(point1,point2)(angle){label%plain}
\tkzLabelCircle[options%keyvals](point1,point2)(angle){label%plain}

#keyvals:\tkzLabelCircle#c
radius
R
below=##L
above=##L
left=##L
right=##L
below left=##L
below right=##L
above left=##L
above right=##L
color=#%color
%color
fill=#%color
font=%<font commands%>
draw
text width=##L
text centered
#endkeyvals

## Label for an arc ##
\tkzLabelArc(point1,point2,point3){label}
\tkzLabelArc[options%keyvals](point1,point2,point3){label}

#keyvals:\tkzLabelArc#c
pos=%<number%>
below=##L
above=##L
left=##L
right=##L
below left=##L
below right=##L
above left=##L
above right=##L
color=#%color
%color
#endkeyvals

### VII. Complements ###

## Using the compass ##
\tkzCompass(point1,point2)
\tkzCompass[options%keyvals](point1,point2)
\tkzCompasss(pt1,pt2 pt3,pt4 ...)
\tkzCompasss[options%keyvals](pt1,pt2 pt3,pt4 ...)

#keyvals:\tkzCompass#c,\tkzCompasss#c
delta=%<degrees%>
length=%<number%>
color=#%color
%color
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
line width=##L
style={%<TikZ options%>}
line width=##L
ultra thin
very thin
thin
semithick
thick
very thick
ultra thick
#endkeyvals

## The Show ##
\tkzShowLine(point1,point2)
\tkzShowLine[options%keyvals](point1,point2)

#keyvals:\tkzShowLine#c
mediator
parallel=through %<point%>
perpendicular=through %<point%>
orthogonal
bisector
K=%<number%>
length=%<number%>
ratio=%<number%>
gap=%<number%>
size=%<number%>
color=#%color
%color
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
line width=##L
style={%<TikZ options%>}
line width=##L
ultra thin
very thin
thin
semithick
thick
very thick
ultra thick
#endkeyvals

\tkzShowTransformation(point1,point2)
\tkzShowTransformation[options%keyvals](point1,point2)

#keyvals:\tkzShowTransformation#c
reflection=over %<point1%>--%<point2%>
symmetry=center %<point%>
projection=onto %<point1%>--%<point2%>
translation=from %<point1%> to %<point2%>
K=%<number%>
length=%<number%>
ratio=%<number%>
gap=%<number%>
size=%<number%>
color=#%color
%color
#endkeyvals

## Protractor ##
\tkzProtractor(point1,point2)
\tkzProtractor[options%keyvals](point1,point2)

#keyvals:\tkzProtractor#c
lw=##L
scale=%<factor%>
return#true,false
#endkeyvals

## Miscellaneous tools ##
\tkzDuplicateSegment(point1,point2)(point3,point4)
\tkzDuplicateSegment(point1,point2)(point3,point4){point5}
\tkzDuplicateLength(point1,point2)(point3,point4)#*
\tkzDuplicateLength(point1,point2)(point3,point4){point5}#*

\tkzCalcLength(point1,point2)
\tkzCalcLength[options%keyvals](point1,point2)

#keyvals:\tkzCalcLength#c
cm#true,false
#endkeyvals

\tkzpttocm(number){csname}
\tkzcmtopt(number){csname}
\tkzGetPointCoord(point){csname}
\tkzSwapPoints(A,B)
\tkzDotProduct(A,B,C)
\tkzPowerCircle(A)(O,M)
\tkzDefRadicalAxis(A,B)(C,D)
\tkzIsLinear(A,B,C)
\tkzIsOrtho(A,B,C)
\tkzGetResult{csname}

### VIII. Working with style ###

## Predefined styles ##
\tkzSetUpColors[options%keyvals]

#keyvals:\tkzSetUpColors#c
background=#%color
text=#%color
#endkeyvals

## Points style ##
\tkzSetUpPoint[options%keyvals]

#keyvals:\tkzSetUpPoint#c
color=#%color
size=%<number%>
fill=#%color
shape=#circle,cross,cross out
#endkeyvals

## Lines, arc, and compass style ##
\tkzSetUpLine[options%keyvals]
\tkzSetUpArc[options%keyvals]
\tkzSetUpCompass[options%keyvals]

#keyvals:\tkzSetUpLine#c,\tkzSetUpArc#c,\tkzSetUpCompass#c
color=#%color
line width=##L
style=#solid,dotted,densely dotted,loosely dotted,dashed,densely dashed,loosely dashed,dash dot,densely dash dot,loosely dash dot,dash dot dot,densely dash dot dot ,loosely dash dot dot
add=%<num1%> and %<num2%>
#endkeyvals

#keyvals:\tkzSetUpLine#c
add=%<num1%> and %<num2%>
#endkeyvals

#keyvals:\tkzSetUpArc#c,\tkzSetUpCompass#c
delta=%<number%>
#endkeyvals

## Label style ##
\tkzSetUpLabel[TikZ options]

## Own style ##
\tkzSetUpStyle[TikZ options]{style name}
\tkzLengthResult#*

## miscellaneous
\fileversion#S
\filedate#S

## deprecated
\tkzDrawBisector(point1,point2,point3)#S
\tkzDefIntSimilitudeCenter(point1,num1)(point2,num2)#S
\tkzDefExtSimilitudeCenter(point1,num1)(point2,num2)#S
\tkzDefIntHomotheticCenter(point1,num1)(point2,num2)#S
\tkzDefExtHomotheticCenter(point1,num1)(point2,num2)#S
\tkzDrawMedian#S
\tkzDrawBisector#S
\tkzDrawAltitude#S
\tkzDrawMedians#S
\tkzDrawBisectors#S
\tkzDrawAltitudes#S
\tkzGetRandPointOn#S
\tkzTangent#S
\tkzDrawTriangle#S

## not documented
# from tkz-euclide.sty
\tkzRadius#*
\tkzLength#*
\iftkzLinear#*
\tkzLineartrue#*
\tkzLinearfalse#*
\iftkzOrtho#*
\tkzOrthotrue#*
\tkzOrthofalse#*

# from tkz-tools-eu-colors.tex
\setupcolorkeys{options}#*
\tkzSetUpAllColors[options]#*

# from tkz-tools-eu-angles.tex
\tkzNormalizeAngle(arg)#*

# from tkz-tools-eu-math.tex
\tkzpointnormalised{arg}#*
\tkzmathrotatepointaround{arg1}{arg2}{arg3}#*

# from tkz-tools-eu-utilities.tex
\extractxy{arg}#*
\iftkznodedefined{node}{true}{false}#*
\tkzActivOff#*
\tkzActivOn#*
\CountToken{arg}#*
\SubStringConditional{arg1}{arg2}#*
\RecursionMacroEnd{arg1}{arg2}{arg3}#*
\ReplaceSubStrings{arg1}{arg2}{arg3}{arg4}#*
\DisabledNumprint#*
\EnabledNumprint#*
\tkzMathResult#*
\tkzHelpGrid#*

# from tkz-tools-eu-text.tex
\tkzText(x,y){text}
\tkzText[options%keyvals](x,y){text}

#keyvals:\tkzText#c
draw
color=#%color
text=#%color
fill=#%color
opacity=%<factor%>
line width=##L
rotate=%<degrees%>
inner sep=##L
text width=##L
#endkeyvals

\tkzLegend{style/size/color/text}
\tkzLegend[options%keyvals]{style/size/color/text}

#keyvals:\tkzLegend#c
line#true,false
#endkeyvals

# from tkz-obj-eu-axesmin.tex
\ifinteger#*
\integertrue#*
\integerfalse#*
\removedot#*
\tkzSetUpAxis[options]#*

\tkzDrawX
\tkzDrawX[options%keyvals]

#keyvals:\tkzDrawX#c
color=#%color
noticks#true,false
right space=##L
left space=##L
label=%<text%>
trig=%<integer%>
tickwd=##L
tickup=##L
tickdn=##L
>=%<end arrow spec%>
#endkeyvals

\tkzDrawY
\tkzDrawY[options%keyvals]

#keyvals:\tkzDrawY#c
color=#%color
noticks#true,false
up space=##L
down space=##L
label=%<text%>
trig=%<integer%>
tickwd=##L
ticklt=##L
tickrt=##L
#endkeyvals

# from tkz-obj-eu-draw-polygons.tex
\tkzDrawPolygons(point1,point2,...)
\tkzDrawPolygons[options](point1,point2,...)
\tkzLabelRegPolygon(point){label1,label2,...}#*
\tkzLabelRegPolygon[options](point){label1,label2,...}#*
\iftkzClipOutPoly#*
\tkzClipOutPolytrue#*
\tkzClipOutPolyfalse#*

# from tkz-draw-eu-circles.tex
\tkzSetUpCircle[options]#*
\iftkzClipOutCircle#*
\tkzClipOutCircletrue#*
\tkzClipOutCirclefalse#*

# from tkz-obj-eu-grids.tex
\tkzSetUpGrid[options]#*

\tkzGrid[%<options%>]
\tkzGrid[%<options%>](%<x1%>,%<y1%>)(%<x2%>,%<y2%>)

#keyvals:\tkzGrid#c
sub#true,false
color=#%color
%color
subxstep=%<number%>
subystep=%<number%>
line width=##L
#endkeyvals

# from tkz-obj-eu-circles-by.tex
\tkzDefCircleTranslation(point1,point2)#*
\tkzDefCircleHomothety(point1,point2)#*
\tkzDefCircleReflection(point1,point2)#*
\tkzDefCircleSymmetry(point1,point2)#*
\tkzDefCircleRotation(point1,point2)#*
\tkzDefOrthogonalCircle(point1,point2,point3)#*
\tkzDefOrthoThroughCircle(point1,point2,point3,point4)#*
\tkzDefInversionCircle(point1,point2,point3,point4)#*

# from tkz-obj-eu-triangles.tex
\tkzDefEquilateral(point1,point2)#*
\tkzDefIsoscelesRightTriangle(point1,point2)#*
\tkzDrawEquilateral[options](point1,point2)#*
\tkzDefIsoscelesRightTriangle[options](point1,point2)#*
\tkzDefTwoOne(point1,point2)#*
\tkzDefPythagore(point1,point2)#*
\tkzDefSchoolTriangle(point1,point2)#*
\tkzDefGoldTriangle(point1,point2)#*
\tkzDefEuclideTriangle(point1,point2)#*
\tkzDefGoldenTriangle(point1,point2)#*
\tkzDefCheopsTriangle(point1,point2)#*
\tkzDefTwoAnglesTriangle(point1,point2)#*
\SetUpPTTR{options}#*
\tkzDefIncentralTriangle[options](point1,point2,point3)(ref1,ref2)#*
\tkzDefExcentralTriangle[options](point1,point2,point3)(ref1,ref2)#*
\tkzExcentralTriangle[options](point1,point2,point3)(ref1,ref2)#*
\tkzDefIntouchTriangle[options](point1,point2,point3)(ref1,ref2)#*
\tkzDefContactTriangle[options](point1,point2,point3)(ref1,ref2)#*
\tkzDefFeuerbachTriangle[options](point1,point2,point3)(ref1,ref2)#*
\tkzDefCentroidTriangle[options](point1,point2,point3)(ref1,ref2)#*
\tkzDefMedialTriangle[options](point1,point2,point3)(ref1,ref2)#*
\tkzDefMidpointTriangle[options](point1,point2,point3)(ref1,ref2)#*
\tkzDefOrthicTriangle[options](point1,point2,point3)(ref1,ref2)#*
\tkzDefAltitudeTriangle[options](point1,point2,point3)(ref1,ref2)#*
\tkzDefEulerTriangle[options](point1,point2,point3)(ref1,ref2)#*
\tkzDefTangentialTriangle[options](point1,point2,point3)(ref1,ref2)#*
\tkzDefSymmedialTriangle[options](point1,point2,point3)(ref1,ref2)#*

# from tkz-draw-eu-points.tex
\tkzPointShowCoord(point)#*
\tkzPointShowCoord[options%keyvals](point)#*
\tkzShowPointCoord(point)#*
\tkzShowPointCoord[options%keyvals](point)#*

# from tkz-obj-eu-circles.tex
\tkzDefCircleR(point1,point2)#*
\tkzDefCircleD(point1,point2)#*
\tkzDefCircumCircle(point1,point2,point3)#*
\tkzDefInCircle(point1,point2,point3)#*
\tkzDefExCircle(point1,point2,point3)#*
\tkzDefExRadius(point1,point2,point3)#*
\tkzDefEulerCircle(point1,point2,point3)#*
\tkzDefNinePointsCircle(point1,point2,point3)#*
\tkzFeuerBachCircle(point1,point2,point3)#*
\tkzDefEulerRadius(point1,point2,point3)#*
\tkzDefApolloniusCircle(point1,point2)#*
\tkzDefOrthogonalCircle(point1,point2,point3)#*
\tkzDefOrthoThroughCircle(point1,point2,point3,point4)#*
\tkzDefSpiekerCircle(point1,point2,point3)#*

# from tkz-draw-eu-sectors.tex
\tkzDrawSectorRAngles[options](point1,point2)(point3)#*
\tkzDrawSectorN[options](point1,point2)(point3)#*
\tkzDrawSectorRotate[options](point1,point2)(point3)#*
\tkzDrawSectorAngles[options](point1,point2)(point3)#*
\tkzDrawSectorRwithNodesAngles[options](point1,point2)(point3)#*
\tkzDrawSectorR[options](point1,point2)(point3)#*
\tkzFillSectorRAngles[options](point1,point2)(point3)#*
\tkzFillSectorN[options](point1,point2)(point3)#*
\tkzFillSectorRotate[options](point1,point2)(point3)#*
\tkzFillSectorAngles[options](point1,point2)(point3)#*
\tkzFillSectorR[options](point1,point2)(point3)#*

# from tkz-obj-eu-lines.tex
\tkzDefLineLL[options](point1,point2,point3)#*
\tkzDefOrthLine[options](point1,point2,point3)#*
\tkzDefMediatorLine[options](point1,point2,point3)#*
\tkzDefBisectorLine(point1,point2,point3)#*
\tkzDefBisectorOutLine(point1,point2,point3)#*
\tkzDefSymmedianLine(point1,point2,point3)#*
\tkzDefAltitudeLine(point1,point2,point3)#*
\tkzDefEulerLine(point1,point2,point3)#*
\tkzTgtAt(point1)(point2)#*
\tkzTgtFromP(point1,point2)(point3)#*
\tkzTgtFromPR(point1,point2)(point3)#*

# from tkz-obj-eu-polygons.tex
\tkzRegPolygonCenter(point1,point2)#*
\tkzRegPolygonSide(point1,point2)#*

# from tkz-obj-eu-points.tex
\tkzRenamePoint(arg1){arg2}#*

#keyvals:\tkzPointShowCoord#c,\tkzShowPointCoord#c
xlabel=%<text%>
xstyle=
noxdraw#true,false
ylabel=%<text%>
ystyle=
noydraw#true,false
#endkeyvals

\tkzGetPointxy(arg1){arg2}#*

# from tkz-draw-eu-angles.tex
\tkzDrawArcTowards[options](point1,point2)(point3)#*
\tkzDrawArcRotate[options](point1,point2)(point3)#*
\tkzDrawArcAngles[options](point1,point2)(point3)#*
\tkzDrawArcRwithNodes[options](point1,point2)(point3)#*
\tkzDrawArcR[options](point1,point2)(point3)#*
\tkzDrawArcRAngles[options](point1,point2)(point3)#*
\tkzDrawArcRAN[options](point1,point2)(point3)#*
\tkzPathArcRAN[options](point1,point2)(point3)#*

# from tkz-obj-eu-points-rnd.tex
\tkzRandPointOnRect(point1,point2)#*
\tkzRandPointOnSegment(point1,point2)#*
\tkzRandPointOnLine(point1,point2)#*
\tkzRandPointOnCircle(point1,point2)#*
\tkzRandPointOnCircleThrough(point1,point2)#*
\tkzRandPointOnDisk(point1,point2)#*

# from tkz-obj-eu-points-with.tex
\tkzVecKOrth[options](point1,point2)#*
\tkzVecK[options](point1,point2)#*
\tkzVecKOrthNorm[options](point1,point2)#*
\tkzVecKNorm[options](point1,point2)#*

# from tkz-draw-eu-show.tex
\tkzShowMediatorLine[opts](arg)#*
\tkzShowLLLine[opts](arg1)(arg2)#*
\tkzShowOrthLine[opts](arg1)(arg2)#*
\tkzShowBisectorLine[opts](arg1)(arg2)#*
\tkzShowTranslation[opts](arg1)(arg2)#*
\tkzShowSymOrth[opts](arg1)(arg2)#*
\tkzShowCSym[opts](arg1)(arg2)#*
\tkzShowProjection[opts](arg1)(arg2)#*

# from tkz-obj-eu-points-by.tex
\ExtractPoint#S
\FirstPointInList{arg}#*
\tkzTranslation(arg1)(arg2){arg3}#*
\tkzUTranslation(arg1)(arg2)#*
\tkzCSym(arg1)(arg2){arg3}#*
\tkzUCSym(arg1)(arg2)#*
\tkzSymOrth(arg1)(arg2){arg3}#*
\tkzUSymOrth(arg1)(arg2)#*
\tkzProjection(arg1)(arg2){arg3}#*
\tkzUProjection(arg1)(arg2)#*
\tkzHomo(arg1)(arg2){arg3}#*
\tkzUHomo(arg1)(arg2)#*
\tkzRotateAngle(arg1)(arg2){arg3}#*
\tkzURotateAngle(arg1)(arg2)#*
\tkzRotateInRad(arg1)(arg2){arg3}#*
\tkzURotateInRad(arg1)(arg2)#*
\tkzInversePoint(arg1)(arg2){arg3}#*
\tkzUInversePoint(arg1)(arg2)#*
\tkzInverseNegativePoint(arg1)(arg2){arg3}#*
\tkzUInverseNegativePoint(arg1)(arg2)#*

# from tkz-obj-eu-points-spc.tex
\tkzDefBCPoint(point1=num1,point2=num2,...)#*
\tkzDivHarmonic(pt1,pt2,pt3)#*
\tkzDivHarmonic[options%keyvals](pt1,pt2,pt3)#*
\tkzOrthoCenter(point1,point2,point3)#*
\tkzDefOrthoCenter(point1,point2,point3)#*
\tkzCentroid(point1,point2,point3)#*
\tkzBaryCenter(point1,point2,point3)#*
\tkzCircumCenter(point1,point2,point3)#*
\tkzDefCircumCenter(point1,point2,point3)#*
\tkzInCenter(point1,point2,point3)#*
\tkzDefInCenter(point1,point2,point3)#*
\tkzExCenter(point1,point2,point3)#*
\tkzDefExCenter(point1,point2,point3)#*
\tkzEulerCenter(point1,point2,point3)#*
\tkzNinePointCenter(point1,point2,point3)#*
\tkzDefEulerCenter(point1,point2,point3)#*
\tkzSymmedianCenter(point1,point2,point3)#*
\tkzLemoinePoint(point1,point2,point3)#*
\tkzGrebePoint(point1,point2,point3)#*
\tkzDefLemoinePoint(point1,point2,point3)#*
\tkzSpiekerCenter(point1,point2,point3)#*
\tkzDefSpiekerCenter(point1,point2,point3)#*
\tkzGergonneCenter(point1,point2,point3)#*
\tkzDefGergonneCenter(point1,point2,point3)#*
\tkzNagelCenter(point1,point2,point3)#*
\tkzDefNagelCenter(point1,point2,point3)#*
\tkzMittenpunktCenter(point1,point2,point3)#*
\tkzDefMittenpunktCenter(point1,point2,point3)#*
\tkzDefMiddlespoint(point1,point2,point3)#*
\tkzFeuerbachCenter(point1,point2,point3)#*
\tkzDefFeuerbachCenter(point1,point2,point3)#*
\tkzOrthogonalCenter(point1,point2)#*

# from tkz-obj-eu-modules.tex
\usetkzobj{list of objects}#*
\usetkztool{list of tools}#*

# from tkz-obj-eu-intersections.tex
\tkzInterLLxy(point1,point2)(point3,point4)#*
\tkzTestInterLC(point1,point2)(point3,point4)#*
\iftkzFlagLC#*
\tkzFlagLCtrue#*
\tkzFlagLCfalse#*
\tkzInterLCR(arg1)(arg2){arg3}{arg4}#*
\tkzInterLCWithNodes(arg1)(arg2){arg3}{arg4}#*
\tkzInterCCWithNodes(arg1)(arg2){arg3}{arg4}#*

# from tkz-obj-eu-base.tex
\tkzAddName[options]{name}#*

# from tkz-draw-eu-protractor.tex
\FullProtractor#*
\FullProtractorReturn#*

# from tkz-euclide.cfg
\tkzmathstyle#*
\tkzCoeffSubColor#*
\tkzCoeffSubLw#*
\tkzRatioLineGrid#*
\tkzPhi#*
\tkzInvPhi#*
\tkzSqrtPhi#*
\tkzSqrTwo#*
\tkzSqrThree#*
\tkzSqrFive#*
\tkzSqrTwobyTwo#*
\tkzPi#*
\tkzEuler#*
