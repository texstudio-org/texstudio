# ticollege package
# Matthew Bertucci 10/18/2021 for v1.8.0

#include:xcolor
#include:newtxtt
#include:tikz
#include:tikzlibrarycalc
#include:tikzlibraryshapes
#include:tikzlibraryshadows
#include:tikzlibrarybackgrounds
#include:tikzlibrarybabel
#include:ifthen
#include:xkeyval
#include:mathtools
#include:amssymb
#include:multido
#include:multirow

\TiC
\TiC[options%keyvals]

#keyvals:\TiC
style=#general,number,arrows
rounded=#none,left,right
principal=%<text%>
position=%<number%>
fontsize=##L
raise=##L
second=%<text%>
colour text=#%color
color text=#%color
colour second=#%color
color second=#%color
colour key=#%color
color key=#%color
circle#true,false
radius=##L
colour circle=#%color
color circle=#%color
thickness=##L
circleup#true,false
circledown#true,false
circleleft#true,false
circleright#true,false
name=
#endkeyvals

\Aff
\TiRacine
\ContrastDown
\ContrastUp
\Div

TIRouge#B
TIOrange#B
TIJaune#B

\TiCMenu{name}
\TiCMenu[options%keyvals]{name}

#keyvals:\TiCMenu
size=##L
select#true,false
colour box=#%color
color box=#%color
text=
#endkeyvals

\TiCScreen{expression}
\TiCScreen[options%keyvals]{expression}

#keyvals:\TiCScreen
colour screen=#%color
color screen=#%color
screenname=
width=%<number%>
height=%<number%>
#endkeyvals

\TiCCalc
\TiCCalc[options%keyvals]

#keyvals:\TiCCalc
title=
colour calc=#%color
color calc=#%color
#endkeyvals

\TiCCalc*
\TiCCalc*[options%keyvals]

#keyvals:\TiCCalc*
calcscale=%<number%>
calcrotate=%<degrees%>
calcraise=##L
#endkeyvals
