# todonotes.sty
# Salim 2008/11/09; A. Weder 2010/06/04; Matthew Bertucci 7/12/2021
# http://midtiby.blogspot.com/
# http://www.ctan.org/tex-archive/help/Catalogue/entries/todonotes.html

#include:xcolor

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

\missingfigure[options%keyvals]{text%todo}#D

#keyvals:\missingfigure
figwidth=##L
figheight=##L
figcolor=#%color
#endkeyvals

\listoftodos[name]
\todototoc
