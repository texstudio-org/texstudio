# tikzphysics.optics tikzlibrary
# Matthew Bertucci 2026/09/04 for v1.1.0

#include:tikzlibrarypatterns
#include:tikzlibrarycalc
#include:tikzlibrarytikzphysics.core

#keyvals:\begin{tikzpicture}#c,\tikz#c,\node#c
mirror radius=##L
mirror thickness=##L
mirror aperture angle=%<degrees%>
convex lens radius=##L
convex lens thickness=##L
convex lens aperture angle=%<degrees%>
concave lens radius=##L
concave lens thickness=##L
concave lens aperture angle=%<degrees%>
slab width=##L
slab height=##L
prism width=##L
prism height=##L
prism apex angle=%<degrees%>
#endkeyvals

#keyvals:\node#c
concave-mirror
convex-mirror
convex-lens
concave-lens
slab
prism
#endkeyvals