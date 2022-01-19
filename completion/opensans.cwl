# opensans package
# Matthew Bertucci 1/18/2022 for v2.2

#include:fontaxes
#include:ifluatex
#include:ifxetex
#include:xkeyval

#keyvals:\usepackage/opensans#c
scaled=%<factor%>
scale=%<factor%>
default
defaultsans
lining
oldstyle
tabular
proportional
type1
#endkeyvals

\opensans
\opensansfamily#*

# deprecated
\fosfamily#S