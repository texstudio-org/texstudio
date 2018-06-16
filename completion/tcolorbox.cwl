# thatlittleboy/2018-06-07 for tcolorbox v4.13
#include:environ
#include:etoolbox
#include:pgf
#include:verbatim

# << Package options (load libraries) >>
#ifOption:skins
#include:tikz
#endif
#ifOption:listings
#include:listings
#endif
#ifOption:listingsutf8
#include:listings
#include:listingsutf8
#endif
#ifOption:minted
#include:minted
#endif
#ifOption:xparse
#include:xparse
#endif
#ifOption:many
#include:tikz
#include:xparse
#endif
#ifOption:most
#include:tikz
#include:listings
#include:listingsutf8
#include:xparse
#endif
#ifOption:all
#include:tikz
#include:listings
#include:listingsutf8
#include:minted
#include:xparse
#endif

# << Libraries >>
\tcbuselibrary{%<library%>%keys}
#keyvals:\tcbuselibrary
skins
vignette
raster
listings
listingsutf8
minted
theorems
breakable
magazine
poster
fitting
hooks
xparse
external
documentation
many
most
all
#endkeyvals

# << Box Creation >>
\begin{tcolorbox}
\begin{tcolorbox}[%<options%>]
\end{tcolorbox}
\tcblower
\tcbset{%<options%>}
\tcbsetforeverylayer{%<options%>}
\tcbox[%<options%>]{%<box content%>}
\newtcolorbox{envname}{options%keyvals}#N
\newtcolorbox[init options%keyvals]{envname}[number][default]{options%keyvals}#*N
\renewtcolorbox{envname}{options%keyvals}
\renewtcolorbox[init options%keyvals]{envname}[number][default]{options%keyvals}#*
\newtcbox{\name}{options%keyvals}
\newtcbox[init options%keyvals]{\name}[number][default]{options%keyvals}#*
\renewtcbox{\name}{options%keyvals}
\renewtcbox[init options%keyvals]{\name}[number][default]{options%keyvals}#*
\tcolorboxenvironment{envname}{options%keyvals}#N

# << Subtitle >>
\tcbsubtitle[options%keyvals]{text}

# << Geometry/Height control >>
\tcbheightfromgroup{macro}{id}

# << Layered Boxes and Every Box settings >>
\tcbsetmanagedlayers{number}

# << Even and Odd pages >>
\tcbifoddpage{odd code}{even code}
\tcbifoddpageoroneside{odd code}{even code}
\thetcolorboxnumber
\thetcolorboxpage

# << Numbered Boxes >>
\thetcbcounter
\tcbcounter

# << Lists of tcolorboxes >>
\tcblistof{name}{title text}
\tcblistof[macro]{name}{title text}

# << Advanced settings from xparse library
\tcbsidebyside{left-handed content}{right-handed content}
\tcbsidebyside[options%keyvals]{left-handed content}{right-handed content}

# << Saving and loading of verbatim texts
\begin{tcbverbatimwrite}{%<file%>}
\end{tcbverbatimwrite}
\tcbverbatimwrite
\endtcbverbatimwrite
\begin{tcbwritetemp}
\end{tcbwritetemp}
\tcbusetemp

# << Recording >>
\tcbstartrecording
\tcbstartrecording[%<file%>]
\tcbrecord{content}
\tcbstoprecording
\tcbinputrecords
\tcbinputrecords[%<file%>]

# << Skins >>
\tcbsubskin{name}{base skin}{options%keyvals}
\tcbheightspace
\tcbtextwidth
\tcbtextheight
\tcbsegmentstate
\begin{tcbclipframe}
\end{tcbclipframe}
\begin{tcbinvclipframe}
\end{tcbinvclipframe}
\begin{tcbclipinterior}
\end{tcbclipinterior}
\begin{tcbcliptitle}
\end{tcbcliptitle}
\tcbstartdraftmode#*
\tcbstopdraftmode#*
\tcbinterruptdraftmode#*
\tcbcontinuedraftmode#*
\tcbline
\tcbline*

# << Inclusion of Boxed Image Files >>
\tcbincludegraphics{file}
\tcbincludegraphics[options%keyvals]{file}
\imagename
\tcbincludepdf{file}
\tcbincludepdf[options%keyvals]{file}
\imagepage
\pdfpages

# << TikZ image and picture fill extensions; Aux macros >>
\tcbpatcharcangular
\tcbpatcharcround
\tcbsettowidthofnode{register}{node}
\tcbsetmacrotowidthofnode{macro}{node}
\tcbsettoheightofnode{register}{node}
\tcbsetmacrotoheightofnode{macro}{node}
\tcbhypernode{macro}{node}

# << Vignette >>
\tcbvignette{options%keyvals}

# << Rasters >>
\begin{tcbraster}
\begin{tcbraster}[options%keyvals]
\end{tcbraster}
\thetcbrasternum
\begin{tcbitemize}
\begin{tcbitemize}[options%keyvals]
\end{tcbitemize}
\tcbitem
\tcbitem[options%keyvals]
\begin{tcboxedraster}{box options}
\begin{tcboxedraster}[raster options]{box options}
\end{tcboxedraster}
\begin{tcboxeditemize}{box options}
\begin{tcboxeditemize}[raster options]{box options}
\end{tcboxeditemize}

