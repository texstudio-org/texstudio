# pythonhighlight package
# Matthew Bertucci 2021/12/16 for v4.2.1

#include:listings
#include:xcolor

commentcolour#B
stringcolour#B
keywordcolour#B
exceptioncolour#B
commandcolour#B
numpycolour#B
literatecolour#B
promptcolour#B
specmethodcolour#B

\framemargin#*
\pythonprompt#*
\literatecolour{text}#*

#keyvals:\lstset,\begin{lstlisting},\lstinputlisting,\lstdefinelanguage,\lstdefinestyle
style=mypython
#endkeyvals

#keyvals:\lstinline,\lstMakeShortInline,\lstdefinelanguage,\lstdefinestyle
style=mypythoninline
#endkeyvals

\inputpython{file}{start num}{end num}
\begin{python}#V
\end{python}
\pyth|%<text%>|
\pyth{verbatimSymbol}#S
