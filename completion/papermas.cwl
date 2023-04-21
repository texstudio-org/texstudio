# papermas package
# Matthew Bertucci 2023/04/12 for v1.1a

#include:kvoptions
#include:intcalc

#keyvals:\usepackage/papermas#c
format=
masss=%<amount in g/m^2%>
pagespersheet=%<integer%>
decimalsep={%<char%>}
#endkeyvals

\papermassPages
\papermasstotal
\papermasformat
\papermasmasss
\papermaspagespersheet
\papermassheets

\thepapermasmasss#S
\thepapermasPPS#S
\thepapermassttl#S
\thepapermassSpace#S
