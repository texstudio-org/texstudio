# tkz-base package
# Matthew Bertucci 6/16/2021

#include:tikz
#include:numprint
#include:xfp

\tkzInit[local options%keyvals]#/tikzpicture

#keyvals:\tkzInit#c
xmin=
xmax=
xstep=
ymin=
ymax=
ystep=
#endkeyvals

\tkzDrawX[local options%keyvals]#/tikzpicture

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

\tkzLabelX[local options%keyvals]#/tikzpicture

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

\tkzAxeX[local options%keyvals]#/tikzpicture

#keyvals:\tkzAxeX#c
label=
trig=
frac=
swap
swap#true,false
#endkeyvals

\tkzDrawY[local options%keyvals]#/tikzpicture

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

\tkzLabelY[local options%keyvals]#/tikzpicture

#keyvals:\tkzLabelY#c
color=#%color
frac=
font=
step=
#endkeyvals

\tkzAxeY[local options%keyvals]#/tikzpicture

#keyvals:\tkzAxeY#c
label=
trig=
frac=
swap
swap#true,false
#endkeyvals

\tkzAxeXY[local options%keyvals]#/tikzpicture

#keyvals:\tkzAxeXY#c
label=
trig=
frac=
swap
swap#true,false
#endkeyvals

\tkzDrawXY[local options%keyvals]#/tikzpicture

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

\tkzLabelXY[local options%keyvals]#/tikzpicture

#keyvals:\tkzLabelXY#c
color=#%color
frac=
font=
step=
#endkeyvals

\tkzSetUpAxis[local options%keyvals]#/tikzpicture

#keyvals:\tkzSetUpAxis#c
line width=##L
tickwd=##L
ticka=##L
tickb=##L
font=
#endkeyvals

\tkzGrid[local options%keyvals](x1;y1)(x2;y2)#/tikzpicture

#keyvals:\tkzGrid#c
sub
sub#true,false
color=#%color
subxstep=
subystep=
line width=##L
#endkeyvals

\tkzDefPoint[local options%keyvals](x,y){name}#/tikzpicture
\tkzDefPoint[local options%keyvals](angle:radius){name}#/tikzpicture

#keyvals:\tkzDefPoint#c
shift=
#endkeyvals

\tkzDefPoints[local options]{x1/y1/name1,x2/y2/name2,...}#/tikzpicture

\tkzDefShiftPoint[point](x,y){name}#/tikzpicture
\tkzDefShiftPoint[point](angle:radius){name}#/tikzpicture

\tkzDefShiftPointCoord[a,b](x,y){name}#/tikzpicture
\tkzDefShiftPointCoord[a,b](angle:radius){name}#/tikzpicture

\tkzDrawPoint[local options%keyvals](point)#/tikzpicture
\tkzDrawPoints[local options%keyvals](point1,point2,...)#/tikzpicture

#keyvals:\tkzDrawPoint#c,\tkzDrawPoints#c
shape=#circle,cross,cross out
size=##L
color=#%color
#endkeyvals

\tkzLabelPoint[local options](point){label%plain}#/tikzpicture
\tkzLabelPoints[local options](point1,point2,...)#/tikzpicture

\tkzAutoLabelPoints[local options%keyvals](point1,point2,...)#/tikzpicture

#keyvals:\tkzAutoLabelPoints#c
center=
dist=
#endkeyvals

\tkzSetUpPoint[local options%keyvals]#/tikzpicture

#keyvals:\tkzSetUpPoint#c
shape=#circle,cross,cross out
size=
color=#%color
fill=
#endkeyvals

\tkzPointShowCoord[local options%keyvals](point)#/tikzpicture

#keyvals:\tkzPointShowCoord#c
xlabel=
xstyle=
noxdraw
noxdraw#true,false
ylabel=
ystyle=
noydraw
noydraw#true,false
#endkeyvals

\tkzShowBB[local options]#/tikzpicture
\tkzClipBB#/tikzpicture
\tkzSetBB(x1;y1)(x2;y2)#/tikzpicture
\tkzSetBB(point1)(point2)#/tikzpicture
\tkzSaveBB#/tikzpicture
\tkzRestoreBB#/tikzpicture

\tkzClip[local options%keyvals]#/tikzpicture

#keyvals:\tkzClip#c
space=
#endkeyvals

\tkzRep[local options%keyvals]#/tikzpicture

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

\tkzHLine[local options%keyvals]{decimal number}#/tikzpicture
\tkzHLines[local options%keyvals]{list of decimal numbers}#/tikzpicture
\tkzVLine[local options%keyvals]{decimal number}#/tikzpicture
\tkzVLines[local options%keyvals]{list of decimal numbers}#/tikzpicture

#keyvals:\tkzHLine#c,\tkzHLines#c,\tkzVLine#c,\tkzVLines#c
color=#%color
line width=##L
style=
#endkeyvals

\tkzHTick[local options%keyvals]{decimal number}#/tikzpicture
\tkzHTicks[local options%keyvals]{list of decimal numbers}#/tikzpicture
\tkzVTick[local options%keyvals]{decimal number}#/tikzpicture
\tkzVTicks[local options%keyvals]{list of decimal numbers}#/tikzpicture

#keyvals:\tkzHTick#c,\tkzHTicks#c,\tkzVTick#c,\tkzVTicks#c
mark=
mark size=##L
mark options=
#endkeyvals

\tkzDefSetOfPoints[local options%keyvals]{x1/y1,x2/y2,...}#/tikzpicture
\tkzDrawSetOfPoints[local options%keyvals]#/tikzpicture
\tkzJoinSetOfPoints[local options%keyvals]#/tikzpicture
\tkzDrawMark[local options%keyvals](point)#/tikzpicture
\tkzDrawMarks[local options%keyvals](point1,point2,...)#/tikzpicture

#keyvals:\tkzDefSetOfPoints#c,\tkzDrawSetOfPoints#c,\tkzJoinSetOfPoints#c,\tkzDrawMark#c,\tkzDrawMarks#c
prefix=
#endkeyvals

\tkzSetUpMark[local options%keyvals]#/tikzpicture

#keyvals:\tkzSetUpMark#c
mark=
#endkeyvals

\tkzText[local options%keyvals](x,y){text}#/tikzpicture

#keyvals:\tkzText#c
color=#%color
text=#%color
fill=#%color
opacity=
#endkeyvals

\tkzLegend[local options%keyvals]{style/size/color/text}#/tikzpicture

#keyvals:\tkzLegend#c
line
line#true,false
#endkeyvals
