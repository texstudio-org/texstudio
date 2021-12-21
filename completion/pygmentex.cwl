# pygmentex package
# Matthew Bertucci 12/16/2021 for v0.2.0

#include:caption
#include:color
#include:efbox
#include:fancyvrb
#include:ifthen
#include:pgfkeys
#include:mdframed
# mdframed loaded with framemethod=tikz
#include:tikz

\begin{pygmented}
\begin{pygmented}[options%keyvals]
\end{pygmented}

\inputpygmented{file}#i
\inputpygmented[options%keyvals]{file}#i

\pyginline|%<code%>|
\pyginline[%<options%>]|%<code%>|
\pyginline[options%keyvals]{verbatimSymbol}#S

\setpygmented{options%keyvals}

#keyvals:\begin{pygmented}#c,\inputpygmented#c,\pyginline#c,\setpygmented#c
lang=%<language%>
sty=%<pygments style%>
font=%<font commands%>
colback=#%color
gobble=%<integer%>
tabsize=%<integer%>
linenos#true,false
linenostart=%<integer%>
linenostep=%<integer%>
linenosep=##L
caption=%<caption%>
label=##l
texcomments#true,false
mathescape#true,false
escapeinside=%<two chars%>
#endkeyvals

#keyvals:\pyginline#c,\setpygmented#c
inline method=%<csname%>
#endkeyvals

#keyvals:\begin{pygmented}#c,\inputpygmented#c,\setpygmented#c
boxing method=%<envname%>
#endkeyvals

\widest{string list}{code}{cmd}#*d
\VerbatimOutAppend#*
\begin{VerbatimOutAppend}#*
\end{VerbatimOutAppend}#*
\remainingglobaloptions#S
\remaininguseroptions#S
\remainingoptions#S
\FormatLineNumber{arg}#*