# jurabook class
# Matthew Bertucci 2022/09/07 for v0.91 (beta)

#include:jurabase
#include:remreset
#include:fancyhdr
#include:multicol
#include:class-book
#include:ifpdf

#keyvals:\documentclass/jurabook#c
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

#ifOption:allowhyphens
#include:ragged2e
#endif

#ifOption:ruwtitle
\titlepublisherbox#*
#endif

\begin{decisionlist}
\end{decisionlist}

\addextrawebcite{URL}#U
\bibtotoc
\birthplace{geburtsort}
\changestarchapters
\chapterlevel
\citeweb[abrufdatum]{URL}{beschreibung%text}#U
\citeweb{URL}{beschreibung%text}#U
\citewebx[abrufdatum]{urldef}{beschreibung%text}
\citewebx{urldef}{beschreibung%text}
\dcs*{gericht}{fundstelle}{stichwort}
\dcs{gericht}{fundstelle}{stichwort}
\decision*[nichtrechtskraeftig]{gericht}{fundstelle}{stichwort}{entschdatum}{az}{extra}{vermerk}
\decision*{gericht}{fundstelle}{stichwort}{entschdatum}{az}{extra}{vermerk}
\decision[nichtrechtskraeftig]{gericht}{fundstelle}{stichwort}{entschdatum}{az}{extra}{vermerk}
\decision{gericht}{fundstelle}{stichwort}{entschdatum}{az}{extra}{vermerk}
\decree*{gericht}{fundstelle}{stichwort}{datum}{az}{extra}{anmerkung}
\decree{gericht}{fundstelle}{stichwort}{datum}{az}{extra}{anmerkung}
\dumpoptions
\dumpoptions[ausgabe]
\examdate{datum}
\FIndex{text}
\findex{text}
\firstexaminer{name}
\hnewline
\ifjpdf
\Index{text}
\leveldown
\levelup
\lonelyappendixchapter[short title]{title}#L1
\lonelyappendixchapter{title}#L1
\longpage
\longpage[size]
\MIndex{text}
\newcourt
\nomencltotoc
\notyet[nichtrechtskraeftig]{gericht}{fundstelle}{stichwort}{entschdatum}{az}{extra}{vermerk}
\notyet{gericht}{fundstelle}{stichwort}{entschdatum}{az}{extra}{vermerk}
\officialtitle{kuerzel%keyvals}
\onehalfspacing
\onespacing
\overview
\publishinfo{pubvermerk%text}
\publishplace{ort}
\publishyear{jahr}
\resetstarchapters
\rn[label]{ersteswort}#l
\rn{ersteswort}
\rnref{label}#r
\rnreff{label}#r
\rnrefff{label}#r
\secondexaminer{name}
\setchaptername[trennz]{name}
\setchaptername{name}
\setjbooklength{element%keyvals}{neuelaenge}
\setjbookstyle{element%keyvals}{neuerstil}
\setjbooktext{element%keyvals}{neuertext}
\shortindexingoff
\shortindexingon
\shortpage
\shortpage[size]
\sub[short title]{title}
\sub{title}
\subauthor{zusatztext}
\subeightsection*{title}
\subeightsection[short title]{title}
\subeightsection{title}
\subfivesection*{title}#L7
\subfivesection[short title]{title}#L7
\subfivesection{title}#L7
\subfoursection*{title}#L6
\subfoursection[short title]{title}#L6
\subfoursection{title}#L6
\subsevensection*{title}#L9
\subsevensection[short title]{title}#L9
\subsevensection{title}#L9
\subsixsection*{title}#L8
\subsixsection[short title]{title}#L8
\subsixsection{title}#L8
\subsubsubsection*{title}#*L5
\subsubsubsection[short title]{title}#*L5
\subsubsubsection{title}#*L5
\subsubsubsubsection*{title}#*L6
\subsubsubsubsection[short title]{title}#*L6
\subsubsubsubsection{title}#*L6
\subthreesection*{title}#L5
\subthreesection[short title]{title}#L5
\subthreesection{title}#L5
\subtitle{untertitel%text}
\tableofwebcites
\toc[short title]{title}
\toc{title}
\TODO{hinweistext%text}
\xref{label}#r

