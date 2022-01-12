# PlayfairDisplay package
# Matthew Bertucci 8/28/2021

#include:ifxetex
#include:ifluatex
#include:textcomp
#include:xkeyval
#include:fontenc
#include:fontaxes
#include:mweights

#keyvals:\usepackage/PlayfairDisplay#c
scale=%<factor%>
scaled=%<factor%>
type1
black
lining#true,false
lf#true,false
oldstyle#true,false
osf#true,false
#endkeyvals

\playfair#n
\playfairblack#n
\playfairOsF#n
\playfairLF#n
\sufigures#n
\textsu{text}#n
\textsuperior{text}#*n
\playfairfamily#*
