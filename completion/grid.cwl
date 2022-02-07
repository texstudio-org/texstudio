# grid package
# Matthew Bertucci 2/5/2022 for v1.0

#include:keyval

#keyvals:\usepackage/grid#c
fontsize=##L
baseline=##L
lines=%<number%>
#endkeyvals

\begin{gridenv}
\end{gridenv}
\begin{gridfltenv}
\end{gridfltenv}

\fight#*
\roundoff#*
\floatunit#*
\allfloats#*
\halfbaselineskip#*
\figboxht#*

\mylines#S
\oldendfigure#S
\oldendtable#S
\oldfigure#S
\oldtable#S
\xbaselineskip#S
\ProcessOptionsKV#S