# << Listings, minted >>
\begin{tcblisting}{options%keyvals}
\end{tcblisting}
\begin{tcboutputlisting}
\end{tcboutputlisting}
\tcbinputlisting{options%keyvals}
\tcbuselistingtext
\tcbuselistinglisting
\tcbusetemplisting
\newtcblisting{envname}{options%keyvals}#N
\newtcblisting[init options%keyvals]{envname}[number][default]{options%keyvals}#*N
\renewtcblisting{envname}{options%keyvals}
\renewtcblisting[init options%keyvals]{envname}[number][default]{options%keyvals}#*
\newtcbinputlisting{\name}{options%keyvals}
\newtcbinputlisting[init options%keyvals]{\name}[number][default]{options%keyvals}#*

# << Theorems >>
\newtcbtheorem{envname}{display name}{options%keyvals}{prefix}#N
\newtcbtheorem[init options%keyvals]{envname}{display name}{options%keyvals}{prefix}#*N
\renewtcbtheorem{envname}{display name}{options%keyvals}{prefix}
\renewtcbtheorem[init options%keyvals]{envname}{display name}{options%keyvals}{prefix}#*
\tcbmaketheorem{name}{display name}{options%keyvals}{counter}{prefix}#*
\tcboxmath[options%keyvals]{mathematical box content}
\tcbhighmath[options%keyvals]{mathematical box content}

# << Breakable >>
\tcbbreak

# << Magazine >>
\newboxarray{name}
\boxarrayreset
\boxarrayreset[%<name%>]
\boxarrayclear
\boxarrayclear[%<name%>]
\begin{boxarraystore}{%<name%>}
\end{boxarraystore}
\boxarraygetsize{macro}
\boxarraygetsize[name]{macro}
\useboxarray{index}
\useboxarray[name]{index}
\usetcboxarray{index}{options%keyvals}
\usetcboxarray[name]{index}{options%keyvals}
\consumeboxarray{index}
\consumeboxarray[name]{index}
\consumetcboxarray{index}{options%keyvals}
\consumetcboxarray[name]{index}{options%keyvals}
\boxarraygetbox{macro}{index}
\boxarraygetbox[name]{macro}{index}
\ifboxarrayempty{index}{true}{false}
\ifboxarrayempty[name]{index}{true}{false}
\boxarraygetwidth{macro}{index}
\boxarraygetwidth[name]{macro}{index}
\boxarraygetheight{macro}{index}
\boxarraygetheight[name]{macro}{index}
\boxarraygetdepth{macro}{index}
\boxarraygetdepth[name]{macro}{index}
\boxarraygettotalheight{macro}{index}
\boxarraygettotalheight[name]{macro}{index}

# << Posters >>
\begin{tcbposter}
\begin{tcbposter}[options%keyvals]
\end{tcbposter}
\tcbposterwidth
\tcbposterheight
\tcbpostercolspacing
\tcbposterrowspacing
\tcbpostercolumns
\tcbposterrows
\tcbpostercolwidth
\tcbposterrowheight
\tcbposterset{options%keyvals}
\posterbox{placement}{box content}
\posterbox[options%keyvals]{placement}{box content}
\begin{posterboxenv}{placement}
\begin{posterboxenv}[options%keyvals]{placement}
\end{posterboxenv}

# << Fitting >>
\tcboxfit{box content}
\tcboxfit[options%keyvals]{box content}
\newtcboxfit{\name}{options%keyvals}
\newtcboxfit[init options%keyvals]{\name}[number][default]{options%keyvals}#*
\renewtcboxfit{\name}{options%keyvals}
\renewtcboxfit[init options%keyvals]{\name}[number][default]{options%keyvals}#*
\tcbfontsize{factor}
\tcbfitdim
\tcbfitsteps

