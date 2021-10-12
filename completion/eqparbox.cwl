# refcount package
# Matthew Bertucci 10/5/2021 for v3.6

#include:array
#include:environ

\eqparbox{tag}{text}
\eqparbox[position]{tag}{text}
\eqparbox[position][height]{tag}{text}
\eqparbox[position][height][inner-pos]{tag}{text}
\eqmakebox{text}
\eqmakebox[tag]{text}
\eqmakebox[tag][position]{text}
\eqframebox{text}
\eqframebox[tag]{text}
\eqframebox[tag][position]{text}
\eqsavebox{cmd}{text}#d
\eqsavebox{cmd}[tag]{text}#d
\eqsavebox{cmd}[tag][position]{text}#d
\begin{eqminipage}{tag}
\begin{eqminipage}[position]{tag}
\begin{eqminipage}[position][height]{tag}
\begin{eqminipage}[position][height][inner-pos]{tag}
\end{eqminipage}
\eqboxwidth{tag}#*
\eqsetminwidth{tag}{width}#*
\eqsetmaxwidth{tag}{width}#*
\eqsetminwidthto{tag}{text}#*
\eqsetmaxwidthto{tag}{text}#*