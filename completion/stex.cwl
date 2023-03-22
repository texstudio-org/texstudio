# stex package
# Matthew Bertucci 2023/03/22 for v3.3.0

#include:l3keys2e
#include:ltxcmds
#include:stex-logo
#include:standalone
#include:babel
#include:stex-tikzinput

### < Basics > ###
#keyvals:\usepackage/stex#c
lang=%<language%>
mathhub=%<directory%>
writesms#true,false
usems#true,false
image#true,false
debug=%<log-prefix%>
checkterms#true,false
#endkeyvals

\libinput{file}#i
\libusepackage{package}#u
\libusepackage[options]{package}#u
\addmhbibresource{bib file}
\addmhbibresource[archive]{bib file}
\libusetikzlibrary{library}
\ifstexhtml
\stexhtmlfalse#S
\stexhtmltrue#S
\STEXinvisible{code}

### < Document Features > ###
\begin{sfragment}{title}
\begin{sfragment}[keyvals]{title}
\end{sfragment}

#keyvals:\begin{sfragment}
id=##l
short=%<short title%>
#endkeyvals

\begin{blindfragment}
\end{blindfragment}
\skipfragment
\setsectionlevel{level}
\currentsectionlevel
\Currentsectionlevel
\inputref{file}#i
\inputref[archive]{file}#i
\mhinput{file}#i
\mhinput[archive]{file}#i
\ifinputref
\inputreftrue#S
\inputreffalse#S
\IfInputref{true}{false}

\mhgraphics{imagefile}#g
\mhgraphics[options%keyvals]{imagefile}#g
\cmhgraphics{imagefile}#g
\cmhgraphics[options%keyvals]{imagefile}#g

#keyvals:\mhgraphics,\cmhgraphics
archive=%<file path%>
# graphicx keys
alt={%<alt text%>}
bb=%<llx lly urx ury%>
bbllx=
bblly=
bburx=
bbury=
natwidth=
natheight=
hiresbb#true,false
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
viewport=%<llx lly urx ury%>
trim=%<llx lly urx ury%>
angle=%<degrees%>
origin=
width=##L
height=##L
totalheight=##L
keepaspectratio#true,false
scale=%<factor%>
clip#true,false
draft#true,false
type=%<file type%>
ext=%<file extension%>
read=%<read-file extension%>
command=
quiet
page=%<page number%>
interpolate#true,false
decodearray={%<color array%>}
#endkeyvals

\lstinputmhlisting{file}
\lstinputmhlisting[options%keyvals]{file}
\clstinputmhlisting{file}
\clstinputmhlisting[options%keyvals]{file}

