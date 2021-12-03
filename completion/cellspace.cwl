# cellspace package
# Matthew Bertucci 11/18/2021 for v1.8.1

#include:ifthen
#include:array
#include:calc
#include:xkeyval

#ifOption:math
#include:amsmath
#endif

\cellspacetoplimit
\cellspacebottomlimit

\bcolumn{arg}#*
\ecolumn#*

\addparagraphcolumntypes{col type}