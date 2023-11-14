# overlock package
# Matthew Bertucci 1/11/2022

#include:ifxetex
#include:ifluatex
#include:xkeyval
#include:fontenc
#include:fontaxes
#include:mweights

#keyvals:\usepackage/overlock#c
scaled=%<factor%>
lining
oldstyle
default
sfdefault
type1
black
#endkeyvals

\overlock
\overlockBlack
\liningnums{text}
\overlockfamily#*