#keyvals:\officialtitle
goe
trier
stgallen
#endkeyvals

#keyvals:\setjbookstyle
officialtitle
title
subtitle
author
titledate
publishinfo
publishplace
thanks
from
subauthor
maketime
partintro
part
chapter
tocextras
indexprologue
indextext
lowprologue
lowtext
decisionprologue
decisionemph
decisiontext
#endkeyvals

#keyvals:\setjbooklength
runnersspace
proofmodetextwidth
proofmodeleftmargin
defaulttocindent
chapterbefore
chapterafter
#endkeyvals

#keyvals:\setjbooktext
maketime
maketimename
rn
page
overview
indexprologue
cwrevisionopen
cwrevision
cwrevisionclose
lowprologue
lowname
decisionsep
decisionlist
notfinal
decisionprologue
decision
decree
decisionfrom
#endkeyvals

# not documented
\appendixchapter#*
\autornref{arg}#S
\chapterextra#*
\chapternumwidth#*
\chapterstartspace#*
\combinemarks#*
\decisionentry{arg1}{arg2}#S
\dnrefname#*
\extrarn[label]{Erstes}#*l
\extrarn{Erstes}#*
\findexproofmode#*
\firstexaminername#*
\fnlabelwidth#S
\fnmarksep#S
\fussnote{text}#S
\ifjscreen#S
\jpdffalse#S
\jpdftrue#S
\jscreenfalse#S
\jscreentrue#S
\jurabookdate#S
\jurabookversion#S
\lowcontentsline{URL}{arg2}{arg3}#*U
\lowcontentslinex{urldef}{arg2}{arg3}#*
\newindexletter{arg}#*
\paragraphtocindent#*
\secondexaminername#*
\sectionnumwidth#*
\sectiontocindent#*
\seealso{arg1}{arg2}#*
\SetJuboPagestyle#*
\subeightsectionmark{code}#S
\subeightsectionnumwidth#*
\subeightsectiontocindent#*
\subfivesectionmark{code}#S
\subfivesectionnumwidth#*
\subfivesectiontocindent#*
\subfoursectionmark{code}#S
\subfoursectionnumwidth#*
\subfoursectiontocindent#*
\subparagraphtocindent#*
\subsectionnumwidth#*
\subsectiontocindent#*
\subsevensectionmark{code}#S
\subsevensectionnumwidth#*
\subsevensectiontocindent#*
\subsixsectionmark{code}#S
\subsixsectionnumwidth#*
\subsixsectiontocindent#*
\subsubsectionnumwidth#*
\subsubsectiontocindent#*
\subsubsubsubsubsection*{title}#SL7
\subsubsubsubsubsection[short title]{title}#SL7
\subsubsubsubsubsection{title}#SL7
\subsubsubsubsubsubsection*{title}#SL8
\subsubsubsubsubsubsection[short title]{title}#SL8
\subsubsubsubsubsubsection{title}#SL8
\subsubsubsubsubsubsubsection*{title}#SL9
\subsubsubsubsubsubsubsection[short title]{title}#SL9
\subsubsubsubsubsubsubsection{title}#SL9
\subsubsubsubsubsubsubsubsection*{title}#S
\subsubsubsubsubsubsubsubsection[short title]{title}#S
\subsubsubsubsubsubsubsubsection{title}#S
\subthreesectionmark{code}#S
\subthreesectionnumwidth#*
\subthreesectiontocindent#*
\theextrarunner#*
\therealchapters#*
\therunner#*
\thesubeightsection#*
\thesubfivesection#*
\thesubfoursection#*
\thesubsevensection#*
\thesubsixsection#*
\thesubthreesection#*
\thetotaldcs#*
\thetotaldecisions#*
\thetotalfootnotes#*
\thetotalnotyets#*
\thetotalsections#*
\thetotalwebcites#*
\uprefname#*