# << xparse >>
\DeclareTColorBox{envname}{specification}{options%keyvals}#N
\DeclareTColorBox[init options%keyvals]{envname}{specification}{options%keyvals}#*N
\NewTColorBox{envname}{specification}{options%keyvals}#N
\NewTColorBox[init options%keyvals]{envname}{specification}{options%keyvals}#*N
\RenewTColorBox{envname}{specification}{options%keyvals}
\RenewTColorBox[init options%keyvals]{envname}{specification}{options%keyvals}#*
\ProvideTColorBox{envname}{specification}{options%keyvals}#N
\ProvideTColorBox[init options%keyvals]{envname}{specification}{options%keyvals}#*N
\DeclareTotalTColorBox{\name}{specification}{options%keyvals}{content}
\DeclareTotalTColorBox[init options%keyvals]{\name}{specification}{options%keyvals}{content}#*
\NewTotalTColorBox{\name}{specification}{options%keyvals}{content}
\NewTotalTColorBox[init options%keyvals]{\name}{specification}{options%keyvals}{content}#*
\RenewTotalTColorBox{\name}{specification}{options%keyvals}{content}
\RenewTotalTColorBox[init options%keyvals]{\name}{specification}{options%keyvals}{content}#*
\ProvideTotalTColorBox{\name}{specification}{options%keyvals}{content}
\ProvideTotalTColorBox[init options%keyvals]{\name}{specification}{options%keyvals}{content}#*
\DeclareTCBox{\name}{specification}{options%keyvals}
\DeclareTCBox[init options%keyvals]{\name}{specification}{options%keyvals}#*
\NewTCBox{\name}{specification}{options%keyvals}
\NewTCBox[init options%keyvals]{\name}{specification}{options%keyvals}#*
\RenewTCBox{\name}{specification}{options%keyvals}
\RenewTCBox[init options%keyvals]{\name}{specification}{options%keyvals}#*
\ProvideTCBox{\name}{specification}{options%keyvals}
\ProvideTCBox[init options%keyvals]{\name}{specification}{options%keyvals}#*
\DeclareTotalTCBox{\name}{specification}{options%keyvals}{content}
\DeclareTotalTCBox[init options%keyvals]{\name}{specification}{options%keyvals}{content}#*
\NewTotalTCBox{\name}{specification}{options%keyvals}{content}
\NewTotalTCBox[init options%keyvals]{\name}{specification}{options%keyvals}{content}#*
\RenewTotalTCBox{\name}{specification}{options%keyvals}{content}
\RenewTotalTCBox[init options%keyvals]{\name}{specification}{options%keyvals}{content}#*
\ProvideTotalTCBox{\name}{specification}{options%keyvals}{content}
\ProvideTotalTCBox[init options%keyvals]{\name}{specification}{options%keyvals}{content}#*
\tcboxverb{verbatim box content}
\tcboxverb[options%keyvals]{verbatim box content}#*
\DeclareTCBListing{envname}{specification}{options%keyvals}#N
\DeclareTCBListing[init options%keyvals]{envname}{specification}{options%keyvals}#*N
\NewTCBListing{envname}{specification}{options%keyvals}#N
\NewTCBListing[init options%keyvals]{envname}{specification}{options%keyvals}#*N
\RenewTCBListing{envname}{specification}{options%keyvals}
\RenewTCBListing[init options%keyvals]{envname}{specification}{options%keyvals}#*
\ProvideTCBListing{envname}{specification}{options%keyvals}#N
\ProvideTCBListing[init options%keyvals]{envname}{specification}{options%keyvals}#*N
\DeclareTCBInputListing{\name}{specification}{options%keyvals}
\DeclareTCBInputListing[init options%keyvals]{\name}{specification}{options%keyvals}#*
\NewTCBInputListing{\name}{specification}{options%keyvals}
\NewTCBInputListing[init options%keyvals]{\name}{specification}{options%keyvals}#*
\RenewTCBInputListing{\name}{specification}{options%keyvals}
\RenewTCBInputListing[init options%keyvals]{\name}{specification}{options%keyvals}#*
\ProvideTCBInputListing{\name}{specification}{options%keyvals}
\ProvideTCBInputListing[init options%keyvals]{\name}{specification}{options%keyvals}#*
\DeclareTCBoxFit{\name}{specification}{options%keyvals}
\DeclareTCBoxFit[init options%keyvals]{\name}{specification}{options%keyvals}#*
\NewTCBoxFit{\name}{specification}{options%keyvals}
\NewTCBoxFit[init options%keyvals]{\name}{specification}{options%keyvals}#*
\RenewTCBoxFit{\name}{specification}{options%keyvals}
\RenewTCBoxFit[init options%keyvals]{\name}{specification}{options%keyvals}#*
\ProvideTCBoxFit{\name}{specification}{options%keyvals}
\ProvideTCBoxFit[init options%keyvals]{\name}{specification}{options%keyvals}#*
\DeclareTotalTCBoxFit{\name}{specification}{options%keyvals}{content}
\DeclareTotalTCBoxFit[init options%keyvals]{\name}{specification}{options%keyvals}{content}#*
\NewTotalTCBoxFit{\name}{specification}{options%keyvals}{content}
\NewTotalTCBoxFit[init options%keyvals]{\name}{specification}{options%keyvals}{content}#*
\RenewTotalTCBoxFit{\name}{specification}{options%keyvals}{content}
\RenewTotalTCBoxFit[init options%keyvals]{\name}{specification}{options%keyvals}{content}#*
\ProvideTotalTCBoxFit{\name}{specification}{options%keyvals}{content}
\ProvideTotalTCBoxFit[init options%keyvals]{\name}{specification}{options%keyvals}{content}#*

