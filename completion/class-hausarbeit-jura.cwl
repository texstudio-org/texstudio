# hausarbeit-jura class
# Matthew Bertucci 2022/09/07 for v2.0

#include:ifthen
#include:iftex
#include:class-jurabook
#include:inputenc
#include:fontenc
# loads T1 option of fontenc
#include:tgtermes
#include:tgheros
#include:tgcursor
#include:textcomp
#include:eurosym
#include:babel
# loads ngerman option of babel
#include:indentfirst
#include:geometry
#include:ellipsis
#include:csquotes
#include:microtype
#include:jurabib

#keyvals:\documentclass/hausarbeit-jura#c
american
british
english
latin1
utf8
ansinew
applemac
centerpagenumber
texgyre
oldfonts
nosuperscriptedition
varioref
headline
headlinetitlepageleft
noautomatter
automatter
# options passed to jurabook
allowhyphens
indexpagenumbers
norunners
rnrefbold
oldfootnotes
fncontinued
showpagenumber
suppresswebdates
longfnrule
classiclayout
centeredpartsintoc
centeredlayout
screenmode
compact
decisionhints
overviewwithsec
seminar
chapterprefix
chaptersuffix
fixtocindent
maketime
ruwtitle
# options passed to book class
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
openright
openany
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

#ifOption:varioref
#include:varioref
#endif

\author[Kurzautor]{Autor}
\matrikelnummer{Matrikelnummer}
\prof{Betreuer}
\sectionafter#*
\sectionbefore#*
\semester[Fachsemester]{Semesterangabe}
\semester{Semesterangabe}
\setpg{Maße}#*
\setpgfront{Maße für Vorspann}
\setpgmain{Maße für Hauptteil}
\setspaceafterchapter{length}
\setspaceaftersection{length}
\setspacebeforechapter{length}
\setspacebeforesection{length}

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

# from ngerman option of babel
\captionsngerman
\datengerman
\extrasngerman
\noextrasngerman
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