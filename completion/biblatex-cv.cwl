# biblatex-cv package
# Matthew Bertucci 4/25/2022 for v0.01

#include:biblatex
#include:totcount
#include:xpatch

#keyvals:\usepackage/biblatex-cv#c
verbose-committee
verbose-education
verbose-teaching
verbose-lists
#endkeyvals

\highlightname{family}{given}{prefix}{suffix}
\NewValue#*
\mkbibdown{number}#*

# from biblatex-cv.bbx
#include:datenumber
#include:fp
\addpar#*