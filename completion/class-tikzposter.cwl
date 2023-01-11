# tikzposter class
# Matthew Bertucci 2/16/2022 for v2.0

#include:xkeyval
#include:calc
#include:ifthen
#include:ae
#include:xstring
#include:etoolbox
#include:tikz
#include:tikzlibraryshapes
#include:tikzlibrarydecorations
#include:tikzlibraryshadows
#include:tikzlibrarybackgrounds
#include:tikzlibrarycalc
#include:tikzlibraryfadings
#include:tikzlibraryfit
#include:tikzlibrarydecorations.pathmorphing
# loads arrows pgflibrary
#include:class-extarticle
#include:geometry

#keyvals:\documentclass/tikzposter#c
12pt
14pt
17pt
20pt
25pt
fleqn
leqno
a0paper
a1paper
a2paper
landscape
portrait
margin=##L
innermargin=##L
colspace=##L
subcolspace=##L
blockverticalspace=##L
#endkeyvals

\titlewidth#*
\titlelinewidth#*
\titleroundedcorners#*
\titleinnersep#*
\titletotopverticalspace#*
\titleheight#*
\titlegraphicheight#*
\titleposleft#*
\titleposright#*
\titlepostop#*
\titleposbottom#*
\colwidth#*
\subcolwidth#*
\blocktitleinnersep#*
\blockbodyinnersep#*
\ifBlockHasTitle#*
\BlockHasTitletrue#*
\BlockHasTitlefalse#*
\blockroundedcorners#*
\blocklinewidth#*
\innerblocktitleinnersep#*
\innerblockbodyinnersep#*
\ifInnerblockHasTitle#*
\InnerblockHasTitletrue#*
\InnerblockHasTitlefalse#*
\innerblockroundedcorners#*
\innerblocklinewidth#*
\noteinnersep#*
\ifNoteHasConnection#*
\NoteHasConnectiontrue#*
\NoteHasConnectionfalse#*
\noterotate#*
\noteroundedcorners#*
\notelinewidth#*

\definebackgroundstyle{name%specialDef}{background commands}#s#%tikzposterbackgroundstyle
\usebackgroundstyle{background style%keyvals}

\definetitlestyle{name%specialDef}{options%keyvals}{title commands}#s#%tikzpostertitlestyle
\usetitlestyle{title style%keyvals}
\usetitlestyle[options]{title style%keyvals}
\maketitle[options%keyvals]

#keyvals:\definetitlestyle,\maketitle
width=##L
roundedcorners=%<number%>
linewidth=##L
innersep=##L
titletotopverticalspace=##L
titletoblockverticalspace=##L
titlegraphictotitledistance=##L
titletextscale=%<factor%>
#endkeyvals

\institute{institute}
\titlegraphic{graphic commands}
\begin{settitle}#S
\end{settitle}#S
\settitle{title code}#*

\defineblockstyle{name%specialDef}{options%keyvals}{commands}#s#%tikzposterblockstyle
\useblockstyle{block style%keyvals}
\useblockstyle[options]{block style%keyvals}
\block{title}{text}
\block[options%keyvals]{title}{text}

#keyvals:\defineblockstyle,\block
titleoffsetx=##L
titleoffsety=##L
bodyoffsetx=##L
bodyoffsety=##L
titlewidthscale=%<factor%>
bodywidthscale=%<factor%>
titleleft
titlecenter
titleright
bodyverticalshift=##L
roundedcorners=%<number%>
linewidth=##L
titleinnersep=##L
bodyinnersep=##L
#endkeyvals

\defineinnerblockstyle{name%specialDef}{options%keyvals}{commands}#s#%tikzposterinnerblockstyle
\useinnerblockstyle{innerblock style%keyvals}
\useinnerblockstyle[options]{innerblock style%keyvals}
\innerblock{heading%text}{text}
\innerblock[options%keyvals]{heading%text}{text}

#keyvals:\defineinnerblockstyle,\innerblock
titlewidth=##L
bodywidth=##L
titlewidthscale=%<factor%>
bodywidthscale=%<factor%>
titleleft
titlecenter
titleright
titleoffsetx=##L
titleoffsety=##L
bodyoffsetx=##L
bodyoffsety=##L
roundedcorners=%<number%>
linewidth=##L
titleinnersep=##L
bodyinnersep=##L
#endkeyvals

