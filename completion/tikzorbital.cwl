# tikzorbital.sty
#
#
#include:ifthen
#include:tikz
#include:tikzlibraryshapes
#
\drawLevel[options%keyvals]{name}#/tikzpicture
\orbital[options%keyvals]{type}#/tikzpicture
\satom[%<options%>]{%<color%>/%<rotation-angle%>/%<anchor%>/%<number of electrons%>/%<scale%>}#/tikzpicture
\atom[%<options%>]{%<color%>/%<rotation-angle%>/%<anchor%>/%<number of electrons%>/%<scale%>}#*/tikzpicture
\setOrbitalDrawing{TikZ options}

#keyvals:\drawLevel
elec=#up,down,updown,pair
pos={(%|)}
width=%<number%>
style={%<TikZ options%>}
spinstyle={%<TikZ options%>}
spinlength=%<number%>
#endkeyvals

#keyvals:\orbital#c
pos={(%|)}
scale=%<factor%>
opacity=%<factor%>
pcolor=#%color
ncolor=#%color
color=#%color
rotate=%<degrees%>
nelec=%<integer%>
#endkeyvals

#keyvals:\satom#c,\atom#c
pos={(%|)}
name=%<name%>
color=#%color
opacity=%<factor%>
scale=%<factor%>
#endkeyvals

innerColor#B
drawColor#B
