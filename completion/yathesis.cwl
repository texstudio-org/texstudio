# mode: yathesis.cls
# denisbitouze, 16.05.2014
#
#include:class-book
#include:latex-document
#include:latex-mathsymbols
#include:tex
#include:babel
#include:geometry
#include:babel
#include:xkvltxp
#include:xkeyval
#include:etoolbox
#include:xpatch
#include:filehook
#include:hopatch
#include:xifthen
#include:geometry
#include:graphicx
#include:environ
#include:adjustbox
#include:array
#include:xstring
#include:textcase
#include:translator
#include:fixltx2e
#include:epigraph
#include:marvosym
#include:setspace
#include:morewrites
#include:shorttoc
#include:tocvsec2
#include:tocbibind
#include:nonumonpart
#include:xcolor
#include:datatool
#include:fncychap
#include:titleps
#include:ifdraft
#include:draftwatermark
#include:index
#include:idxlayout
#include:babel
#include:datetime
#include:datenumber
#include:hyperref
#include:hypcap
#include:bookmark
#
# Document class
#keyvals:\documentclass
mainlanguage=#french,english
secnumdepth=#part,chapter,section,subsection,subsubsection,paragraph,subparagraph
space=#single,onehalf,double
chap-style=#Sonny,Lenny,Glenn,Conny,Rejne,Bjarne,PetersLenny,Bjornstrup,none
nofrontcover#true,false
sepcorpaffilfrench=
sepcorpaffilenglish=
version=#inprogress,inprogress*,submitted,submitted*,final,draft
output=#screen,paper,paper*
10pt
11pt
12pt
leqno
fleqn
oneside
#endkeyvals
#
# Cover and title pages
#
# Author
\author{%<prénom%>}{%<nom%>}#n
\author[%<email%>]{%<prénom%>}{%<nom%>}#n
#
# Title, etc.
\title[%<titre dans la langue secondaire%>]{%<titre dans la langue principale%>}#n
\subtitle[%<sous-titre dans la langue secondaire%>]{%<sous-titre dans la langue principale%>}#n
\academicfield[%<discipline dans la langue secondaire%>]{%<discipline dans la langue principale%>}#n
\speciality[%<spécialité dans la langue secondaire%>]{%<spécialité dans la langue principale%>}#n
\subject[%<sujet dans la langue secondaire%>]{%<sujet dans la langue principale%>}#n
#
\title{%<titre%>}#n
\subtitle{%<sous-titre%>}#n
\academicfield{%<discipline%>}#n
\speciality{%<spécialité%>}#n
\subject{%<sujet%>}#n
\date{%<jour%>}{%<mois%>}{%<année%>}#n
#
# Institute and entities
\pres{%<nom du PRES%>}#n
\institute{%<nom de l'institut%>}#n
\coinstitute{%<nom de l'institut de cotutelle%>}#n
\company{%<nom de l'entreprise%>}#n
\doctoralschool{%<nom de l'école doctorale%>}#n
\laboratory{%<nom du laboratoire%>}{adresse du laboratoire%>}#n
#
\pres[%<précision(s)%>]{%<nom du PRES%>}#n
\institute[%<précision(s)%>]{%<nom de l'institut%>}#n
\coinstitute[%<précision(s)%>]{%<nom de l'institut de cotutelle%>}#n
\company[%<précision(s)%>]{%<nom de l'entreprise%>}#n
\doctoralschool[%<précision(s)%>]{%<nom de l'école doctorale%>}#n
\laboratory[%<précision(s)%>]{%<nom du laboratoire%>}{%<adresse du laboratoire%>}#n
#
#keyvals:\pres
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
juniorresearcher
juniorresearcher*
#endkeyvals
#keyvals:\cosupervisor
affiliation=
professor
seniorresearcher
mcf
mcf*
juniorresearcher
juniorresearcher*
#endkeyvals
#keyvals:\comonitor
affiliation=
professor
seniorresearcher
mcf
mcf*
juniorresearcher
juniorresearcher*
#endkeyvals
#keyvals:\referee
affiliation=
professor
seniorresearcher
mcf
mcf*
juniorresearcher
juniorresearcher*
#endkeyvals
#keyvals:\examiner
affiliation=
professor
seniorresearcher
mcf
mcf*
juniorresearcher
juniorresearcher*
#endkeyvals
#keyvals:\committeepresident
affiliation=
professor
seniorresearcher
mcf
mcf*
juniorresearcher
juniorresearcher*
#endkeyvals
#keyvals:\guest
affiliation=
professor
seniorresearcher
mcf
mcf*
juniorresearcher
juniorresearcher*
#endkeyvals
#
# Misc
\ordernumber[%<numéro d'ordre%>]#n
\ordernumber#n*
#
# Preliminary pages
#
\disclaimer{%<clause%>}#n
\makedisclaimer#n
\makedisclaimer*#n
\keywords{%<mots clés dans la langue secondaire%>}{%<mots clés dans la langue principale%>}#n
\makekeywords#n
\makekeywords*#n
\makelaboratory#n
\makelaboratory*#n
\dedication{%<dédicace%>}#n
\makededications#n
\makededications*#n
\frontepigraph{%<épigraphe%>}{%<auteur%>}
\frontepigraph[%<langue%>]{%<épigraphe%>}{%<auteur%>}
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
\begin{abstract}[%<intitulé alternatif%>]#n*
\end{abstract}#n
\makeabstract#n
\newglssymbol{%<label%>}{%<symbole%>}{%<nom%>}{%<description%>}#n
\newglssymbol[%<classement%>]{%<label%>}{%<symbole%>}{%<nom%>}{%<description%>}#n
\tableofcontents#n*
\tableofcontents[%<précision(s)%>]#n*
#
#keyvals:\tableofcontents
depth=#part,chapter,section,subsection,subsubsection,paragraph,subparagraph
name=
#endkeyvals
#
# Main pages
#
# Appendix pages
#
# Back matter pages
#
\makebackcover
#
# Customization
#
\expression{%<label%>}{%<valeur (en français)%>}{%<valeur (en anglais)%>}#n*
