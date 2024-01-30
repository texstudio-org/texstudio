# pythonimmediate package
# Matthew Bertucci 2024/01/18 for v0.5.0

#include:saveenv
#include:currfile
#include:currfile-abspath
#include:precattl

#keyvals:\usepackage/pythonimmediate#c
args=%<Python args%>
python-executable=%<path%>
python-flags=%<flags%>
child-process#true,false
#endkeyvals

\py{python expr%definition}
\pyc{python code%definition}
\pycq{python code%definition}
\pyfile{file}

\begin{pycode}#V
\end{pycode}
\begin{pycodeq}#V
\end{pycodeq}

\pythonimmediatecontinue{code}#*

# not documented
\pythonimmediatecontinuenoarg#S
\pyv{python expr%definition}#S
\pycv{python code%definition}#S
