# antanilipsum package
# Matthew Bertucci 9/22/2021 for v0.8.1

#include:expl3
#include:xparse

\antani
\antani[num]
\antani[num][num]
\antani[%<num%>-%<num%>]
\antani[%<num%>-%<num%>][%<num%>-%<num%>]
\antani*
\antani*[num]
\antani*[num][num]
\antani*[%<num%>-%<num%>]
\antani*[%<num%>-%<num%>][%<num%>-%<num%>]
\antanidef{cmd}{num}#*d