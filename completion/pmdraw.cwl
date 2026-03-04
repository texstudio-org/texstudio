# pmdraw package
# Matthew Bertucci 2026/03/04 for v2.3

#include:xkeyval
#include:tikz
#include:tikzlibrarymath
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarycalligraphy
#include:tikzlibrarybackgrounds

\pmdEmpty

\pmdBrick[options%keyvals]{U-edges}{L-edges}{T-edges}

#keyvals:\pmdBrick#c
degree=%<integer%>
degree top=%<integer%>
degree bottom=%<integer%>
blank top=%<integer%>
blank bottom=%<integer%>
row sep=%<integer%>
vertices={%<\draw options%>}
no vertex bottom %<num 0-19%>=%<integer%>
no vertex top %<num 0-19%>=%<integer%>
ghost vertex bottom %<num 0-19%>=%<integer%>
ghost vertex top %<num 0-19%>=%<integer%>
ghosts={%<\draw options%>}
vertices options={%<code%>}
ghosts options={%<code%>}
labels
labels top
labels bottom
labels start=%<integer%>
labels top start=%<integer%>
labels bottom start=%<integer%>
no label bottom %<num 0-19%>=%<integer%>
no label top %<num 0-19%>=%<integer%>
labels top draw={%<\draw options%>}
labels top node={%<\node options%>}
labels bottom draw={%<\draw options%>}
labels bottom node={%<\node options%>}
labels top options={%<code%>}
labels bottom options={%<code%>}
no dots
dots draw={%<\draw options%>}
dots node={%<\node options%>}
vertices top phantom
vertices bottom phantom
vertices top uncover={%<overlay spec%>}
vertices bottom uncover={%<overlay spec%>}
levels=%<integer%>
levels top=%<integer%>
levels bottom=%<integer%>
levels sep=%<number%>
levels sep top=%<number%>
levels sep bottom=%<number%>
edges={%<\draw options%>}
edges non-transversal={%<\draw options%>}
edges upper={%<\draw options%>}
edges lower={%<\draw options%>}
edges transversal={%<\draw options%>}
edges first
edges first=#0,1
edges last
edges last=#0,1
transversals first
edges phantom
edges uncover={%<overlay spec%>}
brace={%<options%>}
brace draw={%<\draw options%>}
brace node={%<\node options%>}
bracket={%<options%>}
bracket draw={%<\node options%>}
bracket node={%<\node options%>}
decorate before={%<code%>}
decorate after={%<code%>}
#endkeyvals

\pmdDiagram{bricks}
\pmdDiagram[options%keyvals]{bricks}
\pmdProduct{A-edges}{T-bricks}{B-bricks}
\pmdProduct[options%keyvals]{A-edges}{T-bricks}{B-bricks}
\pmdProductTriple{ATedges}{ABedges}{Tbricks}}{Mbricks}{Bbricks}
\pmdProductTriple[options%keyvals]{ATedges}{ABedges}{Tbricks}}{Mbricks}{Bbricks}
\pmdEquiv{E bricks}
\pmdEquiv[options%keyvals]{E bricks}

#keyvals:\pmdDiagram#c,\pmdProduct#c,\pmdProductTriple#c,\pmdEquiv#c
row sep=%<integer%>
tikz={%<TikZ options%>}
dots options={%<code%>}
grid
decorate before={%<code%>}
decorate after={%<code%>}
#endkeyvals

#keyvals:\pmdProduct#c,\pmdProductTriple#c,\pmdEquiv#c
diagram sep=%<number%>
vertex sep=%<number%>
edges added={%<\draw options%>}
edges added phantom
edges added uncover={%<overlay spec%>}
#endkeyvals

\pmdSetDefault{options%keyvals}
\pmdSetToOriginalDefault

#keyvals:\pmdSetDefault#c
brick={%<keyvals%>}
NTedges={%<keyvals%>}
Tedges={%<keyvals%>}
brace={%<keyvals%>}
diagram={%<keyvals%>}
#endkeyvals
