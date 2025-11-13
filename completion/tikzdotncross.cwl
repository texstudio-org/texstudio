# tikzdotncross package
# Matthew Bertucci 2025/11/12 for v1.3b

#include:tikzlibrarymath
#include:tikzlibraryintersections
#include:etoolbox

\setpindefaults{options%keyvals}

#keyvals:\usepackage/tikzdotncross#c,\setpindefaults
pinsize=%<number%>
pinang=%<degrees%>
pincolor=#%color
pinlength=%<number%>
coordcolor=#%color
#endkeyvals

\showcoordstrue
\showcoordsfalse

\showcoords{on|off}

\ncoord(coord)
\pincoord(coord)
\dotcoord(coord)
\dotpincoord(coord)
\odotcoord(coord)
\odotpincoord(coord)

\pathcross{coordA}{coordB}{path-name}
\pathcross{coordA}{coordB}{path-name}[width]
\pathcross[cross-name]{coordA}{coordB}{path-name}
\pathcross[cross-name]{coordA}{coordB}{path-name}[width]
\pathcross*{coordA}{coordB}{path-name}
\pathcross*{coordA}{coordB}{path-name}[width]
\pathcross*[cross-name]{coordA}{coordB}{path-name}
\pathcross*[cross-name]{coordA}{coordB}{path-name}[width]
