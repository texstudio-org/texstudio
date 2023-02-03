# ekdosis package
# Matthew Bertucci 4/4/2022 for v1.4

#include:luatex
#include:iftex
#include:expkv-opt
#include:expkv-def
#include:luacode
#include:paracol
#include:etoolbox
#include:lineno
#include:trivfloat
#include:refcount
#include:zref-user
#include:zref-abspage
#include:ltxcmds
#include:pdftexcmds
#include:ifoddpage

## The Basics of ekdosis ##
# Loading the Package—General Options #
#keyvals:\usepackage/ekdosis#c
layout=#float,footins,keyfloat,fitapp
divs=#ekdosis,latex
poetry=verse
parnotes=#true,false,roman
teiexport=#true,false,tidy
#endkeyvals

#ifOption:layout=keyfloat
#include:keyfloat
#endif

#ifOption:layout=fitapp
#include:tcolorbox
#include:tcolorboxlibraryfitting
#include:tcolorboxlibraryskins
#endif

#ifOption:poetry=verse
#include:verse
#endif

#ifOption:parnotes
#include:parnotes
#endif

# Setup #
\ekdsetup{options%keyvals}

#keyvals:\ekdsetup
showpagebreaks#true,false
spbmk=%<string%>
hpbmk=%<string%>
#endkeyvals

# Witnesses, Hands, Sources, Scholars & Shorthands #
\DeclareWitness{unique id}{rendition}{description%text}
\DeclareWitness{unique id}{rendition}{description%text}[options%keyvals]

#keyvals:\DeclareWitness
settlement=%<name%>
institution=%<name%>
repository=%<name%>
collection=%<name%>
idno=%<call number%>
msName=%<name%>
origDate=%<date%>
locus=%<locus%>
#endkeyvals

\DeclareHand{unique id}{base ms.}{rendition}
\DeclareHand{unique id}{base ms.}{rendition}[note]
\DeclareSource{unique label}{rendition}

\DeclareScholar{unique id}{rendition}
\DeclareScholar{unique id}{rendition}[options%keyvals]

#keyvals:\DeclareScholar
rawname=%<name%>
forename=%<name%>
surname=%<name%>
addname=%<additional name%>
note=%<note%>
#endkeyvals

\DeclareShorthand{unique id}{rendition}{list of ids}
\getsiglum{list of witnesses}
\SigLine{unique id}

# Editing a Single Text #
\begin{ekdosis}
\end{ekdosis}
\app{apparatus entries%text}
\app[type=%<type%>]{%<apparatus entries%>}

\lem{lemma text%text}
\lem[options%keyvals]{lemma text%text}

#keyvals:\lem
wit=%<list of witnesses%>
source=%<list of sources%>
resp=%<list of scholars%>
alt=%<alternate lemma%>
sep=%<separator%>
nosep#true,false
nolem#true,false
type=%<type%>
num
nonum
pre=%<words%>
post=%<words%>
prewit=%<words%>
postwit=%<words%>
#endkeyvals

\rdg{variant reading}
\rdg[options%keyvals]{variant reading}

#keyvals:\rdg
wit=%<list of witnesses%>
source=%<list of sources%>
resp=%<list of scholars%>
alt=%<alternate lemma%>
nordg#true,false
type=%<type%>
pre=%<words%>
post=%<words%>
prewit=%<words%>
postwit=%<words%>
subsep=%<subseparator%>
nosubsep
#endkeyvals

\note{text}
\note[options%keyvals]{text}
\note*{text}
\note*[options%keyvals]{text}

#keyvals:\note,\note*
pre=%<words%>
post=%<words%>
sep
subsep
#endkeyvals

# Indicating Subvariation in Apparatus Entries #
\rdgGrp{lemma text%text}
\rdgGrpe[type=%<type%>]{%<lemma text%>}

## Emendations and Conjectures ##
# Editorial Addition and Deletion #
\SetCritSymbols{options%keyvals}

#keyvals:\SetCritSymbols
suppbegin=%<symbol%>
suppend=%<symbol%>
delbegin=%<symbol%>
delend=%<symbol%>
sicbegin=%<symbol%>
sicend=%<symbol%>
gapmark=%<symbols%>
keepinapp#true,false
#endkeyvals

\supplied{text}
\surplus{text}
\sic{text}
\sic*{text}

\gap{options%keyvals}

#keyvals:\gap
reason=%<reason%>
unit=%<unit%>
quantity=%<n%>
extent=%<description%>
#endkeyvals

## Alignment of Parallel Texts ##
\begin{alignment}
\begin{alignment}[options%keyvals]
\end{alignment}
\begin{edition}
\end{edition}
\begin{edition*}
\end{edition*}
\begin{translation}
\end{translation}
\begin{translation*}
\end{translation*}

# Alignment of Several Texts #
\SetAlignment{options%keyvals}

#keyvals:\begin{alignment},\SetAlignment
tcols=%<number%>
lcols=%<number%>
texts=%<semicolon-separated values%>
apparatus=%<semicolon-separated values%>
paired#true,false
lineation=#page,document
flush#true,false
segmentation=#auto,noauto
#endkeyvals

## Laying Out the Apparatus Criticus ##
# General Hooks #
\SetHooks{list of hooks%keyvals}

