# mode: yathesis.cls
# denisbitouze, 2021-03-23
#
#include:class-book
#include:adjustbox
#include:array
#include:babel
#include:biblatex
#include:bookmark
#include:colophon
#include:csquotes
#include:datatool
#include:datetime2
#include:draftwatermark
#include:environ
#include:epigraph
#include:etoc
#include:etoolbox
#include:fncychap
#include:geometry
#include:graphicx
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
#include:tabularx
#include:tcolorbox
#include:textcase
#include:titlesec
#include:tocbibind
#include:translator
#include:twoopt
#include:xcolor
#include:xifthen
#include:xkeyval
#include:xpatch
#include:xstring
#include:tcolorboxlibraryskins
# loads pagestyles option of titlesec, which loads titleps
#include:titleps
#
# Document class
#
#keyvals:\documentclass/yathesis
mainlanguage=#french,english
secnumdepth=#part,chapter,section,subsection,subsubsection,paragraph,subparagraph
space=#single,onehalf,double
chap-style=#Sonny,Lenny,Glenn,Conny,Rejne,Bjarne,PetersLenny,Bjornstrup,none
fncychap=#Sonny,Lenny,Glenn,Conny,Rejne,Bjarne,PetersLenny,Bjornstrup,none
nofrontcover#true,false
sepcorpaffilfrench=
sepcorpaffilenglish=
version=#inprogress,inprogress*,submitted,submitted*,final,draft
output=#screen,paper,paper*
colophon-location=#verso-frontcover,recto-backcover,nowhere
hdr
numlaboratories=%<⟨nombre de laboratoires affichés⟩%>
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
graphicx={%<⟨options du package graphicx⟩%>}
adjustbox={%<⟨options du package adjustbox⟩%>}
setspace={%<⟨options du package setspace⟩%>}
xcolor={%<⟨options du package xcolor⟩%>}
datatool={%<⟨options du package datatool⟩%>}
titlesec={%<⟨options du package titlesec⟩%>}
draftwatermark={%<⟨options du package draftwatermark⟩%>}
babel={%<⟨options du package babel⟩%>}
datetime2={%<⟨options du package datetime2⟩%>}
corps=%<⟨corporation⟩%>
role=%<⟨role⟩%>
#endkeyvals
#
\yadsetup{⟨options⟩%keyvals}#n
#
# Cover and title pages
#
# Author
\author{⟨prénom⟩}{⟨nom⟩}#n
\author[⟨email⟩]{⟨prénom⟩}{⟨nom⟩}#n
#
# Title, etc.
\title[⟨titre dans la langue secondaire⟩%text]{⟨titre dans la langue principale⟩%text}#n
\subtitle[⟨sous-titre dans la langue secondaire⟩%text]{⟨sous-titre dans la langue principale⟩%text}#n
\academicfield[⟨discipline dans la langue secondaire⟩%text]{⟨discipline dans la langue principale⟩%text}#n
\speciality[⟨spécialité dans la langue secondaire⟩%text]{⟨spécialité dans la langue principale⟩%text}#n
\subject[⟨sujet dans la langue secondaire⟩%text]{⟨sujet dans la langue principale⟩%text}#n
#
\title{⟨titre⟩%text}#n
\subtitle{⟨sous-titre⟩%text}#n
\academicfield{⟨discipline⟩%text}#n
\speciality{⟨spécialité⟩%text}#n
\subject{⟨sujet⟩%text}#n
\date{⟨jour⟩}{⟨mois⟩}{⟨année⟩}#n
\submissiondate{⟨jour⟩}{⟨mois⟩}{⟨année⟩}#n
#
# Institute and entities
\pres{⟨nom du PRES⟩}#n
\comue{⟨nom de la ComUE⟩}#n
\institute{⟨nom de l'institut⟩%text}#n
\coinstitute{⟨nom de l'institut de cotutelle⟩%text}#n
\company{⟨nom de l'entreprise⟩}#n
\doctoralschool{⟨nom de l'école doctorale⟩%text}#n
\laboratory{⟨nom du laboratoire⟩}{⟨adresse du laboratoire⟩}#n
#
\pres[⟨précisions⟩%keyvals]{⟨nom du PRES⟩}#n
\comue[⟨précisions⟩%keyvals]{⟨nom de la ComUE⟩}#n
\institute[⟨précisions⟩%keyvals]{⟨nom de l'institut⟩%text}#n
\coinstitute[⟨précisions⟩%keyvals]{⟨nom de l'institut de cotutelle⟩%text}#n
\company[⟨précisions⟩%keyvals]{⟨nom de l'entreprise⟩}#n
\doctoralschool[⟨précisions⟩%keyvals]{⟨nom de l'école doctorale⟩%text}#n
#
#keyvals:\pres,\comue,\doctoralschool,\institute,\coinstitute,\company
logo=%<⟨fichier image⟩%>
logoheight=%<⟨hauteur⟩%>
url=%<⟨URL⟩%>
nologo
#endkeyvals
#
\laboratory[⟨précisions⟩%keyvals]{⟨nom du laboratoire⟩}{⟨adresse du laboratoire⟩}#n
#
#keyvals:\laboratory
logo=%<⟨fichier image⟩%>
logoheight=%<⟨hauteur⟩%>
url=%<⟨URL⟩%>
telephone=%<⟨numéro de téléphone⟩%>
fax=%<⟨numéro de fax⟩%>
email=%<⟨courriel⟩%>
nonamelink
#endkeyvals
#
# Committee
\supervisor[⟨précisions⟩%keyvals]{⟨prénom⟩}{⟨nom⟩}#n
\cosupervisor[⟨précisions⟩%keyvals]{⟨prénom⟩}{⟨nom⟩}#n
\comonitor[⟨précisions⟩%keyvals]{⟨prénom⟩}{⟨nom⟩}#n
\referee[⟨précisions⟩%keyvals]{⟨prénom⟩}{⟨nom⟩}#n
\examiner[⟨précisions⟩%keyvals]{⟨prénom⟩}{⟨nom⟩}#n
\committeepresident[⟨précisions⟩%keyvals]{⟨prénom⟩}{⟨nom⟩}#n
\guest[⟨précisions⟩%keyvals]{⟨prénom⟩}{⟨nom⟩}#n
#
\supervisor{⟨prénom⟩}{⟨nom⟩}#n
\cosupervisor{⟨prénom⟩}{⟨nom⟩}#n
\comonitor{⟨prénom⟩}{⟨nom⟩}#n
\referee{⟨prénom⟩}{⟨nom⟩}#n
\examiner{⟨prénom⟩}{⟨nom⟩}#n
\committeepresident{⟨prénom⟩}{⟨nom⟩}#n
\guest{⟨prénom⟩}{⟨nom⟩}#n
#
#keyvals:\supervisor,\cosupervisor,\comonitor,\referee,\examiner,\committeepresident,\guest
affiliation=%<⟨affiliation⟩%>
professor
seniorresearcher
mcf
mcf*
associateprofessor
associateprofessor*
juniorresearcher
juniorresearcher*
male
female
#endkeyvals
#
# Misc
\ordernumber[⟨numéro d'ordre⟩]#n
\ordernumber#*n
#
# Keywords
\keywords{⟨mots clés dans la langue principale⟩%text}{⟨mots clés dans la langue secondaire⟩%text}#n
#
# Title
\maketitle
\maketitle[⟨options⟩%keyvals]
#
#keyvals:\maketitle
nofrontcover
noaim
frametitle=#shadowbox,ovalbox,none,fbox,{⟨autre⟩}
#endkeyvals
#
# Preliminary part
#
\colophontext{⟨texte⟩%text}#*n
\disclaimertext{⟨clause⟩%text}#n
\makedisclaimer#n
\makedisclaimer*#n
\makekeywords#n
\makekeywords*#n
\makelaboratory#n
\makelaboratory*#n
\dedication{⟨dédicace⟩%text}#n
\makededications#n
\makededications*#n
\frontepigraph{⟨épigraphe⟩%text}{⟨auteur⟩}
\frontepigraph[⟨langue⟩]{⟨épigraphe⟩%text}{⟨auteur⟩}
\makefrontepigraphs#n
\makefrontepigraphs*#n
\begin{abstract}#n
\begin{abstract}[⟨titre alternatif⟩%text]#*n
\end{abstract}#n
\makeabstract#n
\newglssymbol{⟨label⟩%labeldef}{⟨symbole⟩}{⟨nom⟩}{⟨description⟩%text}#n
\newglssymbol[⟨classement⟩]{⟨label⟩%labeldef}{⟨symbole⟩}{⟨nom⟩}{⟨description⟩%text}#n
\tableofcontents#*n
\tableofcontents[⟨précisions⟩%keyvals]#*n
#
#keyvals:\tableofcontents
depth=#part,chapter,section,subsection,subsubsection,paragraph,subparagraph
name=%<⟨nom de la table des matières⟩%>
#endkeyvals
#
# Main part
#
\chapter{⟨titre⟩%title}#L1
\chapter*{⟨titre⟩%title}#L1
\chapter[⟨titre alt. pour TdM et entête⟩%short title]{⟨titre⟩%title}#L1
\chapter*[⟨titre alt. pour TdM et entête⟩%short title]{⟨titre⟩%title}#L1
\chapter[⟨titre alt. pour TdM⟩%short title][⟨titre alt. pour entête⟩%short title]{⟨titre⟩%title}#L1
\chapter*[⟨titre alt. pour TdM⟩%short title][⟨titre alt. pour entête⟩%short title]{⟨titre⟩%title}#L1
\section{⟨titre⟩%title}#L2
\section*{⟨titre⟩%title}#L2
\section[⟨titre alt. pour TdM et entête⟩%short title]{⟨titre⟩%title}#L2
\section*[⟨titre alt. pour TdM et entête⟩%short title]{⟨titre⟩%title}#L2
\section[⟨titre alt. pour TdM⟩%short title][⟨titre alt. pour entête⟩%short title]{⟨titre⟩%title}#L2
\section*[⟨titre alt. pour TdM⟩%short title][⟨titre alt. pour entête⟩%short title]{⟨titre⟩%title}#L2
\subsection{⟨titre⟩%title}#L3
\subsection*{⟨titre⟩%title}#L3
\subsection[⟨titre alt. pour TdM et entête⟩%short title]{⟨titre⟩%title}#L3
\subsection*[⟨titre alt. pour TdM et entête⟩%short title]{⟨titre⟩%title}#L3
\subsubsection{⟨titre⟩%title}#L4
\subsubsection*{⟨titre⟩%title}#L4
\subsubsection[⟨titre alt. pour TdM et entête⟩%short title]{⟨titre⟩%title}#L4
\subsubsection*[⟨titre alt. pour TdM et entête⟩%short title]{⟨titre⟩%title}#L4
\paragraph{⟨titre⟩%title}#L5
\paragraph*{⟨titre⟩%title}#L5
\paragraph[⟨titre alt. pour TdM et entête⟩%short title]{⟨titre⟩%title}#L5
\paragraph*[⟨titre alt. pour TdM et entête⟩%short title]{⟨titre⟩%title}#L5
\subparagraph{⟨titre⟩%title}#L6
\subparagraph[⟨titre alt. pour TdM et entête⟩%short title]{⟨titre⟩%title}#L6
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
\leadchapter{⟨texte⟩%text}
\printsymbols[⟨options⟩%keyvals]
#
#keyvals:\printsymbols
style=#yadsymbolstyle,⟨autre⟩
#endkeyvals
#
# Customization
#
\expression{⟨label⟩%labeldef}{⟨valeur en français⟩%text}{⟨valeur en anglais⟩%text}#*n

# from french option of babel
\frenchsetup{options%keyvals}
\frenchbsetup{options%keyvals}#S
#keyvals:\frenchsetup,\frenchbsetup
ShowOptions#true,false
StandardLayout#true,false
GlobalLayoutFrench#true,false
IndentFirst#true,false
PartNameFull#true,false
ListItemsAsPar#true,false
StandardListSpacing#true,false
StandardItemizeEnv#true,false
StandardEnumerateEnv#true,false
StandardItemLabels#true,false
ItemLabels=
ItemLabeli=
ItemLabelii=
ItemLabeliii=
ItemLabeliv=
StandardLists#true,false
ListOldLayout#true,false
FrenchFootnotes#true,false
AutoSpaceFootnotes#true,false
AutoSpacePunctuation#true,false
ThinColonSpace#true,false
OriginalTypewriter#true,false
UnicodeNoBreakSpaces#true,false
og=
fg=
INGuillSpace#true,false
EveryParGuill=#open,close,none
EveryLineGuill=#open,close,none
InnerGuillSingle#true,false
ThinSpaceInFrenchNumbers#true,false
SmallCapsFigTabCaptions#true,false
CustomiseFigTabCaptions#true,false
OldFigTabCaptions#true,false
FrenchSuperscripts#true,false
LowercaseSuperscripts#true,false
SuppressWarning#true,false
#endkeyvals
\AddThinSpaceBeforeFootnotes#*
\alsoname#*
\at
\bibname#*
\AutoSpaceBeforeFDP#*
\begin{descriptionFB}
\begin{enumerateFB}
\begin{itemizeFB}
\begin{listFB}{symbol}
\begin{listORI}{symbol}#*
\boi
\bname{text}
\bsc{text}
\CaptionSeparator#*
\captionsfrench#*
\ccname#*
\chaptername#*
\circonflexe
\dateacadian#*
\datefrench#*
\DecimalMathComma
\degre#*
\degres
\descindentFB#*
\dotFFN#*
\enclname#*
\end{descriptionFB}
\end{enumerateFB}
\end{itemizeFB}
\end{listFB}
\end{listORI}#*
\extrasfrench#*
\FBcolonspace
\FBdatebox#*
\FBdatespace#*
\FBeverylineguill#*
\FBfigtabshape#*
\FBfnindent#*
\FBFrenchFootnotesfalse#*
\FBFrenchFootnotestrue#*
\FBFrenchSuperscriptstrue#*
\FBGlobalLayoutFrenchtrue#*
\FBgspchar#*
\FBguillopen#*
\FBguillspace
\FBInnerGuillSinglefalse#*
\FBInnerGuillSingletrue#*
\FBListItemsAsParfalse#*
\FBListItemsAsPartrue#*
\FBLowercaseSuperscriptstrue#*
\FBmedkern#*
\FBPartNameFulltrue#*
\FBsetspaces[language]{type}{width}{stretch}{shrink}#*
\FBsetspaces{type}{width}{stretch}{shrink}#*
\FBSmallCapsFigTabCaptionstrue#*
\FBStandardEnumerateEnvtrue#*
\FBStandardItemizeEnvtrue#*
\FBStandardItemLabelstrue#*
\FBStandardLayouttrue#*
\FBStandardListSpacingtrue#*
\FBStandardListstrue#*
\FBsupR#*
\FBsupS#*
\FBtextellipsis#*
\FBthickkern#*
\FBthinspace
\FBthousandsep#*
\FBWarning{message%text}#*
\fg
\fgi#*
\fgii#*
\fprimo)
\frenchdate{day}{month}{year}
\FrenchEnumerate{arg}#*
\FrenchFootnotes#*
\FrenchLabelItem#*
\frenchpartfirst#*
\frenchpartsecond#*
\FrenchPopularEnumerate{arg}#*
\frenchtoday#*
\Frlabelitemi#*
\Frlabelitemi#*
\Frlabelitemii#*
\Frlabelitemii#*
\Frlabelitemiii#*
\Frlabelitemiii#*
\Frlabelitemiv#*
\Frlabelitemiv#*
\frquote{text}
\fup{text}
\glossaryname#*
\headtoname#*
\ieme
\iemes
\ier
\iere
\ieres
\iers
\ifFBAutoSpaceFootnotes#*
\ifFBCompactItemize#*
\ifFBCustomiseFigTabCaptions#*
\ifFBfrench#*
\ifFBFrenchFootnotes#*
\ifFBFrenchSuperscripts#*
\ifFBGlobalLayoutFrench#*
\ifFBIndentFirst#*
\ifFBINGuillSpace#*
\ifFBListItemsAsPar#*
\ifFBListOldLayout#*
\ifFBLowercaseSuperscripts#*
\ifFBLuaTeX#*
\ifFBOldFigTabCaptions#*
\ifFBOriginalTypewriter#*
\ifFBPartNameFull#*
\ifFBReduceListSpacing#*
\ifFBShowOptions#*
\ifFBSmallCapsFigTabCaptions#*
\ifFBStandardEnumerateEnv#*
\ifFBStandardItemizeEnv#*
\ifFBStandardItemLabels#*
\ifFBStandardLayout#*
\ifFBStandardLists#*
\ifFBStandardListSpacing#*
\ifFBSuppressWarning#*
\ifFBThinColonSpace#*
\ifFBThinSpaceInFrenchNumbers#*
\ifFBunicode#*
\ifFBXeTeX#*
\ifLaTeXe#*
\kernFFN#*
\labelindentFB#*
\labelwidthFB#*
\leftmarginFB#*
\listfigurename#*
\listindentFB#*
\No
\no
\NoAutoSpaceBeforeFDP#*
\NoAutoSpacing
\NoEveryParQuote#*
\noextrasfrench#*
\nombre{arg}#*
\nos
\Nos
\og
\ogi#*
\ogii#*
\pagename#*
\parindentFFN#*
\partfirst#*
\partfirst#*
\partnameord#*
\partsecond#*
\partsecond#*
\prefacename#*
\primo
\proofname#*
\quarto
\rmfamilyFB#*
\secundo
\seename#*
\sffamilyFB#*
\StandardFootnotes#*
\StandardMathComma
\tertio
\tild
\ttfamilyFB#*
\up{text}
\xspace
