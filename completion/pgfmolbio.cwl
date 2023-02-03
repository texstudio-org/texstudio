# pgfmolbio package
# Matthew Bertucci 2/10/2022 for v0.21

#include:ifluatex
#include:luatexbase
#include:xcolor
# xcolor loaded with svgnames and dvipsnames options
#include:tikz
#include:tikzlibrarypositioning
#include:tikzlibrarysvg.path

#keyvals:\usepackage/pgfmolbio#c
chromatogram
domains
convert
#endkeyvals

\pgfmolbioset{options%keyvals}
\pgfmolbioset[module]{options%keyvals}

#keyvals:\pgfmolbioset#c
coordinate unit=%<unit%>
coordinate format string=%<format string%>
#endkeyvals

\pmbprotocolsizes{x}{y}#*

### chromatogram module ###
#ifOption:chromatogram

\pmbchromatogram{scf file%file}
\pmbchromatogram[options%keyvals]{scf file%file}

#keyvals:\pmbchromatogram#c,\pgfmolbioset#c
sample range=%<lower%>-%<upper%>
sample range=%<lower%>-%<upper%> step %<int%>
x unit=##L
y unit=##L
samples per line=%<number%>
baseline skip=##L
canvas style/.style={%<TikZ options%>}
canvas height=##L
trace A style/.style={%<TikZ options%>}
trace C style/.style={%<TikZ options%>}
trace G style/.style={%<TikZ options%>}
trace T style/.style={%<TikZ options%>}
trace style={%<TikZ options%>}
traces drawn=
tick A style/.style={%<TikZ options%>}
tick C style/.style={%<TikZ options%>}
tick G style/.style={%<TikZ options%>}
tick T style/.style={%<TikZ options%>}
tick style={%<TikZ options%>}
tick length=##L
ticks drawn=
base label A text=%<text%>
base label C text=%<text%>
base label G text=%<text%>
base label T text=%<text%>
base label A style/.style={%<TikZ options%>}
base label C style/.style={%<TikZ options%>}
base label G style/.style={%<TikZ options%>}
base label T style/.style={%<TikZ options%>}
base label style={%<TikZ options%>}
base labels drawn=
show base numbers#true,false
base number style/.style={%<TikZ options%>}
base number range=%<lower%>-%<upper%>
base number range=%<lower%>-%<upper%> step %<int%>
probability distance=##L
probabilities drawn=
probability style function=%<Lua function%>
bases drawn=
#endkeyvals

pmbTraceGreen#B
pmbTraceBlue#B
pmbTraceBlack#B
pmbTraceRed#B
pmbTraceYellow#B

#endif

### domains module ###
#ifOption:domains

\begin{pmbdomains}{sequence length}
\begin{pmbdomains}[options%keyvals]{sequence length}
\end{pmbdomains}

\addfeature{type}{start}{stop}
\addfeature[options%keyvals]{type}{start}{stop}

#keyvals:\begin{pmbdomains}#c,\addfeature#c,\pgfmolbioset#c
name=%<text%>
show name#true,false
description=%<text%>
x unit=##L
y unit=##L
residues per line=%<number%>
baseline skip=%<factor%>
residue numbering={%<numbering scheme%>}
residue range=%<lower%>-%<upper%>
enlarge left=##L
enlarge right=##L
enlarge top=##L
enlarge bottom=##L
style={%<style list%>}
domain font=%<font commands%>
level=%<number%>
disulfide base distance=%<number%>
disulfide level distance=%<number%>
range font=%<font commands%>
show ruler#true,false
ruler range={%<ruler range list%>}
default ruler step size=%<number%>
ruler distance=%<factor%>
sequence=%<sequence%>
magnified sequence font=%<font commands%>
show secondary structure#true,false
secondary structure distance=%<factor%>
sequence length=%<number%>
#endkeyvals

