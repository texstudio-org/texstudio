# pst-kepler package
# Matthew Bertucci 2026/01/03 for v0.01

#include:pstricks
#include:pst-eucl
#include:hvextern
#include:xint
#include:xintexpr
#include:animate
#include:pst-solides3d
#include:pst-xkey

\psKeplerModel
\psKeplerModel(x,y)
\psKeplerModel[options%keyvals]
\psKeplerModel[options%keyvals](x,y)
\psKeplerShow
\psKeplerShow(x,y)
\psKeplerShow[options%keyvals]
\psKeplerShow[options%keyvals](x,y)
\psKeplerAnimate
\psKeplerAnimate[options%keyvals]

# not documented
\psKeplerTetrahedron(arg)#S
\psKeplerHexahedron(arg)#S
\psKeplerOctahedron(arg)#S
\psKeplerDodecahedron(arg)#S
\psKeplerIcosahedron(arg)#S
\psKeplerWorld(arg)#S