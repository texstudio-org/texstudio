# papermas package
# Matthew Bertucci 11/29/2021 for v1.0h

#include:kvoptions
#include:pageslts
#include:intcalc

#keyvals:\usepackage/papermas#c
format=
masss=%<amount in g/m^2%>
pagespersheet=%<integer%>
decimalsep={%<char%>}
#endkeyvals

\unit{unit}
\papermasstotal
\papermasformat
\papermasmasss
\papermaspagespersheet
\papermassheets