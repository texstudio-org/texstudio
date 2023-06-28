# exercises package
# Matthew Bertucci 1/18/2022 for v1.1

#include:verbatim
#include:ifthen
#include:kvoptions
#include:marginnote

#keyvals:\usepackage/exercises#c
printsolution#true,false
exercisespaceabove=##L
exercisespacebelow=##L
solutionspaceabove=##L
solutionspacebelow=##L
blockspace=##L
inlinespace=##L
exercisenumberformat=#arabic,roman,Roman,alph,Alph
pointsposition=#aftername,margin
pointsfontsize=#normalsize,footnotesize
pointsname=%<text%>
exercisename=%<text%>
exercisenameposition=#block,inline
solutionname=%<text%>
solutionnameposition=#block,inline
totalpointsname=%<text%>
braces=#nobraces,round,square
starpoints#true,false
#endkeyvals

\begin{exercise}
\begin{exercise}[points]
\end{exercise}

\begin{solution}
\begin{solution}[space%l]
\end{solution}

\totalpoints
\exercisenewpage
\solutionnewpage
\ifsolutionthenelse{then}{else}
\thei#*