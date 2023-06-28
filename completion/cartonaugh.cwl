# cartonaugh package
# Matthew Bertucci 9/10/2021 for v1.0

#include:luatex
#include:iftex
#include:tikz
#include:tikzlibrarycalc
#include:tikzlibrarymatrix
#include:xstring

\begin{cartonaugh}
\begin{cartonaugh}[Xsize][Ysize][Zsize][Xlabel][Ylabel][Zlabel]
\begin{cartonaugh}[Xsize][Ysize][Zsize][Xlabel][Ylabel][Zlabel][submap_sep_type]#*
\begin{cartonaugh}*[Xsize][Ysize][Zsize][Xlabel][Ylabel][Zlabel][submap_sep_type]#*
\end{cartonaugh}
\autoterms[content]#/cartonaugh
\indeterminants{cells}#/cartonaugh
\manualterms{contents}#/cartonaugh
\maxterms{cells}#/cartonaugh
\minterms{cells}#/cartonaugh
\terms{cells}{content}#/cartonaugh
\implicant{NWcell}{SEcell}#/cartonaugh
\implicant{NWcell}{SEcell}[submaps]#/cartonaugh
\implicantedge{NWpart_NWcell}{NWpart_SEcell}{SEpart_NWcell}{SEpart_SEcell}#/cartonaugh
\implicantedge{NWpart_NWcell}{NWpart_SEcell}{SEpart_NWcell}{SEpart_SEcell}[submaps]#/cartonaugh
\implicantcorner[submaps]#/cartonaugh
\implicantspread{inner%l}{outer%l}#/cartonaugh
\resetimplicantspread
\changecolor{color}
