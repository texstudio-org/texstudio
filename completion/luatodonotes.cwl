# luatodonotes.sty
# Tim Hoffmann 2017/06/17; Matthew Bertucci 9/21/2021 for v0.5

#include:xcolor
#include:ifluatex
#include:ifthen
#include:xkeyval
#include:tikz
#include:tikzlibrarypositioning
#include:tikzlibraryintersections
#include:tikzlibrarydecorations.pathmorphing
#include:luacode
#include:atbegshi
#include:xstring
#include:zref-abspage
#include:ifoddpage
#include:soul
#include:soulpos
#include:etoolbox

#keyvals:\usepackage/luatodonotes#c
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
textsize=%<fontsize csname%>
prependcaption=%<caption%>
shadow
figwidth=##L
figheight=##L
leaderwidth=##L
leadertype=#s,sBezier,opo,os,po
positioning=#inputOrder,inputOrderStacks,sLeaderNorthEast,sLeaderNorthEastBelow,sLeaderNorthEastBelowStacks,sLeaderEast,poLeaders,poLeadersAvoidLines
s
bezier
opo
po
splitting=#none,middle,median,weightedMedian
interNoteSpace=##L
noteInnerSep=##L
routingAreaWidth=##L
minNoteWidth=##L
distanceNotesPageBorder=##L
distanceNotesText=##L
rasterHeight=##L
additionalMargin=##L
debug
#endkeyvals

#ifOption:shadow
#include:tikzlibraryshadows
#endif

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
figwidth=##L
figheight=##L
figcolor=#%color
#endkeyvals

\listoftodos
\listoftodos[name]
\todototoc
