# pagelayout class
# Matthew Bertucci 2023/01/24 for v1.0.3

#include:pgfopts
#include:tikz
#include:tcolorbox
#include:tcolorboxlibrarymagazine
#include:class-standalone

#keyvals:\documentclass/pagelayout#c
pagewidth=##L
pageheight=##L
bleed=##L
outerbleed=##L
innerbleed=##L
topbleed=##L
bottombleed=##L
safetymargin=##L
outersafetymargin=##L
innersafetymargin=##L
topsafetymargin=##L
bottomsafetymargin=##L
coverwidth=##L
coverheight=##L
coverbleed=##L
coverouterbleed=##L
coverinnerbleed=##L
covertopbleed=##L
coverbottombleed=##L
coversafetymargin=##L
coveroutersafetymargin=##L
coverinnersafetymargin=##L
covertopsafetymargin=##L
coverbottomsafetymargin=##L
spinewidth=##L
bindingoffset=##L
margin=##L
outermargin=##L
innermargin=##L
topmargin=##L
bottommargin=##L
gutter=##L
pagecolor=#%color
pagegraphic=%<name%>
color=#%color
grid
safezone
cuttingmarks
graphpaper
placeholder
fillpages
draft
preflight
twoside
fanfold
cover
beginleft
beginright
import
#endkeyvals

\twoside
\beginleft
\fanfold
\cover
\beginright

\pagewidth#L
\pageheight#L
\bleed#L
\outerbleed#L
\innerbleed#L
\topbleed#L
\bottombleed#L
\safetymargin#L
\topsafetymargin#L
\bottomsafetymargin#L
\innersafetymargin#L
\outersafetymargin#L
\margin#L
\innermargin#L
\bottommargin#L
\outermargin#L
\gutter#L
\coverwidth#L
\coverheight#L
\spinewidth#L
\bindingoffset#L
\coverbleed#*
\coverouterbleed#*
\coverinnerbleed#*
\covertopbleed#*
\coverbottombleed#*
\coversafetymargin#*
\covertopsafetymargin#*
\coverbottomsafetymargin#*
\coverinnersafetymargin#*
\coveroutersafetymargin#*

\grid
\nogrid
\safezone
\nosafezone
\cuttingmarks
\nocuttingmarks
\graphpaper
\nographpaper
\placeholders
\noplaceholders
\fillpages
\nofillpages

\page{content%text}
\page[options%keyvals]{content%text}

#keyvals:\page,\newtemplate,\template
gutter=##L
margin=##L
top margin=##L
bottom margin=##L
inner margin=##L
outer margin=##L
vpos=%<number 0-1%>
hpos=%<number 0-1%>
color=#%color
page color=#%color
page graphic=%<name%>
before page=%<name%>
double
front cover
back cover
#endkeyvals

\pagecolor[model]{color}#*
\setpagecolor{color}
\setpagecolor[model]{color}#*

\setpagegraphic{name}
\setpagegraphic[options%keyvals]{name}

#keyvals:\setpagegraphic,\newgraphic
file=%<imagefile%>
scale=%<factor%>
vpos=%<number 0-1%>
hpos=%<number 0-1%>
unsharp=
#endkeyvals

\newbeforepage{name}{content%text}
\setbeforepage{name}
\ifleftpage{content%text}
\ifrightpage{content%text}
\leftpage{content%text}
\rightpage{content%text}
\ifspine{content%text}

\setgrid{config}
\setgrid[options%keyvals]{config}

#keyvals:\setgrid
gutter=##L
margin=##L
top margin=##L
bottom margin=##L
inner margin=##L
outer margin=##L
width=##L
height=##L
x=##L
y=##L
vpos=%<number 0-1%>
hpos=%<number 0-1%>
#endkeyvals

\place{fromrow fromcell torow tocell}

\text{text}
\text[options%keyvals]{text}

#keyvals:\text
name=%<name%>
color=#%color
opacity=%<factor%>
top
center
bottom
boxrule=##L
toprule=##L
rightrule=##L
bottomrule=##L
leftrule=##L
height=##L
parbox
breakable
border radius=##L
arc=##L
border width=##L
border color=#%color
border opacity=%<factor%>
shadow=%<name%>
shadow size=##L
shadow color=#%color
shadow opacity=%<factor%>
shadow xshift=##L
shadow yshift=##L
#endkeyvals

\usetext
\usetext[name]

\newgraphic{name}{options%keyvals}

\graphic{name}
\graphic[options%keyvals]{name}

#keyvals:\graphic
file=%<imagefile%>
scale=%<factor%>
vpos=%<number 0-1%>
hpos=%<number 0-1%>
unsharp=
border=##L
border radius=##L
border width=##L
border color=#%color
border opacity=%<factor%>
shadow=%<name%>
shadow size=##L
shadow color=#%color
shadow opacity=%<factor%>
shadow xshift=##L
shadow yshift=##L
#endkeyvals

\xput{code%text}
\tikzgraphic{TikZ code%text}

\newborder{name}{options%keyvals}
\setborder{name}
\setborder[options%keyvals]{name}

#keyvals:\newborder,\setborder
radius=##L
width=##L
color=#%color
opacity=%<factor%>
#endkeyvals

\newshadow{name}{options%keyvals}
\setshadow{name}
\setshadow[options%keyvals]{name}

#keyvals:\newshadow,\setshadow
size=##L
color=#%color
opacity=%<factor%>
xshift=##L
yshift=##L
#endkeyvals

\newtemplate{name}{layout}
\newtemplate[options%keyvals]{name}{layout}#*
\placeholder{fromrow fromcell torow tocell}
\template{name}{content%text}
\template[options%keyvals]{name}{content%text}

\optimize
\optimize[options%keyvals]

#keyvals:\optimize
density=%<pixels per inch%>
quality=%<number 1-100%>
unsharp=
downsample threshold=%<number%>
#endkeyvals

\import
\preflight
\nopreflight

# not documented
\density{arg}#S
\isoptimizable{arg1}{arg2}#S
\loopcells#S
\looprows#S
\nobeforepage#S
\noborder#S
\nopagegraphic#S
\noshadow#S
\originaltcbset{options}#S
\posx{arg1}{arg2}{arg3}{arg4}#S
\posxcell{arg1}{arg2}{arg3}#S
\posxrow{arg1}{arg2}{arg3}{arg4}#S
\posy{arg1}{arg2}#S
\posycell{arg}#S
\posyrow{arg1}{arg2}#S
\quality{arg}#S
\rowsF#S
\rowsFlex#S
\rowsH#S
\sectioncalled#S
\setcolor{color}#S
\setgraphpaper{arg}#S
\pagelayoutversion#S
