# tcolorbox package
# thatlittleboy/2018-06-07 for tcolorbox v4.13
# muzimuzhi/30 Aug 2019 for tcolorbox v4.20
#     reduce file size by using clist in "#keyvals:\cmdA,\cmdB"
# Matthew Bertucci updated 2023/02/10 for v6.0.0

#include:environ
#include:etoolbox
#include:pgf
#include:verbatim

# << Package options (load libraries) >>
#ifOption:skins
#include:tcolorboxlibraryskins
#endif

#ifOption:vignette
#include:tcolorboxlibraryvignette
#endif

#ifOption:raster
#include:tcolorboxlibraryraster
#endif

#ifOption:listings
#include:tcolorboxlibrarylistings
#endif

#ifOption:listingsutf8
#include:tcolorboxlibrarylistingsutf8
#endif

#ifOption:minted
#include:tcolorboxlibraryminted
#endif

#ifOption:theorems
#include:tcolorboxlibrarytheorems
#endif

#ifOption:breakable
#include:tcolorboxlibrarybreakable
#endif

#ifOption:magazine
#include:tcolorboxlibrarymagazine
#endif

#ifOption:poster
#include:tcolorboxlibraryposter
#endif

#ifOption:fitting
#include:tcolorboxlibraryfitting
#endif

#ifOption:hooks
#include:tcolorboxlibraryhooks
#endif

#ifOption:external
#include:tcolorboxlibraryexternal
#endif

#ifOption:documentation
#include:tcolorboxlibrarydocumentation
#endif

#ifOption:many
#include:tcolorboxlibrarymany
#endif

#ifOption:most
#include:tcolorboxlibrarymost
#endif

#ifOption:all
#include:tcolorboxlibraryall
#endif

# << Libraries >>
\tcbuselibrary{%<library%>%keys}#u
#keyvals:\tcbuselibrary,\usepackage/tcolorbox#c
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

#keyvals:\tcbset
library/skins
library/vignette
library/raster
library/listings
library/listingsutf8
library/minted
library/theorems
library/breakable
library/magazine
library/poster
library/fitting
library/hooks
library/xparse
library/external
library/documentation
library/many
library/most
library/all
#endkeyvals

