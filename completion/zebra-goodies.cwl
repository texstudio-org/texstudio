# zebra-goodies package
# Matthew Bertucci 11/3/2021 for v0.8.0

#include:kvoptions
#include:microtype
#include:xcolor
#include:tikzpagenodes
#include:marginnote
#include:manfnt

#keyvals:\usepackage/zebra-goodies#c
draft#true,false
final
microtype#true,false
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
zebrablue#B
zebrared#B
zebrayellow#B
zebrapurple#B
zebragreen#B
