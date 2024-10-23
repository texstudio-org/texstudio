# tikzdotncross package
# Matthew Bertucci 2023/10/23 for v1.2

#include:tikzlibraryintersections

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
