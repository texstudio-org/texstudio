# cprotect package
# Matthew Bertucci 10/5/2021 for v1.0

#include:ifthen
#include:suffix

\cprotect
\cprotect[args]
\cMakeRobust
\icprotect
\cprotEnv
\CPTbegin{envname}#*
\ReadVerbatimUntil[arg1]{arg2}#*