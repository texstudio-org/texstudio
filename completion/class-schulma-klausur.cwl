# schulma-klausur class
# Matthew Bertucci 202303/15 for v1.4

#include:etoolbox
#include:schulma
#include:schulma-physik
#include:class-scrartcl
#include:scrlayer-scrpage
#include:pdfpages
#include:geometry
#include:comment
#include:beamerarticle
#include:tasks
#include:adjustbox
#include:babel
#include:datetime2

#keyvals:\documentclass/schulma-klausur#c
SLK
p-q-Formel
Differenzenquotient
Differentialquotient
A5quer
AT
GruppeA
GruppeB
Musterloesung
# other options passed to scrartcl
#endkeyvals

#ifOption:Musterloesung
#include:class-schulma-praes
#keyvals:\documentclass/schulma-klausur#c
Seitenzahlen
Druck
Druck2
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
#endif

#ifOption:druck
#include:pgfpages
#endif
#ifOption:druck2
#include:pgfpages
#endif

\Nr{Nummer}
\theAufgabe#*
\theTeilaufgabe#*
\Aufgabenabstand#*
\Teilaufgabenabstand#*
\Kurs{Kursbezeichnung%text}
\Datum{Datum}
\begin{Teilaufgaben}
\end{Teilaufgaben}
\Aufgabe
\Aufgabe[Thema%text]#*
\Aufgabe[Thema%text][Bearbeitungszeit]#*
\Aufgabe(Punktzahl)#*
\Aufgabe[Thema%text](Punktzahl)
\Aufgabe[Thema%text][Bearbeitungszeit](Punktzahl)
\Aufgabe*
\Aufgabe*[Thema%text]#*
\Aufgabe*[Thema%text][Bearbeitungszeit]#*
\Aufgabe*(Punktzahl)#*
\Aufgabe*[Thema%text](Punktzahl)
\Aufgabe*[Thema%text][Bearbeitungszeit](Punktzahl)
\begin{Lsg}
\begin{Lsg}*
\end{Lsg}
\schulmaalph{counter}#*
\Klausurtitel{Titel%text}
\Klausuruntertitel{Untertitel%text}
\Klausurteiltitel{Teiltitel%text}
\Bearbeitungszeit{Zeit in Minuten}
\Hilfsmittel{Hilfsmittel%text}
\Loesungsdatum{Datum}
\Formeldokument{Seitenzahlen}
\Gruppen{Text für GruppeA%text}{Text für GruppeB%text}
\Gruppen*{Text für GruppeA%text}{Text für GruppeB%text}
\Aufgabentitel{Bezeichnung%text}
\Notenspiegel{kommaseparierte Notenliste}
\Notenpunktspiegel{kommaseparierte Notenliste}
\FarbeAufgabe
\FarbeLoesung
\NurAufgabe{Teil der Aufgabe}
\NurLoesung{Teil der Aufgabe}

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
