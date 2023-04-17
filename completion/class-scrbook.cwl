# scrbook class
# Matthew Bertucci 2023/04/17 for v3.39

#include:scrkbase
#include:tocbasic
#include:typearea
#include:scrlogo

#ifOption:emulatestandardclasses
\defaultpapersize
#include:scrlayer-scrpage
#endif

#keyvals:\KOMAoptions#c
draft=#true,on,yes,false,off,no
overfullrule=#true,on,yes,false,off,no
fontsize=##L
titlepage=#true,on,yes,false,off,no,firstiscover
toc=#bibliography,bib,bibliographynumbered,bibnumbered,numberedbibliography,numberedbib,chapterentrywithdots,chapterentrydotfill,chapterentrywithoutdots,chapterentryfill,flat,left,graduated,indent,indented,indenttextentries,indentunnumbered,numberline,index,idx,indexnumbered,idxnumbered,numberedindex,numberedidx,leftaligntextentries,leftalignunnumbered,nonumberline,listof,listofnumbered,numberedlistof,nobibliography,nobib,noindex,noidx,nolistof,sectionentrywithdots,sectionentrydotfill,sectionentrywithoutdots,sectionentryfill
chapterentrydots=#true,on,yes,false,off,no
parskip=#false,off,no,full,true,yes,full-,full+,full*,half,half-,half+,half*,never
cleardoublepage=#empty,headings,myheadings,plain,current
footnotes=#multiple,nomultiple
open=#any,left,right
chapterprefix=#true,on,yes,false,off,no
appendixprefix=#true,on,yes,false,off,no
headings=#big,normal,onelineappendix,noappendixprefix,appendixwithoutprefix,appendixwithoutprefixline,onelinechapter,nochapterprefix,chapterwithoutprefix,chapterwithoutprefixline,openany,openleft,openright,optiontohead,optiontoheadandtoc,optiontotocandhead,optiontotoc,small,standardclasses,twolineappendix,appendixprefix,appendixwithprefix,appendixwithprefixline,twolinechapter,chapterprefix,chapterwithprefix,chapterwithprefixline
numbers=#autoendperiod,autoenddot,auto,endperiod,withendperiod,periodatend,enddot,withenddot,dotatend,noendperiod,noperiodatend,noenddot,nodotatend
chapteratlists
chapteratlists=##L
captions=#bottombeside,besidebottom,centeredbeside,besidecentered,middlebeside,besidemiddle,figureheading,figureabove,abovefigure,topatfigure,figuresignature,belowfigure,bottomatfiggure,heading,above,top,innerbeside,besideinner,leftbeside,besideleft,nooneline,oneline,outerbeside,besideouter,rightbeside,besideright,signature,below,bot,bottom,tableheading,tableabove,abovetable,abovetabular,topattable,tablesignature,belowtable,belowtabular,bottomattable,topbeside,besidetop
listof=#chapterentry,withchapterentry,chaptergapline,onelinechaptergap,chaptergapsmall,smallchaptergap,entryprefix,flat,left,graduated,indent,indented,leveldown,indenttextentries,indentunnumbered,numberline,leftaligntextentries,leftalignunnumbered,nonumberline,nochaptergap,ignorechapter,notoc,nottotoc,plainheading,numbered,totocnumbered,tocnumbered,numberedtoc,numberedtotoc,standardlevel,totoc,toc,notnumbered
bibliography=#leveldown,notoc,nottotoc,plainheading,numbered,tocnumbered,totocnumbered,numberedtoc,numberedtotoc,oldstyle,openstyle,standardlevel,toc,totoc,notnumbered
index=#leveldown,notoc,nottotoc,plainheading,numbered,tocnumbered,totocnumbered,numberedtoc,numberedtotoc,standardlevel,toc,totoc,notnumbered
bookmarkpackage=#true,on,yes,false,off,no
#endkeyvals

