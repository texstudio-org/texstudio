# pythonhighlight package
# Matthew Bertucci 2024/03/18

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
style=pythonhighlight-style
#endkeyvals

#keyvals:\lstinline,\lstMakeShortInline,\lstdefinelanguage,\lstdefinestyle
style=pythonhighlight-inline-style
#endkeyvals

\inputpythonfile{file}
\inputpythonfile{file}[start num]
\inputpythonfile{file}[start num][end num]
\begin{python}#V
\begin{python}[options]#V
\end{python}
\pyth|%<text%>|
\pyth{verbatimSymbol}#S

# deprecated
\inputpython{file}{start num}{end num}#S
