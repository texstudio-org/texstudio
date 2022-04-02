# synproof package
# Matthew Bertucci 4/2/2022 for v1.0

#include:ifthen
#include:pstricks
#include:pst-node
#include:keyval

#keyvals:\usepackage/synproof#c
symbols
#endkeyvals

#ifOption:symbols
\Exists
\Forall
\Neg
\And
\Or
\Falsum
\Implies
#endif

\SetDim{options%keyvals}

\begin{synproof}{derivation length}#\pictureHighlight
\begin{synproof}[options%keyvals]{derivation length}
\end{synproof}

#keyvals:\SetDim,\begin{synproof}
NumToEx=%<number%>
ExToRule=%<number%>
OutLine=%<number%>
LineSpace=%<number%>
AssumeLine=%<number%>
HorAlign=%<number%>
#endkeyvals

\step{expression}{rule}
\step{expression}{rule}[label]
\step[line number]{expression}{rule}
\step[line number]{expression}{rule}[label]
\LineNum{number}
\assumption
\assumend

# not documented
\AssumeLine#*
\ExToRule#*
\LineSpace#*
\newctr{counter name}#*
\Num#*
\NumToEx#*
\OutLine#*
\ResetDim#*
\Start#*
\theembedding#*
\theendassumption#*
\theinfline#*
\thelab#*
\thestep#*