# gillius package
# Matthew Bertucci 1/11/2022

#include:ifxetex
#include:ifluatex
#include:textcomp
#include:xkeyval
#include:fontenc
#include:fontaxes

#keyvals:\usepackage/gillius#c
scale=%<factor%>
scaled=%<factor%>
default
sfdefault
type1
condensed
#endkeyvals

\gillius
\gilliuscondensed
\gilliusfamily#*
\gilliuscondensedfamily#*