# << External >>
\tcbEXTERNALIZE#*
\begin{tcbexternal}{name}#*
\begin{tcbexternal}[options%keyvals]{name}#*
\end{tcbexternal}#*
\begin{extcolorbox}{name}#*
\begin{extcolorbox}[options%keyvals]{name}[tcolorbox options%keyvals]#*
\end{extcolorbox}#*
\begin{extikzpicture}{name}#*
\begin{extikzpicture}[options%keyvals]{name}[tikz options%keyvals]#*
\end{extikzpicture}#*
\tcbifexternal{true}{false}#*
\newtcbexternalizeenvironment{newenv%envname}{env}{options%keyvals}{begin}{end}#*N
\renewtcbexternalizeenvironment{newenv%envname}{env}{options%keyvals}{begin}{end}#*
\newtcbexternalizetcolorbox{newenv%envname}{env}{options%keyvals}{begin end options}#*N
\renewtcbexternalizetcolorbox{newenv%envname}{env}{options%keyvals}{begin end options}#*
\tcbiffileprocess{condition}{source}{md5-file}{target}{true}{false}#*

# << Documentation >>
\begin{docCommand}{name}{parameters}#*
\begin{docCommand}[options%keyvals]{name}{parameters}#*
\end{docCommand}#*
\begin{docCommand*}{name}{parameters}#*
\begin{docCommand*}[options%keyvals]{name}{parameters}#*
\end{docCommand*}#*
\begin{docEnvironment}{name}{parameters}#*
\begin{docEnvironment}[options%keyvals]{name}{parameters}#*
\end{docEnvironment}#*
\begin{docEnvironment*}{name}{parameters}#*
\begin{docEnvironment*}[options%keyvals]{name}{parameters}#*
\end{docEnvironment*}#*
\begin{docKey}{name}{parameters}{description}{key description}#*
\begin{docKey}[key path][options%keyvals]{name}{parameters}{description}{key description}#*
\end{docKey}#*
\begin{docKey*}{name}{parameters}{description}{key description}#*
\begin{docKey*}[key path][options%keyvals]{name}{parameters}{description}{key description}#*
\end{docKey*}#*
\docValue{name}#*
\docValue*{name}#*
\docAuxCommand{name}#*
\docAuxCommand*{name}#*
\docAuxEnvironment{name}#*
\docAuxEnvironment*{name}#*
\docAuxEnvironment*[key path]{name}#*
\docAuxKey{name}#*
\docAuxKey[key path]{name}#*
\docAuxKey*{name}#*
\docAuxKey*[key path]{name}#*
\docCounter{name}#*
\docCounter*{name}#*
\docLength{name}#*
\docLength*{name}#*
\docColor{name}#*
\docColor*{name}#*
\cs{name}#*
\meta{text}#*
\marg{text}#*
\oarg{text}#*
\brackets{text}#*
\begin{dispExample}#*
\end{dispExample}#*
\begin{dispExample*}{options%keyvals}#*
\end{dispExample*}#*
\begin{dispListing}#*
\end{dispListing}#*
\begin*{dispListing}{options%keyvals}#*
\end*{dispListing}#*
\begin{absquote}#*
\end{absquote}#*
\tcbmakedocSubKey{name}{key path}#*
\refCom{name}#*
\refCom*{name}#*
\refEnv{name}#*
\refEnv*{name}#*
\refKey{name}#*
\refKey*{name}#*
\refAux{name}#*
\refAuxcs{name}#*
\colDef{text}#*
\col0pt{text}#*
\tcbdocmarginnote{text}#*
\tcbdocmarginnote[options%keyvals]{text}#*
\tcbdocnew{date}#*
\tcbdocupdated{date}#*

# ---------------------------------------
# << Option Keys >> - Standard + External + Doc
# ---------------------------------------
#keyvals:\tcbset
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=

