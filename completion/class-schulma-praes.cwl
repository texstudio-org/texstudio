# schulma-praes class
# Matthew Bertucci 2/16/2022 for v1.2

#include:class-beamer
#include:etoolbox
#include:adjustbox
#include:babel
#include:isodate
#include:schulma
#include:schulma-physik
#include:tasks

#keyvals:\documentclass/schulma-praes#c
Seitenzahlen
Druck
Druck2
AT
# options passed to beamer
usepdftitle#true,false
envcountsect
notheorems
noamsthm
compress
t
c
leqno
fleqn
handout
trans
pdftex
nativepdf
pdfmark
dvips
dviwindo
dvipsone
vtex
ps2pdf
ignorenonframetext
noamssymb
bigger
smaller
8pt
9pt
10pt
11pt
12pt
14pt
17pt
20pt
draft
CJK
cjk
onlytextwidth
pgf={%<pgf options%>}
hyperref={%<hyperref options%>}
color={%<color options%>}
xcolor={%<xcolor options%>}
ucs
utf8x
utf8
aspectratio=#2013,1610,169,149,141,54,43,32,%<xxxx%>
#endkeyvals

#ifOption:druck
#include:pgfpages
#endif
#ifOption:druck2
#include:pgfpages
#endif

\Kurs{Kursbezeichnung%text}
\Datum{Datum}
\Thema{Thema%text}
\Thema[Nummer]{Thema%text}
dgruen#B
\schulmaalph{counter}#*
\Unterklammer{Formelteil}{Kommentar}#m
\Unterklammer<Folienspezifikaton>{Formelteil}{Kommentar}#m
\Produktregel{Foliennummer}{u'}{v}{u}{v'}#m

# from ngerman option of babel
\captionsngerman#*
\datengerman#*
\extrasngerman#*
\noextrasngerman#*
\dq
\ntosstrue#*
\ntossfalse#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
\mdqon#*
\mdqoff#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"A Ä
#repl:"E Ë
#repl:"I Ï
#repl:"O Ö
#repl:"U Ü
#repl:"s ß
#repl:"z ß
#repl:"S SS
#repl:"Z SZ
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#repl:"/ /
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »

#ifOption:AT
\captionsnaustrian#*
\datenaustrian#*
\extrasnaustrian#*
\noextrasnaustrian#*
#endif