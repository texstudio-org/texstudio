# tkz-base package
# Matthew Bertucci 1/6/2022 for v4.2c

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
#include:tikzlibrarypatterns
#include:tikzlibraryplotmarks
#include:tikzlibrarypositioning
#include:tikzlibraryquotes
#include:tikzlibraryshapes.misc
#include:tikzlibraryshadows
#include:tikzlibrarythrough
#include:numprint
#include:fp

\tkzInit[options%keyvals]

#keyvals:\tkzInit#c
xmin=%<number%>
xmax=%<number%>
xstep=%<number%>
ymin=%<number%>
ymax=%<number%>
ystep=%<number%>
#endkeyvals

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
#endkeyvals

\tkzLabelX[options%keyvals]

#keyvals:\tkzLabelX#c
frac=%<integer%>
trig=%<integer%>
font=%<font commands%>
color=#%color
step=%<number%>
np off#true,false
orig#true,false
text=#%color
#endkeyvals

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

\tkzLabelY[options%keyvals]

#keyvals:\tkzLabelY#c
color=#%color
frac=%<integer%>
font=%<font commands%>
step=%<number%>
text=#%color
#endkeyvals

\tkzAxeX[options%keyvals]
\tkzAxeY[options%keyvals]
\tkzAxeXY[options%keyvals]

#keyvals:\tkzAxeY#c,\tkzAxeX#c,\tkzAxeXY#c
label=%<text%>
trig=%<integer%>
frac=%<integer%>
swap#true,false
text=#%color
#endkeyvals

\tkzDrawXY[options%keyvals]

#keyvals:\tkzDrawXY#c
color=#%color
noticks#true,false
right space=##L
left space=##L
label=%<text%>
trig=%<integer%>
tickwd=##L
ticklt=##L
tickrt=##L
tickup=##L
tickdn=##L
#endkeyvals

\tkzLabelXY[options%keyvals]

#keyvals:\tkzLabelXY#c
color=#%color
frac=%<integer%>
font=%<font commands%>
step=%<number%>
text=#%color
#endkeyvals

\tkzSetUpAxis[options%keyvals]

#keyvals:\tkzSetUpAxis#c
line width=##L
tickwd=##L
ticka=##L
tickb=##L
font=%<font commands%>
#endkeyvals

\tkzGrid[%<options%>]
\tkzGrid[%<options%>](%<x1%>,%<y1%>)(%<x2%>,%<y2%>)

#keyvals:\tkzGrid#c
sub#true,false
color=#%color
subxstep=%<number%>
subystep=%<number%>
line width=##L
#endkeyvals

\tkzDefPoint(%<x%>,%<y%>){%<name%>}
\tkzDefPoint[%<options%>](%<x%>,%<y%>){%<name%>}
\tkzDefPoint(%<angle%>:%<radius%>){%<name%>}
\tkzDefPoint[%<options%>](%<angle%>:%<radius%>){%<name%>}

#keyvals:\tkzDefPoint#c
shift=(%<x%>,%<y%>)
#endkeyvals

\tkzDefPoints{x1/y1/name1,x2/y2/name2,...}
\tkzDefPoints[options]{x1/y1/name1,x2/y2/name2,...}

\tkzDefShiftPoint[point](x,y){name}
\tkzDefShiftPoint[point](angle:radius){name}

\tkzDefShiftPointCoord[a,b](x,y){name}
\tkzDefShiftPointCoord[a,b](angle:radius){name}

\tkzDrawPoint(point)
\tkzDrawPoint[options%keyvals](point)
\tkzDrawPoints(point1,point2,...)
\tkzDrawPoints[options%keyvals](point1,point2,...)

#keyvals:\tkzDrawPoint#c,\tkzDrawPoints#c
shape=#circle,cross,cross out
size=##L
color=#%color
#endkeyvals

\tkzLabelPoint(point){label%plain}
\tkzLabelPoint[TikZ options](point){label%plain}
\tkzLabelPoints(point1,point2,...)
\tkzLabelPoints[TikZ options](point1,point2,...)

\tkzAutoLabelPoints[options%keyvals](point1,point2,...)

#keyvals:\tkzAutoLabelPoints#c
center=
dist=%<factor%>
#endkeyvals

\tkzSetUpPoint[options%keyvals]

#keyvals:\tkzSetUpPoint#c
shape=#circle,cross,cross out
size=%<number%>
color=#%color
fill=#%color
#endkeyvals

\tkzPointShowCoord(point)
\tkzPointShowCoord[options%keyvals](point)
\tkzShowPointCoord(point)#*
\tkzShowPointCoord[options%keyvals](point)#*

#keyvals:\tkzPointShowCoord#c,\tkzShowPointCoord#c
xlabel=%<text%>
xstyle=
noxdraw#true,false
ylabel=%<text%>
ystyle=
noydraw#true,false
#endkeyvals

\tkzClip
\tkzClip[options%keyvals]

#keyvals:\tkzClip#c
space=%<number%>
#endkeyvals

\tkzShowBB[TikZ options]
\tkzClipBB
\tkzSetBB(point1)(point2)#*
\tkzSaveBB#*
\tkzRestoreBB#*

\tkzRep[options%keyvals]

