# lua-widow-control package
# Matthew Bertucci 2022/11/22 for v3.0.0

#include:luatex
#include:microtype

\lwcsetup{options%keyvals}

#keyvals:\lwcsetup,\usepackage/lua-widow-control#c
disable
enable
disablecmds={%<\macro1,\macro2,...%>}
emergencystretch=##L
widowpenalty=%<integer%>
orphanpenalty=%<integer%>
nobreak=#keep,split,warn
max-cost=%<integer%>
draft
showcosts#true,false
showcolours#true,false
draftoffset=##L
debug#true,false
default
strict
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
