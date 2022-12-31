# pdfArticle class
# Matthew Bertucci 1/18/2022 for v1.0

#include:class-extarticle
#include:kvoptions
#include:fontspec
#include:graphicx
#include:graphbox
#include:xcolor
#include:fifo-stack
#include:geometry
#include:fancyvrb
#include:fvextra
#include:ulem
#include:contour
#include:shadowtext
#include:enumitem
#include:alphalph
#include:pbox
#include:varwidth
#include:overpic
#include:wrapfig
#include:array
#include:dcolumn
#include:tabto
#include:changepage
#include:ragged2e
#include:setspace
#include:amsmath
#include:unicode-math
#include:adjustbox
#include:hyperref

#ifOption:extra
#include:minted
#include:tcolorbox
#include:tcolorboxlibrarymany
#include:tcolorboxlibraryvignette
#include:tcolorboxlibraryminted
#include:tcolorboxlibrarymagazine
#include:tcolorboxlibraryposter
#include:tcolorboxlibraryexternal
#endif
#ifOption:extra=true
#include:minted
#include:tcolorbox
#include:tcolorboxlibrarymany
#include:tcolorboxlibraryvignette
#include:tcolorboxlibraryminted
#include:tcolorboxlibrarymagazine
#include:tcolorboxlibraryposter
#include:tcolorboxlibraryexternal
#endif

#keyvals:\documentclass/pdfArticle#c
fontSize=##L
mainFontFeat={%<fontspec features%>}
mainFont=%<font name%>
sansFontFeat={%<fontspec features%>}
sansFont=%<font name%>
monoFontFeat={%<fontspec features%>}
monoFont=%<font name%>
paperSize=#a0paper,a1paper,a2paper,a3paper,a4paper,a5paper,a6paper,b0paper,b1paper,b2paper,b3paper,b4paper,b5paper,b6paper,c0paper,c1paper,c2paper,c3paper,c4paper,c5paper,c6paper,b0j,b1j,b2j,b3j,b4j,b5j,b6j,ansiapaper,ansibpaper,ansicpaper,ansidpaper,ansiepaper,letterpaper,executivepaper,legalpaper
paperMode=#portrait,landscape
tmargin=##L
bmargin=##L
lmargin=##L
rmargin=##L
twoside#true,false
imgResolution=%<ppi%>
extra#true,false
#endkeyvals

\forceNewPageGeometry{options%keyvals}

#keyvals:\forceNewPageGeometry
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
layout=#a0paper,a1paper,a2paper,a3paper,a4paper,a5paper,a6paper,b0paper,b1paper,b2paper,b3paper,b4paper,b5paper,b6paper,c0paper,c1paper,c2paper,c3paper,c4paper,c5paper,c6paper,b0j,b1j,b2j,b3j,b4j,b5j,b6j,ansiapaper,ansibpaper,ansicpaper,ansidpaper,ansiepaper,letterpaper,executivepaper,legalpaper
layoutwidth=##L
layoutheight=##L
layoutsize=##L
layoutsize={%<width%>,%<height%>}
layouthoffset=##L
layoutvoffset=##L
layoutoffset=##L
layoutoffset={%<hoffset%>,%<voffset%>}
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

\hl{text}
\hl[color]{text}
\st{text}
\st[color]{text}
\ul{text}
\ul[color]{text}

\namedLabel{label}{name}#l

\DoNotLoadEpstopdf#S
\oldref{key}#Sr
