# liftarm package
# Matthew Bertucci 3/14/2022 for v1.0

#include:etoolbox
#include:xcolor
# loads dvipsnames option of xcolor
#include:tikz
# loads calc tikzlibrary

\liftarm{point}{length%plain}{angle}
\liftarm[options%keyvals]{point}{length%plain}{angle}

\liftarmconnect{point1}{length1}{point2}{length2}
\liftarmconnect[options%keyvals]{point1}{length1}{point2}{length2}

#keyvals:\liftarm#c,\liftarmconnect#c
axle holes={%<values%>}
brick#true,false
color=#%color
%<color%>
color 0=#%color
color 1=#%color
color 2=#%color
color 3=#%color
color 4=#%color
color 5=#%color
color 6=#%color
color 7=#%color
color modulo=%<integer%>
contour#true,false
coordinate={%<num1/name1,num2/name2/...%>}
hole radius=%<number%>
liftarm thickness=%<number%>
mark color=#%color
mark holes={%<values%>}
origin=%<number%>
scalefactor=%<factor%>
screw color=#%color
screw holes={%<values%>}
screw holes angle=%<degrees%>
#endkeyvals

#keyvals:\liftarmconnect#c
connect coordinate=%<name%>
connect reverse#true,false
liftarm 1={%<options%>}
liftarm 2={%<options%>}
#endkeyvals

\begin{liftarmconstruction}
\begin{liftarmconstruction}[TikZ options]
\end{liftarmconstruction}

\liftarmconstruct{text}{commands}
\liftarmconstruct[TikZ options]{text}{commands}

# from dvipsnames option of xcolor
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