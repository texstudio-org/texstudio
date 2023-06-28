# gitver package
# Matthew Bertucci 2022/07/18 for v1.4

#include:hyperref
#include:catchfile
#include:pdftexcmds
#include:datetime2
#include:ifthen
#include:ifluatex
#include:shellesc

#keyvals:\usepackage/gitver#c
noheader
nopdfinfo
#endkeyvals

\gitVer
\versionBox

\getenv{env-var}#*
\getenv[cmd]{env-var}#*d
