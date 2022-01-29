# changebar package
# Matthew Bertucci 11/3/2021 for v3.6c

#keyvals:\usepackage/changebar#c
DVItoLN03
dvitoln03
DVItoPS
dvitops
DVIps
dvips
emTeX
emtex
textures
Textures
VTeX
vtex
PDFTeX
pdftex
XeTeX
xetex
outerbars
innerbars
leftbars
rightbars
traceon
traceoff
tracestacks
grey
color
xcolor
#endkeyvals

#ifOption:color
#include:color
\cbcolor{color}
#endif

#ifOption:xcolor
#include:xcolor
\cbcolor{color}
#endif

\cbstart
\cbend
\begin{changebar}
\end{changebar}
\cbdelete
\cbdelete[width]
\nochangebars

\changebarwidth#*
\deletebarwidth#*
\changebarsep#*
\thechangebargrey#*
\driver{driver name}#*
