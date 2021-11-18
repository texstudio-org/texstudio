# formal-grammar package
# Matthew Bertucci 11/17/2021 for v1.1

#include:xparse
#include:newfloat
#include:xcolor
#include:colortbl
#include:array

LightCyan#B

\begin{grammar}
\begin{grammar}[caption%text][pos]
\begin{grammar}[caption%text][pos][label]#l
\end{grammar}

\firstcase{letter}{definition%formula}{explanation%text}
\otherform{definition%formula}{explanation%text}
\nonterm{letter}#m

\gralt

\nontermsubtil{arg}#*
\firstcasesubtil{arg}{definition%formula}{explanation%text}#*

\downplay
\highlight
\lochighlight{arg}

\begin{floatgrammar}#*
\end{floatgrammar}#*
\rowstyle{style code}#*