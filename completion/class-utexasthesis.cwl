# utexasthesis class
# Matthew Bertucci 2022/06/07 for v1.0

#include:class-report
#include:geometry
#include:fontenc
# loads T1 option of fontenc
#include:setspace
#include:indentfirst
#include:natbib
#include:tocbibind
#include:tocloft
#include:url
#include:hyperref
#include:doi

#keyvals:\documentclass/utexasthesis#c
masters
copyright
draft
singlespacing
onehalfspacing
doublespacing
10pt
11pt
12pt
#endkeyvals

\begin{acknowledgments}
\end{acknowledgments}
\begin{address}
\end{address}
\begin{dedication}
\end{dedication}
\begin{middlecenter}#*
\end{middlecenter}#*
\begin{vita}
\end{vita}

\cosupervisor{name}
\declaretypist{name}
\graduationdate{date}
\headingsize#*
\makeappendix
\makebibliography{bib file}
\maketableofcontents
\othercommitteemembers{name1,name2,...}
\supervisor{name}

# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n