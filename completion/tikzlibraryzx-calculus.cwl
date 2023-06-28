# zx-calculus tikzlibrary
# 2022/12/06 for v2021/10/22

#include:amssymb
#include:etoolbox
#include:ifthen
#include:bm
#include:tikzlibrarycd
#include:tikzlibrarybackgrounds
#include:tikzlibrarypositioning
#include:tikzlibraryshapes
#include:tikzlibrarycalc
#include:tikzlibraryintersections

\zx{diagram%formula}
\zx[options%keyvals]{diagram%formula}
\begin{ZX}#\array,math
\begin{ZX}[options%keyvals]#\array,math
\end{ZX}

#keyvals:\zx#c,\begin{ZX}#c,\zxSaveDiagram#c
# from tikz-cd
every diagram
diagrams={%<options%>}
every matrix
every cell
cells={%<options%>}
row sep=##L
column sep=##L
sep=##L
cramped
math mode#true,false
background color=#%color
every arrow
arrows={%<options%>}
arrow style=#Latin Modern,math font,tikz
every label
labels={%<options%>}
center yshift=##L
ampersand replacement=%<macro%>
# shared with arrow cmds
shorten=##L
crossing over
crossing over clearance=##L
marking
description
# some useful shared TikZ keys
%color
color=#%color
in=%<degrees%>
out=%<degrees%>
font=%<font commands%>
line width=##L
execute at begin picture={%<code%>}
# provided by zx-calculus
math baseline=%<node alias%>
zx column sep=##L
zx row sep=##L
use diagram={%<\name%>}{%<nodes%>}
#endkeyvals

\zxEmptyDiagram
\zxNone{text%plain}
\zxNone+{text%plain}
\zxNone-{text%plain}
\zxNone|{text%plain}
\zxN{text%plain}#*
\zxN+{text%plain}#*
\zxN-{text%plain}#*
\zxN|{text%plain}#*
\zxNoneDouble{text%plain}
\zxNoneDouble+{text%plain}
\zxNoneDouble-{text%plain}
\zxNoneDouble|{text%plain}
\zxFracZ{numerator}{denominator}
\zxFracZ{numerator}[num with parens][denom with parens]{denominator}
\zxFracZ-{numerator}{denominator}
\zxFracZ-{numerator}[num with parens][denom with parens]{denominator}
\zxFracX{numerator}{denominator}
\zxFracX-{numerator}{denominator}
\zxZ{text%plain}
\zxZ[options%keyvals]{text%plain}
\zxZ*{text%plain}
\zxZ[options%keyvals]*{text%plain}
\zxZ-{text%plain}
\zxZ[options%keyvals]-{text%plain}
\zxX{text%plain}
\zxX[options%keyvals]{text%plain}
\zxX*{text%plain}
\zxX[options%keyvals]*{text%plain}
\zxX-{text%plain}
\zxX[options%keyvals]-{text%plain}
\zxH{text%plain}
\zxH[options%keyvals]{text%plain}

\leftManyDots{text%plain}
\leftManyDots[text scale]{text%plain}#*
\leftManyDots[text scale][dots scale]{text%plain}
\rightManyDots{text%plain}
\rightManyDots[text scale]{text%plain}#*
\rightManyDots[text scale][dots scale]{text%plain}
\middleManyDots
\zxLoop{}
\zxLoop[dir angle]{}#*
\zxLoop[dir angle][open angle]{}#*
\zxLoop[dir angle][open angle][styles]{}
\zxLoopAboveDots{}
\zxLoopAboveDots[open angle]{}#*
\zxLoopAboveDots[open angle][styles]{}

#keyvals:\zx#c,\begin{ZX}#c,\zxSaveDiagram#c,\zxZ#c,\zxX#c,\zxH#c
phase in content
phase in label
phase in label={%<styles%>}
pil
pil={%<styles%>}
phase in label above
phase in label above={%<styles%>}
pila
pila={%<styles%>}
phase in label below
phase in label below={%<styles%>}
pilb
pilb={%<styles%>}
phase in label right
phase in label right={%<styles%>}
pilr
pilr={%<styles%>}
phase in label left
phase in label left={%<styles%>}
pill
pill={%<styles%>}
# some useful shared tikz keys
text=#%color
#endkeyvals

\zxDebugMode#*

#keyvals:\zxZ#c,\zxX#c,\zxH#c
a=%<alias%>
#endkeyvals

## list tikz-cd cmds here without #/tikzcd
\arrow[options%keyvals]
\arrow[options%keyvals]{direction}#*
\ar[options%keyvals]#*
\rar[options%keyvals]{%<labels%>}#*
\lar[options%keyvals]{%<labels%>}#*
\dar[options%keyvals]{%<labels%>}#*
\uar[options%keyvals]{%<labels%>}#*
\drar[options%keyvals]{%<labels%>}#*
\urar[options%keyvals]{%<labels%>}#*
\dlar[options%keyvals]{%<labels%>}#*
\ular[options%keyvals]{%<labels%>}#*

