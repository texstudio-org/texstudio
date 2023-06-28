# conteq package
# Matthew Bertucci 10/18/2021 for v0.1.1

#include:amsmath
#include:environ

\begin{conteq}#\math
\begin{conteq}[layout%keyvals]#\math
\end{conteq}

#keyvals:\begin{conteq}#c,\ConteqSetDefaultLayout#c
plain
explline
headline
onecolumn
oneline
#endkeyvals

\ConteqExplStyle{explanation}#*
\ConteqSetDefaultLayout{layout%keyvals}#*
\ConteqDefineLayout{name}{before}{left}{right1}{right2}{sep}{after}#*