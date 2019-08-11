# mode: yathesis.cls
# denisbitouze, 30.10.2016
#
#include:class-book
#include:latex-document
#include:latex-mathsymbols
#include:tex
#include:pgfopts
#include:etoolbox
#include:xpatch
#include:morewrites%
#include:filehook
#include:hopatch
#include:xifthen
#include:xkeyval%
#include:geometry
#include:graphicx
#include:environ
#include:adjustbox
#include:array
#include:xstring
#include:textcase
#include:translator
#include:iftex
#include:epigraph
#include:tcolorbox
#include:marvosym
#include:setspace
#include:etoc
#include:tocbibind
#include:nonumonpart
#include:xcolor
#include:datatool
#include:fncychap
#include:titleps
#include:ifdraft
#include:draftwatermark
#include:babel
#include:iflang
#include:datetime
#include:hypcap
#include:bookmark
#include:glossaries-babel
#
# Document class
#keyvals:\documentclass/yathesis
mainlanguage=#french,english
secnumdepth=#part,chapter,section,subsection,subsubsection,paragraph,subparagraph
space=#single,onehalf,double
chap-style=#Sonny,Lenny,Glenn,Conny,Rejne,Bjarne,PetersLenny,Bjornstrup,none
nofrontcover#true,false
sepcorpaffilfrench=
sepcorpaffilenglish=
version=#inprogress,inprogress*,submitted,submitted*,final,draft
output=#screen,paper,paper*
localtocs
localtocs/depth=#section,subsection,subsubsection,paragraph,subparagraph
localbibs
localbibs*
10pt
11pt
12pt
leqno
fleqn
oneside
noerror
noauthor
notitle
noacademicfield
nodate
noinstitute
nodoctoralschool
nolaboratory
nolaboratoryadress
nosupervisor
nomaketitle
nokeywords
noabstract
nomakeabstract
notableofcontents
noprintbibliography
graphicx
adjustbox
setspace
xcolor
datatool
titleps
draftwatermark
babel
datetime
#endkeyvals
#
\yadsetup{%<options%>}#n
#
# Cover and title pages
#
# Author
\author{%<prénom%>}{%<nom%>}#n
\author[%<email%>]{%<prénom%>}{%<nom%>}#n
#
# Title, etc.
\title[titre dans la langue secondaire%text]{titre dans la langue principale%text}#n
\subtitle[sous-titre dans la langue secondaire%text]{sous-titre dans la langue principale%text}#n
\academicfield[discipline dans la langue secondaire%text]{discipline dans la langue principale%text}#n
\speciality[spécialité dans la langue secondaire%text]{spécialité dans la langue principale%text}#n
\subject[sujet dans la langue secondaire%text]{sujet dans la langue principale%text}#n
#
\title{titre%text}#n
\subtitle{sous-titre%text}#n
\academicfield{discipline%text}#n
\speciality{spécialité%text}#n
\subject{sujet%text}#n
\date{%<jour%>}{%<mois%>}{%<année%>}#n
\submissiondate{%<jour%>}{%<mois%>}{%<année%>}#n
#
# Institute and entities
\pres{%<nom du PRES%>}#n
\comue{%<nom de la ComUE%>}#n
\institute{nom de l'institut%text}#n
\coinstitute{nom de l'institut de cotutelle%text}#n
\company{%<nom de l'entreprise%>}#n
\doctoralschool{nom de l'école doctorale%text}#n
\laboratory{%<nom du laboratoire%>}{%<adresse du laboratoire%>}#n
#
\pres[%<précision(s)%>]{%<nom du PRES%>}#n
\comue[%<précision(s)%>]{%<nom de la ComUE%>}#n
\institute[%<précision(s)%>]{nom de l'institut%text}#n
\coinstitute[%<précision(s)%>]{nom de l'institut de cotutelle%text}#n
\company[%<précision(s)%>]{%<nom de l'entreprise%>}#n
\doctoralschool[%<précision(s)%>]{nom de l'école doctorale%text}#n
\laboratory[%<précision(s)%>]{%<nom du laboratoire%>}{%<adresse du laboratoire%>}#n
#
#keyvals:\pres
logo=
logoheight=
url=
#endkeyvals
#keyvals:\comue
logo=
logoheight=
url=
#endkeyvals
#keyvals:\institute
logo=
logoheight=
url=
#endkeyvals
#keyvals:\coinstitute
logo=
logoheight=
url=
#endkeyvals
#keyvals:\company
logo=
logoheight=
url=
#endkeyvals
#keyvals:\doctoralschool
logo=
logoheight=
url=
#endkeyvals
#keyvals:\laboratory
logo=
logoheight=
url=
telephone=
fax=
email=
nonamelink
#endkeyvals
#
# Committee
\supervisor{%<prénom%>}{%<nom%>}#n
\cosupervisor{%<prénom%>}{%<nom%>}#n
\comonitor{%<prénom%>}{%<nom%>}#n
\referee{%<prénom%>}{%<nom%>}#n
\examiner{%<prénom%>}{%<nom%>}#n
\committeepresident{%<prénom%>}{%<nom%>}#n
\guest{%<prénom%>}{%<nom%>}#n
#
\supervisor[%<précision(s)%>]{%<prénom%>}{%<nom%>}#n
\cosupervisor[%<précision(s)%>]{%<prénom%>}{%<nom%>}#n
\comonitor[%<précision(s)%>]{%<prénom%>}{%<nom%>}#n
\referee[%<précision(s)%>]{%<prénom%>}{%<nom%>}#n
\examiner[%<précision(s)%>]{%<prénom%>}{%<nom%>}#n
\committeepresident[%<précision(s)%>]{%<prénom%>}{%<nom%>}#n
\guest[%<précision(s)%>]{%<prénom%>}{%<nom%>}#n
#
#keyvals:\supervisor
affiliation=
professor
seniorresearcher
mcf
mcf*
associateprofessor
associateprofessor*
juniorresearcher
juniorresearcher*
#endkeyvals
#keyvals:\cosupervisor
affiliation=
professor
seniorresearcher
mcf
mcf*
associateprofessor
associateprofessor*
juniorresearcher
juniorresearcher*
#endkeyvals
#keyvals:\comonitor
affiliation=
professor
seniorresearcher
mcf
mcf*
associateprofessor
associateprofessor*
juniorresearcher
juniorresearcher*
#endkeyvals
#keyvals:\referee
affiliation=
professor
seniorresearcher
mcf
mcf*
associateprofessor
associateprofessor*
juniorresearcher
juniorresearcher*
#endkeyvals
#keyvals:\examiner
affiliation=
professor
seniorresearcher
mcf
mcf*
associateprofessor
associateprofessor*
juniorresearcher
juniorresearcher*
#endkeyvals
#keyvals:\committeepresident
affiliation=
professor
seniorresearcher
mcf
mcf*
associateprofessor
associateprofessor*
juniorresearcher
juniorresearcher*
#endkeyvals
#keyvals:\guest
affiliation=
professor
seniorresearcher
mcf
mcf*
associateprofessor
associateprofessor*
juniorresearcher
juniorresearcher*
#endkeyvals
#
# Misc
\ordernumber[%<numéro d'ordre%>]#n
\ordernumber#n*
#
# Preliminary part
#
\disclaimer{clause%text}#n
\makedisclaimer#n
\makedisclaimer*#n
\keywords{mots clés dans la langue principale%text}{mots clés dans la langue secondaire%text}#n
\makekeywords#n
\makekeywords*#n
\makelaboratory#n
\makelaboratory*#n
\dedication{dédicace%text}#n
\makededications#n
\makededications*#n
\frontepigraph{épigraphe%text}{%<auteur%>}
\frontepigraph[%<langue%>]{épigraphe%text}{%<auteur%>}
#keyvals:\frontepigraph
afrikaans
bahasa
basque
breton
bulgarian
catalan
croatian
czech
danish
dutch
english
esperanto
estonian
finnish
french
galician
ngerman
greek
hebrew
hungarian
icelandic
interlingua
irish
italian
latin
lowersorbian
samin
norsk
polish
portuguese
romanian
russian
scottish
spanish
slovak
slovene
swedish
serbian
turkish
ukrainian
uppersorbian
welsh
#endkeyvals
\makefrontepigraphs#n
\makefrontepigraphs*#n
\begin{abstract}#n
\begin{abstract}[intitulé alternatif%text]#n*
\end{abstract}#n
\makeabstract#n
\newglssymbol{%<label%>}{%<symbole%>}{%<nom%>}{description%text}#n
\newglssymbol[%<classement%>]{%<label%>}{%<symbole%>}{%<nom%>}{description%text}#n
\tableofcontents#n*
\tableofcontents[%<précision(s)%>]#n*
#
#keyvals:\tableofcontents
depth=#part,chapter,section,subsection,subsubsection,paragraph,subparagraph
name=
#endkeyvals
#
# Main part
#
\chapter{titre%title}#L1
\chapter*{titre%title}#L1
\chapter[titre alt. pour TdM et entête%short title]{titre%title}#L1
\chapter*[titre alt. pour TdM et entête%short title]{titre%title}#L1
\chapter[titre alt. pour TdM%short title][titre alt. pour entête%short title]{titre%title}#L1
\chapter*[titre alt. pour TdM%short title][titre alt. pour entête%short title]{titre%title}#L1
\section{titre%title}#L2
\section*{titre%title}#L2
\section[titre alt. pour TdM et entête%short title]{titre%title}#L2
\section*[titre alt. pour TdM et entête%short title]{titre%title}#L2
\section[titre alt. pour TdM%short title][titre alt. pour entête%short title]{titre%title}#L2
\section*[titre alt. pour TdM%short title][titre alt. pour entête%short title]{titre%title}#L2
\subsection{titre%title}#L3
\subsection*{titre%title}#L3
\subsection[titre alt. pour TdM et entête%short title]{titre%title}#L3
\subsection*[titre alt. pour TdM et entête%short title]{titre%title}#L3
\subsubsection{titre%title}#L4
\subsubsection*{titre%title}#L4
\subsubsection[titre alt. pour TdM et entête%short title]{titre%title}#L4
\subsubsection*[titre alt. pour TdM et entête%short title]{titre%title}#L4
\paragraph{titre%title}#L5
\paragraph*{titre%title}#L5
\paragraph[titre alt. pour TdM et entête%short title]{titre%title}#L5
\paragraph*[titre alt. pour TdM et entête%short title]{titre%title}#L5
\subparagraph{titre%title}#L6
\subparagraph[titre alt. pour TdM et entête%short title]{titre%title}#L6
#
# Appendix part
#
# Back matter part
#
\makebackcover
#
# All parts
#
\startlocaltocs
\stoplocaltocs
\nextwithlocaltoc
\nextwithoutlocaltoc
#
# Customization
#
\expression{%<label%>}{valeur (en français)%text}{valeur (en anglais)%text}#n*