external/runner=
external/prefix=
external/externalize
external/externalize=#true,false
external/force remake
external/force remake=#true,false
external/!
external/-
external/name=
externalize listing=
externalize listing!=
externalize example=
externalize example!=
external/safety=
external/environment=
external/environment with percent
external/environment with percent=#true,false
external/minipage
external/minipage=
external/plain
external/compiler=
external/runs=
external/input source on error
external/input source on error=#true,false
external/preclass=
external/PassOptionsToPackage=
external/PassOptionsToClass=
external/clear preclass
external/preamble=
external/preamble tcbset=
external/clear preamble
docexample/.style=
documentation listing options=
documentation listing style=
documentation minted options=
documentation minted style=
documentation minted language=
keywords bold
keywords bold=#true,false
index command=
index command name=
index format=#pgfsection,pgfchapter,pgf,doc,off
index actual=
index quote=
index level=
index default settings
index german settings
index annotate
index annotate=#true,false
index colorize
index colorize=#true,false
color command=
color environment=
color key=
color value=
color counter=
color length=
color color=
color definition=
color option=
color hyperlink=
english language
doclang/color=
doclang/colors=
doclang/counter=
doclang/environment=
doclang/environments=
doclang/environment content=
doclang/index=
doclang/key=
doclang/keys=
doclang/length=
doclang/lengths=
doclang/new=
doclang/pageshort=
doclang/updated=
doclang/value=
doclang/values=
doc left=
doc right=
doc left indent=
doc right indent=
doc head command=
doc head environment=
doc head key=
doc head=
before doc body command=
after doc body command=
before doc body environment=
after doc body environment=
before doc body key=
after doc body key=
before doc body=
after doc body=
doc description=
doc into index
doc into index=#true,false
doc marginnote=
doc new=
doc updated=
doc new and updated=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard
# ---------------------------------------
#keyvals:\tcbsetforeverylayer
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard
# ---------------------------------------
#keyvals:\tcbox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + Init
# ---------------------------------------
#keyvals:\newtcolorbox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + Init
# ---------------------------------------
#keyvals:\renewtcolorbox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + Init
# ---------------------------------------
#keyvals:\newtcbox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard
# ---------------------------------------
#keyvals:\tcolorboxenvironment
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard
# ---------------------------------------
#keyvals:\tcbsidebyside
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Graphics
# ---------------------------------------
#keyvals:\tcbincludegraphics
graphics options=
graphics orientation=#as-is,landscape,landscape*,portrait,portrait*
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Graphics
# ---------------------------------------
#keyvals:\tcbincludepdf
graphics options=
graphics orientation=#as-is,landscape,landscape*,portrait,portrait*
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Vignette
# ---------------------------------------
#keyvals:\tcbvignette
xmin=
xmax=
ymin=
ymax=
lower left corner=
upper right corner=
inside node=
outside node=
over node=
over node offset=
north size=
south size=
east size=
west size=
vertical size=
horizontal size=
size=
north style=
south style=
east style=
west style=
scope=
raised color=
lowered color=
color from=
base color=
draw method=#direct,clipped
fade in=
fade out=
semi fade in=
semi fade out=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard
# ---------------------------------------
#keyvals:\tcbitem
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard
# ---------------------------------------
#keyvals:\tcbinputlisting
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\newtcblisting
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\newtcbinputlisting
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\newtcbtheorem
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard
# ---------------------------------------
#keyvals:\tcboxmath
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard
# ---------------------------------------
#keyvals:\tcbhighmath
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard
# ---------------------------------------
#keyvals:\usetcboxarray
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard
# ---------------------------------------
#keyvals:\consumetcboxarray
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Posters
# ---------------------------------------
#keyvals:\tcbposterset
poster=
coverage=
no coverage
boxes=
fontsize=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard
# ---------------------------------------
#keyvals:\tcboxfit
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\newtcboxfit
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\DeclareTColorBox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\NewTColorBox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\RenewTColorBox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\ProvideTColorBox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\DeclareTotalTColorBox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\NewTotalTColorBox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\RenewTotalTColorBox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\ProvideTotalTColorBox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\DeclareTCBox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\NewTCBox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\RenewTCBox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\ProvideTCBox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\DeclareTotalTCBox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\NewTotalTCBox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\RenewTotalTCBox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\ProvideTotalTCBox
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard
# ---------------------------------------
#keyvals:\tcboxverb
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\DeclareTCBListing
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\NewTCBListing
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\RenewTCBListing
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\ProvideTCBListing
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\DeclareTCBInputListing
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\NewTCBInputListing
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\RenewTCBInputListing
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\ProvideTCBInputListing
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\DeclareTCBoxFit
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\NewTCBoxFit
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\RenewTCBoxFit
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\ProvideTCBoxFit
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\DeclareTotalTCBoxFit
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\NewTotalTCBoxFit
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\RenewTotalTCBoxFit
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + init
# ---------------------------------------
#keyvals:\ProvideTotalTCBoxFit
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
auto counter
use counter from=
use counter=
use counter*=
no counter
number within=
number format=
number freestyle=
crefname=
Crefname=
blend into=#figures,tables,listings
blend before title=#colon,dash,colon hang, dash hang
blend before title code=
list inside=
list type=
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Standard + doc
# ---------------------------------------
#keyvals:\tcbdocmarginnote
title=
notitle
adjusted title=
adjust text=
squeezed title=
squeezed title*=
detach title
attach title
attach title to upper=
subtitle style=
upperbox=#visible,invisible
visible
invisible
save to=
lowerbox=#visible,invisible,ignore
savelowerto=
lower separated=#true,false
savedelimiter=
colframe=
colback=
title filled=#true,false
colbacktitle=
colupper=
collower=
coltext=
coltitle=
fontupper=
fontlower=
fonttitle=
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
valign scale limit=
width=
text width=
add to width=
toprule=
bottomrule=
leftrule=
rightrule=
titlerule=
boxrule=
arc=
circular arc
bean arc
octogon arc
arc is angular
arc is curved
outer arc=
auto outer arc
boxsep=
left=
left*=
lefttitle=
leftupper=
leftlower=
right=
right*=
righttitle=
rightupper=
rightlower=
top=
toptitle=
bottom=
bottomtitle=
middle=
size=#normal,title,small,fbox,tight,minimal
oversize
oversize=
toggle left and right=#none,forced,evenpage
sharp corners
sharp corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
rounded corners
rounded corners=#northwest,northeast,southwest,southeast,north,south,east,west,downhill,uphill,all
sharpish corners
opacityframe=
opacityback=
opacitybacktitle=
opacityfill=
opacityupper=
opacitylower=
opacitytext=
opacitytitle=
natural height
height=
height plus=
height from=
text height=
add to height=
add to natural height=
height fill
height fill=#true,false,maximum
inherit height
inherit height=
square
space=
space to upper
space to lower
space to both
space to=
split=
equal height group=
minimum for equal height group=
minimum for current equal height group=
use height from group=
before title=
after title=
before upper=
after upper=
before lower=
after lower=
text fill=
tabularx=
tabularx*=
tikz upper
tikz upper=
tikz lower
tikz lower=
tikznode upper
tikznode upper=
tikznode lower
tikznode lower=
tikznode
tikznode=
varwidth upper
varwidth upper=
overlay=
no overlay
overlay broken=
overlay unbroken=
overlay first=
overlay middle=
overlay last=
overlay unbroken and first=
overlay middle and last=
overlay unbroken and last=
overlay first and middle=
floatplacement=
float
float=
float*=
nofloat
every float=
before=
after=
parskip
noparskip
autoparskip
nobeforeafter
forces nobeforeafter
baseline=
box align=#bottom,top,center,base
before skip=
after skip=
beforeafter skip=
left skip=
right skip=
leftright skip=
ignore nobreak=#true,false
before nobreak=
parfillskip restore=#true,false
enlarge top initially by=
enlarge bottom finally by=
enlarge top at break by=
enlarge bottom at break by=
enlarge top by=
enlarge bottom by=
enlarge left by=
enlarge right by=
enlarge by=
grow to left by=
grow to right by=
grow sidewards by=
flush left
flush right
center
toggle enlargement=#none,forced,evenpage
spread inwards
spread inwards=
spread outwards
spread outwards=
move outwards
move outwards=
move outwards*
move outwards*=
fill downwards
fill downwards=
spread upwards
spread upwards=
spread upwards*
spread upwards*=
spread sidewards
spread sidewards=
spread
spread=
spread downwards
spread downwards=
shrink tight
extrude left by=
extrude right by=
extrude top by=
extrude bottom by=
extrude by=
capture=#minipage,hbox,fitbox
hbox
minipage
parbox
parbox=#true,false
hyphenationfix
hyphenationfix=#true,false
tempfile=
tcbox raise=
tcbox raise base
on line
tcbox width=#auto, auto limited, forced center, forced left, forced right, minimum center, minimum left, minimum right
phantom=
nophantom
label=
phantomlabel=
label type=
no label type
step=
step and label=
list entry=
list type=
add to list=
nameref=
hypertarget=
bookmark=
bookmark*=
check odd page
check odd page=#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize=#true,false
external=
remake
remake=#true,false
reset
only=
code=
void
sidebyside
sidebyside=#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch=#true,false
verbatim ignore percent
verbatim ignore percent=#true,false
record=
no recording
skin=
skin first=
skin middle=
skin last=
graphical environment=
frame engine=#standard,path,pathjigsaw,pathfirst,pathfirstjigsaw,pathmiddle,pathmiddlejigsaw,pathlast,pathlastjigsaw,freelance,spartan,empty
interior titled engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
interior engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
segmentation engine=#standard,path,freelance,spartan,empty
title engine=#standard,path,pathfirst,pathmiddle,pathlast,freelance,spartan,empty
geometry nodes
geometry nodes=#true,false
frame code=
frame empty
interior titled code=
interior titled empty
interior code=
interior empty
segmentation code=
segmentation empty
title code=
title empty
skin first is subskin of=
skin middle is subskin of=
skin last is subskin of=
frame style=
frame style image=
frame style title=
frame hidden
interior style=
interior style image=
interior style tile=
interior hidden
segmentation style=
segmentation hidden
title style=
title style image=
title style tile=
title hidden
titlerule style=
tcb fill frame
tcb fill interior
tcb fill title
attach boxed title to top left
attach boxed title to top left=
attach boxed title to top center
attach boxed title to top center=
attach boxed title to top right
attach boxed title to top right=
attach boxed title to bottom left
attach boxed title to bottom left=
attach boxed title to bottom center
attach boxed title to bottom center=
attach boxed title to bottom right
attach boxed title to bottom right=
attach boxed title to top
attach boxed title to top=
attach boxed title to top*
attach boxed title to top*=
attach boxed title to bottom
attach boxed title to bottom=
attach boxed title to bottom*
attach boxed title to bottom*=
flip title
flip title=
xshift=
yshift=
yshifttext=
yshift*
boxed title size=#title,standard,copy
boxed title style=
no boxed title style
hbox boxed title
minipage boxed title=
minipage boxed title*=
tikznode boxed title
tikznode boxed title=
varwidth boxed title
varwidth boxed title=
varwidth boxed title*=
watermark text=
watermark text on=
watermark graphics=
watermark graphics on=
watermark tikz=
watermark tikz on=
no watermark
watermark opacity=
watermark zoom=
watermark shrink=
watermark overzoom=
watermark stretch=
watermark color=
clip watermark
clip watermark=#true,false
clip title
clip title=#true,false
clip upper
clip upper=#true,false
clip lower
clip lower=#true,false
borderline=
no borderline
show bounding box
show bounding box=
borderline north=
borderline sorth=
borderline east=
borderline west=
borderline horizontal=
borderline vertical=
no shadow
drop shadow
drop shadow=
drop fuzzy shadow
drop fuzzy shadow=
drop midday shadow
drop midday shadow=
drop fuzzy midday shadow
drop fuzzy midday shadow=
halo
halo=
fuzzy halo
fuzzy halo=
drop shadow southeast
drop shadow southeast=
drop shadow south
drop shadow south=
drop shadow southwest
drop shadow southwest=
drop shadow west
drop shadow west=
drop shadow northwest
drop shadow northwest=
drop shadow north
drop shadow north=
drop shadow northeast
drop shadow northeast=
drop shadow east
drop shadow east=
drop fuzzy shadow southeast
drop fuzzy shadow southeast=
drop fuzzy shadow south
drop fuzzy shadow south=
drop fuzzy shadow southwest
drop fuzzy shadow southwest=
drop fuzzy shadow west
drop fuzzy shadow west=
drop fuzzy shadow northwest
drop fuzzy shadow northwest=
drop fuzzy shadow north
drop fuzzy shadow north=
drop fuzzy shadow northeast
drop fuzzy shadow northeast=
drop fuzzy shadow east
drop fuzzy shadow east=
drop lifted shadow
drop lifted shadow=
drop small lifted shadow
drop small lifted shadow=
drop large lifted shadow
drop large lifted shadow=
shadow=
fuzzy shadow=
smart shadow arc
smart shadow arc=#true,false
lifted shadow=
tikz=
tikz reset
at begin tikz=
at begin tikz reset
at end tikz=
at end tikz reset
rotate=
scale=
remember
remember as=
underlay=
no underlay
underlay broken=
underlay unbroken=
no underlay unbroken
underlay first=
no underlay first
underlay middle=
no underlay middle
underlay last=
no underlay last
underlay boxed title=
no underlay boxed title
underlay unbroken and first=
underlay middle and last=
underlay unbroken and last=
underlay first and middle=
finish=
no finish
finish broken=
finish unbroken=
no finish unbroken
finish first=
no finish first
finish middle=
no finish middle
finish last=
no finish last
finish unbroken and first=
finish middle and last=
finish unbroken and last=
finish first and middle=
hyperref=
hyperref interior=
hyperref title=
hyperref node=
hyperlink=
hyperlink interior=
hyperlink title=
hyperlink node=
hyperurl=
hyperurl interior=
hyperurl title=
hyperurl node=
hyperurl*=
hyperurl* interior=
hyperurl* title=
hyperurl* node=
draftmode
draftmode=#true,false
standard
standard jigsaw
enhanced
enhanced standard
blank
enhanced jigsaw
enhanced standard jigsaw
marker
bicolor
colbacklower
colbacklower=
tile
beamer
widget
empty
blanker
blankest
spartan
draft
freelance
extend freelance=
extend freelancefirst=
extend freelancemiddle=
extend freelancelast=
graphics directory=
graphics pages=
fill plain image=
fill plain image*=
fill plain picture*=
fill stretch image=
fill stretch image*=
fill stretch picture=
fill overzoom image=
fill overzoom image*=
fill overzoom picture=
fill zoom image=
fill zoom image*=
fill zoom picture=
fill shrink image=
fill shrink image*=
fill shrink picture=
fill tile image=
fill tile image*=
fill tile picture=
fill tile picture*=
fill image opacity=
fill image scale=
fill image options=
underlay vignette=
underlay raise shading vignette=
underlay raise fading vignette=
underlay shade in vignette=
finish vignette=
finish raised fading vignette=
finish fading vignette=
raster columns=
raster rows=
raster width=
raster height=
raster before skip=
raster after skip=
raster equal skip=
raster left skip=
raster right skip=
raster column skip=
raster row skip=
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=
raster force size
raster force size=#true,false
raster reset
raster every box
raster odd column
raster even column
raster odd row
raster even row
raster odd number
raster even number
raster multicolumn=
raster multirow=
listing engine=#listings,minted
listing options=
no listing options
listing style=
listing inputencoding=
listing remove caption
listing remove caption=#true,false
every listing line=
every listing line*=
listing utf8=
minted language=
minted options=
minted style=
listing file=
listing and text
text and listing
listing only
text only
comment=
comment only
image comment=
tcbimage comment=
pdf comment=
pdf extension=
comment style=
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
process code=
run system command=
compilable listing
run pdflatex=
run xelatex=
run lualatex=
run makeindex=
run bibtex=
run biber=
run arara=
run latex=
run dvips=
run ps2pdf=
freeze file=
freeze none
freeze extension=
freeze pdf
freeze png
freeze jpg
separator sign=
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color=
description font=
description formatter=
terminator sign=
terminator sign colon
terminator sign dash
terminator sign none
label separator=
theorem full label supplement=
theorem label supplement=
theorem name and number
theorem number and name
theorem name
theorem=
highlight math
highlight math style=
math upper
math lower
math
ams equation upper
ams equation lower
ams equation
ams equation* upper
ams equation* lower
ams equation*
ams align upper
ams align lower
ams align
ams align* upper
ams align* lower
ams align*
ams gather upper
ams gather lower
ams gather
ams gather* upper
ams gather* lower
ams gather*
ams nodisplayskip upper
ams nodisplayskip lower
ams nodisplayskip
theorem style=#standard,change standard,plain,break,plain apart,change,change break,change apart,margin,margin break,margin apart
breakable
breakable=#true,false,unlimited
unbreakable
enforce breakable
title after break=
notitle after break
adjusted title after break=
lines before break=
break at=
enlargepage=
enlargepage flexible=
compress page
compress page=#all,baselineskip,none
shrink break goal=
toprule at break=
bottomrule at break=
topsep at break=
bottomsep at break=
pad before break=
pad before break*=
pad after break=
pad at break=
pad at* break=
height fixed for=#none,first,middle,last,first and middle,middle and last,all
vfill before first
vfill before first=#true,false
segmentation at break
segmentation at break=#true,false
extras=
no extras
extras broken=
extras unbroken=
no extras unbroken
extras first=
no extras first=
extras middle=
no extras middle
extras last=
no extras last
extras unbroken and first=
extras middle and last=
extras unbroken and last=
extras first and middle=
reset box array
reset box array=
store to box array
store to box array=
reset and store to box array
reset and store to box array=
do not store to box array
fit to=
fit to height=
fit basedim=
fit skip=
fit fontsize macros
fit height plus=
fit width plus=
fit width from=
fit height from=
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=
fit maxfontdiff=
fit maxfontdiffgap=
fit maxwidthdiff=
fit maxwidthdiffgap=
fit warning=#off,on,final
before title app=
before title pre=
after title app=
after title pre=
before upper app=
before upper pre=
after upper app=
after upper pre=
before lower app=
before lower pre=
after lower app=
after lower pre=
before app=
before pre=
after app=
after pre=
overlay app=
overlay pre=
overlay unbroken app=
overlay unbroken pre=
overlay first app=
overlay first pre=
overlay middle app=
overlay middle pre=
overlay last app=
overlay last pre=
overlay broken app=
overlay broken pre=
overlay unbroken and first app=
overlay unbroken and first pre=
overlay middle and last app=
overlay middle and last pre=
overlay unbroken and last app=
overlay unbroken and last pre=
overlay first and middle app=
overlay first and middle pre=
watermark text app=
watermark text pre=
watermark text app on=
watermark text pre on=
watermark graphics app=
watermark graphics pre=
watermark graphics app on=
watermark graphics pre on=
watermark tikz app=
watermark tikz pre=
watermark tikz app on=
watermark tikz pre on=
underlay pre=
underlay unbroken pre=
underlay first pre=
underlay middle pre=
underlay last pre=
underlay boxed title pre=
underlay broken pre=
underlay unbroken and first pre=
underlay middle and last pre=
underlay unbroken and last pre=
underlay first and middle pre=
finish pre=
finish unbroken pre=
finish first pre=
finish middle pre=
finish last pre=
finish broken pre=
finish unbroken and first pre=
finish middle and last pre=
finish unbroken and last pre=
finish first and middle pre=
frame code app=
frame code pre=
interior titled code app=
interior titled code pre=
interior code app=
interior code pre=
segmentation code app=
segmentation code pre=
title code app=
title code pre=
extras pre=
extras unbroken pre=
extras first pre=
extras middle pre=
extras last pre=
extras broken pre=
extras unbroken and first pre=
extras middle and last pre=
extras unbroken and last pre=
extras first and middle pre=
verbatim
IfNoValueTF=
IfValueTF=
IfBooleanTF=
docexample/.style=
documentation listing options=
documentation listing style=
documentation minted options=
documentation minted style=
documentation minted language=
keywords bold
keywords bold=#true,false
index command=
index command name=
index format=#pgfsection,pgfchapter,pgf,doc,off
index actual=
index quote=
index level=
index default settings
index german settings
index annotate
index annotate=#true,false
index colorize
index colorize=#true,false
color command=
color environment=
color key=
color value=
color counter=
color length=
color color=
color definition=
color option=
color hyperlink=
english language
doclang/color=
doclang/colors=
doclang/counter=
doclang/environment=
doclang/environments=
doclang/environment content=
doclang/index=
doclang/key=
doclang/keys=
doclang/length=
doclang/lengths=
doclang/new=
doclang/pageshort=
doclang/updated=
doclang/value=
doclang/values=
doc left=
doc right=
doc left indent=
doc right indent=
doc head command=
doc head environment=
doc head key=
doc head=
before doc body command=
after doc body command=
before doc body environment=
after doc body environment=
before doc body key=
after doc body key=
before doc body=
after doc body=
doc description=
doc into index
doc into index=#true,false
doc marginnote=
doc new=
doc updated=
doc new and updated=
#endkeyvals