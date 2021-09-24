# luatodonotes.sty
# Tim Hoffmann 2017/06/17; Matthew Bertucci 9/21/2021 for v0.5

#include:xcolor
#include:ifluatex
#include:ifthen
#include:tikz
#include:luacode
#include:atbegshi
#include:xstring
#include:zref-abspage
#include:ifoddpage
#include:soul
#include:soulpos
#include:etoolbox

\todo{text%todo}#D
\todo[options%keyvals]{text%todo}#D
\todoarea{note text%todo}{highlighted text}#D
\todoarea[options%keyvals]{note text%todo}{highlighted text}#D

#keyvals:\todo,\todoarea
disable
color=#%color
backgroundcolor=#%color
linecolor=#%color
bordercolor=#%color
line
noline
inline
noinline
size=
list
nolist
caption=
prepend
noprepend
author=
#endkeyvals

\missingfigure{text%todo}#D
\missingfigure[options%keyvals]{text%todo}#D

#keyvals:\missingfigure
figwidth=##l
figheight=##l
figcolor=#%color
#endkeyvals

\listoftodos
\listoftodos[name]
\todototoc