#keyvals:\SetHooks
appfontsize=%<command%>
refnumstyle=%<command%>
postrefnum=%<<command> or <chars>%>
lemmastyle=%<command%>
readingstyle=%<command%>
familysep=%<<symbol> or reset%>
initialrule=%<command%>
noinitialrule
#endkeyvals

#ifOption:layout=keyfloat
#keyvals:\SetHooks
keyparopts={%<keyfloat options%>}
#endkeyvals
#endif

#ifOption:layout=fitapp
#keyvals:\SetHooks
appheight=##L
fitalgorithm=#fontsize,hybrid,areasize,squeeze
#endkeyvals
#endif

# Single-Layer Apparatus Criticus #
\SetLTRapp
\SetRTLapp
\SetSeparator{separator}
\SetSubseparator{subseparator}
\ekdsep
\ekdsubsep
\SetBeginApparatus{characters or commands}
\SetEndApparatus{characters}
\SetUnitDelimiter{delimiter}
\SetDefaultRule{line definition}
\SetApparatusLanguage{language}
\SetApparatusNoteLanguage{language}

\SetApparatus{options%keyvals}

#keyvals:\SetApparatus,\DeclareApparatus
direction=#LR,RL
sep=%<separator%>
subsep=%<subseparator%>
delim=%<delimiter%>
bhook=%<characters or commands%>
ehook=%<characters%>
rule=%<line definition%>
norule
lang=%<language%>
notelang=%<language%>
maxentries=%<integer%>
#endkeyvals

\iffootnoterule#*
\footnoteruletrue
\footnoterulefalse 

# Multiple-Layer Apparatus Criticus #
\SetDefaultApparatus{name}

\DeclareApparatus{name}
\DeclareApparatus{name}[options%keyvals]

## Inserting Notes in Multiple-Layer Apparatus ##
# Other Notes for Comments, Sources or Testimonia #
#keyvals:\note
type=%<type%>
sep=%<separator%>
nosep#true,false
lem=%<lemma text%>
num
nonum
labelb=%<label%>
labele=%<label%>
#endkeyvals

## Poetry ##
# The Standard verse Environment #
\begin{ekdverse}
\begin{ekdverse}[options%keyvals]
\end{ekdverse}

#keyvals:\begin{ekdverse}
width=##L
type=%<type%>
#endkeyvals

\begin{ekdstanza}
\begin{ekdstanza}[options%keyvals]
\end{ekdstanza}

#keyvals:\begin{ekdstanza}
type=%<type%>
#endkeyvals

## Lineation Settings ##
\SetLineation{options%keyvals}

#keyvals:\SetLineation
lineation=#page,document,none
modulo
modulonum=%<integer%>
margin=#right,left,inner,outer
numbers=#elided,full
#endkeyvals

\innerlinenumbers
\outerlinenumbers

#ifOption:poetry=verse
#keyvals:\SetLineation
vlineation=#page,document
vmodulo=%<integer%>
vnumbrokenlines#true,false
vmargin=#right,left
continuousvnum
#endkeyvals
\vmodulolinenumbers
\vmodulolinenumbers[n]
\resetvlinenumber
\resetvlinenumber[n]
#endif

## Languages ##
# Languages Written From Right to Left #
\setRL
\setLR

## Divisions of the Body ##
# LaTeX Standard Divisions #
\MkBodyDivs{div1}{div2}{div3}{div4}{div5}{div6}

# TEI Un-numbered Divisions #
\ekddiv{keyvals}

#keyvals:\ekddiv
type=%<type%>
n=%<value%>
head=%<name%>
barehead=%<name%>
depth=%<n%>
toc=#book,part,chapter,section,subsection,subsubsection,paragraph,subparagraph
mark=%<signpost%>
#endkeyvals

\FormatDiv{n}{code before}{code after}

# Headers and Footers #
\ekdmark
\endmark
\ekdprintmark{selector}{signpost}
\ekdnohfmark
\ekdresethfmarks

## The Tricks of the Trade ##
# The Oscillating Problem #
\ekdpb{line no}
\ekdpb[page no]{line no}
\ekdpb*{}
\addentries{n}
\addentries[layer]{n}

## TEI xml Output ##
# Requesting TEI xml Output #
\SetTEIFileName{file name%file}

# General Principles #
\SetTEIxmlExport{options%keyvals}

#keyvals:\SetTEIxmlExport
autopar#true,false
#endkeyvals

\begin{ekdpar}
\end{ekdpar}

# Processing New Commands or Environments #
\TeXtoTEI{csname}{TEI element}
\TeXtoTEI{csname}{TEI element}[TEI attributes]
\EnvtoTEI{envname}{TEI element}
\EnvtoTEI{envname}{TEI element}[TEI attributes]
\EnvtoTEI*{envname}{TEI element}
\EnvtoTEI*{envname}{TEI element}[TEI attributes]
\TeXtoTEIPat{TeX pattern}{TEI pattern}

# Inserting Code in the TEI xml Ouput File #
\teidirect{XML element}{code}
\teidirect[XML attributes]{XML element}{code}

# References to Cited Works #
\AddxmlBibResource{file name%file}

## not in main documentation ##
\EkdosisColStart#*
\EkdosisColStop#*
\EkdosisOff#*
\EkdosisOn#*
\LRnum{number}#*
\NLS#*
\SetTEIFileName{arg1}#*
\apparatus#*
\blfootnote{text}#*
\ekdatbegshihook#*
\ekdnohfmark#*
\ekdpage#*
\ekdverseindentlength#*
