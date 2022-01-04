# grid-system package
# Matthew Bertucci 1/4/2022 for v0.3.0

#include:calc
#include:environ
#include:forloop
#include:ifthen
#include:xkeyval

\begin{Row}
\begin{Row}[options%keyvals]
\end{Row}

#keyvals:\begin{Row},\begin{row}
cellsep=##L
#endkeyvals

\begin{Cell}
\end{Cell}

# deprecated
\begin{row}{num of cols}{num of cells}#*
\begin{row}[options%keyvals]{num of cols}{num of cells}#*
\end{row}#*

\begin{cell}{num of cols}#*
\end{cell}#*