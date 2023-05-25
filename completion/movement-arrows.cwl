# movement-arrows package
# Matthew Bertucci 2023/05/22 for v1.0

#include:tikz
#include:tikzlibraryext.paths.ortho
#include:etoolbox
#include:calc

\mkword{word%text}
\mkword[name]{word%text}

\arrow{start}{end}
\arrow[options]{start}{end}
\arrow*{start}{end}
\arrow*[options]{start}{end}

\arrowheight#L
\extraexheight#L