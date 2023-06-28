# kao package
# Matthew Bertucci 2022/10/11 for v0.9.8

#include:kvoptions
#include:etoolbox
#include:calc
#include:xcolor
# loads dvipsnames and table options of xcolor
#include:iftex
#include:xifthen
#include:options
#include:xpatch
#include:xstring
#include:afterpage
#include:imakeidx
#include:varioref
#include:scrhack
#include:geometry
#include:scrlayer-scrpage
#include:ragged2e
#include:setspace
#include:hyphenat
#include:microtype
#include:needspace
#include:xspace
#include:placeins
#include:marginnote
#include:sidenotes
#include:chngcntr
#include:footmisc
#include:footnotebackref
#include:graphicx
#include:tikz
#include:tikzpagenodes
#include:booktabs
#include:multirow
#include:multicol
#include:rotating
#include:listings
#include:caption
#include:floatrow
#include:tocbasic
#include:etoc
#include:inputenc
#include:fontenc
# loads T1 option of fontenc
#include:amssymb
#include:newpxtext
#include:newpxmath
#include:beramono
#include:mathalfa
# loads scr=rsfso and cal=boondoxo options of mathalfa
#include:morewrites
#include:hyperref
#include:bookmark
#include:enumitem
# loads inline option of enumitem
#include:tcolorbox
#include:tcolorboxlibrarymost
#include:pdfpages
#include:subfiles
#include:todonotes
#include:listings
#include:algorithm2e
#include:ccicons
#include:imakeidx
#include:glossaries
# loads xindy option of glossaries
#include:nomencl

\begin{fullwidthpar}
\end{fullwidthpar}
\begin{kaobox}
\begin{kaobox}[options%keyvals]
\end{kaobox}
\begin{kaocounter}
\end{kaocounter}
\begin{kaofloating}
\end{kaofloating}
\begin{marginlisting}
\begin{marginlisting}[offset%l]
\end{marginlisting}
\begin{wideequation}#\math
\end{wideequation}
\begin{widepar}
\end{widepar}

\adhoc
\BackrefFootnoteTag#S
\blankpage
\cfr
\cis
\Class{class}
\Command{csname}
\contentwidth#*
\denovo
\eg
\Environment{envname}
\etal
\etc
\etcetera
\floatingboxformat#*
\fullwidthpage#*
\hairsp
\hangp{text}#*
\hangstar#*
\headmarginparsep#*
\headmarginparwidth#*
\headtextwidth#*
\headtotal#*
\hscale#*
\ie
\ifinfloat#*
\IfInFloatingEnvir{true}{false}#*
\Ifthispageodd{true}{false}#*
\ifwidelayout#*
\IfWideLayout{true}{false}#*
\ifxetexorluatex
\infloatfalse#*
\infloattrue#*
\invitro
\invivo
\kaocounterformat#*
\kaomarginskipabove#*
\kaomarginskipbelow#*
\listofinsights
\listoflistings#*
\listofloiname#*
\listoflstlistings
\lstlistingtocdepth#*
\marginfloatsetup#*
\marginlayout#*
\marginskip{skip%l}#*
\margintoc
\margintoc[offset%l]
\margintocnumwidth#*
\margintocpagenumwidth#*
\monthyear
\mtocsection{title}#*
\mtocshift#*
\mtocsubsection{title}#*
\mycap#S
\na#*
\oldcaption#S
\oldmarginnote#S
\oldsection#S
\oldsubsection#S
\oldthanks#S
\Option{option}
\Package{package}
\pagelayout{layout name%keyvals}
\Path{path}
\recalchead#*
\section[short title]{title}[margintoc title%text]#L2
\section{title}[margintoc title%text]#L2
\subsection[short title]{title}[margintoc title%text]#L3
\subsection{title}[margintoc title%text]#L3
\thekaocounter#*
\themargintocdepth#*
\trans
\vs
\vscale#*
\widefloatsetup#*
\widelayout#*
\widelayoutfalse#*
\widelayouttrue#*
\xetexorluatexfalse#*
\xetexorluatextrue#*

