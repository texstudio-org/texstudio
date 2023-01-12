# colorspace package
# Matthew Bertucci 1/12/2021 for v1.3

#include:xcolor

#keyvals:\usepackage/colorspace#c
illuminant=#a,c,e,d50,d55,d65,d75
overprint
opm=#0,1
knockout
#endkeyvals

\definespotcolor{name%specialDef}{PDF name}{CMYK-equivalent}#s#%color
\definespotcolor{name%specialDef}{PDF name}[model]{equivalent}#s#%color
\definespotcolor{%<name%>}{%<PDF name%>}[alt=lab]{%<lab-values%>}#

\definecolorspace{%<name%>}{mixed}{%<color-list%>}
\definecolorspace*{%<name%>}{iccbased}{%<icc-file%>}
\pagecolorspace{colorspace list}
\resetpagecolorspace

\overprintstate{state}#*
\textoverprint{text}#*
\textoverprint[state]{text}#*