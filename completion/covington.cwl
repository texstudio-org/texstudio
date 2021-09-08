# covington package
# Matthew Bertucci 9/7/2021 for v2.7

#include:iftex

\twodias{upper diac}{lower diac}{char}
\acm{arg}
\grm{arg}
\cim{arg}
\SetDiaOffset{length}#*
\exampleno
\exampleno*
\begin{example}
\end{example}
\begin{covexample}#*
\end{covexample}#*
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
\covsubexnumber{arg}#*
\covexamplefs#*
\covexamplenofs#*
\subexpreamblefs#*
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
\reflistitemsep#*
\reflistparsep#*
\sentence{text}
\sentencefs#*
\lexp{word}
\lcon{concept}
\lmean{meaning}
\either{top}{bottom}