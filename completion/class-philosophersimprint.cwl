# philosophersimprint class
# Matthew Bertucci 3/28/2022 for v1.5

#include:ifpdf
#include:color
#include:graphicx
#include:fancyhdr
#include:mathpazo
#include:courier
#include:helvet
#include:fontenc
# loads T1 option of fontenc
#include:textcomp
#include:microtype
#include:trajan
#include:flushend

#keyvals:\documentclass/philosophersimprint#c
titleimage
notitleimage
trajantitle
notrajantitle
nosc
noosf
slantedGreek
noBBpl
flushend
noflushend
# options passed to article class
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

\HUGE
\affiliation{affiliation}
\author[short names]{names}
\copyrightinfo{info%text}
\copyrightlicense{license}
\journalnumber{number}
\journalvolume{number}
\keywords{keyword1,keyword2,...%text}
\subject{subject%text}
\title[short title%text]{text}
\titleimage{imagefile}#g

# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n