# tkz-base package
# Matthew Bertucci 9/17/2021 for v3.06c

#include:tikz
#include:numprint
#include:xfp

\tkzInit[options%keyvals]#/tikzpicture

#keyvals:\tkzInit#c
xmin=
xmax=
xstep=
ymin=
ymax=
ystep=
#endkeyvals

\tkzDrawX[options%keyvals]#/tikzpicture

#keyvals:\tkzDrawX#c
color=#%color
noticks
noticks#true,false
right space=##L
left space=##L
label=
trig=
tickwd=##L
tickup=##L
tickdn=##L
#endkeyvals

\tkzLabelX[options%keyvals]#/tikzpicture

#keyvals:\tkzLabelX#c
frac=
trig=
font=
color=#%color
step=
np off
np off#true,false
orig
orig#true,false
#endkeyvals

\tkzDrawY[options%keyvals]#/tikzpicture

#keyvals:\tkzDrawY#c
color=#%color
noticks
noticks#true,false
up space=##L
down space=##L
label=
trig=
tickwd=##L
ticklt=##L
tickrt=##L
#endkeyvals

\tkzLabelY[options%keyvals]#/tikzpicture

#keyvals:\tkzLabelY#c
color=#%color
frac=
font=
step=
#endkeyvals

\tkzAxeX[options%keyvals]#/tikzpicture
\tkzAxeY[options%keyvals]#/tikzpicture
\tkzAxeXY[options%keyvals]#/tikzpicture

#keyvals:\tkzAxeY#c,\tkzAxeX#c,\tkzAxeXY#c
label=
trig=
frac=
swap
swap#true,false
#endkeyvals

\tkzDrawXY[options%keyvals]#/tikzpicture

#keyvals:\tkzDrawXY#c
color=#%color
noticks
noticks#true,false
right space=##L
left space=##L
label=
trig=
tickwd=##L
ticklt=##L
tickrt=##L
tickup=##L
tickdn=##L
#endkeyvals

\tkzLabelXY[options%keyvals]#/tikzpicture

#keyvals:\tkzLabelXY#c
color=#%color
frac=
font=
step=
#endkeyvals

\tkzSetUpAxis[options%keyvals]#/tikzpicture

#keyvals:\tkzSetUpAxis#c
line width=##L
tickwd=##L
ticka=##L
tickb=##L
font=
#endkeyvals

\tkzGrid[options%keyvals]#/tikzpicture
\tkzGrid[%<options%>](%<x1%>,%<y1%>)(%<x2%>,%<y2%>)#/tikzpicture

#keyvals:\tkzGrid#c
sub
sub#true,false
color=#%color
subxstep=
subystep=
line width=##L
#endkeyvals

\tkzDefPoint[%<options%>](%<x%>,%<y%>){%<name%>}#/tikzpicture
\tkzDefPoint[%<options%>](%<angle%>:%<radius%>){%<name%>}#/tikzpicture

#keyvals:\tkzDefPoint#c
shift=(%<x,y%>)
#endkeyvals

\tkzDefPoints[options]{x1/y1/name1,x2/y2/name2,...}#/tikzpicture

\tkzDefShiftPoint[point](x,y){name}#/tikzpicture
\tkzDefShiftPoint[point](angle:radius){name}#/tikzpicture

\tkzDefShiftPointCoord[a,b](x,y){name}#/tikzpicture
\tkzDefShiftPointCoord[a,b](angle:radius){name}#/tikzpicture

\tkzDrawPoint(point)#/tikzpicture
\tkzDrawPoint[options%keyvals](point)#/tikzpicture
\tkzDrawPoints(point1,point2,...)#/tikzpicture
\tkzDrawPoints[options%keyvals](point1,point2,...)#/tikzpicture

#keyvals:\tkzDrawPoint#c,\tkzDrawPoints#c
shape=#circle,cross,cross out
size=##L
color=#%color
#endkeyvals

\tkzLabelPoint(point){label%plain}#/tikzpicture
\tkzLabelPoint[options](point){label%plain}#/tikzpicture
\tkzLabelPoints(point1,point2,...)#/tikzpicture
\tkzLabelPoints[options](point1,point2,...)#/tikzpicture

\tkzAutoLabelPoints[options%keyvals](point1,point2,...)#/tikzpicture

#keyvals:\tkzAutoLabelPoints#c
center=
dist=
#endkeyvals

\tkzSetUpPoint[options%keyvals]#/tikzpicture

#keyvals:\tkzSetUpPoint#c
shape=#circle,cross,cross out
size=
color=#%color
fill=
#endkeyvals

