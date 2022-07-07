# hypdestopt package
# Matthew Bertucci 2022/07/05 for v2.7

#include:iftex
#include:pdftexcmds
#include:auxhook
#include:pdfescape

#keyvals:\usepackage/hypdestopt#c
verbose
num
name
#endkeyvals

#ifOption:name
#include:alphalph
#endif

\theHypDest#*