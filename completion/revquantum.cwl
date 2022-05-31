# revquantum package
# Matthew Bertucci 2022/05/29 for v0.11

#include:ifthen
#include:iftex
#include:stmaryrd
#include:amsmath
#include:amsfonts
#include:amsthm
#include:amssymb
#include:amsbsy
#include:color
# loads dvipsnames option of color
#include:braket
#include:graphicx
#include:babel
# loads english option of babel
#include:letltxmacro
#include:etoolbox
#include:algorithm
#include:algpseudocode
#include:hyperref

#keyvals:\usepackage/revquantum#c
final
pretty
uselistings
nobibtexhacks
strict
#endkeyvals

#ifOption:pretty
#include:mathpazo
#endif

#ifOption:uselistings
#include:xcolor
#include:listings
#include:textcomp
comment-color#B
#endif

\todo{text%todo}#D
\TODO
\todolist{contents%todo}#D

\ii#m
\dd#m
\defeq#m
\expect#m
\id#m
\llbracket#m
\rrbracket#m

\newaffil{shorthand}{description%text}
\affilTODO
\affilEQuSUSyd
\affilEQuSMacq
\affilUSydPhys
\affilIQC
\affilUWPhys
\affilUWAMath
\affilUWChem
\affilPI
\affilCIFAR
\affilCQuIC
\affilIBMTJW

\inlinecomment{text}#/algorithmic
\linecomment{text}#/algorithmic

\begin{theorem}
\begin{theorem}[heading%text]
\end{theorem}
\begin{lemma}
\begin{lemma}[heading%text]
\end{lemma}

\booloption{boolean name}{option name}{true|false}#*
\newnew{name}{definition}#*
\algorithmautorefname#*
\lemmaautorefname#*
\citeneed#*
\definelanguagealias{alias}{language}#*
\ORIGselectlanguage{language}#S

cud-black#B
cud-orange#B
cud-sky-blue#B
cud-bluish-green#B
cud-yellow#B
cud-blue#B
cud-vermillion#B
cud-reddish-purple#B

# from dvipsnames option of color
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

# from english option of babel
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*