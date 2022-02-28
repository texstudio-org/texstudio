# pst-coxcoor package
# Matthew Bertucci 2/26/2022 for v0.98

#include:pstricks
#include:pst-xkey

\Polygon
\Polygon[options%keyvals]
\Simplex
\Simplex[options%keyvals]
\gammapn
\gammapn[options%keyvals]
\betapn
\betapn[options%keyvals]
\gammaptwo
\gammaptwo[options%keyvals]
\betaptwo
\betaptwo[options%keyvals]

\pscolorVertices#*
\pscolorCenters#*
\pssizeVertices#*
\pssizeCenters#*
\PstCoxeter#S