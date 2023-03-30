# wargame package
# Matthew Bertucci 2023/03/30 for v0.5

#include:xcolor
# loads svgnames option of xcolor
#include:tikz
# loads wargame.hex, wargame.natoapp6c, and wargame.chit tikzlibraries
#include:tikzlibrarycalc
#include:tikzlibraryshapes.symbols
#include:tikzlibrarypositioning
#include:tikzlibraryintersections
#include:tikzlibraryshapes.geometric
#include:tikzlibraryshapes.arrows
#include:tikzlibrarydecorations
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarydecorations.markings
#include:tikzlibrarymath

#keyvals:\usepackage/wargame#c
noterrainpic
terrainpic
#endkeyvals

## from wargame.hex tikzlibrary
#include:alphalph
# loads calc, arrows.meta, arrows, shapes.geometric, shapes.symbols, shapes.arrows, decorations, 
# decorations.pathmorphing, decorations.pathreplacing, decorations.markings, and wargame.util tikzlibraries

\hex(location)
\hex(location)(name)#*
\hex[options%keyvals](location)
\hex[options%keyvals](location)(name)#*
#keyvals:\hex#c
terrain={%<terrain-keys%>}
ridges={%<ridges-keys%>}
label={%<label-keys%>}
town={%<town-keys%>}
bevel={%<bevel-keys%>}
extra={%<extra-keys%>}
extra clipped={%<extra-keys%>}
row=%<row%>
column=%<column%>
#endkeyvals

\road %<⟨path⟩%>;
\road[%<options%>] %<⟨path⟩%>;
\railroad %<⟨path⟩%>;
\railroad[%<options%>] %<⟨path⟩%>;
\river %<⟨path⟩%>;
\river[%<options%>] %<⟨path⟩%>;
\border %<⟨path⟩%>;
\border[%<options%>] %<⟨path⟩%>;
\fortifiedline %<⟨path⟩%>;
\fortifiedline[%<options%>] %<⟨path⟩%>;

\boardframe(lower-left)(upper-right)
\boardframe[margin](lower-left)(upper-right)
\boardclip(lower-left)(upper-right){options}

\splitboard{options%keyvals}
#keyvals:\splitboard#c
paper=#a4,a3,letter,tabloid
landscape
margin=%<number%>
ncol=%<integer%>
nrow=%<integer%>
overlap=%<number%>
image=%<imagefile%>
output=%<file name%>
standalone
scale=%<factor%>
#endkeyvals

\hexdbglvl#*
\markpos{arg1}(arg2)#S
\init#S
\northedge#S
\southedge#S
\northeastedge#S
\northwestedge#S
\southwestedge#S
\southeastedge#S
\hexpath#S
\chitnorth#S
\chitsouth#S
\chiteast#S
\chitwest#S
\chitnortheast#S
\chitnorthwest#S
\chitsouthwest#S
\chitsoutheast#S
\fortmark#*
\fortmark[options%keyvals]#*
\terrainmark{terrain-keys}#*
\terrainmark[options%keyvals]{terrain-keys}#*
\clearhex#*
\clearhex[options%keyvals]#*
\woodshex#*
\woodshex[options%keyvals]#*
\mountainhex#*
\mountainhex[options%keyvals]#*
\cityhex#*
\cityhex[options%keyvals]#*
\beachhex#*
\beachhex[options%keyvals]#*
\seahex#*
\seahex[options%keyvals]#*
\riverhex#*
\riverhex[options%keyvals]#*
\roadhex#*
\roadhex[options%keyvals]#*
\outlinerev#S
\shiftScalePath{macro}{relative-coords}#*
\margin#S
\boardXmin#S
\boardYmin#S
\boardXmax#S
\boardYmax#S
\hexboardpath#*
\boardpath(lower-left)(upper-right)#*
\debuggrid#*
\boardhexes(arg1)(arg2)#*
\boardhexes[options%keyvals](arg1)(arg2)#*
\segment(arg1)(arg2){arg3}{arg4}{arg5}{arg6}#*

