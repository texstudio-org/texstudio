# todonotes.sty
# Salim 2008/11/09; A. Weder 2010/06/04; Matthew Bertucci 2023/01/31 for v1.1.6
# http://midtiby.blogspot.com/
# http://www.ctan.org/tex-archive/help/Catalogue/entries/todonotes.html

#include:ifthen
#include:xkeyval
#include:xcolor
#include:tikz
#include:tikzlibrarypositioning
#include:calc

#keyvals:\usepackage/todonotes#c
disable
obeyDraft
obeyFinal
danish
german
ngerman
english
french
swedish
spanish
catalan
italian
portuguese
dutch
croatian
colorinlistoftodos
color=#%color
backgroundcolor=#%color
linecolor=#%color
bordercolor=#%color
tickmarkheight=##L
textwidth=##L
textsize=%<fontsize csname%>
format=%<csname%>
prependcaption={%<text%>}
loadshadowlibrary
shadow
dvistyle
figwidth=##L
#endkeyvals

#ifOption:loadshadowlibrary
#include:tikzlibraryshadows
#endif

\todo{text%todo}#D
\todo[options%keyvals]{text%todo}#D
\setuptodonotes{options%keyvals}
\todostyle{name%specialDef}{options%keyvals}#s#%todonotesstyle

#keyvals:\todo,\setuptodonotes,\todostyle
disable
color=#%color
backgroundcolor=#%color
textcolor=#%color
linecolor=#%color
bordercolor=#%color
shadow
noshadow
tickmarkheight=##L
format=%<csname%>
line
noline
inline
noinline
size=%<fontsize command%>
list
nolist
caption={%<text%>}
prepend
noprepend
fancyline
author=%<author%>
inlinewidth=##L
inlinepar
noinlinepar
#endkeyvals

\missingfigure{text%todo}#D
\missingfigure[options%keyvals]{text%todo}#D

#keyvals:\missingfigure,\setuptodonotes,\todostyle
figwidth=##L
figheight=##L
figcolor=#%color
#endkeyvals

#keyvals:\todo,\missingfigure,\setuptodonotes,\todostyle
%todonotesstyle
#endkeyvals

\listoftodos
\listoftodos[name]
\todototoc

\todoformat{arg}#*
