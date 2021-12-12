# ltxdockit package
# Matthew Bertucci 11/5/2021 for v1.2d

#include:etoolbox
#include:listings
#include:color
#include:xspace
#include:ifpdf
#include:hyperref

\marglistwidth#*
\marglistsep#*
\marglistfont#*
\margnotefont#*
\optionlistfont#*
\ltxsyntaxfont#*
\ltxsyntaxlabelfont#*
\changelogfont#*
\changeloglabelfont#*
\verbatimfont#*
\displayverbfont#*
spot#B
boxframe#B
boxfill#B
\defaultcolor#*
\spotcolor#*

\cs{csname}
\cmd{csname}
\env{envname}
\len{length}
\cnt{counter}
\prm{arg}
\mprm{arg}
\oprm{arg}
\opt{arg}
\kvopt{key%plain}{value}
\file{filename}
\sty{arg}
\bin{arg}
\acr{arg}
\keyval

\begin{marglist}
\end{marglist}
\begin{keymarglist}
\end{keymarglist}

\refs{sing name}{plural name}{label}#r
\secref{label}#r
\Secref{label}#r
\apxref{label}#r
\Apxref{label}#r
\tabref{label}#r
\Tabref{label}#r

\begin{ltxsyntax}
\end{ltxsyntax}
\csitem{csname}
\cmditem{csname}
\cmditem{csname}[options]
\cmditem{csname}[options]{arg}
\envitem{envname}
\lenitem{length}
\boolitem{key%plain}
\boolitem[true or false]{key%plain}
\cntitem{counter}
\optitem{option}

\begin{optionlist}
\end{optionlist}
\begin{optionlist*}
\end{optionlist*}
\varitem{variable}
\valitem{value}
\choitem{key%plain}{values}
\choitem[opt]{key%plain}{values}
\intitem{key%plain}
\intitem[integer]{key%plain}
\legitem{arg}
  
\begin{valuelist}
\begin{valuelist}[opt]
\end{valuelist}
\begin{valuelist*}
\end{valuelist*}
\begin{argumentlist}{arg}
\end{argumentlist}
\begin{changelog}
\end{changelog}
\begin{release}{version}{date}
\end{release}
\see{label}#r

\lstenvsep#*

\begin{ltxcode}#V
\begin{ltxcode}[options%keyvals]#V
\end{ltxcode}
\begin{ltxexample}#V
\begin{ltxexample}[options%keyvals]#V
\end{ltxexample}

#keyvals:\begin{ltxcode},\begin{ltxexample}
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
texcs=
moretexcs=
deletetxcs=
directives=
moredirectives=
deletedirectives=
sensitive#true,false
alsoletter={%<character sequence%>}
alsodigit={%<character sequence%>}
alsoother={%<character sequence%>}
otherkeywords={%<keywords%>}
tag=
string=
morestring=
deletestring=
comment=
morecomment=
deletecomment=
keywordcomment={%<keywords%>}
morekeywordcomment={%<keywords%>}
deletekeywordcomment={%<keywords%>}
keywordcommentsemicolon={%<keywords%>}{%<keywords%>}{%<keywords%>}
podcomment#true,false
#endkeyvals
