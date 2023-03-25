# milsymb package
# Matthew Bertucci 2023/03/24 for v1.02

#include:tikz
#include:lmodern
#include:fix-cm
#include:arevmath
#include:marvosym
#include:acronym
#include:amssymb
#include:xifthen
#include:textcomp
#include:tikzlibraryshapes.geometric
#include:tikzlibraryshapes.symbols
#include:tikzlibrarypositioning
#include:tikzlibrarycalc

\MilAir[options%keyvals]
\MilAir[options%keyvals](location)
\MilAir[options%keyvals](location)(name){label}
\MilMissile[options%keyvals]
\MilMissile[options%keyvals](location)
\MilMissile[options%keyvals](location)(name){label}
\MilLand[options%keyvals]
\MilLand[options%keyvals](location)
\MilLand[options%keyvals](location)(name){label}
\MilEquipment[options%keyvals]
\MilEquipment[options%keyvals](location)
\MilEquipment[options%keyvals](location)(name){label}
\MilInstallation[options%keyvals]
\MilInstallation[options%keyvals](location)
\MilInstallation[options%keyvals](location)(name){label}
\MilSeaSurface[options%keyvals]
\MilSeaSurface[options%keyvals](location)
\MilSeaSurface[options%keyvals](location)(name){label}
\MilSeaSubsurface[options%keyvals]
\MilSeaSubsurface[options%keyvals](location)
\MilSeaSubsurface[options%keyvals](location)(name){label}
\MilMine[options%keyvals]
\MilMine[options%keyvals](location)
\MilMine[options%keyvals](location)(name){label}
\MilSpace[options%keyvals]
\MilSpace[options%keyvals](location)
\MilSpace[options%keyvals](location)(name){label}
\MilActivity[options%keyvals]
\MilActivity[options%keyvals](location)
\MilActivity[options%keyvals](location)(name){label}
\MilDebris[options%keyvals]
\MilDebris[options%keyvals](location)
\MilDebris[options%keyvals](location)(name){label}
\OwnShip[options%keyvals]
\OwnShip[options%keyvals](location)
\OwnShip[options%keyvals](location)(name){label}

\begin{landgroup}
\begin{landgroup}[options%keyvals]
\end{landgroup}

\begin{landheadquarters}
\begin{landheadquarters}[options%keyvals]
\end{landheadquarters}

\clipfriendly#*
\cliphostile#*
\clipneutral#*
\clipunknown#*

\itemlength#S
\theexitem#S

friendlyA#B
hostileA#B
neutralA#B
unknownA#B
friendlyB#B
hostileB#B
neutralB#B
unknownB#B
offwhite#B
lightgray#B