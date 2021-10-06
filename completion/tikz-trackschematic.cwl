# tikz-trackschematic package
# Matthew Bertucci 10/3/2021 for v0.6.1

#include:tikz
#include:xcolor
#include:etoolbox

\tsFullSymbology#*
\tsSymbol[width]{symbol name}#*

#keyvals:\tikzset#c
traffic practice=
#endkeyvals

\maintrack
\secondarytrack
\sidetrack#*
\tracklabel

\bufferstop[options%keyvals]

#keyvals:\bufferstop
face=#forward,backward
forward
backward
friction=##L
foreground=#%color
#endkeyvals

\trackclosure

\turnout[options%keyvals]

#keyvals:\turnout
face=#forward,backward
forward
backward
branch=#left,right
operation=#manual
fouling point
points=#left,right
shift label={%<(x,y)%>}
foreground=#%color
#endkeyvals

\crossing[options%keyvals]

#keyvals:\crossing
branch=#left,right
fouling point
shift label={%<(x,y)%>}
foreground=#%color
#endkeyvals

\slipturnout[options%keyvals]

#keyvals:\slipturnout
branch=#left,right
slip=#double,none,left,right
operation=#manual
fouling point
forward points=#left,right
backwards points=#left,right
shift label={%<(x,y)%>}
foreground=#%color
#endkeyvals

\derailer[options%keyvals]

#keyvals:\derailer
face=#forward,backward
forward
backward
shift label={%<(x,y)%>}
foreground=#%color
#endkeyvals

\parkedvehicles[options%keyvals]

#keyvals:\parkedvehicles
length=##L
label at={%<(x,y)%>}
label align=#left,right
foreground=#%color
background=#%color
#endkeyvals

\shunting[options%keyvals]

#keyvals:\shunting
face=#forward,backward
movement
forward
backward
operation=#manual,automatic
bend left at={%<(x,y)%>}
bend right at={%<(x,y)%>}
label at={%<(x,y)%>}
label align=#left,right
foreground=#%color
background=#%color
#endkeyvals

\train[options%keyvals]

#keyvals:\train
face=#forward,backward
run=#slow,normal,fast
forward
backward
length=##L
operation=#manual,automatic
ghost
bend left at={%<(x,y)%>}
bend right at={%<(x,y)%>}
shift label={%<(x,y)%>}
label align=#left,right
foreground=#%color
background=#%color
#endkeyvals

\signal[options%keyvals]

#keyvals:\signal
distant
speed type
block
route
shunt limit
shunting
berth
speed=
distant speed=
locked#true,false
position=#left,right
shift label={%<(x,y)%>}
foreground=#%color
#endkeyvals


\distantsignal[options%keyvals]
\speedsignal[options%keyvals]
\blocksignal[options%keyvals]
\routesignal[options%keyvals]
\shuntsignal[options%keyvals]
\shuntlimit[options%keyvals]
\berthsignal[options%keyvals]

#keyvals:\distantsignal,\speedsignal,\blocksignal,\routesignal,\shuntsignal,\shuntlimit,\berthsignal
face=#forward,backward
forward
backward
position=#left,right
shift label={%<(x,y)%>}
foreground=#%color
#endkeyvals

#keyvals:\speedsignal
speed=
#endkeyvals

#keyvals:\routesignal
speed=
locked#true,false
#endkeyvals

#keyvals:\shuntsignal
locked#true,false
#endkeyvals

\viewpoint[options%keyvals]
\clearingpoint[options%keyvals]
\standardclearing[options%keyvals]
\blockclearing[options%keyvals]
\routeclearing[options%keyvals]

#keyvals:\viewpoint,\clearingpoint,\standardclearing,\blockclearing,\routeclearing
face=#forward,backward
forward
backward
position=#left,right
foreground=#%color
#endkeyvals

#keyvals:\clearingpoint
standard
block
route
shift label={%<(x,y)%>}
#endkeyvals

#keyvals:\standardclearing,\blockclearing,\routeclearing
shift label={%<(x,y)%>}
#endkeyvals

\brakingpoint[options%keyvals]
\movementauthority[options%keyvals]
\dangerpoint[options%keyvals]
\balise[options%keyvals]

#keyvals:\brakingpoint,\movementauthority,\dangerpoint,\balise
face=#forward,backward,bidirectional
forward
backward
bidirectional
position=#left,right
shift label={%<(x,y)%>}
foreground=#%color
#endkeyvals

\route[options%keyvals]
\directioncontrol[options%keyvals]

#keyvals:\route,\directioncontrol
face=#forward,backward
forward
backward
background=#%color
#endkeyvals

#keyvals:\directioncontrol
bidirectional
#endkeyvals

\transmitter[options%keyvals]

#keyvals:\transmitter
face=#forward,backward,bidirectional
type=#balise,loop
forward
backward
bidirectional
position=#left,right
shift label={%<(x,y)%>}
foreground=#%color
#endkeyvals

\trackloop[options%keyvals]

#keyvals:\trackloop
position=#left,right
shift label={%<(x,y)%>}
foreground=#%color
#endkeyvals

\platform[options%keyvals]

#keyvals:\platform
side=#left,right,both
length=##L
width=##L
foreground=#%color
#endkeyvals

\levelcrossing[options%keyvals]

#keyvals:\levelcrossing
barrier=#none,semi,full
side=#both,left,right
road width=##L
width=##L
no road
foreground=#%color
#endkeyvals

\bridge[options%keyvals]

#keyvals:\bridge
length=##L
width=##L
shift left=##L
shift right=##L
side=#both,left,right
foreground=#%color
background=#%color
no background
#endkeyvals

\interlocking
\hump

\pylon[options%keyvals]

#keyvals:\pylon
side=#right,left,both
foreground=#%color
background=#%color
#endkeyvals

\distantpoweroff[options%keyvals]
\poweroff[options%keyvals]
\poweron[options%keyvals]
\distantpantographdown[options%keyvals]
\pantographdown[options%keyvals]
\pantographup[options%keyvals]
\wirelimit[options%keyvals]

#keyvals:\distantpoweroff,\poweroff,\poweron,\distantpantographdown,\pantographdown,\pantographup,\wirelimit
face=#forward,backward,bidirectional
forward
backward
bidirectional
position=#left,right
signal color=#%color
shift label={%<(x,y)%>}
foreground=#%color
background=#%color
#endkeyvals

\trackdistance

\berth[options%keyvals]

#keyvals:\berth
face=#forward,backward,bidirectional
forward
backward
bidirectional
length=##L
position=#left,right
foreground=#%color
#endkeyvals

\measureline 

\hectometer[options%keyvals]

#keyvals:\hectometer
hectometer base={%<(x,y)%>}
orientation=#left,right
shift label={%<(x,y)%>}
hectometer color=#%color
#endkeyvals

\trackmarking[color%plain]
