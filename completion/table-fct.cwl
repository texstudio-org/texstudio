# table-fct package
# Matthew Bertucci 4/23/2022 for v1.1

#include:xcolor
# loads table and dvipsnames options of xcolor
#include:graphicx
#include:pstricks
#include:pstricks-add
#include:xifthen
#include:environ
#include:xkeyval
#include:xargs

\begin{table-type1}{variable}{function}#\pictureHighlight
\begin{table-type1}[options%keyvals]{variable}{function}
\end{table-type1}

\colX{arg1}{arg2}{arg3}
\colND{arg}
\colNDV{arg}
\colV
\colC
\colD
\colCvx
\colCcv
\colIflx{arg}

\begin{table-type2}{variable}{function1}{function2}#\pictureHighlight
\begin{table-type2}[options%keyvals]{variable}{function1}{function2}
\end{table-type2}

\collX{arg1}{arg2}{arg3}
\collX[\Zro]{%<arg1%>}{%<arg2%>}{%<arg3%>}
\Zro#*
\collNd{arg1}{arg2}{arg3}
\collNdv{arg1}{arg2}{arg3}
\collND{arg}
\collNDV{arg}
\collV
\collC
\collD
\collCvx
\collCcv
\collIflx{arg}
\collCz{arg}
\collDz{arg}
\collCvxz{arg}
\collCcvz{arg}

#keyvals:\begin{table-type1},\begin{table-type2}
Xunit=##L
Yunit=##L
Scal=%<factor%>
Bcolor=#%color
#endkeyvals

\Bcolor#*
\Pos#*
\Scal#*
\TTpos#*
\Tpos#*
\Xunit#*
\Yunit#*
\Zro#*
\colF{arg1}{arg2}#*
\collF{arg1}{arg2}{arg3}#*
\linF#*
\linM#*
\linS#*
\linnF#*
\linnM#*
\linnS#*

# from table option of xcolor
#include:colortbl

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
