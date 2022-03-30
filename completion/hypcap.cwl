# hypcap package
# Matthew Bertucci 11/5/2021 for v1.12

#include:letltxmacro

#keyvals:\usepackage/hypcap#c
figure
figure*
table
table*
all
#endkeyvals

\capstart
\hypcapspace#*
\hypcapredef{envname}#*
\capstartfalse
\capstarttrue
\ifcapstart#*
