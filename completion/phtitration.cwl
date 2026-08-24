# phtitration package
# Matthew Bertucci 2026/08/19 for v1.0.0
# from author-provided cwl

#include:tikz
#include:pgfplots
#include:xstring
#include:etoolbox
#include:tikzlibrarycalc
#include:tikzlibrarydecorations.markings

\phtitration
\phtitration[options%keyvals]

#keyvals:\phtitration
type=#strong-acid,weak-acid,diprotic-acid,triprotic-acid,strong-base,weak-base,dibase,tribase
Ca=
Va=
Cb=
Vb=
pKa=
pKa1=
pKa2=
pKa3=
pKb=
pKb1=
pKb2=
pKb3=
show-equivalence#true,false
show-half-equivalence#true,false
show-tangents#true,false
show-coordinates#true,false
tangent-slope=##L
tangent-distance=##L
tangent-length=##L
tangent-xshift=##L
curve-color=#%color
curve-style=#thick,very thick,ultra thick,ultra thin,very thin,thin,semithick
tangent-color=#%color
tangent-style=#thick,very thick,ultra thick,ultra thin,very thin,thin,semithick
eq-color=#%color
eq-mark=
eq-size=##L
eq-label-pos=#above,below,left,right,above left,above right,below left,below right
font-style=%<font commands%>
#endkeyvals