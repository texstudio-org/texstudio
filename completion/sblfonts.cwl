# sblfonts package
# Matthew Bertucci 2026/05/07 for v1.1

#include:fontspec
#include:babel

#keyvals:\usepackage/sblfonts#c
mainlang=%<babel language%>
mainlanguageoptions={%<babelprovide options%>}
mainfont=%<name%>
mainfontoptions={%<options%>}
grfont=%<name%>
grfontoptions={%<fontspec options%>}
grlangoptions={%<babelprovide options%>}
hefont=%<name%>
hefontoptions={%<fontspec options%>}
helangoptions={%<babelprovide options%>}
sblfonts=#true,false,fallback
sblgreek=#true,false,fallback
sblhebrew=#true,false,fallback
#endkeyvals