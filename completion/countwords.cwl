# countwords package
# Matthew Bertucci 2026/04/06 for v1.0

#include:luatexbase
#include:luapackageloader

#keyvals:\usepackage/countwords#c
threshold=%<number%>
#endkeyvals

\countwordsstart{counter}
\countwordsstop{counter}