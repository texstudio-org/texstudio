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
#include:class-scrartcl
#include:lmodern
#include:helvet
#include:charter

\fnurl{URL}#U
\fnurl[prefix]{URL}#U
\email{email%URL}#U

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

# from T1 option of fontenc
\DH#n
\NG#n
\dj#n
\ng#n
\k{arg}#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\quotedblbase#n
\quotesinglbase#n
\textquotedbl#n
\DJ#n
\th#n
\TH#n
\dh#n
\Hwithstroke#*n
\hwithstroke#*n
\textogonekcentered{arg}#*n
\guillemetleft#n
\guillemetright#n
