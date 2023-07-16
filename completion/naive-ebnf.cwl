# naive-ebnf package
# Matthew Bertucci 2023/07/12 for v0.0.11

#include:pgfopts
#include:xcolor

#keyvals:\usepackage/naive-ebnf#c
bw
trail=%<file name%>
#endkeyvals

\begin{ebnf}
\begin{ebnf}[width]
\end{ebnf}

\EbnfTerminal{symbol}
\EbnfNonTerminal{rule}
\EbnfSpecial{symbol}
\EbnfRegex{regex}
