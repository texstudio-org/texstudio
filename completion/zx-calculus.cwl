# zx-calculus package
# Matthew Bertucci 10/17/2021

#include:tikz-cd
#include:amssymb
#include:etoolbox
#include:ifthen
#include:xparse
#include:bm

\zx[options]{diagram%formula}
\begin{ZX}#\array,math
\begin{ZX}[options]#\array,math
\end{ZX}

#keyvals:\zx#c,\begin{ZX}#c
every diagram
diagrams=%<options%>
every matrix
every cell
cells=%<options%>
row sep=
column sep=
sep=
cramped
math mode#true,false
background color=#%color
every arrow
arrows=%<options%>
arrow style=#Latin Modern,math font,tikz
phantom
shift left=##L
shift right=##L
shift={%<coordinate%>}
xshift=##L
yshift=##L
start anchor=
end anchor=
shorten=##L
crossing over
crossing over clearance=##L
every label
labels=%<options%>
marking
description
center yshift=##L
execute at begin picture={%<code%>}
text=
/zx/user overlay nodes/.style=
/zx/user overlay wires/.style=
#endkeyvals

\arrow[options%keyvals]
\arrow[options%keyvals]{direction}#*
\ar[options%keyvals]#*
\rar[options%keyvals]%<labels%>#*
\lar[options%keyvals]%<labels%>#*
\dar[options%keyvals]%<labels%>#*
\uar[options%keyvals]%<labels%>#*
\drar[options%keyvals]%<labels%>#*
\urar[options%keyvals]%<labels%>#*
\dlar[options%keyvals]%<labels%>#*
\ular[options%keyvals]%<labels%>#*

#keyvals:\arrow#c,\ar#c,\rar#c,\lar#c,\dar#c,\uar#c,\drar#c,\urar#c,\dlar#c,\ular#c
to head
rightarrow
leftarrow
leftrightarrow
Rightarrow
Leftarrow
Leftrightarrow
maps to
mapsto
mapsfrom
Mapsto
Mapsfrom
hook
hook'
hookrightarrow
hookleftarrow
dashed
dashrightarrow
dashleftarrow
tail
rightarrowtail
leftarrowtail
squiggly
rightsquigarrow
leftsquigarrow
leftrightsquigarrow
two heads
twoheadrightarrow
twoheadleftarrow
no head
no tail
dash
equal
harpoon
harpoon'
rightharpoonup
rightharpoondown
leftharpoonup
leftharpoondown
crossing over
bend right
bend left
from=
to=
start anchor=
end anchor=
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
)'
)'=%<angle%>
s
s'
s'=%<angle%>
s.
s.=%<angle%>
-s'
-s'=%<angle%>
-s.
-s.=%<angle%>
s'-
s'-=%<angle%>
s.-
s.-=%<angle%>
ss
ss.
ss.=%<angle%>
.ss
.ss=%<angle%>
sIs.
sIs.=%<angle%>
.sIs
.sIs=%<angle%>
ss.I-
ss.I-=%<angle%>
I.ss-
I.ss-=%<angle%>
<'
<'=%<angle%>
<.
<.=%<angle%>
'v
'v=%<angle%>
v'
v'=%<angle%>
.^
.^=%<angle%>
^.
^.=%<angle%>
3 dots=%<text%>
3 vdots=%<text%>
H
Z
X
wire centered
wc
wire centered start
wcs
wire centered end
wce
ls=%<looseness%>
between none
bn
#endkeyvals

\zxEmptyDiagram{}
\zxNone{text}
\zxNone+{text}
\zxNone-{text}
\zxNone|{text}
\zxN{text}#*
\zxN+{text}#*
\zxN-{text}#*
\zxN|{text}#*
\zxNoneDouble{text}
\zxNoneDouble+{text}
\zxNoneDouble-{text}
\zxNoneDouble|{text}
\zxFracZ{numerator}{denominator}
\zxFracZ{numerator}[num with parens][denom with parens]{denominator}
\zxFracZ-{numerator}{denominator}
\zxFracZ-{numerator}[num with parens][denom with parens]{denominator}
\zxFracX{numerator}{denominator}
\zxFracX-{numerator}{denominator}
\zxZ{text}
\zxZ[options%keyvals]{text}
\zxX{text}
\zxX[options%keyvals]{text}
\zxH{text}
\zxH[options%keyvals]{text}

#keyvals:\zx#c,\begin{ZX}#c,\zxZ#c,\zxX#c,\zxH#c
a=%<alias%>
phase in content
phase in label
phase in label=%<style%>
pil
pil=%<style%>
phase in label above
phase in label above=%<style%>
pila
pila=%<style%>
phase in label below
phase in label below=%<style%>
pilb
pilb=%<style%>
phase in label right
phase in label right=%<style%>
pilr
pilr=%<style%>
phase in label left
phase in label left=%<style%>
pill
pill=%<style%>
#endkeyvals

#keyvals:\zxZ#c,\zxX#c,\zxH#c
a=%<alias%>
#endkeyvals

\leftManyDots{text}
\leftManyDots[text scale][dots scale]{text}
\rightManyDots{text}
\rightManyDots[text scale][dots scale]{text}
\middleManyDots{}
\zxLoop{}
\zxLoop[dir angle][open angle][styles]{}
\zxLoopAboveDots{}
\zxLoopAboveDots[open angle][styles]{}

\zxDebugMode#*
\zxConvertToFracInContent#*
\zxConvertToFracInLabel#*

colorZxZ#B
colorZxX#B
colorZxH#B

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
\zxDotsCol#*
\zxDotsRow#*
\zxDefaultSoftAngleS#*
\zxDefaultSoftAngleN#*
\zxDefaultSoftAngleO#*
\zxDefaultSoftAngleChevron#*
\zxScaleDots#*
\zxMinus#*
\zxDefaultLineWidth#*