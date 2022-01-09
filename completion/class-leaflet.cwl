# leaflet class
# Matthew Bertucci 1/8/2021 for v2.1a

#include:graphicx
#include:pifont

#keyvals:\documentclass/leaflet#c
dvips
pdftex
vtex
dvipdfm
twoside
twocolumn
landscape
portrait
debug
twopart
notwopart
nospecialtricks
a3paper
combine
nocombine
frontside
backside
bothsides
tumble
notumble
foldmark
nofoldmark
foldcorr
nofoldcorr
draft
final
#endkeyvals

\setmargins{top%l}{bottom%l}{left%l}{right%l}
\CutLine{page num}
\CutLine*{page num}
\AddToBackground{page num}{picture commands%definition}
\AddToBackground*{page num}{picture commands%definition}

\noparskip#*
\sectfont#*
\descfont#*
\foldmarkrule#*
\foldmarklength#*
\Scissors#*

\iflandscape#*
\landscapetrue#*
\landscapefalse#*
\iftumble#*
\tumbletrue#*
\tumblefalse#*
\iftwopart#*
\twoparttrue#*
\twopartfalse#*
\iffoldcorr#*
\foldcorrtrue#*
\foldcorrfalse#*