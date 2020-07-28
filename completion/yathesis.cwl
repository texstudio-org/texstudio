# mode: yathesis.cls
# denisbitouze, 2020-04-05
#
#include:adjustbox
#include:array
#include:babel
#include:biblatex
#include:bookmark
#include:colophon
#include:csquotes
#include:datatool
#include:datetime
#include:draftwatermark
#include:environ
#include:epigraph
#include:etoc
#include:etoolbox
#include:filehook
#include:fncychap
#include:geometry
#include:graphicx
#include:hopatch
#include:hypcap
#include:ifdraft
#include:iflang
#include:iftex
#include:letltxmacro
#include:marvosym
#include:morewrites
#include:nonumonpart
#include:pgfopts
#include:setspace
#include:tcolorbox
#include:textcase
#include:titleps
#include:tocbibind
#include:translator
#include:twoopt
#include:xcolor
#include:xifthen
#include:xkeyval
#include:xpatch
#include:xstring
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
colophon=#verso-frontcover,recto-backcover,nowhere
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
nolaboratoryaddress
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
\author{prénom}{nom}#n
\author[email]{prénom}{nom}#n
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
\date{jour}{mois}{année}#n
\submissiondate{jour}{mois}{année}#n
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
\pres[précision%keyvals]{nom du PRES}#n
\comue[précision%keyvals]{nom de la ComUE}#n
\institute[précision%keyvals]{nom de l'institut%text}#n
\coinstitute[précision%keyvals]{nom de l'institut de cotutelle%text}#n
\company[précision%keyvals]{nom de l'entreprise}#n
\doctoralschool[précision%keyvals]{nom de l'école doctorale%text}#n
\laboratory[précision%keyvals]{nom du laboratoire}{adresse du laboratoire}#n
#
#keyvals:\pres,\comue,\doctoralschool
logo=
logoheight=
url=
#endkeyvals
#keyvals:\institute,\coinstitute,\company
logo=
logoheight=
url=
nologo
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
\supervisor{prénom}{nom}#n
\cosupervisor{prénom}{nom}#n
\comonitor{prénom}{nom}#n
\referee{prénom}{nom}#n
\examiner{prénom}{nom}#n
\committeepresident{prénom}{nom}#n
\guest{prénom}{nom}#n
#
\supervisor[précision%keyvals]{prénom}{nom}#n
\cosupervisor[précision%keyvals]{prénom}{nom}#n
\comonitor[précision%keyvals]{prénom}{nom}#n
\referee[précision%keyvals]{prénom}{nom}#n
\examiner[précision%keyvals]{prénom}{nom}#n
\committeepresident[précision%keyvals]{prénom}{nom}#n
\guest[précision%keyvals]{prénom}{nom}#n
#
#keyvals:\supervisor,\cosupervisor,\comonitor,\referee,\examiner,\committeepresident,\guest
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
\ordernumber[numéro d'ordre]#n
\ordernumber#*n
#
#keyvals:\maketitle
nofrontcover
noaim
frametitle=#shadowbox,ovalbox,none,fbox
#endkeyvals
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
\frontepigraph{épigraphe%text}{auteur}
\frontepigraph[langue%keyvals]{épigraphe%text}{auteur}
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
\begin{abstract}[intitulé alternatif%text]#*n
\end{abstract}#n
\makeabstract#n
\newglssymbol{label}{symbole}{nom}{description%text}#n
\newglssymbol[classement]{label}{symbole}{nom}{description%text}#n
\tableofcontents#*n
\tableofcontents[précision%keyvals]#*n
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
\expression{label}{valeur (en français)%text}{valeur (en anglais)%text}#*n
