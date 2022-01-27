# engord package
# Matthew Bertucci 11/17/2021 for v1.9

#include:ltxcmds
#include:infwarerr

#keyvals:\usepackage/engord#c
normal
raise
#endkeyvals

\engord{counter}
\engordnumber{number}
\engordletters{text%plain}#*
\engorderror{number}#*
\ifengordraise#*
\engordraisetrue#*
\engordraisefalse#*
