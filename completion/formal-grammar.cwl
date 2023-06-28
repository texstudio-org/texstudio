# formal-grammar package
# Matthew Bertucci 2/19/2022 for v1.2

#include:newfloat
#include:xcolor
#include:colortbl
#include:array

#keyvals:\usepackage/formal-grammar#c
center
#endkeyvals

LightCyan#B

\begin{grammar}
\begin{grammar}[caption%text][pos]
\begin{grammar}[caption%text][pos][label]#l
\end{grammar}

\firstcase{letter}{definition%formula}{explanation%text}
\otherform{definition%formula}{explanation%text}
\nonterm{text%plain}#m

\gralt

\nontermsubtil{arg}#*
\firstcasesubtil{arg}{definition%formula}{explanation%text}#*

\downplay
\highlight
\lochighlight{text}

\begin{floatgrammar}#*
\end{floatgrammar}#*
\rowstyle{style code}#*
