# covington package
# Matthew Bertucci 2022/08/31 for v2.8

#include:xkeyval
#include:iftex

#keyvals:\usepackage/covington#c
force
keeplayout
noglossbreaks
owncounter
ownfncounter
ownfncounter*
#endkeyvals

\twodias{upper diac}{lower diac}{char}
\acm{arg}
\grm{arg}
\cim{arg}
\SetDiaOffset{length}#*
\twoacc[%<upper%>|%<lower%>]#*
\exampleno
\exampleno*

\begin{example}
\begin{example}[options%keyvals]
\end{example}
\begin{covexample}#*
\begin{covexample}[options%keyvals]#*
\end{covexample}#*

#keyvals:\begin{example},\begin{covexample}
preamble={%<text%>}
#endkeyvals

\examplenumbersep#*
\subexamplenumbersep#*
\exampleind#*

\begin{examples}
\end{examples}
\begin{covexamples}#*
\end{covexamples}#*

\begin{subexamples}
\begin{subexamples}[option%keyvals]
\end{subexamples}
\begin{covsubexamples}[option%keyvals]#*
\end{covsubexamples}#*

#keyvals:\begin{subexamples},\begin{covsubexamples}
preamble={%<text%>}
#endkeyvals

\covexnumber{arg}#*
\covexnumberfn{arg}#*
\covsubexnumber{arg}#*
\covexamplefs#*
\covexamplenofs#*
\subexpreamblefs#*
\expreamblefs#*
\thecovfnex#*
\pxref{label}#r
\digloss[options%keyvals]{glossline1}{glossline2}{translation}
\trigloss[options%keyvals]{glossline1}{glossline2}{glossline3}{translation}
\setglossoptions{options%keyvals}

#keyvals:\digloss,\trigloss,\setglossoptions
ex#true,false
tlr#true,false
fsi={%<font settings%>}
fsii={%<font settings%>}
fsiii={%<font settings%>}
preamble={%<text%>}
postamble={%<text%>}
#endkeyvals

\gll#*
\glll#*
\xgll#*
\xglll#*
\xgle#*
\glt#*
\gln#*
\glot{translation}#*
\glosspreamble{text}#*
\glend#*
\glosslineone#*
\glosslinetwo#*
\glosslinethree#*
\glosslinetrans{text}#*
\covenquote{text}#*
\glosslinepreamble#*
\glosslinepostamble#*
\psr{constituent}{sub-constituents}
\fs{contents}
\lfs{label%plain}{contents}
\drs{variables}{contents}
\sdrs{above-text}{variables}{contents}
\negdrs{variables}{contents}
\ifdrs{variables1}{contents1}{variables2}{contents2}
\alifdrs{variables1}{contents1}{variables2}{contents2}
\begin{exercise}
\begin{exercise}[name]
\end{exercise}
\begin{covexercise}#*
\begin{covexercise}[name]#*
\end{covexercise}#*
\begin{reflist}
\end{reflist}
\reflistindent#*
\reflistitemsep#*
\reflistparsep#*
\sentence{text}
\sentencefs#*
\lexp{word}
\lcon{concept}
\lmean{meaning}
\either{top}{bottom}
\twoaccsep#*

# not documented
\bx#S
\donewords#S
\eachwordone#S
\eachwordthree#S
\eachwordtwo#S
\ex#S
\filedate#S
\filename#S
\fileversion#S
\forceredeffalse#S
\forceredeftrue#S
\getwords#S
\gexamplefalse#S
\gexampletrue#S
\ggexamplefalse#S
\ggexampletrue#S
\ggtrightfalse#S
\ggtrighttrue#S
\gline#S
\glossglue#S
\gtrightfalse#S
\gtrighttrue#S
\ifforceredef#S
\ifgexample#S
\ifggexample#S
\ifggtright#S
\ifgtright#S
\ifnoglossbreaks#S
\ifnotdone#S
\ifownexcounter#S
\ifownfnexcounter#S
\ifresetownfnexcounter#S
\iftweaklayout#S
\lastword{arg1}{arg2}{arg3}#S
\lglosslineone#S
\lglosslinethree#S
\lglosslinetwo#S
\lineone#S
\linethree#S
\linetwo#S
\more#S
\noglossbreaksfalse#S
\noglossbreakstrue#S
\notdonefalse#S
\notdonetrue#S
\ownexcounterfalse#S
\ownexcountertrue#S
\ownfnexcounterfalse#S
\ownfnexcountertrue#S
\resetownfnexcounterfalse#S
\resetownfnexcountertrue#S
\testdone#S
\thecovex#*
\threesent#S
\tweaklayoutfalse#S
\tweaklayouttrue#S
\twosent#S
\wordone#S
\wordthree#S
\wordtwo#S
\xdonewords#S
\xgetwords#S
\xthreesent#S
\xtwosent#S
