# lua-widow-control package
# Matthew Bertucci 2022/08/24 for v2.2.2

#include:luatex
#include:microtype

\lwcsetup{options%keyvals}

#keyvals:\lwcsetup,\usepackage/lua-widow-control#c
enable
disable
strict
emergencystretch=##L
disablecmds={%<\macro1,\macro2,...%>}
widowpenalty=%<integer%>
orphanpenalty=%<integer%>
nobreak=#keep,split,warn
max-cost=%<integer%>
debug#true,false
draft#true,false
balanced
#endkeyvals

#keyvals:\usepackage/lua-widow-control#c
microtype#true,false
#endkeyvals

# deprecated
\lwcenable#S
\lwcdisable#S
\lwcemergencystretch#S
\lwcdisablecmd{cmd}#S
