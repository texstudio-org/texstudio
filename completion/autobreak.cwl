# autobreak package
# Matthew Bertucci 9/11/2021 for v0.3

#include:amsmath
#include:catchfile

\begin{autobreak}#/align,align*
\end{autobreak}#/align,align*
\MoveEqLeft
\MoveEqLeft[length]
\everybeforeautobreak{tokens}#*
\everyaftereautobreak{tokens}#*