# tabularht package
# Matthew Bertucci 10/1/2021 for v2.7

#include:iftex

\begin{tabularht}{height spec%keyvals}{preamble}#\tabular
\end{tabularht}
\begin{tabularht*}{height spec%keyvals}{width}{preamble}#\tabular
\end{tabularht*}
\begin{arrayht}{height spec%keyvals}{preamble}#m\array
\end{arrayht}
\begin{tabularhtx}{height spec%keyvals}{width}{preamble}#*\tabular
\end{tabularhtx}#*

\interrowspace{height spec%keyvals}
\interrowspace[line num list]{height spec%keyvals}
\interrowfill
\interrowfill[line num list]
\interrowstart
\interrowstart[line num list]
\interrowstop

#keyvals:\begin{tabularht}#c,\begin{tabularht*}#c,\begin{arrayht}#c,\begin{tabularhtx}#c,\interrowspace#c
to=##L
spread=##L
#endkeyvals