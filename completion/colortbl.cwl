# colortbl package
# neeraavi 26 Mar 2007
# updated 2022/08/01 for v1.0f

#include:array
#include:color

#keyvals:\usepackage/colortbl#c
# options passed to color package
monochrome
debugshow
setpagesize
nosetpagesize
dvips
xdvi
dvipdf
dvipdfm
dvipdfmx
pdftex
luatex
dvisvgm
xetex
dvipsone
dviwindo
emtex
dviwin
oztex
textures
pctexps
pctexwin
pctexhp
pctex32
truetex
tcidvi
vtex
dvipsnames
nodvipsnames
usenames
#endkeyvals

\arrayrulecolor{color}
\arrayrulecolor[color model]{color}
\cellcolor{color}
\cellcolor[color model]{color}[left overhang][right overhang]
\columncolor{color}
\columncolor[color model]{color}[left overhang][right overhang]
\doublerulesepcolor{color}
\doublerulesepcolor[color model]{color}
\rowcolor{color}
\rowcolor[color model]{color}[left overhang][right overhang]
\minrowclearance#*

# NOTE: these commands were formerly in xcolor under "table" option; moved to colortbl.sty in v1.0f
## double command as workaround for color args to be recognized properly as colors
\rowcolors{row}{odd-row-color}{even-row-color}
\rowcolors[commands]{row}{odd-row-color}{even-row-color}
\rowcolors{row}{color}{color}#S
\rowcolors[commands]{row}{color}{color}#S
\rowcolors*{row}{odd-row-color}{even-row-color}
\rowcolors*[commands]{row}{odd-row-color}{even-row-color}
\rowcolors*{row}{color}{color}#S
\rowcolors*[commands]{row}{color}{color}#S
\showrowcolors
\hiderowcolors
\rownum
\therownum

## dvipsnames colors
#ifOption:dvipsnames
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
#endif
