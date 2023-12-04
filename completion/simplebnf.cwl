# simplebnf package
# Matthew Bertucci 2023/11/24 for v1.0.0

#include:tabularray
#include:mathtools

\begin{bnf}
\begin{bnf}[tblr options]
\begin{bnf}(options%keyvals)
\begin{bnf}(options%keyvals)[tblr options]
\end{bnf}

\SetBNFLayout{tblr options}
\SetBNFConfig{options%keyvals}

#keyvals:\begin{bnf},\SetBNFConfig
prod-delim={%<characters%>}
new-line-delim={%<characters%>}
single-line-delim={%<characters%>}
comment={%<characters%>}
relation={%<characters%>}
relation-sym-map={%<specification%>}
or-sym=%<symbol%>
prod-sep=##L
row-sep=##L
#endkeyvals

# deprecated
\SimpleBNFDefEq#S
\SimpleBNFDefOr#S
\SimpleBNFStretch#S
\bnfexpr{text%plain}#S
\bnfannot{text%plain}#S
\begin{bnfgrammar}#S\math
\begin{bnfgrammar}[cols]#S\math
\begin{bnfgrammar}[cols][newline sep regexp]#S\math
\begin{bnfgrammar}[cols][newline sep regexp][non-breaking sep regexp]#S\math
\end{bnfgrammar}#S
