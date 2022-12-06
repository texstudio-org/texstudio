# simplenodes package
# Matthew Bertucci 4/4/2022

#include:kvoptions
#include:tikz
#include:tikzlibrarymath
#include:color

#keyvals:\usepackage/simplenodes#c
align=#left,flush left,right,flush right,center,flush center,justify
width=##L
minheight=##L
innersep=##L
outersep=##L
thickness=##L
#endkeyvals

\simplenode{name}{text}
\examplenode{name}{text}
\alertnode{name}{text}
\warnnode{name}{text}

\link{name1}{name2}

\gettikzxy{(x,y)}{xcmd%cmd}{ycmd%cmd}#*d
\mynode{draw color}{fill color}#*
\myline{anchor1}{anchor2}#*

InvisibleRed#B
InvisibleGreen#B
InvisibleBlue#B
InvisibleYellow#B
MediumRed#B
MediumGreen#B
MediumBlue#B
MediumYellow#B
