# karnaugh-map package
# Matthew Bertucci 1/18/2022 for v2.0

#include:kvoptions
#include:keyval
#include:xstring
#include:tikz
#include:tikzlibrarycalc
#include:tikzlibrarymatrix

\begin{karnaugh-map}
\begin{karnaugh-map}[%<x-size%>][%<y-size%>][%<z-size%>]
\begin{karnaugh-map}(%<options%>)[%<x-size%>][%<y-size%>][%<z-size%>]
\begin{karnaugh-map}[%<x-size%>][%<y-size%>][%<z-size%>][%<label-A%>]%<...[label-F]%>
\begin{karnaugh-map}(%<options%>)[%<x-size%>][%<y-size%>][%<z-size%>][%<label-A%>]%<...[label-F]%>
\end{karnaugh-map}

#keyvals:\usepackage/karnaugh-map#c,\begin{karnaugh-map}
implicantcolors={%<list of colors%>}
label=#middle,corner
#endkeyvals

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
\implicantedge{NWNW}{NWSE}{SENW}{SESE}[submaps]#/karnaugh-map
\implicantcorner#/karnaugh-map
\implicantcorner[submaps]#/karnaugh-map
