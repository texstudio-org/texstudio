# tablefootnote package
# Matthew Bertucci 11/29/2021 for v1.1c

#include:ltxcmds
#include:letltxmacro
#include:xifthen
#include:etoolbox

\tablefootnote{text}
\tablefootnote[number]{text}

\swtablemakefntext{text}#*
\tablemakefntext{text}#S
\tfnendorigsidewaystable#S
\tfnorigsidewaystable#S
