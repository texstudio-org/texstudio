# gridslides package
# Matthew Bertucci 2/5/2022 for v0.1.1

#include:inputenc
#include:amsmath
#include:amsthm
#include:amssymb
#include:mathtools
#include:babel
#include:braket
#include:siunitx
#include:xspace
#include:dsfont
#include:microtype
#include:ragged2e
#include:tikz
#include:geometry
#include:xstring
#include:enumerate
#include:environ
#include:hyperref
#include:tikzlibrarycalc

\begin{slide}{title%text}
\end{slide}
\begin{style}
\end{style}
\begin{rawslide}
\end{rawslide}

\bg{imagefile}#g
\txt(x,y){text}
\txt<n-m>(x,y){text}
\block(x,y,w){content%text}
\block<>(x,y,w){content%text}
\fig(x,y,w){imagefile}#g
\eq(x,y){formula}
\only<n-m>{content%text}
\alt<n-m>{content%text}{alt content%text}

\institute{institute%text}
\theheadline
\theslide
\theauthor
\thetitle
\thedate
\theinstitute

\rgb{rgb}#*

# from ngerman option of babel
\captionsngerman#*
\datengerman#*
\extrasngerman#*
\noextrasngerman#*
\dq
\ntosstrue#*
\ntossfalse#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
\mdqon#*
\mdqoff#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"A Ä
#repl:"E Ë
#repl:"I Ï
#repl:"O Ö
#repl:"U Ü
#repl:"s ß
#repl:"z ß
#repl:"S SS
#repl:"Z SZ
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#repl:"/ /
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »
