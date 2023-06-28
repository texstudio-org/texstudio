# bookcover class
# Matthew Bertucci 12/30/2021 for v3.3

#include:kvoptions
#include:geometry
#include:graphicx
#include:calc
#include:tikz
#include:etoolbox
#include:fgruler

#keyvals:\documentclass/bookcover#c
coverheight=##L
coverwidth=##L
spinewidth=##L
flapwidth=##L
wrapwidth=##L
bleedwidth=##L
marklength=##L
foldingmargin#true,false
10pt
11pt
12pt
markthick=##L
markcolor=#%color
pagecolor=#%color
trimmed#true,false
trimmingcolor=#%color
#endkeyvals

\begin{bookcover}
\end{bookcover}

\bookcovercomponent{type%keyvals}{part}{content}
\bookcovercomponent{type%keyvals}{part}[left,bottom,right,top]{content}
\begin{bookcoverelement}{type%keyvals}{part}
\begin{bookcoverelement}{type%keyvals}{part}[left,bottom,right,top]
\end{bookcoverelement}

#keyvals:\bookcovercomponent#c,\begin{bookcoverelement}#c
color
tikz
tikz clip
picture
normal
center
ruler
%bookcovertype
#endkeyvals

\partheight
\partwidth
\coverheight
\coverwidth
\spinewidth
\flapwidth
\wrapwidth
\bleedwidth
\marklength
\markthick

\bookcoverdescgeometry{geometry parameters%keyvals}

#keyvals:\bookcoverdescgeometry
## Layout size (section 5.2)
layout=#a0paper,a1paper,a2paper,a3paper,a4paper,a5paper,a6paper,b0paper,b1paper,b2paper,b3paper,b4paper,b5paper,b6paper,c0paper,c1paper,c2paper,c3paper,c4paper,c5paper,c6paper,b0j,b1j,b2j,b3j,b4j,b5j,b6j,ansiapaper,ansibpaper,ansicpaper,ansidpaper,ansiepaper,letterpaper,executivepaper,legalpaper
layoutwidth=##L
layoutheight=##L
layoutsize=##L
layoutsize={%<width%>,%<height%>}
layouthoffset=##L
layoutvoffset=##L
layoutoffset=##L
layoutoffset={%<hoffset%>,%<voffset%>}
## Body size (section 5.3)
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
## Margin size (section 5.4)
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
## Native dimensions (section 5.5)
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

\begin{bookcoverdescription}
\end{bookcoverdescription}

#ifOption:trimmed
\bookcovertrimmedpart{trimmed part}
\bookcovertrimmedpart{trimmed part}[left,bottom,right,top]
#endif
#ifOption:trimmed=true
\bookcovertrimmedpart{trimmed part}
\bookcovertrimmedpart{trimmed part}[left,bottom,right,top]
#endif

\setbookcover{options%keyvals}

#keyvals:\setbookcover
markthick=##L
markcolor=#%color
pagecolor=#%color
trimmed#true,false
trimmingcolor=#%color
#endkeyvals

\newbookcoverpart{new part}{setting}
\renewbookcoverpart{defined part}{setting}

\setpartposx{coord x}
\setpartposy{coord y}
\setpartwidth{width}
\setpartheight{height}
\settrimmedpart{width minus}{height minus}{shift x}{shift y}

\newnamebookcoverpart{new part}{defined part}
\letnamebookcoverpart{new part}{defined part}
\letnamebookcoverpart{new part}{defined part}[left,bottom,right,top]

\newbookcovercomponenttype{new type%specialDef}{formatting}#s#%bookcovertype
\renewbookcovercomponenttype{defined type}{formatting}
\newnamebookcovercomponenttype{new type%specialDef}{defined type}#s#%bookcovertype
\letnamebookcovercomponenttype{new type%specialDef}{defined type}#s#%bookcovertype

\makebookcover#*

\bookcover#S
\endbookcover#S