# arsenal package
# Matthew Bertucci 2023/09/06 for v0.2

#include:fontspec
#include:iwonamath

#keyvals:\usepackage/arsenal#c
default
sfdefault
math=#none,arsenal+kpsans,kpsans,iwona
scale=%<factor%>
#endkeyvals

#ifOption:math=arsenal+kpsans
#include:kpfonts-otf
#endif

#ifOption:math=kpsans
#include:kpfonts-otf
#endif

\arsenalfamily
\textarsenal{text}
\texthryvnia
\texttugrik
\texttenge
\textruble
\textaldine
\textsmilewhite
\textsmileblack