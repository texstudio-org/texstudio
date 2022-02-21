# pst-math package
# Matthew Bertucci 2/19/2022 for v0.65

#include:pst-calculate
#include:ifluatex
#include:xstring
#include:xkeyval

\pstPI%<<num>%>

\defineRandIntervall(min,max){number}
\makeSimpleRandomNumberList
\makeRandomNumberList
\getNumberFromList{number}

\PSTmathLoaded#S
\fileversion
\filedate#S