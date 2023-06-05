# ctxdoc class
# Matthew Bertucci 2022-07-26 for release 2022-06-07

#include:class-l3doc
#include:ctex
# loads heading option of ctex
#include:multitoc
#include:geometry
#include:tabularx
#include:makecell
#include:threeparttable
#include:siunitx
#include:unicode-math
#include:xcolor
#include:caption
#include:fancyvrb-ex
#include:zref-base

#keyvals:\documentclass/ctxdoc#c
# options passed to l3doc class
full
onlydoc
check
nocheck
checktest
nochecktest
kernel
stdmodule
cm-default
lm-default
cs-break-off
cs-break-nohyphen
show-notes
hide-notes
# options passed to article class
a4paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

\email{email%URL}#U
\ctexdocverbaddon#*
\ctexdisableecglue#*
\ctexplainps#*
\begin{arguments}[options%keyvals]
\begin{optdesc}
\begin{optdesc}[options%keyvals]
\end{optdesc}
\begin{tablenotes}[options%keyvals]
\TPTtagStyle{link text}
\begin{frameverb}#V
\begin{frameverb}[options%keyvals]
\end{frameverb}
\begin{ctexexam}#V
\begin{ctexexam}[options%keyvals]
\end{ctexexam}
\ctexexamlabelref#*
\thectexexam#*
\ctexsetverticalspacing#*
\ctexfixverticalspacing#*
\SideBySideExampleSet
\exptarget
\rexptarget
\expstar
\rexpstar
\zihaopt{size}
\StopSpecialIndexModule
\package{package}
\package[CTAN path%URL]{package}
\GetFileId{file}
\orbar#*
\defaultval{value}
\defaultvalaux{value}
\TF
\TTF
\TFF
\opt{option}
\XeLaTeX
\LuaLaTeX
\pdfLaTeX
\LaTeXiii
\dvipdfmx
\TeXLive
\MiKTeX
\ApTeX
\ApLaTeX
\upLaTeX
\bashcmd{command%plain}
\BSTACK#*
\ESTACK#*
\begin{defaultcapconfig}
\end{defaultcapconfig}
\ctexkit
\ctexkitrev{commit}
\IndexLayout

#keyvals:\begin{arguments}#c,\begin{optdesc}#c,\begin{tablenotes}#c
topsep=##L
partopsep=##L
parsep=##L
itemsep=##L
leftmargin=##L
rightmargin=##L
listparindent=##L
labelwidth=##L
labelsep=##L
itemindent=##L
label=%<commands%>
label*=%<commands%>
ref=%<commands%>
font=%<commands%>
format=%<commands%>
align=#left,right,parleft
labelindent=##L
left=%<labelindent%>
left=%<labelindent%> .. %<leftmargin%>
widest
widest=%<string%>
widest*=%<integer%>
labelsep*=##L
labelindent*=##L
start=%<integer%>
resume
resume=%<series name%>
resume*
resume*=%<series name%>
series=%<series name%>
beginpenalty=%<integer%>
midpenalty=%<integer%>
endpenalty=%<integer%>
before=%<code%>
before*=%<code%>
after=%<code%>
after*=%<code%>
first=%<code%>
first*=%<code%>
style=#standard,unboxed,nextline,sameline,multiline
noitemsep
nosep
wide
wide=%<parindent%>
itemjoin=%<string%>
itemjoin*=%<string%>
afterlabel=%<string%>
mode=#unboxed,boxed
#endkeyvals

#keyvals:\begin{frameverb},\begin{ctexexam}
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
vspace=##L
listparameters={%<code%>}
#endkeyvals

#keyvals:\begin{ctexexam}
labelref=##l
#endkeyvals

# from heading option of ctex
\CTEXnumberline{arg}#*
