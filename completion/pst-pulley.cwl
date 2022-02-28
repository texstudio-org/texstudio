# pst-pulley package
# Matthew Bertucci 2/27/2022 for v0.02

#include:pstricks
# loads dvipsnames option of pstricks (hence of xcolor)
#include:pst-grad
#include:pst-slpe
#include:pst-eucl
#include:pstricks-add

\pspulleys
\pspulleys[options%keyvals]

#keyvals:\pspulleys#c
pulleyGrid#true,false
N=#1,2,3,4,5,6
M=%<mass in kg%>
h=%<height in cm%>
Dx=%<number%>
#endkeyvals

\pulleyA#*
\pulleyB#*
\pulleyC#*
\radianAI#*
\radianBI#*
\radianCI#*
\poulieA#*
\poulieB#*
\poulieC#*
\poulieD#*
\poulieE#*
\poulieF#*
\flzlx#*
\Npulleys#*
\PSTpulleyLoaded#S

# from dvipsnames option
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