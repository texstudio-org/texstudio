# subfloat package
# Matthew Bertucci 12/13/2021 for v2.14

#keyvals:\usepackage/subfloat#c
countmax
nocountmax
#endkeyvals

\begin{subfigures}
\end{subfigures}
\begin{subtables}
\end{subtables}

\subfiguresbegin#*
\subfiguresend#*
\subtablesbegin#*
\subtablesend#*

\thesubfloatfigure
\thesubfloattable
\themainfigure
\themaintable

\ifinsubfloatfigures#*
\insubfloatfigurestrue#*
\insubfloatfiguresfalse#*
\ifinsubfloattables#*
\insubfloattablestrue#*
\insubfloattablesfalse#*

#ifOption:countmax
\thesubfloatfiguremax
\thesubfloattablemax
#endif