# pdfpagediff package
# Matthew Bertucci 1/20/2022 for v1.5

#include:geometry
#include:graphicx
#include:color
#include:substr

\layerPages{file1%file}{file2%file}
\layerPages[page numbers]{file1%file}{file2%file}
\FirstDoc{text}
\SecondDoc{text}

\obj{arg}#*
\objref{arg}#*
\doobjref{arg}#*
\objrefs{arg}#*
\lastobjref#*
\thisobjref#*
\nextobjref#*
\openlayer#*
\closelayer#*
\PPDonercname#*
\PPDoneobjnum#*
\PPDone#*
\PPDtworcname#*
\PPDtwoobjnum#*
\PPDtwo#*
\layersnames#*
\next#*
\layersorder#*
\layerson#*
\layersoff#*
\layersconfig#*
\layersOn#*
\thecpages#*
\thepages#*
\vlength#*
\hoddlength#*
\hevenlength#*
\buildPageList{arg}#*
\processNormal{arg}#*
\processComma{arg}#*
\processOther{arg}#*
\processHyphen{arg}#*
\findPages{arg}#*
\ifFiles#*
\Filestrue#*
\Filesfalse#*
\PPDfirstdoc#*
\PPDseconddoc#*
\PPDfirstlastpage#*
\PPDsecondlastpage#*
\lastpage#*
\pdflastpage#*
\placepages#*
\definejnldata#*
\normaljnldata{jid}{vlength}{hodd}{heven}#*
\starjnldata{jid}{vlength}{hodd}{heven}#*
\nameUse{arg}#*

\Fileversion#S
\Filedate#S
