# pgf-interference package
# Matthew Bertucci 1/21/2022 for v0.1

#include:tikz

#keyvals:\usepackage/pgf-interference#c
draft
#endkeyvals

\pgfinterferencepattern{options%keyvals}
\pgfinterferenceoptions{options%keyvals}

#keyvals:\pgfinterferencepattern,\pgfinterferenceoptions
wavelength=%<number%>
intensity=%<number%>
slits=%<integer%>
slit-distance=%<number%>
slit-width=%<number%>
screen-distance=%<number%>
screen-width=%<number%>
screen-height=%<number%>
scale=%<factor%>
screen-color=#%color
ruler=#above,below,screen,none
#endkeyvals