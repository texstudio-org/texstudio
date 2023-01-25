# For geometry v5.9 (2020/01/02) by Hideo Umeki.
# URL: https://ctan.org/pkg/geometry
# Created by Brian Schubert (2021/08/03)

## User Interface (section 4)
\geometry{options%keyvals}
\newgeometry{options%keyvals}
\restoregeometry
\savegeometry{name%specialDef}#s#%geometry
\loadgeometry{name%keyvals}
#keyvals:\loadgeometry
%geometry
#endkeyvals

## Paper size (section 5.1) (not available for \newgeometry)
#keyvals:\geometry,\usepackage/geometry#c
paper=#a0paper,a1paper,a2paper,a3paper,a4paper,a5paper,a6paper,b0paper,b1paper,b2paper,b3paper,b4paper,b5paper,b6paper,c0paper,c1paper,c2paper,c3paper,c4paper,c5paper,c6paper,b0j,b1j,b2j,b3j,b4j,b5j,b6j,ansiapaper,ansibpaper,ansicpaper,ansidpaper,ansiepaper,letterpaper,executivepaper,legalpaper
papername=#a0paper,a1paper,a2paper,a3paper,a4paper,a5paper,a6paper,b0paper,b1paper,b2paper,b3paper,b4paper,b5paper,b6paper,c0paper,c1paper,c2paper,c3paper,c4paper,c5paper,c6paper,b0j,b1j,b2j,b3j,b4j,b5j,b6j,ansiapaper,ansibpaper,ansicpaper,ansidpaper,ansiepaper,letterpaper,executivepaper,legalpaper
a0paper
a1paper
a2paper
a3paper
a4paper
a5paper
a6paper
b0paper
b1paper
b2paper
b3paper
b4paper
b5paper
b6paper
c0paper
c1paper
c2paper
c3paper
c4paper
c5paper
c6paper
b0j
b1j
b2j
b3j
b4j
b5j
b6j
ansiapaper
ansibpaper
ansicpaper
ansidpaper
ansiepaper
letterpaper
executivepaper
legalpaper
screen
paperwidth=##L
paperheight=##L
papersize=##L
papersize={%<width%>,%<height%>}
landscape#true,false
portrait#true,false
#endkeyvals

## Layout size (section 5.2)
#keyvals:\geometry,\newgeometry,\usepackage/geometry#c
layout=#a0paper,a1paper,a2paper,a3paper,a4paper,a5paper,a6paper,b0paper,b1paper,b2paper,b3paper,b4paper,b5paper,b6paper,c0paper,c1paper,c2paper,c3paper,c4paper,c5paper,c6paper,b0j,b1j,b2j,b3j,b4j,b5j,b6j,ansiapaper,ansibpaper,ansicpaper,ansidpaper,ansiepaper,letterpaper,executivepaper,legalpaper
layoutwidth=##L
layoutheight=##L
layoutsize=##L
layoutsize={%<width%>,%<height%>}
layouthoffset=##L
layoutvoffset=##L
layoutoffset=##L
layoutoffset={%<hoffset%>,%<voffset%>}
#endkeyvals

## Body size (section 5.3)
#keyvals:\geometry,\newgeometry,\usepackage/geometry#c
hscale=%<scale%>
vscale=%<scale%>
scale=%<scale%>
scale={%<hscale%>,%<vscale%>}
width=##L
totalwidth=##L
height=##L
totalheight=##L
total=##L
total={%<width%>,%<height%>}
textwidth=##L
textheight=##L
text=##L
body={%<width%>,%<height%>}
lines=%<integer%>
includehead#true,false
includefoot#true,false
includeheadfoot#true,false
includemp#true,false
includeall#true,false
ignorehead#true,false
ignorefoot#true,false
ignoreheadfoot#true,false
ignoremp#true,false
ignoreall#true,false
heightrounded#true,false
hdivide={%<left margin%>,%<width%>,%<right margin%>}
vdivide={%<top margin%>,%<height%>,%<bottom margin%>}
divide={%<left/top margin%>,%<width/height%>,%<right/bottom margin%>}
#endkeyvals

## Margin size (section 5.4)
#keyvals:\geometry,\newgeometry,\usepackage/geometry#c
left=##L
lmargin=##L
inner=##L
right=##L
rmargin=##L
outer=##L
top=##L
tmargin=##L
bottom=##L
bmargin=##L
hmargin=##L
hmargin={%<left margin%>,%<right margin%>}
vmargin=##L
vmargin={%<top margin%>,%<bottom margin%>}
margin=##L
margin={%<left/top margin%>,%<right/bottom margin%>}
hmarginratio=%<left%>:%<right%>
vmarginratio=%<top%>:%<bottom%>
marginratio={%<left%>:%<right%>,%<top%>:%<bottom%>}
marginratio=%<left/top%>:%<right/bottom%>
ratio={%<left%>:%<right%>,%<top%>:%<bottom%>}
ratio=%<left/top%>:%<right/bottom%>
hcentering#true,false
vcentering#true,false
centering#true,false
twoside#true,false
asymmetric#true,false
bindingoffset=##L
#endkeyvals

## Native dimensions (section 5.5)
#keyvals:\geometry,\newgeometry,\usepackage/geometry#c
headheight=##L
head=##L
headsep=##L
footskip=##L
foot=##L
nohead#true,false
nofoot#true,false
noheadfoot#true,false
footnotesep=##L
marginparwidth=##L
marginpar=##L
marginparsep=##L
nomarginpar#true,false
columnsep=##L
hoffset=##L
voffset=##L
offset=##L
offset={%<hoffset%>,%<voffset%>}
twocolumn#true,false
onecolumn#true,false
twoside#true,false
reversemp#true,false
reversemarginpar#true,false
#endkeyvals

## Drivers (section 5.6) (not available for \newgeometry)
#keyvals:\geometry,\usepackage/geometry#c
driver=#auto,none,dvips,dvipdfm,pdftex,luatex,xetex,vtex,dvipdfmx,xdvipdfmx
dvips
dvipdfm
pdftex
luatex
xetex
vtex
dvipdfmx
xdvipdfmx
#endkeyvals

## Other options (section 5.7) (not available for \newgeometry)
#keyvals:\geometry,\usepackage/geometry#c
verbose#true,false
reset#true,false
mag=%<magnification%>
truedimen#true,false
pass#true,false
showframe#true,false
showcrop#true,false
#endkeyvals