# << Box Creation >>
\begin{tcolorbox}
\begin{tcolorbox}[%<options%>]
\end{tcolorbox}
\tcblower
\tcbset{%<options%>}
\tcbsetforeverylayer{%<options%>}
\tcbox{box content%text}
\tcbox[options%keyvals]{box content%text}
\newtcolorbox{envname}{options%keyvals}#N
\newtcolorbox{envname}[args]{options%keyvals}#N
\newtcolorbox{envname}[args][default]{options%keyvals}#N
\newtcolorbox[init options]{envname}{options%keyvals}#N
\newtcolorbox[init options]{envname}[args]{options%keyvals}#*N
\newtcolorbox[init options]{envname}[args][default]{options%keyvals}#*N
\renewtcolorbox{envname}{options%keyvals}
\renewtcolorbox{envname}[args]{options%keyvals}
\renewtcolorbox{envname}[args][default]{options%keyvals}
\renewtcolorbox[init options]{envname}{options%keyvals}
\renewtcolorbox[init options]{envname}[args]{options%keyvals}#*
\renewtcolorbox[init options]{envname}[args][default]{options%keyvals}#*
\DeclareTColorBox{envname}{xargs}{options%keyvals}#N
\DeclareTColorBox[init options]{envname}{xargs}{options%keyvals}#N
\NewTColorBox{envname}{xargs}{options%keyvals}#N
\NewTColorBox[init options]{envname}{xargs}{options%keyvals}#N
\RenewTColorBox{envname}{xargs}{options%keyvals}
\RenewTColorBox[init options]{envname}{xargs}{options%keyvals}
\ProvideTColorBox{envname}{xargs}{options%keyvals}#N
\ProvideTColorBox[init options]{envname}{xargs}{options%keyvals}#N
\DeclareTotalTColorBox{cmd}{xargs}{options%keyvals}{content}#d
\DeclareTotalTColorBox[init options]{cmd}{xargs}{options%keyvals}{content}#d
\NewTotalTColorBox{cmd}{xargs}{options%keyvals}{content}#d
\NewTotalTColorBox[init options]{cmd}{xargs}{options%keyvals}{content}#d
\RenewTotalTColorBox{cmd}{xargs}{options%keyvals}{content}
\RenewTotalTColorBox[init options]{cmd}{xargs}{options%keyvals}{content}
\ProvideTotalTColorBox{cmd}{xargs}{options%keyvals}{content}#d
\ProvideTotalTColorBox[init options]{cmd}{xargs}{options%keyvals}{content}#d
\newtcbox{cmd}{options%keyvals}#d
\newtcbox{cmd}[args]{options%keyvals}#d
\newtcbox{cmd}[args][default]{options%keyvals}#d
\newtcbox[init options]{cmd}{options%keyvals}#d
\newtcbox[init options]{cmd}[args]{options%keyvals}#*d
\newtcbox[init options]{cmd}[args][default]{options%keyvals}#*d
\renewtcbox{cmd}{options%keyvals}
\renewtcbox{cmd}[args]{options%keyvals}
\renewtcbox{cmd}[args][default]{options%keyvals}
\renewtcbox[init options]{cmd}{options%keyvals}
\renewtcbox[init options]{cmd}[args]{options%keyvals}#*
\renewtcbox[init options]{cmd}[args][default]{options%keyvals}#*
\DeclareTCBox{cmd}{xargs}{options%keyvals}#d
\DeclareTCBox[init options]{cmd}{xargs}{options%keyvals}#d
\NewTCBox{cmd}{xargs}{options%keyvals}#d
\NewTCBox[init options]{cmd}{xargs}{options%keyvals}#d
\RenewTCBox{cmd}{xargs}{options%keyvals}
\RenewTCBox[init options]{cmd}{xargs}{options%keyvals}
\ProvideTCBox{cmd}{xargs}{options%keyvals}#d
\ProvideTCBox[init options]{cmd}{xargs}{options%keyvals}#d
\DeclareTotalTCBox{cmd}{xargs}{options%keyvals}{content}#d
\DeclareTotalTCBox[init options]{cmd}{xargs}{options%keyvals}{content}#d
\NewTotalTCBox{cmd}{xargs}{options%keyvals}{content%text}#d
\NewTotalTCBox[init options]{cmd}{xargs}{options%keyvals}{content%text}#d
\RenewTotalTCBox{cmd}{xargs}{options%keyvals}{content%text}
\RenewTotalTCBox[init options]{cmd}{xargs}{options%keyvals}{content%text}
\ProvideTotalTCBox{cmd}{xargs}{options%keyvals}{content%text}#d
\ProvideTotalTCBox[init options]{cmd}{xargs}{options%keyvals}{content%text}#d
\tcboxverb{verbatim box content%definition}
\tcboxverb[options%keyvals]{verbatim box content%definition}
\tcolorboxenvironment{envname}{options%keyvals}

# << Title >>
\tcbtitletext
\tcbtitle

# << Subtitle >>
\tcbsubtitle{text}
\tcbsubtitle[options%keyvals]{text}

# << Geometry/Height control >>
\tcbheightfromgroup{macro%cmd}{id}#d

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
\tcblistof{name}{title}
\tcblistof{name}[short title]{title}
\tcblistof[section macro]{name}{title}
\tcblistof[section macro]{name}[short title]{title}

# << Advanced settings
\tcbsidebyside{left-handed content%text}{right-handed content%text}
\tcbsidebyside[options%keyvals]{left-handed content%text}{right-handed content%text}

