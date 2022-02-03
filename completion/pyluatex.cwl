# pyluatex package
# Matthew Bertucci 2/1/2022 for v0.4.0

#include:luatex
#include:expl3
#include:kvoptions

#keyvals:\usepackage/pyluatex#c
executable=%<path%>
ignoreerrors#true,false
verbose#true,false
#endkeyvals

\py{code%definition}
\pyq{code%definition}
\pyc{code%definition}
\pycq{code%definition}
\pyfile{path%definition}
\pyfileq{path%definition}
\pyfilerepl{path%definition}
\pysession{session}
\pyoption{option%keyvals}{value}
#keyvals:\pyoption
executable
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