#keyvals:\begin{kaobox}
### << always available keys >> ###
title=%<text%>
notitle
adjusted title=%<text%>
adjust text=%<text%>
squeezed title=%<text%>
squeezed title*=%<text%>
titlebox=#visible,invisible
detach title
attach title
attach title to upper=%<text%>
subtitle style={%<options%>}
upperbox=#visible,invisible
visible
invisible
saveto=%<file name%>
lowerbox=#visible,invisible,ignore
savelowerto=%<file name%>
lower separated#true,false
savedelimiter=%<name%>
colframe=#%color
colback=#%color
title filled#true,false
colbacktitle=#%color
colupper=#%color
collower=#%color
coltext=#%color
coltitle=#%color
fontupper=%<text%>
fontlower=%<text%>
fonttitle=%<text%>
halign=#justify,left,flush left,right,flush right,center,flush center
halign upper=#justify,left,flush left,right,flush right,center,flush center
halign lower=#justify,left,flush left,right,flush right,center,flush center
halign title=#justify,left,flush left,right,flush right,center,flush center
flushleft upper
center upper
flushright upper
flushleft lower
center lower
flushright lower
flushleft title
center title
flushright title
valign=#top,center,bottom,scale,scale*
valign upper=#top,center,bottom,scale,scale*
valign lower=#top,center,bottom,scale,scale*
valign scale limit=%<number%>
width=##L
text width=##L
add to width=##L
toprule=##L
bottomrule=##L
leftrule=##L
rightrule=##L
titlerule=##L
boxrule=##L
arc=##L
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=##L
auto outer arc
boxsep=##L
left=##L
left*=##L
lefttitle=##L
leftupper=##L
leftlower=##L
right=##L
right*=##L
righttitle=##L
rightupper=##L
rightlower=##L
top=##L
toptitle=##L
bottom=##L
bottomtitle=##L
middle=##L
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=##L
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=%<fraction%>
opacityback=%<fraction%>
opacitybacktitle=%<fraction%>
opacityfill=%<fraction%>
opacityupper=%<fraction%>
opacitylower=%<fraction%>
opacitytext=%<fraction%>
opacitytitle=%<fraction%>
natural height
height=##L
height plus=##L
height from=%<min%> to %<max%>
text height=##L
add to height=##L
add to natural height=##L
height fill
height fill=#true,false,maximum
inherit height
inherit height=%<fraction%>
square
space=%<fraction%>
space to upper
space to lower
space to both
space to=%<macro%>
split=%<fraction%>
equal height group=%<id%>
minimum for equal height group=%<id:length%>
minimum for current equal height group=##L
use height from group
use height from group=%<id%>
before title={%<code%>}
after title={%<code%>}
before upper={%<code%>}
before upper*={%<code%>}
after upper={%<code%>}
after upper*={%<code%>}
before lower={%<code%>}
before lower*={%<code%>}
after lower={%<code%>}
after lower*={%<code%>}
text fill=
tabulars={%<preamble%>}
tabulars*={%<code%>}{%<preamble%>}
tabularx={%<preamble%>}
tabularx*={%<code%>}{%<preamble%>}
tikz upper
tikz upper={%<TikZ options%>}
tikz lower
tikz lower={%<TikZ options%>}
tikznode upper
tikznode upper={%<TikZ options%>}
tikznode lower
tikznode lower={%<TikZ options%>}
tikznode
tikznode={%<TikZ options%>}
varwidth upper
varwidth upper=##L
overlay={%<code%>}
no overlay
overlay broken={%<code%>}
overlay unbroken={%<code%>}
overlay first={%<code%>}
overlay middle={%<code%>}
overlay last={%<code%>}
overlay unbroken and first={%<code%>}
overlay middle and last={%<code%>}
overlay unbroken and last={%<code%>}
overlay first and middle={%<code%>}
floatplacement=%<values%>
float
float=%<values%>
float*
float*=%<values%>
nofloat
every float={%<code%>}
before float={%<code%>}
after float={%<code%>}
before={%<code%>}
after={%<code%>}
nobeforeafter
force nobeforeafter
before skip balanced=%<glue%>
after skip balanced=%<glue%>
beforeafter skip balanced=%<glue%>
before skip=##L
after skip=##L
beforeafter skip=##L
left skip=##L
right skip=##L
leftright skip=##L
parskip
noparskip
autoparskip
baseline=##L
box align=#bottom,top,center,base
ignore nobreak#true,false
before nobreak={%<code%>}
parfillskip restore#true,false
enlarge top initially by=##L
enlarge bottom finally by=##L
enlarge top at break by=##L
enlarge bottom at break by=##L
enlarge top by=##L
enlarge bottom by=##L
enlarge left by=##L
enlarge right by=##L
enlarge by=##L
grow to left by=##L
grow to right by=##L
grow sidewards by=##L
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=##L
spread outwards
spread outwards=##L
move upwards
move upwards=##L
move upwards*
move upwards*=##L
fill downwards
fill downwards=##L
spread upwards
spread upwards=##L
spread upwards*
spread upwards*=##L
spread sidewards
spread sidewards=##L
spread
spread=##L
spread downwards
spread downwards=##L
shrink tight
extrude left by=##L
extrude right by=##L
extrude top by=##L
extrude bottom by=##L
extrude by=##L
every box/.style={%<options%>}
every box on layer 1/.style={%<options%>}
every box on layer 2/.style={%<options%>}
every box on layer 3/.style={%<options%>}
every box on layer 4/.style={%<options%>}
capture=#minipage,hbox,fitbox
hbox
minipage
parbox#true,false
hyphenationfix#true,false
tempfile=%<file name%>
phantom={%<code%>}
nophantom
label=##l
phantomlabel=##l
label type=%<type%>
no label type
step=%<counter%>
step and label={%<counter%>}{%<marker%>}
list entry=%<text%>
list text=%<text%>
add to list={%<list%>}{%<type%>}
nameref=%<text%>
hypertarget=%<marker%>
bookmark=%<text%>
bookmark*={%<options%>}{%<text%>}
index=%<entry%>
index*={%<name%>}{%<entry%>}
check odd page#true,false
if odd page={%<odd options%>}{%<even options%>}
if odd page or oneside={%<odd options%>}{%<even options%>}
if odd page*={%<odd options%>}{%<even options%>}
if odd page or oneside*={%<odd options%>}{%<even options%>}
shield externalize#true,false
external=%<file name%>
remake
remake#true,false
reset
code={%<code%>}
IfBlankTF={%<token list%>}{%<true%>}{%<false%>}
IfBlankT={%<token list%>}{%<true%>}
IfBlankF={%<token list%>}{%<false%>}
IfEmptyTF={%<token list%>}{%<true%>}{%<false%>}
IfEmptyT={%<token list%>}{%<true%>}
IfEmptyF={%<token list%>}{%<false%>}
IfNoValueTF={%<arg%>}{%<true%>}{%<false%>}
IfNoValueT={%<arg%>}{%<true%>}
IfNoValueF={%<arg%>}{%<false%>}
IfValueTF={%<arg%>}{%<true%>}{%<false%>}
IfValueT={%<arg%>}{%<true%>}
IfValueF={%<arg%>}{%<false%>}
IfBooleanTF={%<arg%>}{%<true%>}{%<false%>}
IfBooleanT={%<arg%>}{%<true%>}
IfBooleanF={%<arg%>}{%<false%>}
void
nirvana
blend before title=#colon,dash,colon hang,dash hang
blend before title code={%<code%>}
sidebyside#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=##L
lefthand width=##L
righthand width=##L
lefthand ratio=%<fraction%>
righthand ratio=%<fraction%>
sidebyside adapt=#none,left,right,both
sidebyside switch#true,false
verbatim ignore percent#true,false
record=%<content%>
no recording
skin=%<name%>
skin first=%<name%>
skin middle=%<name%>
skin last=%<name%>
graphical environment=%<envname%>
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes#true,false
frame code={%<code%>}
frame empty
interior titled code={%<code%>}
interior titled empty
interior code={%<code%>}
interior empty
segmentation code={%<code%>}
segmentation empty
title code={%<code%>}
title empty
skin first is subskin of={%<base skin%>}{%<options%>}
skin middle is subskin of={%<base skin%>}{%<options%>}
skin last is subskin of={%<base skin%>}{%<options%>}

