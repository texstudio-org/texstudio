# covington package
# Matthew Bertucci 2023/06/02 for v2.10

#include:iftex

#keyvals:\usepackage/covington#c
force#true,false
keeplayout#true,false
noglossbreaks#true,false
owncounter#true,false
fnexamplecounter=#main,own,own-reset
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

\setexampleoptions{options%keyvals}

\begin{examples}
\begin{examples}[options%keyvals]
\end{examples}
\begin{covexamples}#*
\begin{covexamples}[options%keyvals]#*
\end{covexamples}#*

\examplenumbersep#*
\subexamplenumbersep#*
\exampleind#*

\expreamble{text}
\expostamble{text}

\begin{subexamples}
\begin{subexamples}[option%keyvals]
\end{subexamples}
\begin{covsubexamples}[option%keyvals]#*
\end{covsubexamples}#*

\subexpreamble{text}
\subexpostamble{text}

#keyvals:\begin{example},\begin{covexample},\begin{examples},\begin{covexamples},\begin{subexamples},\begin{covsubexamples},\setexampleoptions
fs={%<font settings%>}
fsno={%<font settings%>}
leftmargin=##L
addnumbersep=##L
numberformat={%<template%>}
fnnumberformat={%<template%>}
#endkeyvals

## keys with no effect in examples environment
#keyvals:\begin{example},\begin{covexample},\begin{subexamples},\begin{covsubexamples},\setexampleoptions
preamble={%<text%>}
postamble={%<text%>}
fspreamble={%<font settings%>}
fspostamble={%<font settings%>}
#endkeyvals

#keyvals:\begin{example},\begin{covexample},\setexampleoptions
postamble*={%<text%>}
#endkeyvals

## keys only for subexamples
#keyvals:\begin{subexamples},\begin{covsubexamples},\setexampleoptions
fssubpreamble={%<font settings%>}
fssubpostamble={%<font settings%>}
addsubnumbersep=##L
subnumberformat={%<template%>}
#endkeyvals

\covexnumber{arg}#*
\covexnumberfn{arg}#*
\covsubexnumber{arg}#*
\covexamplefs#*
\covexamplenofs#*
\expreamblefs#*
\subexpreamblefs#*
\expostamblefs#*
\subexpostamblefs#*
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
fstl={%<font settings%>}
enquotetl#true,false
preamble={%<text%>}
postamble={%<text%>}
fspreamble={%<font settings%>}
fspostamble={%<font settings%>}
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
\glosslinetrans{text}#*
\covenquote{text}#*
\glosslinepreamble#*
\glosslinepostamble#*
\psr{constituent}{sub-constituents}
\fs{contents}
\lfs{label%plain}{contents}
\drs{variables}{contents}
\sdrs{above-text%text}{variables}{contents}
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
\fsglpostamble#S
\fsglpreamble#S
\getwords#S
\gline#S
\glossglue#S
\glosslineone#S
\glosslinetwo#S
\glosslinethree#S
\ifforceredef#S
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
