# pstricks-pdf package
# Matthew Bertucci 2/18/2022 for v0.02

#include:ifpdf
#include:xkeyval
#include:ifplatform
#include:pst-pdf

#keyvals:\usepackage/pstricks-pdf#c
off
on
crop=#on,off
ext=%<extension%>
latex={%<latex cmds%>}
dvips={%<dvips options%>}
pspdf={%<pspdf options%>}
pdfcrop={%<pdfcrop options%>}
cleanup={%<extension list%>}
runs=%<number%>
# options passed to pst-pdf
active
inactive
pstricks
nopstricks
draft
final
tightpage
notightpage
displaymath
# options passed to pstricks
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

\OnlyIfFileExists{file}{code}#*
\NotIfFileExists{file}{code}#*