\tkzPointShowCoord(point)#/tikzpicture
\tkzPointShowCoord[options%keyvals](point)#/tikzpicture
\tkzShowPointCoord(point)#*/tikzpicture
\tkzShowPointCoord[options%keyvals](point)#*/tikzpicture

#keyvals:\tkzPointShowCoord#c,\tkzShowPointCoord#c
xlabel=
xstyle=
noxdraw
noxdraw#true,false
ylabel=
ystyle=
noydraw
noydraw#true,false
#endkeyvals

\tkzShowBB[options]#*/tikzpicture
\tkzClipBB#*/tikzpicture
\tkzSetBB(point1)(point2)#*/tikzpicture
\tkzSaveBB#*/tikzpicture
\tkzRestoreBB#*/tikzpicture

\tkzClip#/tikzpicture
\tkzClip[options%keyvals]#/tikzpicture

#keyvals:\tkzClip#c
space=
#endkeyvals

\tkzRep[options%keyvals]#/tikzpicture

#keyvals:\tkzRep#c
line width=##L
xlabel=
ylabel=
posxlabel=
posylabel=
xnorm=
ynorm=
color=#%color
colorlabel=#%color
#endkeyvals

\tkzHLine{decimal number}#/tikzpicture
\tkzHLine[options%keyvals]{decimal number}#/tikzpicture
\tkzHLines{list of decimal numbers}#/tikzpicture
\tkzHLines[options%keyvals]{list of decimal numbers}#/tikzpicture
\tkzVLine{decimal number}#/tikzpicture
\tkzVLine[options%keyvals]{decimal number}#/tikzpicture
\tkzVLines{list of decimal numbers}#/tikzpicture
\tkzVLines[options%keyvals]{list of decimal numbers}#/tikzpicture

#keyvals:\tkzHLine#c,\tkzHLines#c,\tkzVLine#c,\tkzVLines#c
color=#%color
line width=##L
style=
#endkeyvals

\tkzHTick{decimal number}#/tikzpicture
\tkzHTick[options%keyvals]{decimal number}#/tikzpicture
\tkzHTicks{list of decimal numbers}#/tikzpicture
\tkzHTicks[options%keyvals]{list of decimal numbers}#/tikzpicture
\tkzVTick{decimal number}#/tikzpicture
\tkzVTick[options%keyvals]{decimal number}#/tikzpicture
\tkzVTicks{list of decimal numbers}#/tikzpicture
\tkzVTicks[options%keyvals]{list of decimal numbers}#/tikzpicture

#keyvals:\tkzHTick#c,\tkzHTicks#c,\tkzVTick#c,\tkzVTicks#c
mark=
mark size=##L
mark options=
#endkeyvals

\tkzDefSetOfPoints{x1/y1,x2/y2,...}#/tikzpicture
\tkzDefSetOfPoints[options%keyvals]{x1/y1,x2/y2,...}#/tikzpicture
\tkzDrawSetOfPoints[options%keyvals]#/tikzpicture
\tkzJoinSetOfPoints[options%keyvals]#/tikzpicture
\tkzDrawMark(point)#/tikzpicture
\tkzDrawMark[options%keyvals](point)#/tikzpicture
\tkzDrawMarks(point1,point2,...)#/tikzpicture
\tkzDrawMarks[options%keyvals](point1,point2,...)#/tikzpicture

#keyvals:\tkzDefSetOfPoints#c,\tkzDrawSetOfPoints#c,\tkzJoinSetOfPoints#c,\tkzDrawMark#c,\tkzDrawMarks#c
prefix=
#endkeyvals

\tkzSetUpMark[options%keyvals]#/tikzpicture

#keyvals:\tkzSetUpMark#c
mark=
#endkeyvals

\tkzText(x,y){text}#/tikzpicture
\tkzText[options%keyvals](x,y){text}#/tikzpicture

#keyvals:\tkzText#c
color=#%color
text=#%color
fill=#%color
opacity=
#endkeyvals

\tkzLegend{style/size/color/text}#/tikzpicture
\tkzLegend[options%keyvals]{style/size/color/text}#/tikzpicture

#keyvals:\tkzLegend#c
line
line#true,false
#endkeyvals

\tkzCalcLength(point1,point2){macro}#*/tikzpicture
\tkzCalcLength[unit](point1,point2){macro}#*/tikzpicture
\tkzGetLength{arg}#/tikzpicture
\tkzGetPoint{point}#/tikzpicture
\tkzGetFirstPoint{point}#*/tikzpicture
\tkzGetSecondPoint{point}#*/tikzpicture
