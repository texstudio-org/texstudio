# logoetalab package
# Matthew Bertucci 2023/11/21 for v0.1.1

#include:graphicx
#include:tikz
#include:tikzlibrarycalc
#include:xstring
#include:calc
#include:simplekv

\loetalab
\loetalab[options%keyvals]
\loetalab*
\loetalab*[options%keyvals]
\affloetalab
\affloetalab[options%keyvals]
\affloetalab*
\affloetalab*[options%keyvals]

#keyvals:\loetalab,\loetalab*,\affloetalab,\affloetalab*
Couleur=#%color
Legende#true,false
TexteLegende={%<texte%>}
#endkeyvals

\loetalabtkz
\loetalabtkz[options%keyvals]
\loetalabtkz*
\loetalabtkz*[options%keyvals]
\affloetalabtkz
\affloetalabtkz[options%keyvals]
\affloetalabtkz*
\affloetalabtkz*[options%keyvals]

#keyvals:\loetalabtkz,\loetalabtkz*,\affloetalabtkz,\affloetalabtkz*
Couleur=#%color
Hauteur=
DecalageV=
#endkeyvals
