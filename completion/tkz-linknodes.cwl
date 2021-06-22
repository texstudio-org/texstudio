# tkz-linknodes package
# Matthew Bertucci 6/21/2021

#include:tikz
#include:amsmath

\begin{NodesList}[keyvals]
\end{NodesList}
\LinkNodes[keyvals]{expression}#/NodesList

#keyvals:\begin{NodesList},\LinkNodes
margin=##L
dy=##L
#endkeyvals

\AddNode[number]#/NodesList