# mnotes package
# Matthew Bertucci 12/12/2021 for v0.7

#include:kvoptions
#include:marginnote
#include:tikz
#include:ifoddpage

#ifOpton:sidenotes
#include:sidenotes
#endif

#keyvals:\usepackage/mnotes#c
scale
scale=%<factor%>
mnwidth=##L
boxcolour=#%color
hide
sidenotes
basic
reverseconnect
centre
fontsize=##L
#endkeyvals

\MNOTE{text%todo}#D
\MNOTE[TikZ options]{text%todo}#D
\HideMNOTES
\ShowMNOTES
\ReverseMNConnect

\mnotespaperwidth#*
\MNOTEWIDTH#*
\MNCOLOUR#*
\MNFONT#*
\MNOTEon{text}#*
\MNOTEon[TikZ options]{text}#*
\mnoteseastlink{TikZ options}#*
\mnoteswestlink{TikZ options}#*