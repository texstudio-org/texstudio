# tipfr package
# Matthew Bertucci 1/25/2022 for v1.4b

#include:xcolor
# loads the dvipsnames and table options of xcolor
#include:newtxtt
#include:tikz
#include:tikzlibrarycalc
#include:tikzlibraryshapes
#include:tikzlibraryshadows
#include:tikzlibrarybackgrounds
#include:tikzlibrarybabel
#include:ifthen
#include:xkeyval
#include:mathtools
#include:amssymb
#include:multido

\Touche
\Touche[options%keyvals]

#keyvals:\Touche
style=#function,number,operation,graph,second,alpha,on,enter,arrows
principal=%<text%>
position=%<nombre%>
raise=##L
fontsize=##L
second=%<text%>
alpha=%<text%>
circle#true,false
radius=##L
colour=#%color
color=#%color
thickness=##L
fixed#true,false
xoffset=##L
yoffset=##L
scalearrows=%<nombre%>
arrowtot#true,false
arrowup#true,false
arrowdown#true,false
arrowleft#true,false
arrowright#true,false
name=%<text%>
#endkeyvals

\Menu{nom}
\Menu[option%keyvals]{nom}

#keyvals:\Menu
size=##L
select#true,false
colourbox=#%color
text=%<text%>
#endkeyvals

\Ecran{contenu}
\Ecran[options%keyvals]{contenu}

#keyvals:\Ecran
screencolour=#%color
screencolor=#%color
screenname=%<text%>
width=%<nombre%>
height=%<nombre%>
graphic#true,false
xgrad=%<nombre%>
ygrad=%<nombre%>
nbgradx=%<nombre%>
nbgrady=%<nombre%>
origin={(%<x,y%>)}
plotcolour=#%color
plotcolor=#%color
plotwidth=##L
#endkeyvals

\x#S

\Calculatrice
\Calculatrice[title%text]
\Calculatrice*[options%keyvals]

#keyvals:\Calculatrice*
calcscale=%<nombre%>
calcrotate=%<degrés%>
calcraise=##L
#endkeyvals

\Circonflexe
\Racine

\theLineCommand#*
\theLineResult#*
\DefBool{bool name}#*
\courbe#S
\domain#S
\fileauthor#S
\filedate#S
\fileversion#S

# from the table option of xcolor
#include:colortbl

# from the dvipsnames option of xcolor
Apricot#B
Aquamarine#B
Bittersweet#B
Black#B
Blue#B
BlueGreen#B
BlueViolet#B
BrickRed#B
Brown#B
BurntOrange#B
CadetBlue#B
CarnationPink#B
Cerulean#B
CornflowerBlue#B
Cyan#B
Dandelion#B
DarkOrchid#B
Emerald#B
ForestGreen#B
Fuchsia#B
Goldenrod#B
Gray#B
Green#B
GreenYellow#B
JungleGreen#B
Lavender#B
LimeGreen#B
Magenta#B
Mahogany#B
Maroon#B
Melon#B
MidnightBlue#B
Mulberry#B
NavyBlue#B
OliveGreen#B
Orange#B
OrangeRed#B
Orchid#B
Peach#B
Periwinkle#B
PineGreen#B
Plum#B
ProcessBlue#B
Purple#B
RawSienna#B
Red#B
RedOrange#B
RedViolet#B
Rhodamine#B
RoyalBlue#B
RoyalPurple#B
RubineRed#B
Salmon#B
SeaGreen#B
Sepia#B
SkyBlue#B
SpringGreen#B
Tan#B
TealBlue#B
Thistle#B
Turquoise#B
Violet#B
VioletRed#B
White#B
WildStrawberry#B
Yellow#B
YellowGreen#B
YellowOrange#B
