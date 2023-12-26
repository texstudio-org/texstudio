# changebar package
# Matthew Bertucci 2023/12/26 for v3.7a

#keyvals:\usepackage/changebar#c
dvitoln03
dvitops
dvips
emtex
textures
vtex
pdftex
xetex
luatex
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
