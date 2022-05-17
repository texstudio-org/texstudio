# caesar_book class
# Matthew Bertucci 2022/05/16 for v1.00a

#include:amsmath
#include:mhchem
#include:class-book
#include:sidenotes
#include:morefloats
#include:marginfix
#include:microtype
#include:geometry
#include:ifluatex
#include:mathpazo
#include:helvet
#include:beramono
#include:fontenc
# loads T1 option of fontenc
#include:titlesec
#include:titletoc
#include:fancyhdr
#include:ragged2e
#include:enumitem
#include:ifthen
#include:textcase
#include:color

\begin{fullwidth}
\end{fullwidth}
\maketitlepage
\marginparstyle#*
\newthought{text}
\overhang#*
\publisher{name}
\sidecite{bibid}#C
\sidecite[postnote]{bibid}#C
\sidecite[prenote][postnote]{bibid}#C
\thesis{text}
darkgray#B

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