# basque-book class
# Matthew Bertucci 2022/06/05 for v1.20

#include:basque-date

#keyvals:\documentclass/basque-book#c
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
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

\frontmatter#n
\mainmatter#n
\backmatter#n
\thechapter#*
\chaptername#n
\bibname#n
\captionwidth{width}
\chapter{title}#L1
\chapter*{title}#L1
\chapter[short title]{title}#L1
\chaptermark{code}#*