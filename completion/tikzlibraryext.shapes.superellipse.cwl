# ext.shapes.superellipse tikzlibrary
# 2022/12/09 for v0.4.2

#include:tikzlibraryshapes.geometric
#include:tikzlibraryintersections

#keyvals:\node#c,\coordinate#c,\nodepart#c,\pic#c
superellipse
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\node#c,\coordinate#c,\nodepart#c,\pic#c
superellipse x exponent=%<exponent%>
superellipse y exponent=%<exponent%>
superellipse step=%<integer%>
superellipse exponent=%<exponent%>
#endkeyvals

\pgfmathsuperellipsex{t}{2/m}{r_x}#*
\pgfmathsuperellipsey{t}{2/n}{r_y}#*
\pgfmathsuperellipseXY{t}{2/m}{2/n}{a}{b}#*