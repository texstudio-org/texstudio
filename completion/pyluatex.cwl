# pyluatex package
# Matthew Bertucci 2026/04/20 for v0.7.0

#include:luatex

#keyvals:\usepackage/pyluatex#c
executable=%<path%>
localimports#true,false
shutdown=#veryveryend,veryenddocument,off
#endkeyvals



\py{code%definition}
\py[options%keyvals]{code%definition}
\pyc{code%definition}
\pyc[options%keyvals]{code%definition}
\pyfile{file}
\pyfile[options%keyvals]{file}
\pyif{test}{then clause}{else clause}
\pyif[options%keyvals]{test}{then clause}{else clause}
\pyoptions{options%keyvals}

\begin{python}#V
\begin{python}[options%keyvals]#V
\end{python}

\PyLTVerbatimEnv

#keyvals:\usepackage/pyluatex#c,\py,\pyc,\pyfile,\pyif,\pyoptions,\begin{python},\pyq,\pycq,\pyfileq,\pyfilerepl,\begin{pythonq},\begin{pythonrepl}
ignoreerrors#true,false
quiet#true,false
repl#true,false
session#true,false
store#true,false
verbose#true,false
#endkeyvals

# deprecated
\pyq{code%definition}#*
\pyq[options%keyvals]{code%definition}#*
\pycq{code%definition}#*
\pycq[options%keyvals]{code%definition}#*
\pyfileq{file}#*
\pyfileq[options%keyvals]{file}#*
\pyfilerepl{file}#*
\pyfilerepl[options%keyvals]{file}#*
\pysession{session}#*
\pyoption{option%keyvals}{value}#*
\begin{pythonq}#*V
\begin{pythonq}[options%keyvals]#*V
\end{pythonq}#*
\begin{pythonrepl}#*V
\begin{pythonrepl}[options%keyvals]#*V
\end{pythonrepl}#*