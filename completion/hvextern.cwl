# hvextern package
# Matthew Bertucci 4/25/2022 for v0.19

#include:shellesc
#include:xkeyval
#include:graphicx
#include:marginnote
#include:fancyvrb
#include:tikz
#include:listings
#include:ifplatform
#include:tcolorbox
# loads skins and breakable tcolorbox libraries
# from breakable tcolorbox library
#include:pdfcol

\begin{externalDocument}{filename}
\begin{externalDocument}[options%keyvals]{filename}
\end{externalDocument}
\begin{ErstelleGrafik}{filename}#*
\begin{ErstelleGrafik}[options%keyvals]{filename}#*
\end{ErstelleGrafik}#*

#keyvals:\begin{externalDocument},\begin{ErstelleGrafik}
progpath=%<path%>
runsequence=
runs=%<integer%>
grfOptions={%<\includegraphics options%>}
lstOptions={%<listings options%>}
BGpreamble=#%color
BGbody=#%color
BOpreamble=#%color
BObody=#%color
docType=#context,lua,pl,tex,latex,mp,py
caption={%<text%>}
label=##l
pages={%<page numbers%>}
cropmargin=%<length in pt%>
mpwidth=##L
ext=%<file ext%>
usefancyvrb#true,false
showFilename#true,false
code#true,false
force#true,false
crop#true,false
biber#true,false
xindex#true,false
xindexOptions=
includegraphic#true,false
inline#true,false
frame#true,false
float#true,false
cleanup=
moveToExampleDir#true,false
align=
ExampleDir=
eps#true,false
verbose#true,false
compiler=
#endkeyvals

\PreambleVerbatim{file}#i
\PreambleVerbatim[options%keyvals]{file}#i
\BodyVerbatim{file}#i
\BodyVerbatim[options%keyvals]{file}#i

# fancyvrb options
#keyvals:\PreambleVerbatim,\BodyVerbatim
commentchar=%<single char%>
gobble=%<integer%>
formatcom=%<commands%>
formatcom*=%<commands%>
fontfamily=%<family%>
fontsize=%<size macro%>
fontshape=%<shape%>
fontseries=%<series%>
frame=#none,leftline,topline,bottomline,lines,single
framerule=##L
framesep=##L
rulecolor=%<color cmd%>
fillcolor=%<color cmd%>
label=%<label text%>
labelposition=#none,topline,bottomline,all
numbers=#none,left,right
numbersep=##L
firstnumber=%<auto|last|<integer>%>
stepnumber=%<integer%>
numberblanklines#true,false
firstline=%<integer%>
lastline=%<integer%>
showspaces#true,false
showtabs#true,false
obeytabs#true,false
tabsize=%<integer%>
baselinestretch=%<factor%>
commandchars=%<three chars%>
xleftmargin=##L
xrightmargin=##L
resetmargins#true,false
hfuzz=##L
samepage#true,false
codes={%<code%>}
codes*={%<code%>}
defineactive={%<code%>}
defineactive*={%<code%>}
reflabel=##l
fileext=%<extension%>
#endkeyvals

\PreambleListing{file}#i
\PreambleListing[options%keyvals]{file}#i
\BodyListing{file}#i
\BodyListing[options%keyvals]{file}#i

# listings options
#keyvals:\PreambleListing,\BodyListing
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

\LineWidth#*
\ResetKeys
\perCent#*
\DoubleperCent#*
\NumChar#*
\DoubleNumChar#*
\hvExternDateiname#*
\hvexternFileversion#S
\hvFileversion#S