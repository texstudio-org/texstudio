# pst-solarsystem package
# Matthew Bertucci 2024/01/30 for v0.14

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
language=#DE,FR,EN
#endkeyvals

\Jupiter#*
\Saturn#*
\PSTSOLARSYSTEMELoaded#S
\SolarSystemLangEN#S
\SolarSystemLangDE#S
\SolarSystemLangFR#S
