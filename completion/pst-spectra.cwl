# pst-spectra package
# Matthew Bertucci 2/27/2022 for v0.91

#include:pstricks
#include:multido
#include:pst-xkey

\psspectrum
\psspectrum[options%keyvals]

#keyvals:\psspectrum
begin=%<wavelength in nm%>
end=%<wavelength in nm%>
gamma=%<factor%>
brightness=%<factor%>
numlines=%<integer%>
lines=%<wavelengths in nm%>
element=%<text%>
emission#true,false
absorption#true,false
lwidth=%<width%>
lmin=%<factor%>
axe#true,false
DI=%<length in nm%>
axecolor=#%color
axewidth=%<width%>
wlangle=%<degrees%>
wlcmd=%<font commands%>
#endkeyvals

\PSTwlLoaded#S
\pstwlfileversion#S
\pstwlfiledate#S