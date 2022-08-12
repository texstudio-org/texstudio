# simplebnf package
# Matthew Bertucci 2022/08/11 for v0.3.1

#include:expl3
#include:xparse
#include:mathtools

\SimpleBNFDefEq#*
\SimpleBNFDefOr#*

\bnfexpr{text%plain}
\bnfannot{text%plain}

\begin{bnfgrammar}#\math
\begin{bnfgrammar}[cols]#\math
\begin{bnfgrammar}[cols][newline sep regexp]#\math
\begin{bnfgrammar}[cols][newline sep regexp][non-breaking sep regexp]#\math
\end{bnfgrammar}
