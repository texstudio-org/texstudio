# SASnRdisplay package
# Matthew Bertucci 10/14/2021 for v0.95

#include:listings
#include:xkeyval
#include:xcolor
#include:etoolbox
#include:caption
#include:needspace

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
delim=
moredelim=
deletedelim=
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
firstnumber=
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
frame=
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
index=
moreindex=
deleteindex=
indexstyle=
columns=
flexiblecolumns#true,false
keepspaces#true,false
basewidth=##L
fontadjust#true,false
texcl#true,false
mathescape#true,false
escapechar=%<character%>
escapeinside=
escapebegin=%<tokens%>
escapeend=%<tokens%>
fancyvrb#true,false
fvcmdparams=
morefvcmdparams=
literate=
rangebeginprefix=
rangebeginsuffix=
rangeendprefix=
rangeendsuffix=
rangeprefix=
rangesuffix=
includerangemarker#true,false
multicols=%<number%>
float
float=%<subset of tbph%>
float=*%<subset of tbph%>
floatplacement=
firstline=%<number%>
lastline=%<number%>
linerange={%<first1-last1,first2-last2,...%>}
consecutivenumbers#true,false
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
hyperanchor=
hyperlink=
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