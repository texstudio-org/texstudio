# tlc-article class
# Matthew Bertucci 1/29/2022 for v1.0.17

#include:geometry
#include:multicol
#include:lmodern
#include:fontenc
# fontenc loaded with T1 option
#include:textcomp
#include:inputenc
#include:hyperref
#include:bookmark
#include:glossaries
# glossaries loaded with acronym option
#include:graphicx
#include:xcolor
# xcolor loaded with table option
#include:listings
#include:spverbatim
#include:array
#include:csvsimple
#include:enumitem
#include:longtable
#include:makecell
#include:tabularx
#include:pdflscape
#include:pdfpages
#include:appendix
#include:todonotes
#include:tocloft
#include:fancyhdr
#include:titling
#include:lastpage

#keyvals:\documentclass/tlc-article#c
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
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

darkblue#B
codegreen#B
codegray#B
codepurple#B
backcolour#B

\tlcDarkblue{text}
\tlcBeginLandscape
\tlcEndLandscape
\tlcVersionPart{column}
\ER#t
\tlcVspace
\inputIfExists{file}#i
\tlcTitlePageAndTableOfContents{title%text}{author%text}{abstract%text}
\tlcIsDefined{file}
\tlcDebug

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

# from acronym option of glossaries
\printacronyms
\printacronyms[options%keyvals]

# from table option of xcolor
#include:colortbl
