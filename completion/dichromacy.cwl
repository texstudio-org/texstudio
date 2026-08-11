# dichromacy package
# Matthew Bertucci 2026/08/11 for v0.3.0

#include:iftex
#include:xcolor
#include:graphicx

\cvdtype{type%keyvals}
\cvdseverity{factor}
\cvdenable
\cvddisable
\cvdincludegraphics{imagefile}#*g
\cvdincludegraphics[options%keyvals]{imagefile}#*g
\cvddefinecolor{source color}{target color%specialDef}#s#%color
\cvddefinecolor[options%keyvals]{source color}{target color%specialDef}#s#%color
\cvdset{options%keyvals}

#keyvals:\cvdset,\cvddefinecolor,\usepackage/dichromacy#c
type=#protanopia,deuteranopia,tritanopia
severity=%<factor%>
graphics hook#true,false
graphics convert#true,false
protanopia
deuteranopia
tritanopia
protanomaly
deuteranomaly
tritanomaly
#endkeyvals

#keyvals:\cvdtype
protanopia
deuteranopia
tritanopia
#endkeyvals