### << skins library keys >> ###
frame style={%<TikZ options%>}
frame style image=%<file name%>
frame style tile={%<graphics options%>}{%<file%>}
frame hidden
interior style={%<TikZ options%>}
interior style image=%<file name%>
interior style tile={%<graphics options%>}{%<file%>}
interior hidden
segmentation style={%<TikZ options%>}
segmentation hidden
title style={%<TikZ options%>}
title style image=%<file name%>
title style tile={%<graphics options%>}{%<file%>}
title hidden
titlerule style={%<TikZ options%>}
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left={%<boxtitle options%>}
attach boxed title to top text left
attach boxed title to top text left={%<boxtitle options%>}
attach boxed title to top center
attach boxed title to top center={%<boxtitle options%>}
attach boxed title to top right
attach boxed title to top right={%<boxtitle options%>}
attach boxed title to top text right
attach boxed title to top text right={%<boxtitle options%>}
attach boxed title to bottom left
attach boxed title to bottom left={%<boxtitle options%>}
attach boxed title to bottom text left
attach boxed title to bottom text left={%<boxtitle options%>}
attach boxed title to bottom center
attach boxed title to bottom center={%<boxtitle options%>}
attach boxed title to bottom right
attach boxed title to bottom right={%<boxtitle options%>}
attach boxed title to bottom text right
attach boxed title to bottom text right={%<boxtitle options%>}
attach boxed title to top
attach boxed title to top={%<boxtitle options%>}
attach boxed title to top*
attach boxed title to top*={%<boxtitle options%>}
attach boxed title to bottom
attach boxed title to bottom={%<boxtitle options%>}
attach boxed title to bottom*
attach boxed title to bottom*={%<boxtitle options%>}
flip title
flip title={%<boxtitle options%>}
boxed title size=#title,standard,copy
boxed title style={%<options%>}
no boxed title style
hbox boxed title
minipage boxed title
minipage boxed title=##L
minipage boxed title*
minipage boxed title*=##L
tikznode boxed title={%<TikZ options%>}
varwidth boxed title
varwidth boxed title=##L
varwidth boxed title*
varwidth boxed title*=##L
watermark text=%<text%>
watermark text on=%<part%> is %<text%>
watermark graphics=%<file name%>
watermark graphics on=%<part%> is %<file%>
watermark tikz={%<code%>}
watermark tikz on=%<part%> is %<code%>
no watermark
watermark opacity=%<fraction%>
watermark zoom=%<fraction%>
watermark shrink=%<fraction%>
watermark overzoom=%<fraction%>
watermark stretch=%<fraction%>
watermark color=#%color
clip watermark#true,false
clip title#true,false
clip upper#true,false
clip lower#true,false
borderline={%<width%>}{%<offset%>}{%<TikZ options%>}
no borderline
show bounding box
show bounding box=#%color
borderline north={%<width%>}{%<offset%>}{%<TikZ options%>}
borderline south={%<width%>}{%<offset%>}{%<TikZ options%>}
borderline east={%<width%>}{%<offset%>}{%<TikZ options%>}
borderline west={%<width%>}{%<offset%>}{%<TikZ options%>}
borderline horizontal={%<width%>}{%<offset%>}{%<TikZ options%>}
borderline vertical={%<width%>}{%<offset%>}{%<TikZ options%>}
no shadow
drop shadow
drop shadow=#%color
drop fuzzy shadow
drop fuzzy shadow=#%color
drop midday shadow
drop midday shadow=#%color
drop fuzzy midday shadow
drop fuzzy midday shadow=#%color
halo
halo=%<size%> with %<color%>
fuzzy halo
fuzzy halo=%<size%> with %<color%>
drop shadow southeast
drop shadow southeast=#%color
drop shadow south
drop shadow south=#%color
drop shadow southwest
drop shadow southwest=#%color
drop shadow west
drop shadow west=#%color
drop shadow northwest
drop shadow northwest=#%color
drop shadow north
drop shadow north=#%color
drop shadow northeast
drop shadow northeast=#%color
drop shadow east
drop shadow east=#%color
drop fuzzy shadow southeast
drop fuzzy shadow southeast=#%color
drop fuzzy shadow south
drop fuzzy shadow south=#%color
drop fuzzy shadow southwest
drop fuzzy shadow southwest=#%color
drop fuzzy shadow west
drop fuzzy shadow west=#%color
drop fuzzy shadow northwest
drop fuzzy shadow northwest=#%color
drop fuzzy shadow north
drop fuzzy shadow north=#%color
drop fuzzy shadow northeast
drop fuzzy shadow northeast=#%color
drop fuzzy shadow east
drop fuzzy shadow east=#%color
drop lifted shadow
drop lifted shadow=#%color
drop small lifted shadow
drop small lifted shadow=#%color
drop large lifted shadow
drop large lifted shadow=#%color
shadow={%<xshift%>}{%<yshift%>}{%<offset%>}{%<TikZ options%>}
fuzzy shadow={%<xshift%>}{%<yshift%>}{%<offset%>}{%<step%>}{%<TikZ options%>}
smart shadow arc#true,false
lifted shadow={%<xshift%>}{%<yshift%>}{%<bend%>}{%<step%>}{%<TikZ options%>}
tikz={%<TikZ options%>}
tikz reset
at begin tikz={%<TikZ code%>}
at begin tikz reset
at end tikz={%<TikZ code%>}
at end tikz reset
rotate=%<angle%>
scale=%<fraction%>
remember
remember as=%<name%>
underlay={%<code%>}
no underlay
underlay broken={%<code%>}
underlay unbroken={%<code%>}
no underlay unbroken
underlay first={%<code%>}
no underlay first
underlay middle={%<code%>}
no underlay middle
underlay last={%<code%>}
no underlay last
underlay boxed title={%<code%>}
no underlay boxed title
underlay unbroken and first={%<code%>}
underlay middle and last={%<code%>}
underlay unbroken and last={%<code%>}
underlay first and middle={%<code%>}
finish={%<code%>}
no finish
finish broken={%<code%>}
finish unbroken={%<code%>}
no finish unbroken
finish first={%<code%>}
no finish first
finish middle={%<code%>}
no finish middle
finish last={%<code%>}
no finish last
finish unbroken and first={%<code%>}
finish middle and last={%<code%>}
finish unbroken and last={%<code%>}
finish first and middle={%<code%>}
hyperref=%<marker%>
hyperref interior=%<marker%>
hyperref title=%<marker%>
hyperref node={%<marker%>}{%<node%>}
hyperlink=%<marker%>
hyperlink interior=%<marker%>
hyperlink title=%<marker%>
hyperlink node={%<marker%>}{%<node%>}
hyperurl=%<URL%>
hyperurl interior=%<URL%>
hyperurl title=%<URL%>
hyperurl node={%<URL%>}{%<node%>}
hyperurl*={%<hyperref options%>}{%<URL%>}
hyperurl* interior={%<hyperref options%>}{%<URL%>}
hyperurl* title={%<hyperref options%>}{%<URL%>}
hyperurl* node={%<hyperref options%>}{%<URL%>}{%<node%>}
draftmode#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower=#%color
opacitybacklower=%<fraction%>
overlaplower=##L
bicolor jigsaw
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance={%<options%>}
extend freelancefirst={%<options%>}
extend freelancemiddle={%<options%>}
extend freelancelast={%<options%>}
only=<%<overlay spec%>>{%<options%>}
hide=<%<overlay spec%>>
beamer hidden/.style={%<options%>}
alert=<%<overlay spec%>>
beamer alerted/.style={%<options%>}

