# tkz-linknodes package
# Matthew Bertucci 9/17/2021 for v1.1d

#include:tikz
#include:amsmath

\begin{NodesList}
\begin{NodesList}[keyvals]
\end{NodesList}
\LinkNodes{expression}#/NodesList
\LinkNodes[keyvals]{expression}#/NodesList

#keyvals:\begin{NodesList},\LinkNodes
margin=##L
dy=##L
#endkeyvals

\AddNode#/NodesList
\AddNode[number]#/NodesList