#keyvals:\setkomafont#c,\addtokomafont#c,\usekomafont#c,\usesizeofkomafont#c,\usefamilyofkomafont#c,\useseriesofkomafont#c,\useshapeofkomafont#c,\useencodingofkomafont#c,\usefontofkomafont#c
author
caption
captionlabel
chapter
chapterentry
chapterentrydots
chapterentrypagenumber
chapterprefix
date
dedication
descriptionlabel
dictum
dictumauthor
dictumtext
disposition
footnote
footnotelabel
footnotereference
footnoterule
itemizelabel
labelinglabel
labelingseparator
labelitemi
labelitemii
labelitemiii
labelitemiv
minisec
pagefoot
pagehead
pageheadfoot
pagenumber
pagination
paragraph
part
partentry
partentrypagenumber
partnumber
publishers
section
sectionentry
sectionentrydots
sectionentrypagenumber
sectioning
subject
subparagraph
subsection
subsubsection
subtitle
title
titlehead
#endkeyvals

\addchap*[short title]{title}#L1
\addchap*{title}#L1
\addchap[short title]{title}#L1
\addchap{title}#L1
\addchapmark{running head}#*
\addchaptertocentry{number}{heading%text}#*
\addparagraphtocentry{number}{heading%text}#*
\addpart*[short title]{title}#L0
\addpart*{title}#L0
\addpart[short title]{title}#L0
\addpart{title}#L0
\addpartmark{running head}#*
\addparttocentry{number}{heading%text}#*
\addsec*[short title]{title}#L2
\addsec*{title}#L2
\addsec[short title]{title}#L2
\addsec{title}#L2
\addsecmark{running head}#*
\addsectiontocentry{number}{heading%text}#*
\addsubparagraphtocentry{number}{heading%text}#*
\addsubsectiontocentry{number}{heading%text}#*
\addsubsubsectiontocentry{number}{heading%text}#*
\addtocentrydefault{level}{number}{heading%text}#*
\AddToSectionCommandOptionsDoList{key%plain}#*
\AfterBibliographyPreamble{code}#*
\appendixmore#*
\AtEndBibliography{code}#*
\autodot#*
\backmatter
\begin{addmargin*}[inner indent%l]{indent%l}
\begin{addmargin*}{indent%l}
\begin{addmargin}[left indent%l]{indent%l}
\begin{addmargin}{indent%l}
\begin{captionbeside}[short title]{caption text%text}[placement][width][offset%l]
\begin{captionbeside}{caption text%text}
\begin{captionofbeside}{float type}[short title]{caption text%text}[placement][width][offset%l]
\begin{captionofbeside}{float type}{caption text%text}
\begin{labeling}[delimiter]{widest pattern}
\begin{labeling}{widest pattern}
\bibpreamble#*
\BreakBibliography{interruption code}#*
\capfont#*
\caplabelfont#*
\captionabove[entry]{title%text}
\captionabove[entry]{title%text}
\captionabove{title%text}
\captionaboveof{float type}[entry]{title%text}
\captionaboveof{float type}{title%text}
\captionbelow{title%text}
\captionbelowof{float type}[entry]{title%text}
\captionbelowof{float type}{title%text}
\captionformat#*
\captionof{float type}[entry]{title%text}
\captionof{float type}{title%text}
\changefontsizes{font size%l}#*
\chapapp#*
\chapappifchapterprefix{additional test}#*
\chapter{title}#L1
\chapter*{title}#L1
\chapter[short title]{title}#L1
\chapterformat#*
\chapterheadendvskip#*
\chapterheadmidvskip#*
\chapterheadstartvskip#*
\chapterlinesformat{level}{number}{text}#*
\chapterlineswithprefixformat{level}{number}{text}#*
\chaptermarkformat#*
\chapternumdepth#*
\chapterpagestyle#*
\ClassName#*
\cleardoubleemptypage
\cleardoubleevenemptypage
\cleardoubleevenpage
\cleardoubleevenpageusingstyle{pagestyle%keyvals}
\cleardoubleevenplainpage
\cleardoubleevenstandardpage
\cleardoubleoddemptypage
\cleardoubleoddpage
\cleardoubleoddpageusingstyle{pagestyle%keyvals}
\cleardoubleoddplainpage
\cleardoubleoddstandardpage
\cleardoublepageusingstyle{pagestyle%keyvals}
\cleardoubleplainpage
\cleardoublestandardpage
\coverpagebottommargin#*
\coverpageleftmargin#*
\coverpagerightmargin#*
\coverpagetopmargin#*
\DeclareNewSectionCommand[attributes%keyvals]{name}#*
\DeclareNewSectionCommand{name}#*
\DeclareNewSectionCommands[attributes%keyvals]{list of names}#*
\DeclareNewSectionCommands{list of names}#*
\DeclareSectionCommand[attributes%keyvals]{name}
\DeclareSectionCommand{name}
\DeclareSectionCommands[attributes%keyvals]{list of names}
\DeclareSectionCommands{list of names}
\DeclareSectionCommandStyleFontOption{section level}{key%plain}{prefix}{postfix}#*
\DeclareSectionCommandStyleFuzzyOption{section level}{key%plain}{prefix}{postfix}{alt}#*
\DeclareSectionCommandStyleLengthOption{section level}{key%plain}{prefix}{postfix}#*
\DeclareSectionCommandStyleNumberOption{section level}{key%plain}{prefix}{postfix}#*
\DeclareSectionCommandStyleOption{section level}{key%plain}{code}#*
\dedication{dedication%text}
\deffootnote[mark width%l]{indent%l}{parindent%l}{definition}#*
\deffootnote{indent%l}{parindent%l}{definition}#*
\deffootnotemark{definition}#*
\descfont#*
\dictum[author]{text}
\dictum{text}
\dictumauthorformat{author}#*
\dictumrule#*
\dictumwidth#*
\end{addmargin*}
\end{addmargin}
\end{captionbeside}
\end{captionofbeside}
\end{labeling}
\extratitle{short title}
\FamilyElseValue#*
\figureformat#*
\footfont#*
\frontispiece{frontispiece%text}
\frontmatter
\headfont#*
\IfChapterUsesPrefixLine{then code}{else code}#*
\Ifnumbered{section level}{then code}{else code}#*
\ifonelinecaptions#*
\IfSectionCommandStyleIs{name}{style}{then code}{else code}#*
\Ifthispageodd{true code}{false code}#*
\ifthispagewasodd#*
\Ifunnumbered{section level}{then code}{else code}#*
\IfUseNumber{then code}{else code}#*
\IfUsePrefixLine{then code}{else code}#*
\indexpagestyle#*
\KOMAClassFileName#*
\KOMAClassName#*
\labelinglabel{arg}#*
\listoftocname#*
\lowertitleback{titlebackfoot%text}
\mainmatter
\maketitle[page number]
\marginline{margin note%text}
\maybesffamily
\minisec{title}
\multfootsep#*
\multiplefootnotemarker#*
\multiplefootnoteseparator#*
\newbibstyle[parent style]{name}{commands}#*
\newbibstyle{name}{commands}#*
\onelinecaptionsfalse#*
\onelinecaptionstrue#*
\pagemark#*
\paragraphformat#*
\paragraphnumdepth#*
\paragraphtocdepth#*
\partformat#*
\partheademptypage#*
\partheadendvskip#*
\partheadmidvskip#*
\partheadstartvskip#*
\partlineswithprefixformat{level}{number}{text}#*
\partmark{text}#*
\partnumdepth#*
\partpagestyle#*
\parttocdepth#*
\pnumfont#*
\ProvideSectionCommand[attributes%keyvals]{name}
\ProvideSectionCommand{name}
\ProvideSectionCommands[attributes%keyvals]{list of names}
\ProvideSectionCommands{list of names}
\publishers{publisher}
\raggedcaption#*
\raggedchapter#*
\raggedchapterentry#*
\raggeddictum#*
\raggeddictumauthor#*
\raggeddictumtext#*
\raggedfootnote#*
\raggedpart#*
\raggedsection#*
\raggedsectionentry#*
\RedeclareSectionCommand[attributes%keyvals]{name}
\RedeclareSectionCommand{name}
\RedeclareSectionCommands[attributes%keyvals]{list of names}
\RedeclareSectionCommands{list of names}
\RelaxSectionCommandOptions#*
\SecDef{star command}{command}#*
\sectfont#*
\sectioncatchphraseformat{level}{indent%l}{number}{text}#*
\sectionformat#*
\sectionlinesformat{level}{indent%l}{number}{text}#*
\sectionmarkformat#*
\sectionnumdepth#*
\sectiontocdepth#*
\setbibpreamble{preamble%text}
\setcapdynwidth[justification%keyvals]{width}#*
\setcapdynwidth{width}#*
\setcaphanging#*
\setcapindent*{indent%l}#*
\setcapindent{indent%l}#*
\setcapmargin*[inner margin%l]{margin%l}#*
\setcapmargin*{margin%l}#*
\setcapmargin[left margin%l]{margin%l}#*
\setcapmargin{margin%l}#*
\setcaptionalignment[float type]{alignment%keyvals}#*
\setcaptionalignment{alignment%keyvals}#*
\setcapwidth[justification%keyvals]{width}#*
\setcapwidth{width}#*
\setchapterpreamble[position%keyvals][width]{preamble%text}
\setchapterpreamble[position%keyvals]{preamble%text}
\setchapterpreamble{preamble%text}
\setfootnoterule[thickness]{length}#*
\setfootnoterule{length}#*
\setindexpreamble{preamble%text}
\setparsizes{indent%l}{distance%l}{last-line end space}#*
\setpartpreamble[position%keyvals][width]{preamble%text}
\setpartpreamble[position%keyvals]{preamble%text}
\setpartpreamble{preamble%text}
\subject{subject%text}
\subparagraphformat#*
\subparagraphnumdepth#*
\subparagraphtocdepth#*
\subsectionformat#*
\subsectionmarkformat#*
\subsectionnumdepth#*
\subsectiontocdepth#*
\subsubsectionformat#*
\subsubsectionnumdepth#*
\subsubsectiontocdepth#*
\subtitle{subtitle%text}
\tableformat#*
\textmaybesf{text}
\thechapter#*
\thefootnotemark#*
\thispagestyle{page style%keyvals}
\thispagewasoddfalse#*
\thispagewasoddtrue#*
\titlefont#*
\titlehead{title head%text}
\titlepagestyle#*
\uppertitleback{titlebackhead%text}
\UseNumberUsageError{then code}{else code}#*

