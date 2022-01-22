# nexus-otf package
# Matthew Bertucci 1/18/2022 for v0.02

#include:ifxetex
#include:ifluatex
#include:textcomp
#include:xkeyval
#include:unicode-math

#keyvals:\usepackage/nexus-otf#c
pro#true,false
math#true,false
lining#true,false
lf#true,false
oldstyle#true,false
osf#true,false
tabular#true,false
tf#true,false
proportional#true,false
pf#true,false
ScaleRM=%<factor%>
ScaleSF=%<factor%>
scale=%<factor%>
scaled=%<factor%>
#endkeyvals

\sufigures
\textsu{text}
\infigures
\textin{text}