#keyvals:\lstinputmhlisting,\clstinputmhlisting
inputpath=%<path%>
aboveskip=##L
belowskip=##L
lineskip=##L
boxpos=#b,c,t
print#true,false
showlines#true,false
emptylines=%<number%>
emptylines=*%<number%>
gobble=%<number%>
style=%<style name%>
language=%<language%>
language=[%<dialect%>]%<language%>
alsolanguage=%<language%>
alsolanguage=[%<dialect%>]%<language%>
defaultdialect=[%<dialect%>]%<language%>
printpod#true,false
usekeywordsintag#true,false
tagstyle=%<style%>
markfirstintag=%<style%>
makemacrouse#true,false
basicstyle=%<style%>
identifierstyle=%<style%>
commentstyle=%<style%>
stringstyle=%<style%>
keywordstyle=%<style%>
keywordstyle=[%<number%>]%<style%>
keywordstyle=[%<number%>]*%<style%>
ndkeywordstyle=%<style%>
classoffset=%<number%>
texcsstyle=%<style%>
texcsstyle=[%<class number%>]%<style%>
texcsstyle=*[%<class number%>]%<style%>
directivestyle=%<style%>
emph={%<identifier list%>}
emph=[%<number%>]{%<identifier list%>}
moreemph={%<identifier list%>}
moreemph=[%<number%>]{%<identifier list%>}
deleteemph={%<identifier list%>}
deleteemph=[%<number%>]{%<identifier list%>}
emphstyle={%<style%>}
emphstyle=[%<number%>]{%<style%>}
delim=[%<type%>][%<style%>]%<delimiters%>
delim=*[%<type%>][%<style%>]%<delimiters%>
delim=**[%<type%>][%<style%>]%<delimiters%>
moredelim=[%<type%>][%<style%>]%<delimiters%>
moredelim=*[%<type%>][%<style%>]%<delimiters%>
moredelim=**[%<type%>][%<style%>]%<delimiters%>
deletedelim=[%<type%>][%<style%>]%<delimiters%>
deletedelim=*[%<type%>][%<style%>]%<delimiters%>
deletedelim=**[%<type%>][%<style%>]%<delimiters%>
extendedchars#true,false
inputencoding=%<encoding%>
upquote#true,false
tabsize=%<number%>
showtabs#true,false
tab=%<tokens%>
showspaces#true,false
showstringspaces#true,false
formfeed=%<tokens%>
numbers=#none,left,right
stepnumber=%<number%>
numberfirstline#true,false
numberstyle=%<style%>
numbersep=##L
numberblanklines#true,false
firstnumber=%<auto|last|<number>%>
name=%<name%>
title=%<title text%>
caption={%<caption text%>}
caption={[%<short%>]%<caption text%>}
label=##l
nolol#true,false
numberbychapter#true,false
captionpos=%<subset of tb%>
abovecaptionskip=##L
belowcaptionskip=##L
linewidth=##L
xleftmargin=##L
xrightmargin=##L
resetmargins#true,false
breaklines#true,false
breakatwhitespace#true,false
prebreak=%<tokens%>
postbreak=%<tokens%>
breakindent=##L
breakautoindent#true,false
frame=%<type%>
frameround=
framesep=##L
rulesep=##L
framerule=##L
framexleftmargin=##L
framexrightmargin=##L
framextopmargin=##L
framexbottommargin=##L
backgroundcolor=#%color
rulecolor=#%color
fillcolor=#%color
rulesepcolor=#%color
frameshape={%<top shape%>}{%<left shape%>}{%<right shape%>}{%<bottom shape%>}
index={%<identifiers%>}
index=[%<number%>]{%<identifiers%>}
index=[%<number%>][%<keyword classes%>]{%<identifiers%>}
moreindex={%<identifiers%>}
moreindex=[%<number%>]{%<identifiers%>}
moreindex=[%<number%>][%<keyword classes%>]{%<identifiers%>}
deleteindex={%<identifiers%>}
deleteindex=[%<number%>]{%<identifiers%>}
deleteindex=[%<number%>][%<keyword classes%>]{%<identifiers%>}
indexstyle=%<one-parameter macro%>
indexstyle=[%<number%>]%<one-parameter macro%>
columns=%<alignment%>
columns=[%<c|l|r%>]%<alignment%>
flexiblecolumns#true,false
keepspaces#true,false
basewidth=##L
fontadjust#true,false
texcl#true,false
mathescape#true,false
escapechar=%<character%>
escapeinside=%<<char1><char2>%>
escapebegin=%<tokens%>
escapeend=%<tokens%>
fancyvrb#true,false
fvcmdparams=%<<cmd1> <num1> ...%>
morefvcmdparams=%<<cmd1> <num1> ...%>
literate={%<replace%>}{%<replacement text%>}{%<length%>}%<...%>
literate=*{%<replace%>}{%<replacement text%>}{%<length%>}%<...%>
rangebeginprefix=%<prefix%>
rangebeginsuffix=%<suffix%>
rangeendprefix=%<prefix%>
rangeendsuffix=%<suffix%>
rangeprefix=%<prefix%>
rangesuffix=%<suffix%>
includerangemarker#true,false
multicols=%<number%>
float
float=%<subset of tbph%>
float=*%<subset of tbph%>
floatplacement=%<place specifiers%>
firstline=%<number%>
lastline=%<number%>
linerange={%<first1-last1,first2-last2,...%>}
consecutivenumbers#true,false
keywordsprefix=%<prefix%>
keywords={%<list of keywords%>}
keywords=[%<number%>]{%<list of keywords%>}
morekeywords={%<list of keywords%>}
morekeywords=[%<number%>]{%<list of keywords%>}
deletekeywords={%<list of keywords%>}
deletekeywords=[%<number%>]{%<list of keywords%>}
ndkeywords={%<list of keywords%>}
moreendkeywords={%<list of keywords%>}
deleteendkeywords={%<list of keywords%>}
texcs={%<list of csnames%>}
texcs=[%<class number%>]{%<list of csnames%>}
moretexcs={%<list of csnames%>}
moretexcs=[%<class number%>]{%<list of csnames%>}
deletetexcs={%<list of csnames%>}
deletetexcs=[%<class number%>]{%<list of csnames%>}
directives={%<list of compiler directives%>}
moredirectives={%<list of compiler directives%>}
deletedirectives={%<list of compiler directives%>}
sensitive#true,false
alsoletter={%<character sequence%>}
alsodigit={%<character sequence%>}
alsoother={%<character sequence%>}
otherkeywords={%<keywords%>}
tag=%<<char1><char2>%>
string=%<delimiter%>
string=[%<b|d|m|bd|s%>]%<delimiter%>
morestring=%<delimiter%>
morestring=[%<b|d|m|bd|s%>]%<delimiter%>
deletestring=%<delimiter%>
deletestring=[%<b|d|m|bd|s%>]%<delimiter%>
comment=%<delimiter(s)%>
comment=[%<type%>]%<delimiter(s)%>
morecomment=%<delimiter(s)%>
morecomment=[%<type%>]%<delimiter(s)%>
deletecomment=%<delimiter(s)%>
deletecomment=[%<type%>]%<delimiter(s)%>
keywordcomment={%<keywords%>}
morekeywordcomment={%<keywords%>}
deletekeywordcomment={%<keywords%>}
keywordcommentsemicolon={%<keywords%>}{%<keywords%>}{%<keywords%>}
podcomment#true,false
#endkeyvals

