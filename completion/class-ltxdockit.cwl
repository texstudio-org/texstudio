# ltxdockit class
# Matthew Bertucci 11/5/2021 for v1.2d

#include:etoolbox
#include:multicol
#include:keyval
#include:fontenc
#include:textcomp
#include:ltxdockit
#include:hyperref
#include:hypcap
#include:class-scrartcl,scrreprt,scrbook
#include:lmodern
#include:helvet
#include:charter

\fnurl{text}
\fnurl[prefix]{text}
\email{email}

\titlefont#*
\titlepage{options%keyvals}
#keyvals:\titlepage
title=
subtitle=
url=
author=
email=
revision=
date=
#endkeyvals
\printtitlepage

\rcsfile#*
\rcsrevision#*
\rcsdate#*
\rcstime#*
\rcsstate#*
\rcsauthor#*
\rcslocker#*
\rcstoday#*
\rcsid{arg}#*

\AtBeginToc#*
\AtEndToc#*
\AtBeginLot#*
\AtEndLot#*

\tex
\etex
\pdftex
\xetex
\luatex
\latex
\pdflatex
\xelatex
\lualatex
\bibtex
\lppl
\pdf
\utf
\ie
\eg

\tablesetup

\textln{text}