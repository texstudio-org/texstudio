# cnltx-example package
# Matthew Bertucci 10/18/2021 for v0.15

#include:cnltx-listings
#include:cnltx-translations
#include:mdframed
#include:idxcmds
#include:textcomp
#include:adjustbox
#include:ifxetex
#include:ulem

\code{arg}
\verbcode|%<text%>|
\verbcode{verbatimSymbol}#S
\cs{name}
\cs*{name}
\csidx{name}
\env{name}
\env*{name}
\envidx{name}
\beginend{text}#*
\beginenv
\beginenv*
\endenv
\endenv*
\meta{meta}
\marg{arg}
\Marg{arg}
\oarg{arg}
\Oarg{arg}
\darg{arg}
\Darg{arg}
\sarg

\newarg{cmd}{left delim}{right delim}#d
\newarg[formatting]{cmd}{left delim}{right delim}#d

\option{name}
\option*{name}
\optionidx{name}
\module{name}
\module*{name}
\moduleidx{name}
\key{name}{value}
\key*{name}{value}
\key-{name}{value}
\keyis{name}{value}
\keyis*{name}{value}
\keyis-{name}{value}
\choices{list of choices}
\choicekey{name}{list of choices}
\boolkey{name}
\default{value}

\pkg{package}
\pkg*{package}
\pkgidx{package}
\cls{class}
\cls*{class}
\clsidx{class}
\bnd{bundle}
\bnd*{bundle}
\bnd{bundle}

\inputexample{file}#i
\inputexample[options%keyvals]{file}#i
\inputsidebyside{file}#i
\inputsidebyside[options%keyvals]{file}#i
\inputsourcecode{file}
\inputsourcecode[options%keyvals]{file}
\implementation{file}
\implementation[options%keyvals]{file}

#keyvals:\implementation
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

\newinputsourcefilecmd{cmd}
\newinputsourcefilecmd[options%keyvals]{cmd}

\begin{example}
\begin{example}[options%keyvals]
\end{example}
\begin{sidebyside}
\begin{sidebyside}[options%keyvals]
\end{sidebyside}
\begin{sourcecode}#V
\begin{sourcecode}[options%keyvals]#V
\end{sourcecode}
\begin{bash}#V
\begin{bash}[options%keyvals]#V
\end{bash}

\newsourcecodeenv{envname}#N
\newsourcecodeenv[options%keyvals]{envname}#N

#keyvals:\setcnltx#c,\inputexample,\inputsidebyside,\inputsourcecode,\newinputsourcefilecmd,\begin{example},\begin{sidebyside},\begin{sourcecode},\newsourcecodeenv
side-by-side#true,false
code-only#true,false
code-left#true,false
compile#true,false
code-sep={%<definitions%>}
pre-code={%<definitions%>}
after-code={%<definitions%>}
pre-output={%<definitions%>}
after-output={%<definitions%>}
add-frame-options={%<mdframed options%>}
frame-options={%<mdframed options%>}
add-local-frame={%<mdframed options%>}
local-frame={%<mdframed options%>}
gobble=%<integer%>
add-cmds={%<list of csnames%>}
add-silent-cmds={%<list of csnames%>}
listings-options={%<listings options%>}
add-listings-options={%<listings options%>}
add-sourcecode-options={%<listings options%>}
sourcecode-options={%<listings options%>}
add-envs={%<list of envnames%>}
add-silent-envs={%<list of envnames%>}
max-pages=%<number%>
max-height=##L
pages={%<specs%>}
runs=%<number%>
program=#pdflatex,lualatex,xelatex,arara
file-ext=%<extension%>
exe-with={%<options%>}
graphics={%<options%>}
float#true,false
float-env=%<envname%>
caption={%<text%>}
float-pos={%<float parameters%>}
outside#true,false
add-frame#true,false
before-skip=##L
after-skip=##L
#endkeyvals

\codefont#*
\sourceformat#*
\exampleformat#*
\versionnoteformat#*
\packageformat#*
\classformat#*
\argumentformat#*

#keyvals:\setcnltx#c
title-format={%<definitions%>}
abstract-width=##L
abstract-format={%<definitions%>}
caption-font={%<definitions%>}
caption-label-font={%<definitions%>}
code-font={%<definitions%>}
source-format={%<definitions%>}
expl-format={%<definitions%>}
module-sep={%<definitions%>}
version-note-format={%<definitions%>}
pkg-format={%<definitions%>}
cls-format={%<definitions%>}
arg-format={%<definitions%>}
deafult-format={%<definitions%>}
#endkeyvals

\indexcs{name}#*
\indexenv{name}#*
\MakePercentComment#*