# << Saving and loading of verbatim texts
\begin{tcbverbatimwrite}{%<file%>}
\end{tcbverbatimwrite}
\tcbverbatimwrite#*
\endtcbverbatimwrite#*
\begin{tcbwritetemp}
\end{tcbwritetemp}
\tcbusetemp

# << Recording >>
\tcbstartrecording
\tcbstartrecording[file]
\tcbrecord{content}
\tcbstoprecording
\tcbinputrecords
\tcbinputrecords[file]

# << Subskins >>
\tcbsubskin{name}{base skin}{options%keyvals}

# << Useful Properties >>
\tcbheightspace#L
\tcbtextwidth#L
\tcbtextheight#L
\tcbsegmentstate

# << Color Names >>
tcbcolframe#B
tcbcolback#B
tcbcolbacktitle#B
tcbcolbacklower#B
tcbcolupper#B
tcbcollower#B
tcbcoltitle#B

# << Straightening of the Arcs >>
\tcbpatcharcangular
\tcbpatcharcround

# ------------------------------
# << Option Keys >> - always available
# ------------------------------

#keyvals:\tcbset,\begin{tcolorbox},\tcbsetforeverylayer,\tcbox,\newtcolorbox,\renewtcolorbox,\newtcbox,\renewtcbox,\tcolorboxenvironment,\tcbsubtitle,\tcbsidebyside,\tcbsubskin,\tcbincludegraphics,\tcbincludepdf,\begin{tcbraster},\begin{tcbitemize},\tcbitem,\begin{tcboxedraster},\begin{tcboxeditemize},\begin{tcblisting},\tcbinputlisting,\newtcblisting,\renewtcblisting,\newtcbinputlisting,\renewtcbinputlisting,\NewTcbTheorem,\newtcbtheorem,\RenewTcbTheorem,\renewtcbtheorem,\ProvideTcbTheorem,\DeclareTcbTheorem,\tcboxmath,\tcbhighmath,\usetcboxarray,\consumetcboxarray,\posterbox,\begin{posterboxenv},\tcboxfit,\newtcboxfit,\renewtcboxfit,\DeclareTColorBox,\NewTColorBox,\RenewTColorBox,\ProvideTColorBox,\DeclareTotalTColorBox,\NewTotalTColorBox,\RenewTotalTColorBox,\ProvideTotalTColorBox,\DeclareTCBox,\NewTCBox,\RenewTCBox,\ProvideTCBox,\DeclareTotalTCBox,\NewTotalTCBox,\RenewTotalTCBox,\ProvideTotalTCBox,\DeclareTCBListing,\NewTCBListing,\RenewTCBListing,\ProvideTCBListing,\DeclareTCBInputListing,\NewTCBInputListing,\RenewTCBInputListing,\ProvideTCBInputListing,\DeclareTCBoxFit,\NewTCBoxFit,\RenewTCBoxFit,\ProvideTCBoxFit,\DeclareTotalTCBoxFit,\NewTotalTCBoxFit,\RenewTotalTCBoxFit,\ProvideTotalTCBoxFit,\tcboxverb,\begin{docCommand},\begin{docCommand*},\begin{docCommands},\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\begin{docKey},\begin{docKey*},\begin{docKeys},\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations},\docValue,\docValue*,\docAuxCommand,\docAuxCommand*,\docAuxEnvironment,\docAuxEnvironment*,\docAuxKey,\docAuxKey*,\docCounter,\docCounter*,\docLength,\docLength*,\docColor,\docColor*,\begin{dispExample*},\begin{dispListing*},\tcbdocmarginnote
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
lowerbox=#visible,invisible,ignored
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
halign code={%<code%>}
halign upper code={%<code%>}
halign lower=#justify,left,flush left,right,flush right,center,flush center
halign lower code={%<code%>}
halign title=#justify,left,flush left,right,flush right,center,flush center
halign title code={%<code%>}
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
before title*={%<code%>}
after title={%<code%>}
after title*={%<code%>}
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
every box on higher layers/.style={%<options%>}
capture=#minipage,hbox,fitbox
hbox
minipage
parbox#true,false
hyphenationfix#true,false
tempfile=%<file name%>
phantom={%<code%>}
nophantom
label is label
label is zlabel
label=##l
phantomlabel=##l
step=%<counter%>
step and label={%<counter%>}{%<marker%>}
label type=%<type%>
no label type
nameref=%<text%>
short title=%<text%>
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
list entry=%<text%>
list text=%<text%>
add to list={%<list%>}{%<type%>}
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
verbatim ignore indention at end#true,false
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
#endkeyvals

