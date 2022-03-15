# pyluatex package
# Matthew Bertucci 3/12/2022 for v0.4.3

#include:luatex
#include:expl3
#include:kvoptions

#keyvals:\usepackage/pyluatex#c
executable=%<path%>
ignoreerrors#true,false
localimports#true,false
shutdown=#veryveryend,veryenddocument,off
verbose#true,false
#endkeyvals

\py{code%definition}
\pyq{code%definition}
\pyc{code%definition}
\pycq{code%definition}
\pyfile{file}#i
\pyfileq{file}#i
\pyfilerepl{file}#i
\pysession{session}
\pyoption{option%keyvals}{value}
#keyvals:\pyoption
ignoreerrors
verbose
#endkeyvals
\begin{python}#V
\end{python}
\begin{pythonq}#V
\end{pythonq}
\begin{pythonrepl}#V
\end{pythonrepl}
\PyLTVerbatimEnv
