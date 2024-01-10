# exsol package
# Matthew Bertucci 2024/01/07 for v1.6

#include:ifmtarg
#include:fancyvrb
#include:ifthen
#include:kvoptions
#include:multicol
#include:varwidth

#keyvals:\usepackage/exsol#c
local#true,false
external#true,false
inline#true,false
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

\begin{solutionseries}{arg1}{arg2}#S
\begin{solutionseries}[options]{arg1}{arg2}#S
\end{solutionseries}#S
\columncount#S
\exercisesfontsize#S
\exercisestream#S
\exsolexerciseitemindent#S
\exsolexerciselabelsep#S
\exsolexerciselabelwidth#S
\exsolexerciseleftmargin#S
\exsolexerciseparindent#S
\exsolexerciseparsep#S
\exsolexerciserightmargin#S
\exsolexercisesaboveskip#S
\exsolexercisesbelowskip#S
\exsolexercisetopbottomsep#S
\exsubrule#S
\formulacollectionstream#S
\formulastream#S
\ifnoexinchapter#S
\noexercisesinchapter#S
\noexercisesinnextchapter#S
\noexinchapterfalse#S
\noexinchaptertrue#S
\solsubrule#S
\solutionstream#S
\theexercise#S
\theexerciseseries#S