## tcbox special keys
#keyvals:\tcbset,\tcbsetforeverylayer,\tcbox,\newtcbox,\renewtcbox,\tcboxmath,\tcbhighmath,\usetcboxarray,\consumetcboxarray,\tcboxfit,\newtcboxfit,\renewtcboxfit,\DeclareTCBox,\NewTCBox,\RenewTCBox,\ProvideTCBox,\DeclareTotalTCBox,\NewTotalTCBox,\RenewTotalTCBox,\ProvideTotalTCBox,\tcboxverb,\DeclareTCBoxFit,\NewTCBoxFit,\RenewTCBoxFit,\ProvideTCBoxFit,\DeclareTotalTCBoxFit,\NewTotalTCBoxFit,\RenewTotalTCBoxFit,\ProvideTotalTCBoxFit
tcbox raise=##L
tcbox raise base
on line
verbatim
tcbox width=#auto,auto limited,forced center,forced left,forced right,minimum center,minimum left,minimum right
#endkeyvals

## not documented
\tcbdimto{arg1}{arg2}#S
\tcbglueto{arg1}{arg2}#S
\tcbpkgprefix#S

# << init options >>

# NOTE: Init options, documented in Sec. 5 of package doc, always come with 
# another more powerful and mandatory option list argument. For example,
#     \newtcolorbox[init options]{envname}{options%keyvals}#N
# Since currently texstudio doesn't support to mark a second keyvals field in 
# one command, the following (relatively short) init option list is temporarily 
# commented.

# # NOTE: this is not a valid syntax of #keyvals.
# \newtcolorbox,\renewtcolorbox,\newtcbox,\renewtcbox,
# \newtcblisting,\renewtcblisting,\newtcbinputlisting,\renewtcbinputlisting,
# \newtcbtheorem,\renewtcbtheorem,
# \newtcboxfit,\renewtcboxfit,
# \DeclareTColorBox,\NewTColorBox,\RenewTColorBox,\ProvideTColorBox,
# \DeclareTotalTColorBox,\NewTotalTColorBox,\RenewTotalTColorBox,\ProvideTotalTColorBox,
# \DeclareTCBox,\NewTCBox,\RenewTCBox,\ProvideTCBox,
# \DeclareTotalTCBox,\NewTotalTCBox,\RenewTotalTCBox,\ProvideTotalTCBox,
# \DeclareTCBListing,\NewTCBListing,\RenewTCBListing,\ProvideTCBListing,
# \DeclareTCBInputListing,\NewTCBInputListing,\RenewTCBInputListing,\ProvideTCBInputListing,
# \DeclareTCBoxFit,\NewTCBoxFit,\RenewTCBoxFit,\ProvideTCBoxFit,
# \DeclareTotalTCBoxFit,\NewTotalTCBoxFit,\RenewTotalTCBoxFit,\ProvideTotalTCBoxFit
# #keyvals:
# auto counter
# auto counter
# use counter from=
# use counter=
# use counter*=
# no counter
# reset counter on overlays#true,false
# number within=
# number format=
# number freestyle=
# crefname={%<singular%>}{%<plural%>}
# Crefname={%<singular%>}{%<plural%>}
# blend into=#figures,tables,listings
# blend before title=#colon,dash,colon hang,dash hang
# blend before title code=
# list inside=
# list type=
# #endkeyvals
