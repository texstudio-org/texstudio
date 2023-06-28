# endiagram package
# Matthew Bertucci 2022/04/29 for v0.1d

#include:l3keys2e
#include:siunitx
#include:tikz
#include:tikzlibrarycalc

\ENsetup{options%keyvals}
\ENsetup[module]{options%keyvals}

\begin{endiagram}#\pictureHighlight
\begin{endiagram}[options%keyvals]
\end{endiagram}

#keyvals:\ENsetup#c,\begin{endiagram}
unit=##L
scale=%<factor%>
offset=%<integer%>
r-offset=%<integer%>
l-offset=%<integer%>
axes=#xy,y,y-l,y-r,x,all,false
x-axis={%<TikZ keys%>}
y-axis={%<TikZ keys%>}
x-label=#below,right
y-label=#above,left
x-label-pos=%<value%>
y-label-pos=%<value%>
x-label-offset=##L
y-label-offset=##L
x-label-angle=%<degrees%>
y-label-angle=%<degrees%>
x-label-text=%<text%>
y-label-text=%<text%>
debug#true,false
draft#true,false
final#true,false
tikz={%<TikZ keys%>}
ticks=#y,y-l,y-r,none
ticks-step=%<number%>
energy-unit=%<unit%>
energy-step=%<number%>
energy-zero=%<number%>
energy-unit-separator=%<separator%>
energy-round=%<number%>
calculate#true,false
#endkeyvals

\ENcurve{level1,level2,level3,...}
\ENcurve[options%keyvals]{level1,level2,level3,...}

#keyvals:\ENcurve
step=%<integer%>
looseness=%<factor%>
minima#true,false
tikz={%<TikZ keys%>}
#endkeyvals

\ShowNiveaus
\ShowNiveaus[options%keyvals]

#keyvals:\ShowNiveaus
length=%<number%>
shift=%<number%>
tikz={%<TikZ keys%>}
niveau=%<id%>
#endkeyvals

\ShowGain
\ShowGain[options%keyvals]

#keyvals:\ShowGain
tikz={%<TikZ keys%>}
connect={%<TikZ keys%>}
connect-from-line#true,false
offset=%<number%>
label
label=%<text%>
label-side=#right,left
label-pos=%<value%>
label-tikz={%<TikZ keys%>}
#endkeyvals

\ShowEa
\ShowEa[options%keyvals]

#keyvals:\ShowEa
max=#first,all
from={(%<x1,y1%>) to (%<x2,y2%>)}
tikz={%<TikZ keys%>}
connect={%<TikZ keys%>}
label
label=%<text%>
label-side=#right,left
label-pos=%<value%>
label-tikz={%<TikZ keys%>}
#endkeyvals

\MakeOrigin

\AddAxisLabel{(%<point1%>)%<[label1];(point2);...%>}
\AddAxisLabel[%<options%>]{(%<point1%>)%<[label1];(point2);...%>}
\AddAxisLabel*{%<level1%>%<[label1];level2;...%>}
\AddAxisLabel*[%<options%>]{%<level1%>%<[label1];level2;...%>}

#keyvals:\AddAxisLabel,\AddAxisLabel*
axis=#y-l,y-r,x
connect={%<TikZ keys%>}
font=%<font commands%>
#endkeyvals