### << breakable library keys >> ###
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=%<text%>
notitle after break
adjusted title after break=%<text%>
lines before break=%<number%>
break at=%<length1/length2/...%>
enlargepage=%<length1/length2/...%>
enlargepage flexible=##L
compress page
compress page=#all,baselineskip,none
shrink break goal=##L
use color stack#true,false
toprule at break=##L
bottomrule at break=##L
topsep at break=##L
bottomsep at break=##L
pad before break=##L
pad before break*=##L
pad after break=##L
pad at break=##L
pad at break*=##L
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first#true,false
segmentation at break#true,false
extras={%<options%>}
no extras
extras broken={%<options%>}
extras unbroken={%<options%>}
no extras unbroken
extras first={%<options%>}
no extras first
extras middle={%<options%>}
no extras middle
extras last={%<options%>}
no extras last
extras unbroken and first={%<options%>}
extras middle and last={%<options%>}
extras unbroken and last={%<options%>}
extras first and middle={%<options%>}
extras title after break={%<options%>}
no extras title after break

### << hooks library keys >> ###
before title app={%<code%>}
before title pre={%<code%>}
after title app={%<code%>}
after title pre={%<code%>}
before upper app={%<code%>}
before upper pre={%<code%>}
after upper app={%<code%>}
after upper pre={%<code%>}
before lower app={%<code%>}
before lower pre={%<code%>}
after lower app={%<code%>}
after lower pre={%<code%>}
before app={%<code%>}
before pre={%<code%>}
after app={%<code%>}
after pre={%<code%>}
before float app={%<code%>}
before float pre={%<code%>}
after float app={%<code%>}
after float pre={%<code%>}
overlay app={%<code%>}
overlay pre={%<code%>}
overlay unbroken app={%<code%>}
overlay unbroken pre={%<code%>}
overlay first app={%<code%>}
overlay first pre={%<code%>}
overlay middle app={%<code%>}
overlay middle pre={%<code%>}
overlay last app={%<code%>}
overlay last pre={%<code%>}
overlay broken app={%<code%>}
overlay broken pre={%<code%>}
overlay unbroken and first app={%<code%>}
overlay unbroken and first pre={%<code%>}
overlay middle and last app={%<code%>}
overlay middle and last pre={%<code%>}
overlay unbroken and last app={%<code%>}
overlay unbroken and last pre={%<code%>}
overlay first and middle app={%<code%>}
overlay first and middle pre={%<code%>}
watermark text app=%<text%>
watermark text pre=%<text%>
watermark text app on=%<part%> is %<text%>
watermark text pre on=%<part%> is %<text%>
watermark graphics app=%<file name%>
watermark graphics pre=%<file name%>
watermark graphics app on=%<part%> is %<file%>
watermark graphics pre on=%<part%> is %<file%>
watermark tikz app={%<code%>}
watermark tikz pre={%<code%>}
watermark tikz app on=%<part%> is %<code%>
watermark tikz pre on=%<part%> is %<code%>
underlay pre={%<code%>}
underlay unbroken pre={%<code%>}
underlay first pre={%<code%>}
underlay middle pre={%<code%>}
underlay last pre={%<code%>}
underlay boxed title pre={%<code%>}
underlay broken pre={%<code%>}
underlay unbroken and first pre={%<code%>}
underlay middle and last pre={%<code%>}
underlay unbroken and last pre={%<code%>}
underlay first and middle pre={%<code%>}
finish pre={%<code%>}
finish unbroken pre={%<code%>}
finish first pre={%<code%>}
finish middle pre={%<code%>}
finish last pre={%<code%>}
finish broken pre={%<code%>}
finish unbroken and first pre={%<code%>}
finish middle and last pre={%<code%>}
finish unbroken and last pre={%<code%>}
finish first and middle pre={%<code%>}
frame code app={%<code%>}
frame code pre={%<code%>}
interior titled code app={%<code%>}
interior titled code pre={%<code%>}
interior code app={%<code%>}
interior code pre={%<code%>}
segmentation code app={%<code%>}
segmentation code pre={%<code%>}
title code app={%<code%>}
title code pre={%<code%>}
extras pre={%<options%>}
extras unbroken pre={%<options%>}
extras first pre={%<options%>}
extras middle pre={%<options%>}
extras last pre={%<options%>}
extras broken pre={%<options%>}
extras unbroken and first pre={%<options%>}
extras middle and last pre={%<options%>}
extras unbroken and last pre={%<options%>}
extras first and middle pre={%<options%>}
listing options app={%<options%>}
listing options pre={%<options%>}
minted options app={%<options%>}
minted options pre={%<options%>}

