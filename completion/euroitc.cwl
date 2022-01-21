# euroitc package
# Matthew Bertucci 1/18/2022 for v1.1a

#include:keyval
#include:ifthen

#keyvals:\usepackage/euroitc#c
sans
serif
scaled
scaled=%<factor%>
bolder
#endkeyvals

\euro
\sanseuro#*
\serifeuro#*
\ProcessOptionsWithKV{family}#S