# droidserif package
# Matthew Bertucci 7/27/2021

#include:ifluatex
#include:ifxetex
#include:xkeyval

#keyvals:\usepackage/droidserif#c
scale=%<factor%>
scaled=%<factor%>
default
type1
#endkeyvals

\droidserif
\droidseriffamily#*

# deprecated
\fdrfamily#S
