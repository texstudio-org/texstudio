# pst-spinner package
# Matthew Bertucci 2/22/2022 for v0.13

#include:pstricks
#include:pst-node
#include:pst-plot
#include:pst-3d
#include:pst-grad
#include:pst-tools
#include:pst-xkey

\SolarSystem
\SolarSystem[options%keyvals]

#keyvals:\SolarSystem#c
Day=%<day%>
Month=%<month%>
Year=%<year%>
Hour=%<hour%>
Minute=%<minute%>
Second=%<second%>
solarValues#true,false
viewpoint=
#endkeyvals

\Jupiter#*
\Saturne#*
\PSTSOLARSYSTEMELoaded#S