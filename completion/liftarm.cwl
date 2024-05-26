# liftarm package
# Matthew Bertucci 2024/05/20 for v3.0

#include:xcolor
# loads dvipsnames option of xcolor
#include:tikz
#include:tikzlibrarycalc

\liftarm{point}{length%plain}{angle}
\liftarm[options%keyvals]{point}{length%plain}{angle}

\begin{liftarmconnect}
\begin{liftarmconnect}[options%keyvals]
\end{liftarmconnect}

#keyvals:\liftarm#c,\begin{liftarmconnect}#c
axle holes={%<values%>}
brick#true,false
color={%<number%>}{%<color%>}
color modulo=%<number%>
contour#true,false
contour style={%<options%>}
coordinate={%<num1/name1,num2/name2/...%>}
hole radius=%<number%>
liftarm style={%<options%>}
liftarm thickness=%<number%>
mark holes={%<values%>}
mark radius=%<factor%>
mark style={%<options%>}
origin=%<number%>
scalefactor=%<factor%>
screw angle=%<degrees%>
screw holes={%<values%>}
screw radius=%<factor%>
screw style={%<options%>}
trace={%<num1/numframes1/code1,...%>}
type=#liftarm,line segment
#endkeyvals

#keyvals:\begin{liftarmconnect}#c
connect stop=#1-norm,2-norm,iterations
#endkeyvals

\liftarmconstruct{commands}
\liftarmconstructclear

\liftarmanimate{frame rate}{list}{commands}
\liftarmanimate[options%keyvals]{frame rate}{list}{commands}

# options passed to animateinline
#keyvals:\liftarmanimate#c
label=%<label%>
type=%<file ext%>
poster
poster=#first,last,none,%<number%>
every=%<number%>
autopause
autoplay
autoresume
loop
palindrome
step
width=##L
height=##L
totalheight=##L
keepaspectratio
scale=%<factor%>
bb=%<llx lly urx ury%>
viewport=%<llx lly urx ury%>
trim=%<left bottom right top%>
clip
hiresbb
interpolate
pagebox=
controls=#all,true,on,none,false,off
controlsaligned=
buttonsize=##L
buttonbg=#%color
buttonfg=#%color
buttonalpha=%<opacity%>
draft
final
nomouse
method=#icon,widget,ocg
measure
alttext=#none,%<alt description%>
begin={%<begin code%>}
end={%<end code%>}
timeline=%<file%>
#endkeyvals

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
