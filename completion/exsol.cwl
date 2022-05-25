# exsol package
# Matthew Bertucci 2022/05/23 for v1.4

#include:ifmtarg
#include:fancyvrb
#include:ifthen
#include:kvoptions
#include:multicol
#include:varwidth

#keyvals:\usepackage/exsol#c
local#true,false
nolabels#true,false
exercisesfontsize=%<fontsize csname%>
exerciseaslist#true,false
copyexercisesinsolutions#true,false
minipage#true,false
usesolutionserieslabels#true,false
#endkeyvals

\begin{exercises}
\begin{exercises}[options%keyvals]
\end{exercises}
\begin{exerciseseries}{title%text}
\begin{exerciseseries}[options%keyvals]{title%text}
\end{exerciseseries}

#keyvals:\begin{exercises},\begin{exerciseseries}
columns=%<integer%>
exsubrule
solsubrule
subrule
#endkeyvals

\begin{exercise}
\end{exercise}
\begin{solution}
\end{solution}

\begin{informulacollection}
\end{informulacollection}
\begin{informulacollectiononly}
\end{informulacollectiononly}

\exercisename
\exercisesname
\seriesname
\solutionname
\solutionsname
\loadSolutions

\begin{solutionseries}{arg1}{arg2}#*
\begin{solutionseries}[options]{arg1}{arg2}#*
\end{solutionseries}#*
\columncount#*
\exercisesfontsize#*
\exercisestream#*
\exsolexerciseitemindent#*
\exsolexerciselabelsep#*
\exsolexerciselabelwidth#*
\exsolexerciseleftmargin#*
\exsolexerciseparindent#*
\exsolexerciseparsep#*
\exsolexerciserightmargin#*
\exsolexercisesaboveskip#*
\exsolexercisesbelowskip#*
\exsolexercisetopbottomsep#*
\exsubrule#*
\formulacollectionstream#*
\formulastream#*
\ifnoexinchapter#*
\noexercisesinchapter#*
\noexercisesinnextchapter#*
\noexinchapterfalse#*
\noexinchaptertrue#*
\solsubrule#*
\solutionstream#*
\theexercise#*
\theexerciseseries#*