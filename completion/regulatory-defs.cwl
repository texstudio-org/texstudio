# regulatory-defs package
# Matthew Bertucci 2026/09/12 for v1.0.0

#include:regulatory-struct
#include:glossaries
#include:glossaries-extra

\describe{gls-label%special}
\loadglsdefs{bib file}
\newdefinition{gls-label%specialDef}{name}{description%text}#s#%gls-label
\printdefs[style]{width}
\printdefs{width}