# eurion package
# Matthew Bertucci 2026/04/28 for v0.1.0

#include:xkeyval
#include:tikz
#include:eso-pic

\eurion{TikZ coord}
\eurion[options%keyvals]{TikZ coord}

#keyvals:\usepackage/eurion#c,\eurion
mode=#scatter,corner,manual
color=#%color
size=%<factor%>
density=%<integer%>
rotate=#random,none,%<degrees%>
corner=#top-left,top-right,bottom-left,bottom-right
seed=%<integer%>
#endkeyvals