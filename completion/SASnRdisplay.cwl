# SASnRdisplay package
# Matthew Bertucci 10/14/2021 for v0.95

#include:listings
#include:xkeyval
#include:xcolor
#include:etoolbox
#include:caption
#include:needspace

#keyvals:\usepackage/SASnRdisplay#c
danish
english
grayscale
countbysection
countbychapter
consecutive
countbylistings
noautotitles-r
noautotitles-sas
needspace=##L
noneedspace
sweave
sasweave
#endkeyvals

\begin{SAScode}#V
\begin{SAScode}[options%keyvals]#V
\end{SAScode}
\begin{SAScode*}#V
\begin{SAScode*}[options%keyvals]#V
\end{SAScode*}
\begin{SASoutput}#V
\begin{SASoutput}[options%keyvals]#V
\end{SASoutput}
\begin{SASoutput*}#V
\begin{SASoutput*}[options%keyvals]#V
\end{SASoutput*}
\begin{Rcode}#V
\begin{Rcode}[options%keyvals]#V
\end{Rcode}
\begin{Rcode*}#V
\begin{Rcode*}[options%keyvals]#V
\end{Rcode*}
\begin{Routput}#V
\begin{Routput}[options%keyvals]#V
\end{Routput}
\begin{Routput*}#V
\begin{Routput*}[options%keyvals]#V
\end{Routput*}

\inputSAScode{file}
\inputSAScode[options%keyvals]{file}
\inputSAScode*{file}
\inputSAScode*[options%keyvals]{file}
\inputSASoutput{file}
\inputSASoutput[options%keyvals]{file}
\inputSASoutput*{file}
\inputSASoutput*[options%keyvals]{file}
\inputRcode{file}
\inputRcode[options%keyvals]{file}
\inputRcode*{file}
\inputRcode*[options%keyvals]{file}
\inputRoutput{file}
\inputRoutput[options%keyvals]{file}
\inputRoutput*{file}
\inputRoutput*[options%keyvals]{file}

\SASinline|%<code%>|
\SASinline[%<options%>]|%<code%>|
\SASinline[options%keyvals]{verbatimSymbol}#S
\Rinline|%<code%>|
\Rinline[%<options%>]|%<code%>|
\Rinline[options%keyvals]{verbatimSymbol}#S

#keyvals:\begin{SAScode},\begin{SAScode*},\begin{SASoutput},\begin{SASoutput*},\begin{Rcode},\begin{Rcode*},\begin{Routput},\begin{Routput*},\inputSAScode,\inputSAScode*,\inputSASoutput,\inputSASoutput*,\inputRcode,\inputRcode*,\inputRoutput,\inputRoutput*,\SASinline,\Rinline
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

#ifOption:procnames
#keyvals:\lstset,\lstinline,\begin{lstlisting},\lstinputlisting
procnamekeys={%<keywords%>}
moreprocnamekeys={%<keywords%>}
deleteprocnamekeys={%<keywords%>}
procnamestyle=%<style%>
indexprocnames#true,false
#endkeyvals
#endif

#ifOption:hyper
#keyvals:\lstset,\lstinline,\begin{lstlisting},\lstinputlisting
hyperref={%<identifiers%>}
morehyperref={%<identifiers%>}
deletehyperref={%<identifiers%>}
hyperanchor=%<two-parameter macro%>
hyperlink=%<two-parameter macro%>
#endkeyvals
#endif

#ifOption:lgrind
#keyvals:\lstset,\lstinline,\begin{lstlisting},\lstinputlisting
lgrindef=%<language%>
#endkeyvals
\lstlgrindeffile
#endif

#ifOption:formats
\lstdefineformat{name}{format}
\lstformatfiles#*
#endif

\SnRRcodename#*
\SnRSAScodename#*
\SnRRoutputname#*
\SnRSASoutputname#*

SnRBG#B
SnRFrame#B
SnRBGGray#B
SnRFrameGray#B

\SnRversion#S
