# pas-cv package
# Matthew Bertucci 12/28/2021 for v2.01

#include:xkeyval
#include:graphicx
#include:tikz
#include:tikzlibraryshadows
#include:tikzlibrarycalc
#include:tikzlibraryfadings
#include:tikzlibraryshapes.geometric
#include:tikzlibrarypatterns
#include:tikzlibrarydecorations.pathmorphing
#include:eso-pic
#include:fp
#include:geometry

\CVbg[options%keyvals]

#keyvals:\CVbg
modele=#andromede,architecte,centaure,dynamique,gaia,jupiter,mars,neptune,orion,pegase,pluton,saturne,univers,uranus,venus
bgcolor=#%color
bordercolor=#%color
postesize=%<size macro%>
postecolor=#%color
poste={%<texte%>}
pic=%<image file%>
borderpic=#%color
scalepic=%<factor%>
#endkeyvals

\infoLeft{info%text}
\infoRight{info%text}

\CVmargins

\CVtitle{le titre%text}
\CVtitle[options%keyvals]{le titre%text}

#keyvals:\CVtitle
color=#%color
bordercolor=#%color
#endkeyvals

\CVclearpage

\CVh{hauteur en cm}
