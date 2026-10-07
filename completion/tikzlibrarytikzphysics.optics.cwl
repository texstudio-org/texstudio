# tikzphysics.optics tikzlibrary
# Matthew Bertucci 2026/10/01 for v1.7.0

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
mirror height=##L
lens height=##L
lens thickness=##L
lens front radius=##L
lens back radius=##L
#endkeyvals

#keyvals:\node#c
concave-mirror
convex-mirror
convex-lens
concave-lens
slab
prism
plane-mirror
plano-convex-lens
plano-concave-lens
positive-meniscus-lens
negative-meniscus-lens
#endkeyvals