# zebra package
# Matthew Bertucci 2026/04/27 for v1.8.0

#include:microtype
#include:xcolor
#include:marginnote
#include:hyperref
#include:manfnt

#keyvals:\usepackage/zebra-goodies#c
draft#true,false
final
sort=#none,type
font-expansion#true,false
pagelinks#true,false
unnumbered#true,false
#endkeyvals

\todo{text%todo}#D
\todo[name]{text%todo}#D
\note{text}
\note[name]{text}
\comment{text}
\comment[name]{text}
\fixed{text}
\fixed[name]{text}
\placeholder{text}
\placeholder[name]{text}
\zebratodo{text%todo}#*D
\zebratodo[name]{text%todo}#*D
\zebranote{text}#*
\zebranote[name]{text}#*
\zebracomment{text}#*
\zebracomment[name]{text}#*
\zebrafixed{text}#*
\zebrafixed[name]{text}#*
\zebraplaceholder{text}#*
\zebraplaceholder[name]{text}#*
\zebranewnote{note name}{color}
\zebranewnote{note name}{color}[symbol]
\zebraref{label}#r
\zebrasetup{keyvals}
zebrablue#B
zebrared#B
zebrayellow#B
zebrapurple#B
zebragreen#B