#keyvals:\arrow#c,\ar#c,\rar#c,\lar#c,\dar#c,\uar#c,\drar#c,\urar#c,\dlar#c,\ular#c
C
C=%<radius ratio%>
C.
C.=%<radius ratio%>
C'
C'=%<radius ratio%>
C-
C-=%<radius ratio%>
o'
o'=%<angle%>
o.
o.=%<angle%>
o-
o-=%<angle%>
-o
-o=%<angle%>
(
(=%<angle%>
)
)=%<angle%>
('-
('=%<angle%>
(.
(.=%<angle%>
start fake center north
start fake center south
start fake center east
start fake center west
start real center
end fake center north
end fake center south
end fake center east
end fake center west
end real center
left to right
right to left
up to down
down to up
force left to right
force right to left
force up to down
force down to up
no fake center
s
s=%<-andL config%>
s'
s'=%<-andL config%>
s.
s.=%<-andL config%>
-s
-s=%<-andL config%>
-s'
-s'=%<-andL config%>
-s.
-s.=%<-andL config%>
s'-
s'-=%<-andL config%>
s.-
s.-=%<-andL config%>
S
S=%<-andL config%>
S'
S'=%<-andL config%>
S.
S.=%<-andL config%>
-S
-S=%<-andL config%>
-S'
-S'=%<-andL config%>
-S.
-S.=%<-andL config%>
S'-
S'-=%<-andL config%>
S.-
S.-=%<-andL config%>
ss
ss=%<-andL config%>
SS
SS=%<-andL config%>
ss.
ss.=%<-andL config%>
.ss
.ss=%<-andL config%>
sIs.
sIs.=%<-andL config%>
.sIs
.sIs=%<-andL config%>
ss.I
ss.I=%<-andL config%>
I.ss
I.ss=%<-andL config%>
SIS
SIS=%<-andL config%>
.SIS
.SIS=%<-andL config%>
ISS
ISS=%<-andL config%>
SS.I
SS.I=%<-andL config%>
I.SS
I.SS=%<-andL config%>
SSI
SSI=%<-andL config%>
N
N=%<-andL config%>
N'
N'=%<-andL config%>
N.
N.=%<-andL config%>
-N
-N=%<-andL config%>
-N'
-N'=%<-andL config%>
-N.
-N.=%<-andL config%>
N-
N-=%<-andL config%>
N'
N'=%<-andL config%>
N.
N.=%<-andL config%>
Nbase
Nbase=%<-andL config%>
NN
NN=%<-andL config%>
NN.
NN.=%<-andL config%>
.NN
.NN=%<-andL config%>
NIN
NIN=%<-andL config%>
INN
INN=%<-andL config%>
NNI
NNI=%<-andL config%>
<'
<'=%<-andL config%>
<.
<.=%<-andL config%>
'>
'>=%<-andL config%>
.>
.>=%<-andL config%>
'v
'v=%<-andL config%>
v'
v'=%<-andL config%>
.^
.^=%<-andL config%>
^.
^.=%<-andL config%>
3 dots
3 dots=%<text%>
3 vdots
3 vdots=%<text%>
H
H={%<styles%>}
Z
Z={%<styles%>}
X
X={%<styles%>}
wire centered
wc
wire centered start
wcs
wire centered end
wce
edge above
edge not above
control points visible
control points not visible
use intersections
dont use intersections
ui
#endkeyvals

colorZxZ#B
colorZxX#B
colorZxH#B

\zxConvertToFracInContent#*
\zxConvertToFracInLabel#*
\zxMinusInShort#*

\zxHCol#*
\zxHRow#*
\zxHColFlat#*
\zxHRowFlat#*
\zxSCol#*
\zxSRow#*
\zxSColFlat#*
\zxSRowFlat#*
\zxHSCol#*
\zxHSRow#*
\zxHSColFlat#*
\zxHSRowFlat#*
\zxWCol#*
\zxWRow#*
\zxwCol#*
\zxwRow#*
\zxDotsCol#*
\zxDotsRow#*
\zxZeroCol#*
\zxZeroRow#*
\zxNCol#*
\zxNRow#*
\zxDefaultColumnSep#*
\zxDefaultRowSep#*
\zxDefaultSoftAngleS#*
\zxDefaultSoftAngleN#*
\zxDefaultSoftAngleO#*
\zxDefaultSoftAngleChevron#*
\zxScaleDots#*
\zxMinus#*
\zxEdgesAbove#*
\zxControlPointsVisible#*
\zxEnableIntersections#*
\zxDisableIntersections#*
\zxEnableIntersectionsNodes#*
\zxEnableIntersectionsWires#*
\zxIntersectionLineBetweenStartEnd#*
\zxDefaultLineWidth#*

\zxSaveDiagram{cmd}{diagram%formula}#d
\zxSaveDiagram{cmd}[options%keyvals]{diagram%formula}#d

# not documented
\chdots#S
\controlOne#S
\controlTwo#S
\cvdots#S
\cvdotsAboveBaseline#S
\cvdotsCenterBaseline#S
\cvdotsCenterMathline#S
\ifAnchorExists{arg1}{arg2}{arg3}{arg4}#S
\ifAnchorExistsFromShape{arg1}{arg2}{arg3}{arg4}#S
\ifPgfpointOrNode{arg1}{arg2}{arg3}#S
\StartPoint#S
\TargetPoint#S
\zxChooseStyle{arg1}{arg2}{arg3}{arg4}#S
\zxMaxDepthPlusHeight#S
\zxMaxRatio#S
\zxUseDiagram{arg}#S
\zxWireInsideIfNoIntersectionName#S