# pmdraw package
# Matthew Bertucci 2023/11/14 for v1.1

#include:keyval
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
vertices options={%<code%>}
labels
labels top
labels bottom
labels start=%<integer%>
labels top start=%<integer%>
labels bottom start=%<integer%>
labels top draw={%<\draw options%>}
labels top node={%<\node options%>}
labels bottom draw={%<\draw options%>}
labels bottom node={%<\node options%>}
labels top options={%<code%>}
labels bottom options={%<code%>}
no dots
dots draw={%<\draw options%>}
dots node={%<\node options%>}
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
transversals first
brace={%<options%>}
brace draw={%<\draw options%>}
brace node={%<\node options%>}
decorate before={%<code%>}
decorate after={%<code%>}
#endkeyvals

\pmdDiagram{bricks}
\pmdDiagram[options%keyvals]{bricks}
\pmdProduct{A-edges}{T-bricks}{B-bricks}
\pmdProduct[options%keyvals]{A-edges}{T-bricks}{B-bricks}

#keyvals:\pmdDiagram#c,\pmdProduct#c
row sep=%<integer%>
tikz={%<TikZ options%>}
dots options={%<code%>}
grid
decorate before={%<code%>}
decorate after={%<code%>}
#endkeyvals

#keyvals:\pmdProduct#c
diagram sep=%<number%>
edges added={%<\draw options%>}
#endkeyvals