\sref{label}#r
\sref[options]{label}#r
\sref[options1]{label}[options2]#r
\srefsetin{file}{title%text}
\srefsetin[archive]{file}{title%text}
\sreflabel{label}#l
\extref{label}{keyvals}#r
\extref[options]{label}{keyvals}#r

### < Modules and Symbols > ###
\begin{smodule}{module}
\begin{smodule}[options%keyvals]{module}
\end{smodule}

#keyvals:\begin{smodule}
title={%<text%>}
style=
id=##l
ns=%<URI%>
lang=%<language%>
sig=%<language%>
#endkeyvals

\STEXexport{code}
\symdecl{name}
\symdecl{name}[options]
\symdecl*{name}
\symdecl*{name}[options]
\textsymdecl{name}{definition}
\textsymdecl{name}[options]{definition}
\symdef{name}{definition}
\symdef{name}[options]{definition}
\symref{name}{text}
\sr{name}{text}

\symname{name}
\symname[options%keyvals]{name}
\sn{name}
\sn[options%keyvals]{name}
\Symname{name}
\Symname[options%keyvals]{name}
\Sn{name}
\Sn[options%keyvals]{name}

#keyvals:\symname,\sn,\Symname,\Sn
pre=
post=
#endkeyvals

\sns{name}
\Sns{name}
\srefsym{name}{text}
\srefsymuri{URI}{text}
\symuse{name}
\notation{name}{definition}
\notation{name}[options]{definition}
\notation*{name}{definition}
\notation*{name}[options]{definition}
\comp{component}
\maincomp{component}
\setnotation{name}{id}
\infprec
\neginfprec
\dobrackets{code}
\withbrackets{left}{right}{code}
\argsep{parameter token}{separator}
\argmap{parameter token}{code}{separator}
\argarraymap{arg1}{arg2}{arg3}{arg4}#*
\arg{code}
\arg[i]{code}
\arg*{code}
\arg*[i]{code}
\usemodule{module}
\usemodule[archive]{module}
\requiremodule{module}#*
\requiremodule[archive]{module}#*
\importmodule{module}
\importmodule[archive]{module}
\vardef{name}{definition}
\vardef{name}[options]{definition}
\varnotation{name}{definition}
\varnotation{name}[options]{definition}
\svar{text}
\svar[name]{text}
\varseq{name}{range}{definition}
\varseq{name}[options]{range}{definition}
\ellipses
\seqmap{code}{sequence}
\begin{mathstructure}{name}
\begin{mathstructure}{name}[options]
\end{mathstructure}
\this
\begin{extstructure}{name}{structs}
\begin{extstructure}{name}[options]{structs}
\end{extstructure}
\begin{extstructure*}{name}{struct}
\end{extstructure*}
\usestructure{struct}

### < Statements > ###
\begin{sdefinition}
\begin{sdefinition}[options]
\end{sdefinition}
\begin{sassertion}
\begin{sassertion}[options]
\end{sassertion}
\begin{sexample}
\begin{sexample}[options]
\end{sexample}
\begin{sparagraph}
\begin{sparagraph}[options]
\end{sparagraph}
\inlineass{text}
\inlineass[options]{text}
\inlinedef{text}
\inlinedef[options]{text}
\inlineex{text}
\inlineex[options]{text}
\varbind{cls}
\definiendum{name}{code}
\definame{name}
\definame[options]{name}
\Definame{name}
\Definame[options]{name}
\defnotation{code}
\definiens{code}
\definiens[name]{code}
\premise{text}
\conclusion{text}
\conclusion[symbol]{text}
\begin{sproof}
\begin{sproof}[options]
\end{sproof}

