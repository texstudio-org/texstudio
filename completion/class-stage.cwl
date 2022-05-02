# stage package
# Matthew Bertucci 4/5/2022 for v1.01

#include:class-book
#include:ifthen
#include:fancyhdr
#include:extramarks
#include:needspace
#include:changepage

#keyvals:\documentclass/stage#c
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
openright
openany
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

\address{address}
\begin{castpage}
\end{castpage}
\addcharacter{name}{description%text}
\act
\dialog{character}{speech%text}
\dialogue{character}{speech%text}
\introduce{character}
\pause
\scene
\charsd{direction%text}
\opensd{direction%text}
\open{direction%text}
\stage{direction%text}

\actname#*
\castname#*
\continuedname#*
\scenename#*
\theactcounter#*
\theendname#*
\thescenecounter#*
\paren{direction%text}#*
\saveparskip#*
\stageoldep#*

# deprecated
\initsd{text}#S