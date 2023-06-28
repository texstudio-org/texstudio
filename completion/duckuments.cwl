# duckuments package
# Matthew Bertucci 9/21/2021 for v0.5

#include:letltxmacro
#include:l3keys2e

\duckument
\duckument[options%keyvals]
\blindduck
\blindduck[options%keyvals]

#keyvals:\duckument#c,\blindduck#c
toc#true,false
maths=#both,inline,display,none
full
all
immediate#true,false
#endkeyvals

\ducklist{environment}
\ducklist*{environment}
\ducklistlist{environment}
\ducklistlist*{environment}
\duckitemize
\duckenumerate
\duckdescription

\duckumentsCreateExampleFiles#*
\duckumentsDrawRandomDucks#*
\duckumentsDrawRandomDucks[number]#*
\duckumentsDrawRandomDucks*#*
\duckumentsDrawRandomDucks*[number]#*
