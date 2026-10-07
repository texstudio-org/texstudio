# tikzphysics.waves tikzlibrary
# Matthew Bertucci 2026/10/01 for v1.7.0

#include:tikzlibrarytikzphysics.core

#keyvals:\begin{tikzpicture}#c,\tikz#c,\node#c
wave length=##L
wave amplitude=##L
wave cycles=%<number%>
wave phase=%<number%>
standing wave lobes=%<number%>
wave coils=%<number%>
wave compression=%<factor%>
pipe length=##L
pipe width=##L
pipe mode=%<integer%>
#endkeyvals

#keyvals:\node#c
transverse wave
standing wave
longitudinal wave
open pipe
closed pipe
#endkeyvals