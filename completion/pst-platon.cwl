# pst-platon package
# Matthew Bertucci 2/25/2022 for v0.01

#include:pstricks
#include:pst-3d
#include:pst-xkey

\psTetrahedron
\psTetrahedron[options%keyvals]
\psHexahedron
\psHexahedron[options%keyvals]
\psOctahedron
\psOctahedron[options%keyvals]
\psDodecahedron
\psDodecahedron[options%keyvals]
\psIcosahedron
\psIcosahedron[options%keyvals]

#keyvals:\psTetrahedron#c,\psHexahedron#c,\psOctahedron#c,\psDodecahedron#c,\psIcosahedron#c
PstPicture#true,false
Frame#true,false
Viewpoint=%<x y z%>
faceName=#\Alph,\alph,\arabic,\Roman,\roman
faceNameFont=%<font commands%>
colorType=%<type%>
psscale=%<factor%>
#endkeyvals

\colorTypeA#*
\colorTypeB#*

\face#S
\faceA#S
\faceB#S
\faceC#S
\faceD#S
\faceE#S
\faceF#S
\faceG#S
\faceH#S
\Nx#S
\nx#S
\Ny#S
\ny#S
\Nz#S
\nz#S
\Ox#S
\ox#S
\Oy#S
\oy#S
\Oz#S
\oz#S
\RA#S
\ra#S
\rb#S
\rc#S
\rd#S