#keyvals:\DeclareSectionCommand#c,\DeclareNewSectionCommand#c,\RedeclareSectionCommand#c,\ProvideSectionCommand#c,\DeclareSectionCommands#c,\DeclareNewSectionCommands#c,\RedeclareSectionCommands#c,\ProvideSectionCommands#c
counterwithin=%<counter%>
counterwithout=%<counter%>
expandtopt=#true,on,yes,false,off,no
level=%<integer%>
style=%<style%>
tocstyle=%<TOC style%>
afterindent=##L
afterskip=##L
beforeskip=##L
font=%<font commands%>
indent=##L
runin=#true,on,yes,false,off,no
innerskip=##L
pagestyle=%<page style%>
prefixfont=%<font commands%>
#endkeyvals

#keyvals:\setcapwidth,\setcapdynwidth
l
c
r
i
o
#endkeyvals

#keyvals:\setcaptionalignment
c
j
l
r
C
J
L
R
#endkeyvals

#keyvals:\cleardoublepageusingstyle#c,\cleardoubleoddpageusingstyle#c,\cleardoubleevenpageusingstyle#c
empty
headings
myheadings
plain
#endkeyvals

#keyvals:\setpartpreamble,\setchapterpreamble
o
u
l
r
c
#endkeyvals

# available if float package loaded
#keyvals:\floatstyle
komaabove
komabelow
#endkeyvals

# deprecated
\ifnumbered#S
\ifthispageodd#S
\ifunnumbered#S
\othersectionlevelsformat#S
