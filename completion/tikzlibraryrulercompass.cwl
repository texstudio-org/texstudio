# rulercompass tikzlibrary
# 2022/12/06 for v1

#include:intersections
#include:calc

\thepointlabels#*

\point{path1}{path2}{intersection}
\point[styles]{path1}{path2}{intersection}
\ruler{point1}{point2}
\ruler[styles]{point1}{point2}
\compass{point1}{point2}
\compass[styles]{point1}{point2}

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
stop jumping
max size={%<width%>}{%<height%>}
enclosing box/offset=##L
constrain
#endkeyvals

\constrain