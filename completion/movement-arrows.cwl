# movement-arrows package
# Matthew Bertucci 2023/06/02 for v2.0

#include:tikz
#include:tikzlibraryext.paths.ortho
#include:etoolbox
#include:calc

\mkword{word%text}
\mkword[name]{word%text}

\mvarrow{start}{end}
\mvarrow[options]{start}{end}
\mvarrow*{start}{end}
\mvarrow*[options]{start}{end}
\mvlink{start}{end}
\mvlink[options]{start}{end}
\mvlink*{start}{end}
\mvlink*[options]{start}{end}

\setarrowstyle{style}

\arrowheight#L
\extraexheight#L
\glarrowheight#L

\arrowstrut
\arrowgloss
