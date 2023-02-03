# hvpygmentex package
# Matthew Bertucci 3/7/2022 for v0.01

#include:caption
#include:color
#include:efbox
#include:fancyvrb
#include:ifthen
#include:pgfkeys
#include:shellesc
#include:mdframed
# mdframed loaded with framemethod=tikz
#include:tikz

#keyvals:\usepackage/hvpygmentex#c
force
#endkeyvals

\begin{pygmented}#V
\begin{pygmented}[options%keyvals]#V
\end{pygmented}

\inputpygmented{file}
\inputpygmented[options%keyvals]{file}

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

\widest(string list){code}{cmd}#*d
\VerbatimOutAppend#*
\begin{VerbatimOutAppend}#*
\end{VerbatimOutAppend}#*
\remainingglobaloptions#S
\remaininguseroptions#S
\remainingoptions#S
\FormatLineNumber{arg}#*
