# pst-math package
# Matthew Bertucci 2023/07/03 for v0.67

#include:multido
#include:pstricks
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
