# pst-diffraction package
# Matthew Bertucci 2/25/2022 for v1.02

#include:pstricks
#include:pst-3dplot
#include:pst-xkey

\psdiffractionRectangle
\psdiffractionRectangle[options%keyvals]

#keyvals:\psdiffractionRectangle
a=%<area%>
Alpha=%<number%>
colorMode=#0,1,2,3
contrast=%<number%>
f=%<focal length%>
IIID#true,false
k=%<height%>
lambda=%<wavelength in nm%>
pixel=%<factor%>
s=%<distance%>
twoSlit
#endkeyvals

\psdiffractionCircular
\psdiffractionCircular[options%keyvals]

#keyvals:\psdiffractionCircular
colorMode=#0,1,2,3
contrast=%<number%>
d=%<distance%>
f=%<focal length%>
IIID#true,false
lambda=%<wavelength in nm%>
pixel=%<factor%>
r=%<radius%>
twoHole
#endkeyvals

\psdiffractionTriangle
\psdiffractionTriangle[options%keyvals]

#keyvals:\psdiffractionTriangle
colorMode=#0,1,2,3
contrast=%<number%>
f=%<focal length%>
h=%<height%>
scale=%<factor%>
IIID#true,false
lambda=%<wavelength in nm%>
#endkeyvals

\PSTDiffractionLoaded#S