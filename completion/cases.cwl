# Package cases
# http://ctan.org/tex-archive/macros/latex/contrib/cases
# By astroscion: 2012-02-15

#keyvals:\usepackage/cases#c
subnum
fleqn
leqno
amsstyle
casesstyle
cases
#endkeyvals

\begin{numcases}{left side}#\array,math
\begin{subnumcases}{left side}#\array,math
\end{subnumcases}
\end{numcases}

\begin{subequations}
\end{subequations}
\begin{subeqnarray}#\math,array
\end{subeqnarray}

\thesubequation#*
\themainequation#*
