# lcg package
# Matthew Bertucci 9/30/2021 for v1.3

#include:keyval

\rand
\reinitrand[options%keyvals]
\chgrand[options%keyvals]

#keyvals:\reinitrand,\chgrand,\usepackage/lcg#c
counter=%<counter%>
first=%<integer%>
last=%<integer%>
seed=%<integer%>
quiet
#endkeyvals
