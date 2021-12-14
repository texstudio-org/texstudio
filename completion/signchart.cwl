# signchart package
# Matthew Bertucci 12/12/2021 for v1.01

#include:tikz
#include:pgfplots
#include:xstring
#include:xkeyval

#keyvals:\usepackage/signchart#c
signunder
valunder
#endkeyvals

\signchart{values}{signs}
\signchart[options%keyvals]{values}{signs}

#keyvals:\signchart
height=##L
valanchor=%<anchor name%>
valsep=##L
width=##L
arrows=%<arrow style%>
#endkeyvals

\signHeightKey#*
\valNorthSouthKey#*
\valSepKey#*
\signChartWidth#*
\signHeight#*
\valNorthSouth#*
\valSep#*

\snht#S
\wid#S
\vals#S
\signs#S
\valsarray#S
\theArrow#S
\thisVal#S
\len#S
\k#S
\pos#S
\leftParti#S
\rightPart#S
\aLength#S
\cutAmount#S
\leftPartii#S
\valpos#S
\signpos#S
\s#S