# newpax package
# Matthew Bertucci 2022/06/13 for v0.51

#include:graphicx
#include:ltxcmds
#include:kvsetkeys
#include:kvoptions
#include:auxhook
#include:etoolbox

\newpaxsetup{options%keyvals}

#keyvals:\newpaxsetup
usefileattributes#true,false
destsuffix=%<suffix%>
addannots#true,false
paxextension=#pax,newpax
#endkeyvals