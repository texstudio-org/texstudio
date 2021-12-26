# karnaugh-map package
# Matthew Bertucci 12/22/2021 for v1.1

#include:xparse
#include:xstring
#include:tikz
# loads calc and matrix tikzlibraries

\begin{karnaugh-map}
\begin{karnaugh-map}[x-size][y-size][z-size]
\begin{karnaugh-map}[x-size][y-size][z-size][x-label][y-label][z-label]
\begin{karnaugh-map}*[x-size][y-size][z-size][x-label][y-label][z-label]
\end{karnaugh-map}

\autoterms#/karnaugh-map
\autoterms[content]#/karnaugh-map
\indeterminants{cells}#/karnaugh-map
\manualterms{content}#/karnaugh-map
\maxterms{cells}#/karnaugh-map
\minterms{cells}#/karnaugh-map
\terms{cells}{content}#/karnaugh-map
\implicant{northwest cell}{southeast cell}#/karnaugh-map
\implicant{northwest cell}{southeast cell}[submaps]#/karnaugh-map
\implicantedge{NWNW}{NWSE}{SENW}{SESE}#/karnaugh-map
\implicantcorner#/karnaugh-map
\implicantcorner[submaps]#/karnaugh-map