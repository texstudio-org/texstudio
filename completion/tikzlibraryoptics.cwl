# optics tikzlibrary
# 2022/12/09 for v0.2.3

#include:tikzlibrarydecorations
#include:tikzlibrarydecorations.markings
#include:tikzlibrarydecorations.pathreplacing
#include:etoolbox

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\scoped#c
use optics
#endkeyvals

#keyvals:\node#c,\coordinate#c
object height=##L
object aspect ratio=%<number%>
lens
draw focal points
draw focal points={%<TikZ keys%>}
focal length=##L
lens height=%<number%>
lens type=#converging,diverging
slit
slit height=%<number%>
double slit
slit separation=%<number%>
mirror
mirror decoration separation=%<number%>
mirror decoration amplitude=%<number%>
spherical mirror
spherical mirror angle=%<degrees%>
spherical mirror type=#concave,convex
concave mirror
convex mirror
spherical mirror orientation=#ltr,rtl
draw mirror center
draw mirror center={%<TikZ keys%>}
draw mirror focus
draw mirror focus={%<TikZ keys%>}
polarizer
beam splitter
double amici prism
prism height=##L
prism apex angle=%<degrees%>
thin optics element
thick optics element
heat filter
screen
diffraction grating
grid
semi-transparent mirror
diaphragm
generic optics io
io body height=##L
io body aspect ratio=%<number%>
io aperture width=%<number%>
io aperture height=%<number%>
io aperture shift=%<number%>
io orientation=#ltr,rtl
sensor line
sensor line height=##L
sensor line aspect ratio=%<number%>
sensor line pixel number=%<number%>
sensor line pixel width=%<number%>
sensor line inner ysep=%<number%>
generic sensor
generic lamp
halogen lamp
spectral lamp
laser
laser'
#endkeyvals

#keyvals:\draw#c
->-
-<-
->>-
-<<-
->n={n=%<〈num〉,〈specs〉%>}
-<n={n=%<〈num〉,〈specs〉%>}
put arrow
put arrow={%<options%>}
put coordinate=%<coord%> at %<position%>
#endkeyvals

\tikzopticsversiondate#S
\tikzopticsversion#S