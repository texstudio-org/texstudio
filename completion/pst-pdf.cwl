# pst-pdf package
# Matthew Bertucci 1/12/2022 for v1.2f

#include:ifpdf
#include:ifxetex
#include:ifvtex
#include:luatex85
#include:graphicx
#include:pstricks
#include:preview
#include:environ

#keyvals:\usepackage/pst-pdf#c
active
inactive
pstricks
nopstricks
draft
final
tightpage
notightpage
displaymath
# options from pstricks
noxcolor
useCalc
gsfonts
psfonts
noEngineCheck
pdf
xetex
distiller
monochrome
grayscale
#endkeyvals

#ifOption:useCalc
#include:pst-calculate
#endif

\PDFcontainer

\begin{postscript}
\begin{postscript}[options%keyvals]
\end{postscript}

\savepicture{name}
\usepicture{name}
\usepicture[options%keyvals]{name}

\begin{pst-pdf-defs}
\end{pst-pdf-defs}

#keyvals:\includegraphics,\usepicture,\begin{postscript}
frame#true,false
innerframe#true,false
ignore#true,false
showname#true,false
namefont=%<font commands%>
#endkeyvals

\thepspicture#*
