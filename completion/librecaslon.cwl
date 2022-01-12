# librecaslon package
# Matthew Bertucci 8/10/2021

#include:ifxetex
#include:ifluatex
#include:xkeyval
#include:textcomp
#include:fontenc
#include:fontaxes

#keyvals:\usepackage/librecaslon#c
scale=%<factor%>
scaled=%<factor%>
type1
lining#true,false
lf#true,false
oldstyle#true,false
osf#true,false
#endkeyvals

\librecaslon
\librecaslonLF
\librecaslonOsF
\librecaslonTLF
\textsu{text}
\sufigures
\textin{text}
\infigures
\useosf#*
