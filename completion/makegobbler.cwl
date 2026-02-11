# makegobbler package
# Matthew Bertucci 2026/02/02 for v0.3

#keyvals:\usepackage/makegobbler#c
ifthen
tense
#endkeyvals

#ifOption:ifthen
#include:ifthen
#endif

\MGBkeep
\MGBkeep*
\MGBdrop
\MGBdrop*
\MGBkeepelse
\MGBkeepelse*
\MGBdropelse
\MGBdropelse*
\makegobbler{command}#d
\makeungobbler{command}#d