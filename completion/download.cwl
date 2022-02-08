# download package
# Matthew Bertucci 2/7/2022 for v1.2

#include:expl3
#include:l3keys2e
#include:pdftexcmds
#include:xparse

#keyvals:\usepackage/download#c
engine=#auto,curl,wget,aria2,axel
#endkeyvals

\download{URL}
\download[filename%URL]{URL}