# tikz-trackschematic package
# Matthew Bertucci 4/8/2022 for v0.7.0

#include:tikz
#include:xkeyval
#include:etoolbox
#include:tikzlibrarycalc
#include:tikzlibraryintersections
#include:tikzlibrarypatterns
# symbology sublibrary loads the following
#include:booktabs
#include:xltabular
#include:multicol
#include:adjustbox

\tsFullSymbology#*
\tsSymbol[width]{symbol name}#*

#keyvals:\tikzset#c
traffic practice=#left,right
#endkeyvals

\maintrack
\secondarytrack
\sidetrack#*
\tracklabel

\bufferstop[options%keyvals]

#keyvals:\bufferstop#c
face=#forward,backward
forward
backward
friction=##L
foreground=#%color
#endkeyvals

\trackclosure

\turnout[options%keyvals]

#keyvals:\turnout#c
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

#keyvals:\crossing#c
branch=#left,right
fouling point
shift label={%<(x,y)%>}
foreground=#%color
#endkeyvals

\slipturnout[options%keyvals]

#keyvals:\slipturnout#c
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

#keyvals:\derailer#c
face=#forward,backward
forward
backward
branch=#left,right
shift label={%<(x,y)%>}
foreground=#%color
#endkeyvals

\parkedvehicles[options%keyvals]

#keyvals:\parkedvehicles#c
length=##L
label at={%<(x,y)%>}
label align=#left,right
foreground=#%color
background=#%color
#endkeyvals

\shunting[options%keyvals]

#keyvals:\shunting#c
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

#keyvals:\train#c
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

#keyvals:\signal#c
distant
speed type
block
route
shunt limit
shunting
berth
face=#forward,backward
forward
backward
speed=
distant speed=
locked#true,false
position=#left,right
shift label={%<(x,y)%>}
foreground=#%color
rotate=%<degrees%>
#endkeyvals

\distantsignal[options%keyvals]
\speedsignal[options%keyvals]
\speedsign[options%keyvals]#*
\blocksignal[options%keyvals]
\routesignal[options%keyvals]
\shuntsignal[options%keyvals]
\shuntlimit[options%keyvals]
\berthsignal[options%keyvals]
\berthsign[options%keyvals]#*

#keyvals:\distantsignal#c,\speedsignal#c,\speedsign#c,\blocksignal#c,\routesignal#c,\shuntsignal#c,\shuntlimit#c,\berthsignal#c,\berthsign#c
face=#forward,backward
forward
backward
position=#left,right
shift label={%<(x,y)%>}
foreground=#%color
rotate=%<degrees%>
#endkeyvals

#keyvals:\speedsignal#c,\speedsign#c
speed=
#endkeyvals

#keyvals:\routesignal#c
speed=
locked#true,false
#endkeyvals

#keyvals:\shuntsignal#c
locked#true,false
#endkeyvals

\viewpoint[options%keyvals]
\clearingpoint[options%keyvals]
\standardclearing[options%keyvals]
\blockclearing[options%keyvals]
\routeclearing[options%keyvals]

#keyvals:\viewpoint#c,\clearingpoint#c,\standardclearing#c,\blockclearing#c,\routeclearing#c
face=#forward,backward
forward
backward
position=#left,right
foreground=#%color
rotate=%<degrees%>
#endkeyvals

#keyvals:\clearingpoint#c
standard
block
route
shift label={%<(x,y)%>}
#endkeyvals

#keyvals:\standardclearing#c,\blockclearing#c,\routeclearing#c
shift label={%<(x,y)%>}
#endkeyvals

\brakingpoint[options%keyvals]
\movementauthority[options%keyvals]
\dangerpoint[options%keyvals]

#keyvals:\brakingpoint#c,\movementauthority#c,\dangerpoint#c
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

#keyvals:\route#c,\directioncontrol#c
face=#forward,backward
forward
backward
background=#%color
#endkeyvals

#keyvals:\directioncontrol#c
bidirectional
#endkeyvals

\balise[options%keyvals]

#keyvals:\balise#c
face=#forward,backward
forward
backward
switched
shift label={%<(x,y)%>}
foreground=#%color
along={%<list of integers%>}
oppose={%<list of integers%>}
along switched={%<list of integers%>}
oppose switched={%<list of integers%>}
index
#endkeyvals

\transmitter[options%keyvals]

#keyvals:\transmitter#c
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

#keyvals:\trackloop#c
position=#left,right
shift label={%<(x,y)%>}
foreground=#%color
#endkeyvals

\platform[options%keyvals]

#keyvals:\platform#c
side=#left,right,both
length=##L
width=##L
foreground=#%color
#endkeyvals

\levelcrossing[options%keyvals]

#keyvals:\levelcrossing#c
barrier=#none,semi,full
side=#both,left,right
road width=##L
width=##L
no road
foreground=#%color
#endkeyvals

\bridge[options%keyvals]

#keyvals:\bridge#c
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

#keyvals:\pylon#c
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

#keyvals:\distantpoweroff#c,\poweroff#c,\poweron#c,\distantpantographdown#c,\pantographdown#c,\pantographup#c,\wirelimit#c
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

#keyvals:\berth#c
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

#keyvals:\hectometer#c
hectometer base={%<(x,y)%>}
orientation=#left,right
shift label={%<(x,y)%>}
hectometer color=#%color
#endkeyvals

\trackmarking[color%plain]

## not documented ##
# from tikzlibrarytrackschematic.constructions.code.tex
\background#S
\barrier#S
\foreground#S
\objectwidth#S
\roadwidth#S
\shiftleft#S
\shiftright#S
\side#S
\sidefactor#S
\trafficfactor#S
\trafficpractice#S

# from tikzlibrarytrackschematic.electrics.code.tex
\align#S
\coordcommand#S
\facefactor#S
\labelcommand#S
\labelcontent#S
\labelcoord#S
\signalcolor#S

# from tikzlibrarytrackschematic.measures.code.tex
\basecoord#S
\hectometercolor#S
\objectlength#S

# from tikzlibrarytrackschematic.topology.code.tex
\backwardpoints#S
\branch#S
\branchfactor#S
\forwardpoints#S
\friction#S
\labelcontentleft#S
\labelcontentright#S
\operationmode#S
\patterntype#S
\points#S

# from tikzlibrarytrackschematic.trafficcontrol.code.tex
\along#S
\alongswitched#S
\distantspeed#S
\face#S
\oppose#S
\opposeswitched#S
\speed#S
\trafficfactorTEST#S
\trafficfactorX#S
\type#S

# from tikzlibrarytrackschematic.vehicles.code.tex
\baseX#S
\baseY#S
\bendfactor#S
\bendleftcoord#S
\bendlength#S
\bendrightcoord#S
\bendrightX#S
\bendrightY#S
\bendX#S
\bendY#S
\frontBendfactor#S
\frontBendX#S
\labelalign#S
\labelanchor#S
\rearBendfactor#S
\rearBendX#S
\rearBendY#S
\trainrun#S
