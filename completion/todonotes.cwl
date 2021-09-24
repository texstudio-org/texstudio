# todonotes.sty
# Salim 2008/11/09; A. Weder 2010/06/04; Matthew Bertucci 9/21/2021 for v1.1.5
# http://midtiby.blogspot.com/
# http://www.ctan.org/tex-archive/help/Catalogue/entries/todonotes.html

#include:ifthen
#include:xcolor
#include:tikz
#include:calc

\todo{text%todo}#D
\todo[options%keyvals]{text%todo}#D

#keyvals:\todo
disable
color=#%color
backgroundcolor=#%color
textcolor=#%color
linecolor=#%color
bordercolor=#%color
shadow
noshadow
tickmarkheight=##L
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
fancyline
author=
inlinewidth=##L
inlinepar
noinlinepar
#endkeyvals

\missingfigure{text%todo}#D
\missingfigure[options%keyvals]{text%todo}#D

#keyvals:\missingfigure
figwidth=##L
figheight=##L
figcolor=#%color
#endkeyvals

\listoftodos
\listoftodos[name]
\todototoc