### << xparse library keys >> ###
verbatim

### << listings library keys >> ###
listing options={%<listings options%>}
no listing options
listing style=%<style%>
listing inputencoding=%<encoding%>
listing remove caption#true,false
every listing line=%<text%>
every listing line*=%<text%>
listing utf8=%<encoding%>
minted language=%<programming lang%>
minted options={%<minted options%>}
default minted options={%<minted options%>}
minted style=%<style%>
listing engine=#listings,minted
listing file=%<file name%>
listing and text
text and listing
listing only
text only
comment=%<text%>
comment only
image comment={%<graphics options%>}{%<file%>}
tcbimage comment=%<file name%>
pdf comment
pdf comment=%<file name%>
pdf extension=%<extension%>
comment style={%<options%>}
listing and comment
comment and listing
listing side text
text side listing
listing outside text
text outside listing
listing side comment
comment side listing
listing outside comment
comment outside listing
listing above text
listing above* text
text above listing
text above* listing
listing above comment
listing above* comment
comment above listing
comment above* listing
no process
process code={%<code%>}
run system command=%<system command%>
compilable listing
run pdflatex=%<arguments%>
run pdflatex
run xelatex=%<arguments%>
run xelatex
run lualatex=%<arguments%>
run lualatex
run makeindex=%<arguments%>
run makeindex
run bibtex=%<arguments%>
run bibtex
run biber=%<arguments%>
run biber
run arara=%<arguments%>
run arara
run latex=%<arguments%>
run latex
run dvips=%<arguments%>
run dvips
run ps2pdf=%<arguments%>
run ps2pdf
freeze file=%<file%>
freeze none
freeze extension=%<text%>
freeze pdf
freeze png
freeze jpg
externalize listing=%<name%>
externalize listing!=%<name%>
#endkeyvals

