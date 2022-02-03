# ncc class
# Matthew Bertucci 2/3/2022 for v1.10

#include:dcounter
#include:makeidx
#include:nccbiblist
#include:nccheadings
#include:ncclatex
#include:nccold
#include:ncctitlepage
#include:tocenter
#include:topsection
#include:watermark

#keyvals:\documentclass/ncc#c
a4paper
a5paper
a5a4paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
fittopage
10pt
11pt
12pt
14pt
oneside
twoside
draft
final
openany
openright
onecolumn
twocolumn
openbib
article
preprint
book
report
centertags
#endkeyvals

#ifOption:article
\setseries{series%text}
\theseries#*
\setvolume{volume%text}
\thevolume#*
\setissue{issue%text}
\theissue#*
#endif

#ifOption:preprint
#include:ncctitle
#include:afterpackage
\preprintname#*
\preprint{number}
\thepreprint#*
#endif

#ifOption:book
#include:ncctitle
\bookeditor{text}
#endif

#ifOption:report
#include:ncctitle
\bookeditor{text}
#endif

\AuthorBeforeTitle
\TitleBeforeAuthor
\begin{alloweqbreak}#*
\end{alloweqbreak}#*
\alloweqbreak
\begin{noeqbreak}#*
\end{noeqbreak}#*
\noeqbreak
\begin{theglossary}
\end{theglossary}
\bibname#*
\chapter{title}#L1
\chapter[short title]{title}#L1
\chapter*{title}#L1
\thechapter#*
\chaptername#*
\glossaryname#*
\mit#*m
\prefacename#*
\printglossary
\setyear{year}
\theyear#*
\openrightorany