\coloredbox{text}
\coloredbox[options%keyvals]{text}

#keyvals:\coloredbox
width=##L
linewidth=##L
roundedcorners=%<number%>
bgcolor=#%color
fgcolor=#%color
framecolor=#%color
#endkeyvals

\definenotestyle{name%specialDef}{options%keyvals}{commands}#s#%tikzposternotestyle
\usenotestyle{note style%keyvals}
\usenotestyle[options]{note style%keyvals}
\note{text}
\note[options%keyvals]{text}

#keyvals:\definenotestyle,\note
targetoffsetx=##L
targetoffsety=##L
angle=%<degrees%>
radius=##L
width=##L
connection
rotate=%<degrees%>
roundedcorners=%<number%>
linewidth=##L
innersep=##L
#endkeyvals

\definecolorpalette{name%specialDef}{definitions}#s#%tikzpostercolorpalette
\usecolorpalette{color palette%keyvals}

\definecolorstyle{name%specialDef}{default palette}{definitions}#s#%tikzpostercolorstyle
\usecolorstyle{color style%keyvals}
\usecolorstyle[options]{color style%keyvals}

\definelayouttheme{name%specialDef}{commands}#s#%tikzpostertheme
\usetheme{theme%keyvals}

\begin{columns}
\end{columns}
\column{relative width}
\begin{subcolumns}
\end{subcolumns}
\subcolumn{relative width}

\tikzposterlatexaffectionproofon
\tikzposterlatexaffectionproofoff

\thefigurecounter#*
\begin{tikzfigure}
\begin{tikzfigure}[caption%text]
\end{tikzfigure}
\rememberparameter#S

# from tikzposterColorpalettes.tex
#keyvals:\usecolorpalette#c
Default
BlueGrayOrange
GreenGrayViolet
PurpleGrayBlue
BrownBlueOrange
%tikzpostercolorpalette
#endkeyvals

colorOne#B
colorTwo#B
colorThree#B

# from tikzposterColorstyles.tex
#keyvals:\usecolorstyle#c
Default
Australia
Britain
Sweden
Spain
Russia
Denmark
Germany
%tikzpostercolorstyle
#endkeyvals

backgroundcolor#B
framecolor#B
titlefgcolor#B
titlebgcolor#B
blocktitlebgcolor#B
blocktitlefgcolor#B
blockbodybgcolor#B
blockbodyfgcolor#B
innerblocktitlebgcolor#B
innerblocktitlefgcolor#B
innerblockbodybgcolor#B
innerblockbodyfgcolor#B
notefgcolor#B
notebgcolor#B
notefrcolor#B
	
# from tikzposterBackgroundstyles.tex
#keyvals:\usebackgroundstyle#c
Default
Rays
VerticalGradation
BottomVerticalGradation
Empty
%tikzposterbackgroundstyle
#endkeyvals

# from tikzposterTitlestyles.tex
#keyvals:\usetitlestyle#c
Default
Basic
Envelope
Wave
VerticalShading
Filled
Empty
%tikzpostertitlestyle
#endkeyvals

# from tikzposterBlockstyles.tex
#keyvals:\useblockstyle#c
Default
Basic
Minimal
Envelope
Corner
Slide
TornOut
%tikzposterblockstyle
#endkeyvals

# from tikzposterInnerblockstyles.tex
#keyvals:\useinnerblockstyle#c
Default
Table
Basic
Minimal
Envelope
Corner
Slide
TornOut
%tikzposterinnerblockstyle
#endkeyvals

# from tikzposterNotestyles.tex
#keyvals:\usenotestyle#c
Default
Corner
VerticalShading
Sticky
%tikzposternotestyle
#endkeyvals

# from tikzposterLayoutthemes.tex
#keyvals:\usetheme#c
Default
Rays
Basic
Simple
Envelope
Wave
Board
Autumn
Desert
%tikzpostertheme
#endkeyvals
