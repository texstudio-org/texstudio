# elzcards package
# Matthew Bertucci 2022/07/24 for v0.4d

#include:calc
#include:keyval
#include:xcolor

\BusinessCard{front side%text}
\BusinessCard{front side%text}[back side%text]
\IndexCard{front side%text}
\IndexCard{front side%text}[back side%text]
\FlashCard{front side%text}
\FlashCard{front side%text}[back side%text]

\CurrentIC
\CurrentFC
\TotalIC
\TotalFC

\MakeBC
\MakeBC[options%keyvals]
\MakeBC*
\MakeBC*[options%keyvals]
\MakeIC
\MakeIC[options%keyvals]
\MakeIC*
\MakeIC*[options%keyvals]
\MakeFC
\MakeFC[options%keyvals]
\MakeFC*
\MakeFC*[options%keyvals]

#keyvals:\MakeBC,\MakeBC*,\MakeIC,\MakeIC*,\MakeFC,\MakeFC*
order=%<num1 num2 ...%>
transverse
no transverse
rows=%<number%>
columns=%<number%>
hsize=##L
vsize=##L
hgap=##L
vgap=##L
autogap inner
autogap total
no autogap
crosses
segments
lines
dots
no marks
segment length=##L
line thickness=##L
dot size=##L
crop color=#%color
#endkeyvals

\Transverse
\NoTransverse
\BCdim{h-size}{v-size}
\ICdim{h-size}{v-size}
\FCdim{h-size}{v-size}
\CardGap{h-gap}{v-gap}
\AutoGapInner
\AutoGapTotal
\NoAutoGap
\CropCrosses
\CropSegments
\CropLines
\CropDots
\NoCropMarks
\SegmentLength{length}
\LineThickness{thickness}
\DotSize{size}
\CropColor{color}

\PKGERROR{text}#S
\PKGWARNING{text}#S