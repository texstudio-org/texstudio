# hrefhide package
# Matthew Bertucci 2025/01/30 for v1.1b

#include:xcolor
#include:hyperref

#keyvals:\usepackage/hrefhide#c
linktextcolour=#%color
backgroundcolour=#%color
pdfborder={%<a b c%>}
#endkeyvals

\hrefdisplayonly{URL}{text%plain}#U
\hycon
\hycoff

hyanchorbordercolor#B
hycitebordercolor#B
hyfilebordercolor#B
hylinkbordercolor#B
hymenubordercolor#B
hyrunbordercolor#B
hyurlbordercolor#B

\ifhrefhide#S
\hrefhidetrue#S
\hrefhidefalse#S
