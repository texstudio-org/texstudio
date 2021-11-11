# continue package
# Matthew Bertucci 11/10/2021 for v0.2

#include:atbegshi
#include:picture
#include:zref-abspage
#include:zref-lastpage

\flagcont
\flagend
\flagword
\preflagword
\postflagword
\contsep
\contdrop

\ifcontmargin#*
\contmarginfalse#*
\contmargintrue#*
\ifcontword#*
\contwordfalse#*
\contwordtrue#*
\ifcontallpages#*
\contallpagesfalse#*
\contallpagestrue#*

\contgo
\contstop

\FirstWordBox#*
\NextWordBox#*
\LastWordBox#*