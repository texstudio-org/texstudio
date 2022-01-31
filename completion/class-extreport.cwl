# extreport class
# Matthew Bertucci 1/18/2021 for v1.0

#include:exscale

#keyvals:\documentclass/extreport#c
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
8pt
9pt
10pt
11pt
12pt
14pt
17pt
20pt
oneside
twoside
draft
final
titlepage
notitlepage
openright
openany
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

\thechapter#*
\chaptername#n
\bibname#n
\chapter{title}#L1
\chapter*{title}#L1
\chapter[short title]{title}#L1
\chaptermark{code}