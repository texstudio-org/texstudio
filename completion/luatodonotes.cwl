# luatodonotes.sty
# Tim Hoffmann 2017/06/17; Matthew Bertucci 7/24/2021

#include:xcolor

\todo[keyvals]{text%todo}#D
\todoarea[keyvals]{note text%todo}{highlighted text}#D

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

\missingfigure[keyvals]{text%todo}#D

#keyvals:\missingfigure
figwidth=##l
figheight=##l
figcolor=#%color
#endkeyvals

\listoftodos[name]
\todototoc
