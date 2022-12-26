# pythonimmediate package
# Matthew Bertucci 2022/12/23 for v0.0.0

#include:saveenv
#include:currfile
#include:precattl

#keyvals:\usepackage/pythonimmediate#c
outputdir=%<directory%>
mode=#multiprocessing-network,unnamed-pipe
#endkeyvals

\py{python expr%definition}
\pyc{python code%definition}
\pycq{python code%definition}
\pyfile{file}#i

\begin{pycode}#V
\end{pycode}
\begin{pycodeq}#V
\end{pycodeq}

\pythonimmediatecontinue{code}#*

# not documented
\pythonimmediatecontinuenoarg#S
\pyv{python expr%definition}#S
\pycv{python code%definition}#S