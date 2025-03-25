# ext.shapes.superellipse tikzlibrary
# 2025/03/19 for v0.6

#include:tikzlibraryshapes.geometric
#include:tikzlibraryintersections

#keyvals:\node#c,\coordinate#c,\nodepart#c,\pic#c
ext_superellipse
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\node#c,\coordinate#c,\nodepart#c,\pic#c
ext/superellipse x exponent=%<exponent%>
ext/superellipse y exponent=%<exponent%>
ext/superellipse step=%<integer%>
ext/superellipse exponent=%<exponent%>
#endkeyvals

\pgfmathsuperellipsex{t}{2/m}{r_x}#*
\pgfmathsuperellipsey{t}{2/n}{r_y}#*
\pgfmathsuperellipseXY{t}{2/m}{2/n}{a}{b}#*

# from tikzext-util.tex
\tikzextversion#S
\tikzextversionnumber#S
\tikzextset{options%keyvals}
\pgfextset{options%keyvals}