## from wargame.util tikzlibrary
\wargamelogo#*
\wargamelogo[options%keyvals]#*
\wargamedbglvl#*
\settosave{arg}#S
\begin{getbbl}#*
\end{getbbl}#*
\begin{getbb}#*
\end{getbb}#*
\wglogbb{arg}#S

## from wargame.natoapp6c tikzlibrary
# loads wargame.util, calc, arrows.meta, shapes.symbols, positioning, and intersections tikzlibraries
\natoapp(location)
\natoapp(location)(name)
\natoapp[options%keyvals](location)
\natoapp[options%keyvals](location)(name)
#keyvals:\natoapp#c
faction=%<faction%>
command=#air,land,equipment,installation,sea surface,sub surface,space,activity,none
main={%<mains%>}
left={%<lefts%>}
right={%<rights%>}
top={%<tops%>}
bottom={%<bottoms%>}
below={%<belows%>}
echelon=#team,squad,section,platoon,company,battalion,regiment,brigade,division,corps,army,army group,theatre,command
frame={%<frame-keys%>}
#endkeyvals

\natoappdbglvl#*
friendly#B
hostile#B
neutral#B
unknown#B
\octagon#S
\topline#S
\bottomline#S
\thenatoappid#S
\natoappmark{mains}#*
\natoappmark[options%keyvals]{mains}#*
\echelonmark{arg}#*
\echelonmark[options%keyvals]{arg}#*
\armouredmark#*
\armouredmark[options%keyvals]#*
\infantrymark#*
\infantrymark[options%keyvals]#*
\artillerymark#*
\artillerymark[options%keyvals]#*
\combinedmark#*
\combinedmark[options%keyvals]#*
\pgmark#*
\pgmark[options%keyvals]#*
\reconnaissancemark#*
\reconnaissancemark[options%keyvals]#*
\corpsmark#*
\corpsmark[options%keyvals]#*
\divisionmark#*
\divisionmark[options%keyvals]#*
\brigademark#*
\brigademark[options%keyvals]#*
\regimentmark#*
\regimentmark[options%keyvals]#*
\sofmark#*
\sofmark[options%keyvals]#*
\mountaineermark#*
\mountaineermark[options%keyvals]#*
\airbornemark#*
\airbornemark[options%keyvals]#*
\amphibiousmark#*
\amphibiousmark[options%keyvals]#*
\airassaultmark#*
\airassaultmark[options%keyvals]#*
\testpath{arg}#*
\cntrl#S
\cntrlnortheast#S
\frameopt#S
\frameshape#S
\innernortheast#S
\linex#S
\liney#S

## from wargame.chit tikzlibrary
#include:amsmath
#include:amstext
# loads wargame.util, wargame.natoapp6c, and math tikzlibraries
\chit(location)
\chit(location)(name)
\chit[options%keyvals](location)
\chit[options%keyvals](location)(name)
#keyvals:\chit#c
symbol={%<nato app 6(c) spec%>}
full={%<spec%>}
color=#%color
fill=#%color
text=#%color
draw=#%color
bevel={%<bevel-keys%>}
#endkeyvals

\chitdbglvl#*
\chitframeopt#S
\shadechit(arg)#*
\eliminatechit(arg)#*
\stackchits(arg1)(arg2){arg3}#*
\oob#S
\chits{arg1}{arg2}{arg3}#*
\chits*{arg1}{arg2}{arg3}#*
\doublechits{arg1}{arg2}{arg3}#*
\doublechits*{arg1}{arg2}{arg3}#*
\chitmark{chit-keys}#*
\chitmark[options%keyvals]{chit-keys}#*
\stackmark#*
\stackmark[options%keyvals]#*
\zocmark#*
\zocmark[options%keyvals]#*
\dicemark{arg}#*
\dicemark[options%keyvals]{arg}#*

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
