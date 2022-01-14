# kurdishlipsum package
# Matthew Bertucci 1/13/2022 for v1.1

#include:biditools

#keyvals:\usepackage/kurdishlipsum#c
nopar
#endkeyvals

\setkurdishlipsumdefault{%<num%>-%<num%>}
\kurdishlipsum
\kurdishlipsum[num]
\kurdishlipsum[%<num%>-%<num%>]
\kurdishlipsum*
\ChangeKurdishlipsumPar#*