\setfeaturestyle{type}{style list}
\setfeaturestylealias{new type}{existing type}
\setfeatureshape{type}{TikZ code}
\xLeft
\xMid
\xRight
\yMid
\pmbdomvalueof{key%plain}
\featureSequence
\residueNumber
\currentResidue
\setfeatureshapealias{new type}{existing type}
\setfeaturealias{new type}{existing type}
\setdisulfidefeatures{key list}
\adddisulfidefeatures{key list}
\removedisulfidefeatures{key list}
\setfeatureprintfunction{key list}{Lua function}
\removefeatureprintfunction{key list}
\pmbdomdrawfeature{type}
\inputuniprot{Uniprot file%file}
\inputgff{gff file%file}

#endif

### convert module ###
#ifOption:convert

#keyvals:\pgfmolbioset#c
output file name=%<text%>
output file extension=%<text%>
output code=#pgfmolbio,tikz
include description#true,false
#endkeyvals

#endif

# from svgnames option of xcolor
AliceBlue#B
DarkKhaki#B
Green#B
LightSlateGrey#B
AntiqueWhite#B
DarkMagenta#B
GreenYellow#B
LightSteelBlue#B
Aqua#B
DarkOliveGreen#B
Grey#B
LightYellow#B
Aquamarine#B
DarkOrange#B
Honeydew#B
Lime#B
Azure#B
DarkOrchid#B
HotPink#B
LimeGreen#B
Beige#B
DarkRed#B
IndianRed#B
Linen#B
Bisque#B
DarkSalmon#B
Indigo#B
Magenta#B
Black#B
DarkSeaGreen#B
Ivory#B
Maroon#B
BlanchedAlmond#B
DarkSlateBlue#B
Khaki#B
MediumAquamarine#B
Blue#B
DarkSlateGray#B
Lavender#B
MediumBlue#B
BlueViolet#B
DarkSlateGrey#B
LavenderBlush#B
MediumOrchid#B
Brown#B
DarkTurquoise#B
LawnGreen#B
MediumPurple#B
BurlyWood#B
DarkViolet#B
LemonChiffon#B
MediumSeaGreen#B
CadetBlue#B
DeepPink#B
LightBlue#B
MediumSlateBlue#B
Chartreuse#B
DeepSkyBlue#B
LightCoral#B
MediumSpringGreen#B
Chocolate#B
DimGray#B
LightCyan#B
MediumTurquoise#B
Coral#B
DimGrey#B
LightGoldenrod#B
MediumVioletRed#B
CornflowerBlue#B
DodgerBlue#B
LightGoldenrodYellow#B
MidnightBlue#B
Cornsilk#B
FireBrick#B
LightGray#B
MintCream#B
Crimson#B
FloralWhite#B
LightGreen#B
MistyRose#B
Cyan#B
ForestGreen#B
LightGrey#B
Moccasin#B
DarkBlue#B
Fuchsia#B
LightPink#B
NavajoWhite#B
DarkCyan#B
Gainsboro#B
LightSalmon#B
Navy#B
DarkGoldenrod#B
GhostWhite#B
LightSeaGreen#B
NavyBlue#B
DarkGray#B
Gold#B
LightSkyBlue#B
OldLace#B
DarkGreen#B
Goldenrod#B
LightSlateBlue#B
Olive#B
DarkGrey#B
Gray#B
LightSlateGray#B
OliveDrab#B
Orange#B
Plum#B
Sienna#B
Thistle#B
OrangeRed#B
PowderBlue#B
Silver#B
Tomato#B
Orchid#B
Purple#B
SkyBlue#B
Turquoise#B
PaleGoldenrod#B
Red#B
SlateBlue#B
Violet#B
PaleGreen#B
RosyBrown#B
SlateGray#B
VioletRed#B
PaleTurquoise#B
RoyalBlue#B
SlateGrey#B
Wheat#B
PaleVioletRed#B
SaddleBrown#B
Snow#B
White#B
PapayaWhip#B
Salmon#B
SpringGreen#B
WhiteSmoke#B
PeachPuff#B
SandyBrown#B
SteelBlue#B
Yellow#B
Peru#B
SeaGreen#B
Tan#B
YellowGreen#B
Pink#B
Seashell#B
Teal#B

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
