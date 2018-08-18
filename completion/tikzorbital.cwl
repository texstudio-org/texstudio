# tikzorbital.sty
#
#
#include:ifthen
#include:tikz
#
\drawLevel[options%keyvals]{name}#/tikzpicture
\orbital[options%keyvals]{type%keyvals}#/tikzpicture
\satom[options%keyvals]{%<color%>/%<rotation-angle%>/%<anchor%>/%<number of electrons%>/%<scale%>}#/tikzpicture
\atom[options%keyvals]{%<color%>/%<rotation-angle%>/%<anchor%>/%<number of electrons%>/%<scale%>}#S/tikzpicture
\colorlet{color type%keyvals}{color}#/tikzpicture
\setOrbitalDrawing{{%<argument list%>}}#/tikzpicture

#keyvals:\drawLevel
elec=#up,down,updown,pair
pos={(%|)}
width=
style={%|}
spinstyle={%|}
spinlength=
#endkeyvals

#keyvals:\orbital#c
lobe
s
px
py
pz
dxy
dxz
dyz
dx2y2
dz2
pos={(%|)}
scale=
opacity=
pcolor=#%color
ncolor=#%color
color=#%color
rotate=
nelec=
#endkeyvals

#keyvals:\satom#c
pos={(%|)}
name=
color=#%color
opcaity=
scale=
#endkeyvals

#keyvals:\atom#c
pos={(%|)}
name=
color=#%color
opcaity=
scale=
#endkeyvals

#keyvals:\colorlet
innerColor
drawColor
#endkeyvals
