# abntex2cite package
# Matthew Bertucci 2022/05/19 for v1.9.7

#include:ifthen
#include:calc
#include:abntex2abrev
#include:setspace
#include:url
#include:ifpdf
#include:ifxetex
#include:breakurl
#include:relsize

#keyvals:\usepackage/abntex2cite
alf
num
foot
not-foot
load-text-on-demand
load-text
alfantigo
experimental
bibjustif
bibleftalign
biblabel-on-margin
biblabel-not-on-margin
abnt-option-file
no-abnt-option-file
recuo
indent
overcite
inlinecite
versalete
abnt-substyle=COPPE
#endkeyvals

#keyvals:\bibliographystyle#c
abntex2-alf
#endkeyvals

\citeonline{keylist}#c
\citeonline[add. text]{keylist}#c
\apud{keylist}{keylist}#c
\apud[add. text]{keylist}{keylist}#c
\apudonline{keylist}{keylist}#c
\apudonline[add. text]{keylist}{keylist}#c
\footciteref{keylist}#c
\Idem{keylist}#c
\Idem[add. text]{keylist}#c
\Ibidem{keylist}#c
\Ibidem[add. text]{keylist}#c
\opcit{keylist}#c
\opcit[add. text]{keylist}#c
\passim{keylist}#c
\passim[add. text]{keylist}#c
\loccit{keylist}#c
\loccit[add. text]{keylist}#c
\cfcite{keylist}#c
\cfcite[add. text]{keylist}#c
\etseq{keylist}#c
\etseq[add. text]{keylist}#c
\citeauthoronline{keylist}#c
\citeauthor{keylist}#c
\citeyear{keylist}#c
\citetext{keylist}#c
\authorcapstyle#*
\authorstyle#*
\yearstyle#*
\citebrackets{delim1}{delim2}
\bibtextitlecommand{tipo}{campo}#*

\citeoption{option%keyvals}
#keyvals:\citeoption#c,\usepackage/abntex2cite#c
abnt-and-type=#e,&
abnt-etal-cite=#0,2,3,4,5
abnt-etal-list=#0,2,3,4,5
abnt-etal-text=#none,default,emph,it
abnt-full-initials=#no,yes
abnt-last-names=#abnt,bibtex
abnt-missing-year=#void,sd
abnt-repeated-author-omit=#no,yes
abnt-repeated-title-omit=#no,yes
abnt-thesis-year=#final,title,both
abnt-refinfo=#no,yes
abnt-show-options=#no,warn,list
abnt-verbatim-entry=#no,yes
abnt-doi=#expand,link,doi
abnt-substyle=#COPPE,UFLA
abnt-nbr10520=#2001,1988
#endkeyvals

# not documented
\ABCIaddtocitelist{arg1}#*
\ABCIaftercitex#*
\ABCIaux#*
\ABCIauxlen#*
\ABCIccomma#*
\ABCIcitation#*
\ABCIcitecolondefault#*
\ABCIcitecomma#*
\ABCIcitecommadefault#*
\ABCIcitelist#*
\ABCIcomma#*
\ABCIdemand{arg}#*
\ABCIfirst#*
\ABCIgetcitetext{arg1}#*
\ABCIgetcitetextecho{arg1}#*
\ABCIinitcitecomma#*
\ABCIlast#*
\ABCIlistwithoutmaximum{arg1}#*
\ABCInewblock#*
\ABCIoutputgroupedcitelist#*
\ABCIprocesscitetext#*
\ABCIscriptfont#*
\ABCIsortlist{arg1}#*
\ABCItemplist#*
\ABCItempslist#*
\ABCIthebibliformat#*
\ABCIthebiblihook#*
\ABCItoken{arg}#*
\AbntCitetype#*
\AbntCitetypeALF#*
\abntnextkey#*
\abntrefinfo{arg1}{arg2}{arg3}#*
\addtociteoptionlist{option}#*
\AfterTheBibliography{code}#*
\apudname#*
\bibciteEXPL{arg1}{arg2}#*
\bibciteIMPL{arg1}{arg2}#*
\bibciteYEAR{arg1}{arg2}#*
\biblabelsep#*
\biblabeltext#*
\cfcitename#*
\citeclose#*
\citeifnotcited{keylist}#*c
\citen[add. text]{keylist}#c
\citen{keylist}#*c
\citenum[add. text]{keylist}#c
\citenum{keylist}#*c
\citenumstyle#*
\citeonlineifnotcited{keylist}#*c
\citeopen#*
\citeoptionlist#*
\etseqname#*
\grabseven{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}#*
\grabsix{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#*
\hiddenbibitem{arg}#*
\Ibidemname#*
\Idemname#*
\ifcited{key}{true}{false}#*
\ifconsecutive{num1}{num2}{block1}{block2}#*
\IfSubStringInString{substring}{string}{true}{false}#*
\loccitname#*
\maximuminlist{list}#*
\minimumbiblabelwidth#*
\opcitname#*
\optionaltextstyle#*
\passimname#*
\setcitebrackets#*
\texforht#*
\theABCIaux#*
\theABCImax#*
\thebibliographyBkUp#S