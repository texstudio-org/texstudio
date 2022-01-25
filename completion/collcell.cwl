# collcell package
# Matthew Bertucci 12/6/2021 for v0.5

#include:array
#include:etoolbox

#keyvals:\usepackage/collcell#c
verb
noverb
robustcr
norobustcr
#endkeyvals

#ifOption:verb
#include:tabularx
#endif

\collectcell
\collectcell{cmd}#Sd
\endcollectcell
\ccunskip#*
\cci#*
