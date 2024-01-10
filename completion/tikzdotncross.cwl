# tikzdotncross package
# Matthew Bertucci 2023/01/08 for v1.0

#include:tikzlibraryintersections

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