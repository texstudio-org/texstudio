# mnotes package
# Matthew Bertucci 2022/06/13 for v0.9

#include:kvoptions
#include:soul
#include:marginnote
#include:tikz
#include:ifoddpage

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
fontsize=%<number%>
#endkeyvals

#ifOpton:sidenotes
#include:sidenotes
#endif

\MNOTE{text%todo}#D
\MNOTE[TikZ options]{text%todo}#D
\Mnewauthor{name}{TikZ options}
\Mnewauthor[initials]{name}{TikZ options}
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
