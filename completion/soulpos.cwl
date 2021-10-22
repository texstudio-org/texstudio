# soulpos package
# Matthew Bertucci 10/19/2021 for v1.2

#include:soulutf8
#include:keyval

\ulposdef{cmd}{definition}#d
\ulposdef{cmd}[options%keyvals]{definition}#d

#keyvals:\ulposdef
xoffset=##L
xoffset-start=##L
xoffset-end=##L
gap=##L
gap-start=##L
gap-end=##L
hyphens=#include,exclude
overdraw#true,false
#endkeyvals

\ifulstarttype{type}{true}{false}
\ifulendtype{type}{true}{false}
\ulstarttype
\ulendtype
\ulpostolerance#*
\ulwidth#*