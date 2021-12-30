# nbaseprt package
# Matthew Bertucci 12/29/2021 for v0.11

#include:numprint
#include:ifthen

#keyvals:\usepackage/nbaseprt#c
nosepfour
sepfour
noaddmissingzero
addmissingzero
noaddplus
addplus
noaddplusexponent
addplusexponent
noautolanguage
autolanguage
np
oldcolumntypes
newcolumntypes
boldmath
warning
error
debug
#endkeyvals

#ifOption:np
\np{number}
\np[unit]{number}
\nbp{number}
#endif

\nbaseprint{number}

\nbaseposttext
\nbasepretext