#keyvals:\pagelayout
margin
wide
fullwidth
#endkeyvals

#keyvals:\pagestyle#c,\thispagestyle#c
pagenum.scrheadings
centeredpagenum.scrheadings
#endkeyvals

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

# from table option of xcolor
#include:colortbl

# from hang option of footmisc
\hangfootparskip#*
\hangfootparindent#*

# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n

# from scr=rsfso option of mathalfa
\mathscr{text%plain}#m

# from cal=boondoxo options of mathalfa
\mathcal{text%plain}#m
\mathbfcal{text%plain}#m

# from inline option of enumitem
\begin{enumerate*}
\begin{enumerate*}[options%keyvals]
\end{enumerate*}
\begin{itemize*}
\begin{itemize*}[options%keyvals]
\end{itemize*}
\begin{description*}
\begin{description*}[options%keyvals]
\end{description*}

# from xindy option of glossaries
\GlsSetXdyLanguage{language}
\GlsSetXdyLanguage[glossary type]{language}
\GlsSetXdyCodePage{code}
\GlsAddXdyCounters{counter list}
\GlsAddXdyAttribute{name}
\GlsAddXdyLocation{name}{definition}
\GlsAddXdyLocation[prefix-location]{name}{definition}
\GlsSetXdyLocationClassOrder{location names}
\GlsSetXdyMinRangeLength{integer}
\GlsSetXdyFirstLetterAfterDigits{letter}
\GlsSetXdyNumberGroupOrder{relative location}
\GlsAddLetterGroup{arg1}{arg2}
\GlsAddSortRule{arg1}{arg2}
\GlsAddXdyAlphabet{name}{definition}
\GlsAddXdyStyle{xindy style}
\GlsSetXdyStyles{xindy styles}
