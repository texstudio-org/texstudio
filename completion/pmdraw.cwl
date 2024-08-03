# pmdraw package
# Matthew Bertucci 2024/06/02 for v1.4

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
no vertex bottom 1=%<integer%>
no vertex bottom 2=%<integer%>
no vertex bottom 3=%<integer%>
no vertex bottom 4=%<integer%>
no vertex bottom 5=%<integer%>
no vertex bottom 6=%<integer%>
no vertex bottom 7=%<integer%>
no vertex bottom 8=%<integer%>
no vertex bottom 9=%<integer%>
no vertex top 1=%<integer%>
no vertex top 2=%<integer%>
no vertex top 3=%<integer%>
no vertex top 4=%<integer%>
no vertex top 5=%<integer%>
no vertex top 6=%<integer%>
no vertex top 7=%<integer%>
no vertex top 8=%<integer%>
no vertex top 9=%<integer%>
vertices options={%<code%>}
labels
labels top
labels bottom
labels start=%<integer%>
labels top start=%<integer%>
labels bottom start=%<integer%>
no label bottom 1=%<integer%>
no label bottom 2=%<integer%>
no label bottom 3=%<integer%>
no label bottom 4=%<integer%>
no label bottom 5=%<integer%>
no label bottom 6=%<integer%>
no label bottom 7=%<integer%>
no label bottom 8=%<integer%>
no label bottom 9=%<integer%>
no label top 1=%<integer%>
no label top 2=%<integer%>
no label top 3=%<integer%>
no label top 4=%<integer%>
no label top 5=%<integer%>
no label top 6=%<integer%>
no label top 7=%<integer%>
no label top 8=%<integer%>
no label top 9=%<integer%>
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
transversals first
edges phantom
edges uncover={%<overlay spec%>}
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
vertex sep=%<number%>
edges added={%<\draw options%>}
edges added phantom
edges added uncover={%<overlay spec%>}
#endkeyvals
