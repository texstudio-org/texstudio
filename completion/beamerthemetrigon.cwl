# trigon beamertheme
# Matthew Bertucci 3/12/2022 for v0.6.3

# Dependency Tree:
# beamerthemetrigon.sty
# ├── pgfopts.sty
# ├── tikz.sty
# ├── sourcesanspro.sty
# ├── beamercolorthemetrigon.sty
# │   └── pgfopts.sty
# ├── beamerfontthemetrigon.sty
# │   └── pgfopts.sty
# ├── beamerinnerthemetrigon.sty
# │   ├── pgfopts.sty
# │   ├── tikz.sty
# │   ├── tikzlibrarycalc.code.tex
# │   └── tikzlibrary3d.code.tex
# └── beamerouterthemetrigon.sty
#     └── pgfopts.sty

#include:pgfopts
#include:tikz
#include:tikzlibrarycalc
#include:tikzlibrary3d
#include:sourcesanspro

\trigonset{options%keyvals}

#keyvals:\usetheme/trigon,\trigonset
background=#light,dark
titleformat=#regular,smallcaps,allsmallcaps,allcaps
usesourcefonts#true,false
sectionpage=#none,simple
titlestyle=#plain,style1,style2
sectionstyle=#plain,style1,style2,style3
slidestyle=#blank,style1,cyber
numbering=#none,counter,fraction
block=#transparent,fill
headingcolor=#default,theme
textgcolor=#default,theme
titleformat title=#regular,smallcaps,allsmallcaps,allcaps
titleformat subtitle=#regular,smallcaps,allsmallcaps,allcaps
titleformat section=#regular,smallcaps,allsmallcaps,allcaps
titleformat frame=#regular,smallcaps,allsmallcaps,allcaps
#endkeyvals

# from beamercolorthemetrigon.sty
\headcol#*
\txtcol#*
tGreenBlue#B
tGreenBlueLight#B
tOrange#B
tYellowOrange#B
tBeigePale#B
tBeige#B
tDarkBg#B
tDarkFg#B
tLightBg#B
tPrim#B
tSec#B
tAccent#B
tTxt#B
tBg#B
tGreyBg#B
tGrey#B
tTheme#B

# from beamerfontthemetrigon.sty
# no user commands

# from beamerinnerthemetrigon.sty
\logbig#*
\biglogo{imagefile}#g
\biglogo[options%keyvals]{imagefile}#g
\slidestyle#*
\titlestyle#*
\sectionstyle#*
\leftTriangle{x}{y}
\rightTriangle{x}{y}
\topTriangle{x}{y}
\leftColorTriangle{color}{x}{y}
\rightColorTriangle{color}{x}{y}
\topColorTriangle{color}{x}{y}
\titleframe
\sectionframe

# from beamerouterthemetrigon.sty
\logsmall#*
\smalllogo{imagefile}#g
\smalllogo[options%keyvals]{imagefile}#g

#keyvals:\biglogo,\smalllogo
alt={%<alt text%>}
bb=%<llx lly urx ury%>
bbllx=
bblly=
bburx=
bbury=
natwidth=
natheight=
hiresbb#true,false
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
viewport=%<llx lly urx ury%>
trim=%<llx lly urx ury%>
angle=%<degrees%>
origin=
width=##L
height=##L
totalheight=##L
keepaspectratio#true,false
scale=%<factor%>
clip#true,false
draft#true,false
type=%<file type%>
ext=%<file extension%>
read=%<read-file extension%>
command=
quiet
page=%<page number%>
interpolate#true,false
decodearray={%<color array%>}
#endkeyvals