#keyvals:\tkzRep#c
line width=##L
xlabel=
ylabel=
posxlabel=
posylabel=
xnorm=%<number%>
ynorm=%<number%>
color=#%color
colorlabel=#%color
#endkeyvals

\tkzHLine{decimal number}
\tkzHLine[options%keyvals]{decimal number}
\tkzHLines{list of decimal numbers}
\tkzHLines[options%keyvals]{list of decimal numbers}
\tkzVLine{decimal number}
\tkzVLine[options%keyvals]{decimal number}
\tkzVLines{list of decimal numbers}
\tkzVLines[options%keyvals]{list of decimal numbers}

#keyvals:\tkzHLine#c,\tkzHLines#c,\tkzVLine#c,\tkzVLines#c
color=#%color
line width=##L
style={%<TikZ options%>}
#endkeyvals

\tkzHTick{decimal number}
\tkzHTick[options%keyvals]{decimal number}
\tkzHTicks{list of decimal numbers}
\tkzHTicks[options%keyvals]{list of decimal numbers}
\tkzVTick{decimal number}
\tkzVTick[options%keyvals]{decimal number}
\tkzVTicks{list of decimal numbers}
\tkzVTicks[options%keyvals]{list of decimal numbers}

#keyvals:\tkzHTick#c,\tkzHTicks#c,\tkzVTick#c,\tkzVTicks#c,\tkzDrawSetOfPoints#c,\tkzDrawMark#c,\tkzDrawMarks#c
mark=%<mark%>
mark size=##L
mark options={%<TikZ options%>}
#endkeyvals

\tkzDefSetOfPoints{x1/y1,x2/y2,...}
\tkzDefSetOfPoints[options%keyvals]{x1/y1,x2/y2,...}
\tkzDrawSetOfPoints[options%keyvals]
\tkzJoinSetOfPoints[options%keyvals]
\tkzDrawMark(point)
\tkzDrawMark[options%keyvals](point)
\tkzDrawMarks(point1,point2,...)
\tkzDrawMarks[options%keyvals](point1,point2,...)

#keyvals:\tkzDefSetOfPoints#c,\tkzDrawSetOfPoints#c,\tkzJoinSetOfPoints#c,\tkzDrawMark#c,\tkzDrawMarks#c
prefix=%<prefix%>
#endkeyvals

\tkzSetUpMark[options%keyvals]

#keyvals:\tkzSetUpMark#c
mark=%<mark%>
color=#%color
fill=#%color
size=##L
#endkeyvals

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

\tkzGetPoint{point}
\tkzGetFirstPoint{point}#*
\tkzGetSecondPoint{point}#*
\tkzmathstyle#*

### not documented ###

\fileversion#S
\filedate#S

# from tkz-base.cfg
\tkzInvPhi#*
\tkzPhi#*
\tkzInvPhi#*
\tkzSqrtPhi#*
\tkzSqrTwo#*
\tkzSqrThree#*
\tkzSqrFive#*
\tkzSqrTwobyTwo#*
\tkzPi#*
\tkzEuler#*
\tkzSetUpStyle[TikZ options]{style name}#*

# from tkz-tools-modules.tex
\usetkzobj{list of objects}#*
\usetkztool{list of tools}#*

# from tkz-tools-print.tex
\tkzPrintFrac{arg1}{arg2}#*
\tkzPrintFracWithPi{arg1}{arg2}#*
\tkzprintfrac#S

# from tkz-tools-arith.tex
\tkzfactors{arg}#*
\tkzReducFrac{arg1}{arg2}#*
\tkzMathFirstResult#*
\tkzMathSecondResult#*

# from tkz-tools-utilities.tex
\extractxy{arg}#*
\iftkznodedefined{node}{true}{false}#*
\tkzActivOff#*
\tkzActivOn#*
\tkzTwoPtCode#*
\tkzPtExCode#*
\tkzPtVirCode#*
\CountToken{arg}#*
\SubStringConditional{arg1}{arg2}#*
\RecursionMacroEnd{arg1}{arg2}{arg3}#*
\ReplaceSubStrings{arg1}{arg2}{arg3}#*
\DisabledNumprint#*
\EnabledNumprint#*
\tkzSwapPoints(A,B)
\tkzPermute(A,B,C)
\tkzDotProduct(A,B,C)
\tkzGetResult{name}
\tkzIsLinear(A,B,C)
\tkzIsOrtho(A,B,C)
\tkzHelpGrid#*

# from tkz-tools-colors.tex
\setupcolorkeys{color keys}#*
\tkzSetUpColors[options]#*
\tkzSetUpAllColors[options]#*

# from tkz-tools-base.tex
\tkzAddName[TikZ options]{name}#*

# from tkz-obj-axesmin.tex
\ifinteger#*
\integertrue#*
\integerfalse#*
\removedot#*
\tkzgetinteger{arg}#*

# from tkz-obj-grids.tex
\tkzSetUpGrid[options]#*

# from tkz-obj-points.tex
\tkzRenamePoint(arg1){arg2}#*
\tkzGetPoints{arg1}{arg2}#*
\tkzSetUpLabel[options]#*
\tkzGetPointCoord(arg1){arg2}#*
\tkzGetPointxy(arg1){arg2}#*