## < Customizing Typesetting > ##
\symrefemph{text}#*
\compemph{text}#*
\defemph{text}#*
\varemph{text}#*
\stexstylemodule{definition}#*
\stexstylemodule[style]{definition}#*
\stexstylecopymodule{definition}#*
\stexstylecopymodule[style]{definition}#*
\stexstyleinterpretmodule{definition}#*
\stexstyleinterpretmodule[style]{definition}#*
\stexstylerealization{definition}#*
\stexstylerealization[style]{definition}#*
\stexstylemathstructure{definition}#*
\stexstylemathstructure[style]{definition}#*
\stexstyleextstructure{definition}#*
\stexstyleextstructure[style]{definition}#*
\stexstyledefinition{definition}#*
\stexstyledefinition[style]{definition}#*
\stexstyleassertion{definition}#*
\stexstyleassertion[style]{definition}#*
\stexstyleexample{definition}#*
\stexstyleexample[style]{definition}#*
\stexstyleparagraph{definition}#*
\stexstyleparagraph[style]{definition}#*
\stexstyleproof{definition}#*
\stexstyleproof[style]{definition}#*
\stexstylesubproof{definition}#*
\stexstylesubproof[style]{definition}#*
\stexstyleusemodule{definition}#*
\stexstyleusemodule[style]{definition}#*
\stexstyleimportmodule{definition}#*
\stexstyleimportmodule[style]{definition}#*
\stexstylerequiremodule{definition}#*
\stexstylerequiremodule[style]{definition}#*
\stexstyleassign{definition}#*
\stexstyleassign[style]{definition}#*
\stexstylerenamedecl{definition}#*
\stexstylerenamedecl[style]{definition}#*
\stexstyleassignMorphism{definition}#*
\stexstyleassignMorphism[style]{definition}#*
\stexstylecopymod{definition}#*
\stexstylecopymod[style]{definition}#*
\stexstyleinterpretmod{definition}#*
\stexstyleinterpretmod[style]{definition}#*
\stexstylerealize{definition}#*
\stexstylerealize[style]{definition}#*
\stexstylesymdecl{definition}#*
\stexstylesymdecl[style]{definition}#*
\stexstyletextsymdecl{definition}#*
\stexstyletextsymdecl[style]{definition}#*
\stexstylenotation{definition}#*
\stexstylenotation[style]{definition}#*
\stexstylevarnotation{definition}#*
\stexstylevarnotation[style]{definition}#*
\stexstylesymdef{definition}#*
\stexstylesymdef[style]{definition}#*
\stexstylevardef{definition}#*
\stexstylevardef[style]{definition}#*
\stexstylevarseq{definition}#*
\stexstylevarseq[style]{definition}#*
\stexstylespfsketch{definition}#*
\stexstylespfsketch[style]{definition}#*
\stexstyleMMTinclude{definition}#*
\stexstyleMMTinclude[style]{definition}#*

# not documented
\assign{arg1}{arg2}#S
\assignMorphism#S
\assumption{text}#S
\begin{copymodule}{arg1}{arg2}#S
\begin{interpretmodule}{arg1}{arg2}#S
\begin{mmtinterface}[opt]{arg1}{arg2}#S
\begin{mmtinterface}{arg1}{arg2}#S
\begin{realization}[optarg1]{arg2}#S
\begin{realization}{arg1}#S
\begin{spfblock}#S
\begin{subproof}[options]{text}#S
\begin{subproof}{text}#S
\conclude[options]{text}#S
\conclude{text}#S
\end{copymodule}#S
\end{interpretmodule}#S
\end{mmtinterface}#S
\end{realization}#S
\end{spfblock}#S
\end{subproof}#S
\eqstep*{text}#S
\eqstep{text}#S
\mathhub#S
\mmlarg{arg1}{arg2}#S
\mmlintent{arg1}{arg2}#S
\mmtdef{arg}#S
\mmtdef{arg}[opt]#S
\MMTinclude{arg1}#S
\MMTrule{arg1}{arg2}#S
\MSC{arg1}#S
\realize{arg1}{arg2}#S
\renamedecl[optarg1]{arg2}{arg3}#S
\renamedecl{arg1}{arg2}#S
\spfjust{text}#S
\spfstep[options]{text}#S
\spfstep{text}#S
\sproofend#S
\stexcommentfont#S
\stexdoctitle{arg}#S
\STEXInternalSetSrefSymURL{arg1}{arg2}#S
\STEXInternalSrefRestoreTarget{arg1}{arg2}{arg3}{arg4}{arg5}#S
\STEXInternalSymbolAfterInvokationTL#S
\STEXInternalTermMathArgiii{arg1}{arg2}{arg3}#S
\STEXInternalTermMathAssocArgiiiii{arg1}{arg2}{arg3}{arg4}{arg5}#S
\STEXRestoreNotsEnd#S
\thisarchive#S
\thiscopyname#S
\thismodulename#S
\thismoduleuri#S
\thisstyle#S
\thistitle#S
\yield{text}#S
