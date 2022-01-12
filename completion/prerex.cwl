# prerex package
# Matthew Bertucci 1/11/2022

#include:relsize
#include:calc
#include:pgf
#include:tikz
# loads arrows.meta tikzlibrary
#include:textcomp
#include:hyperref
#include:xcolor

\begin{chart}
\end{chart}

\halfcourse %<x%>,%<y%>:{%<code%>}{%<title%>}{%<timetable%>}
\reqhalfcourse %<x%>,%<y%>:{%<code%>}{%<title%>}{%<timetable%>}
\opthalfcourse %<x%>,%<y%>:{%<code%>}{%<title%>}{%<timetable%>}
\fullcourse %<x%>,%<y%>:{%<code%>}{%<title%>}{%<timetable%>}
\reqfullcourse %<x%>,%<y%>:{%<code%>}{%<title%>}{%<timetable%>}
\optfullcourse %<x%>,%<y%>:{%<code%>}{%<title%>}{%<timetable%>}

\halfcoursec %<x%>,%<y%>:{%<code%>}{%<title%>}{%<timetable%>}{%<color%>}
\reqhalfcoursec %<x%>,%<y%>:{%<code%>}{%<title%>}{%<timetable%>}{%<color%>}
\opthalfcoursec %<x%>,%<y%>:{%<code%>}{%<title%>}{%<timetable%>}{%<color%>}
\fullcoursec %<x%>,%<y%>:{%<code%>}{%<title%>}{%<timetable%>}{%<color%>}
\reqfullcoursec %<x%>,%<y%>:{%<code%>}{%<title%>}{%<timetable%>}{%<color%>}
\optfullcoursec %<x%>,%<y%>:{%<code%>}{%<title%>}{%<timetable%>}{%<color%>}

\mini %<x%>,%<y%>:{%<code%>}
\text %<x%>,%<y%>:{%<text%>}

\prereq %<x0%>,%<y0%>,%<x1%>,%<y1%>:
\coreq %<x0%>,%<y0%>,%<x1%>,%<y1%>:
\recomm %<x0%>,%<y0%>,%<x1%>,%<y1%>:

\prereqc %<x0%>,%<y0%>,%<x1%>,%<y1%>;%<c%>:
\coreqc %<x0%>,%<y0%>,%<x1%>,%<y1%>;%<c%>:
\recommc %<x0%>,%<y0%>,%<x1%>,%<y1%>;%<c%>:

\grid

\solidarrow
\dottedarrow
\dashedarrow
\lightbox
\boldbox
\dottedbox

\unit#*
\DefaultCurvature#*
\CourseURL{arg1}{arg2}{URL}#*U
\background#*
\dpi#*
\PixelsPerUnit#*
\thediagheight#*
\solidwidth#*
\boldwidth#*
\dottedwidth#*
\dashedwidth#*
\smallersize#*
\baselineAdj#*
\ifgridon#*
\gridonfalse#*
\gridontrue#*

light#B
somewhatlight#B
verylight#B