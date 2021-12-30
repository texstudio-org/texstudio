# totpages package
# Matthew Bertucci 12/28/2021 for v2.00

#include:everyshi
#include:keyval

#keyvals:\usepackage/totpages#c
dvi
nodvi
pagespersheet=%<integer%>
nopagespersheet
#endkeyvals

\theTotPages
\TotPerSheet
\TotSheets

\ifTotPagesToDvi#*
\TotPagesToDvitrue#*
\TotPagesToDvifalse#*
\ifPagesPerSheet#*
\PagesPerSheettrue#*
\PagesPerSheetfalse#*