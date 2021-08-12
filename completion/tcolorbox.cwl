# tcolorbox package
# thatlittleboy/2018-06-07 for tcolorbox v4.13
# muzimuzhi/30 Aug 2019 for tcolorbox v4.20
#     reduce file size by using clist in "#keyvals:\cmdA,\cmdB"

#include:environ
#include:etoolbox
#include:pgf
#include:verbatim

# << Package options (load libraries) >>
#ifOption:external
#include:pdftexcmds
#include:shellesc
#include:incgraph
#endif

#ifOption:listings
#include:listings
#include:pdftexcmds
#include:shellesc
#endif

#ifOption:listingsutf8
## loads option listings
#include:listings
#include:listingsutf8
#include:pdftexcmds
#include:shellesc
#endif

#ifOption:minted
#include:minted
#endif

#ifOption:skins
#include:tikz
#endif

#ifOption:theorems
#include:amsmath
#endif

#ifOption:xparse
#include:xparse
#endif

#ifOption:documentation
## loads options listings, skins, and xparse
#include:hyperref
#include:listings
#include:makeidx
#include:marginnote
#include:marvosym
#include:pdftexcmds
#include:pifont
#include:refcount
#include:shellesc
#include:tikz
#include:xparse
#endif

#ifOption:many
## loads options skins, theorems, and xparse
#include:amsmath
#include:tikz
#include:xparse
#endif

#ifOption:most
## loads all options except minted and documentation
#include:amsmath
#include:incgraph
#include:listings
#include:listingsutf8
#include:pdftexcmds
#include:pdftexcmds
#include:shellesc
#include:shellesc
#include:tikz
#include:xparse
#endif

#ifOption:all
## loads all options except documentation
#include:amsmath
#include:incgraph
#include:listings
#include:listingsutf8
#include:minted
#include:pdftexcmds
#include:pdftexcmds
#include:shellesc
#include:shellesc
#include:tikz
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
\newtcolorbox[init options]{envname}[args][default]{options%keyvals}#N
\renewtcolorbox{envname}{options%keyvals}
\renewtcolorbox[init options]{envname}[args][default]{options%keyvals}
\newtcbox{cmd}{options%keyvals}#d
\newtcbox[init options]{cmd}[args][default]{options%keyvals}#d
\renewtcbox{cmd}{options%keyvals}#d
\renewtcbox[init options]{cmd}[args][default]{options%keyvals}#d
\tcolorboxenvironment{envname}{options%keyvals}#N

# << Title >>
\tcbtitletext
\tcbtitle

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
\tcboxedtitlewidth
\tcboxedtitleheight
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
\newtcblisting[init options]{envname}[args][default]{options%keyvals}#N
\renewtcblisting{envname}{options%keyvals}#N
\renewtcblisting[init options]{envname}[args][default]{options%keyvals}#N
\newtcbinputlisting{cmd}{options%keyvals}
\newtcbinputlisting[init options]{cmd}[args][default]{options%keyvals}
\renewtcbinputlisting{cmd}{options%keyvals}
\renewtcbinputlisting[init options]{cmd}[args][default]{options%keyvals}

# << Theorems >>
\newtcbtheorem{envname}{display name}{options%keyvals}{prefix}#N
\newtcbtheorem[init options]{envname}{display name}{options%keyvals}{prefix}#N
\renewtcbtheorem{envname}{display name}{options%keyvals}{prefix}
\renewtcbtheorem[init options]{envname}{display name}{options%keyvals}{prefix}
\tcbmaketheorem{envname}{display name}{options%keyvals}{counter}{prefix}#N
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
\newtcboxfit{cmd}{options%keyvals}
\newtcboxfit[init options]{cmd}[args][default]{options%keyvals}
\renewtcboxfit{cmd}{options%keyvals}
\renewtcboxfit[init options]{cmd}[args][default]{options%keyvals}
\tcbfontsize{factor}
\tcbfitdim
\tcbfitsteps

# << xparse >>
\DeclareTColorBox{envname}{specification}{options%keyvals}#N
\DeclareTColorBox[init options]{envname}{specification}{options%keyvals}#*N
\NewTColorBox{envname}{specification}{options%keyvals}#N
\NewTColorBox[init options]{envname}{specification}{options%keyvals}#*N
\RenewTColorBox{envname}{specification}{options%keyvals}
\RenewTColorBox[init options]{envname}{specification}{options%keyvals}#*
\ProvideTColorBox{envname}{specification}{options%keyvals}#N
\ProvideTColorBox[init options]{envname}{specification}{options%keyvals}#*N
\DeclareTotalTColorBox{cmd}{specification}{options%keyvals}{content}
\DeclareTotalTColorBox[init options]{cmd}{specification}{options%keyvals}{content}#*
\NewTotalTColorBox{cmd}{specification}{options%keyvals}{content}
\NewTotalTColorBox[init options]{cmd}{specification}{options%keyvals}{content}#*
\RenewTotalTColorBox{cmd}{specification}{options%keyvals}{content}
\RenewTotalTColorBox[init options]{cmd}{specification}{options%keyvals}{content}#*
\ProvideTotalTColorBox{cmd}{specification}{options%keyvals}{content}
\ProvideTotalTColorBox[init options]{cmd}{specification}{options%keyvals}{content}#*
\DeclareTCBox{cmd}{specification}{options%keyvals}
\DeclareTCBox[init options]{cmd}{specification}{options%keyvals}#*
\NewTCBox{cmd}{specification}{options%keyvals}
\NewTCBox[init options]{cmd}{specification}{options%keyvals}#*
\RenewTCBox{cmd}{specification}{options%keyvals}
\RenewTCBox[init options]{cmd}{specification}{options%keyvals}#*
\ProvideTCBox{cmd}{specification}{options%keyvals}
\ProvideTCBox[init options]{cmd}{specification}{options%keyvals}#*
\DeclareTotalTCBox{cmd}{specification}{options%keyvals}{content}
\DeclareTotalTCBox[init options]{cmd}{specification}{options%keyvals}{content}#*
\NewTotalTCBox{cmd}{specification}{options%keyvals}{content}
\NewTotalTCBox[init options]{cmd}{specification}{options%keyvals}{content}#*
\RenewTotalTCBox{cmd}{specification}{options%keyvals}{content}
\RenewTotalTCBox[init options]{cmd}{specification}{options%keyvals}{content}#*
\ProvideTotalTCBox{cmd}{specification}{options%keyvals}{content}
\ProvideTotalTCBox[init options]{cmd}{specification}{options%keyvals}{content}#*
\tcboxverb{verbatim box content}
\tcboxverb[options%keyvals]{verbatim box content}#*
\DeclareTCBListing{envname}{specification}{options%keyvals}#N
\DeclareTCBListing[init options]{envname}{specification}{options%keyvals}#*N
\NewTCBListing{envname}{specification}{options%keyvals}#N
\NewTCBListing[init options]{envname}{specification}{options%keyvals}#*N
\RenewTCBListing{envname}{specification}{options%keyvals}
\RenewTCBListing[init options]{envname}{specification}{options%keyvals}#*
\ProvideTCBListing{envname}{specification}{options%keyvals}#N
\ProvideTCBListing[init options]{envname}{specification}{options%keyvals}#*N
\DeclareTCBInputListing{cmd}{specification}{options%keyvals}
\DeclareTCBInputListing[init options]{cmd}{specification}{options%keyvals}#*
\NewTCBInputListing{cmd}{specification}{options%keyvals}
\NewTCBInputListing[init options]{cmd}{specification}{options%keyvals}#*
\RenewTCBInputListing{cmd}{specification}{options%keyvals}
\RenewTCBInputListing[init options]{cmd}{specification}{options%keyvals}#*
\ProvideTCBInputListing{cmd}{specification}{options%keyvals}
\ProvideTCBInputListing[init options]{cmd}{specification}{options%keyvals}#*
\DeclareTCBoxFit{cmd}{specification}{options%keyvals}
\DeclareTCBoxFit[init options]{cmd}{specification}{options%keyvals}#*
\NewTCBoxFit{cmd}{specification}{options%keyvals}
\NewTCBoxFit[init options]{cmd}{specification}{options%keyvals}#*
\RenewTCBoxFit{cmd}{specification}{options%keyvals}
\RenewTCBoxFit[init options]{cmd}{specification}{options%keyvals}#*
\ProvideTCBoxFit{cmd}{specification}{options%keyvals}
\ProvideTCBoxFit[init options]{cmd}{specification}{options%keyvals}#*
\DeclareTotalTCBoxFit{cmd}{specification}{options%keyvals}{content}
\DeclareTotalTCBoxFit[init options]{cmd}{specification}{options%keyvals}{content}#*
\NewTotalTCBoxFit{cmd}{specification}{options%keyvals}{content}
\NewTotalTCBoxFit[init options]{cmd}{specification}{options%keyvals}{content}#*
\RenewTotalTCBoxFit{cmd}{specification}{options%keyvals}{content}
\RenewTotalTCBoxFit[init options]{cmd}{specification}{options%keyvals}{content}#*
\ProvideTotalTCBoxFit{cmd}{specification}{options%keyvals}{content}
\ProvideTotalTCBoxFit[init options]{cmd}{specification}{options%keyvals}{content}#*

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
\begin{docCommands}{{%<variant1%>},{%<variant2%>}}#*
\begin{docCommands}[options%keyvals]{{%<variant1%>},{%<variant2%>}}#*
\end{docCommands}#*
\begin{docEnvironment}{name}{parameters}#*
\begin{docEnvironment}[options%keyvals]{name}{parameters}#*
\end{docEnvironment}#*
\begin{docEnvironment*}{name}{parameters}#*
\begin{docEnvironment*}[options%keyvals]{name}{parameters}#*
\end{docEnvironment*}#*
\begin{docEnvironments}{{%<variant1%>},{%<variant2%>}}#*
\begin{docEnvironments}[options%keyvals]{{%<variant1%>},{%<variant2%>}}#*
\end{docEnvironments}#*
\begin{docKey}{name}{parameters}{description}#*
\begin{docKey}[key path][options%keyvals]{name}{parameters}{description}#*
\end{docKey}#*
\begin{docKey*}{name}{parameters}{description}#*
\begin{docKey*}[key path][options%keyvals]{name}{parameters}{description}#*
\end{docKey*}#*
\begin{docKeys}{{%<variant1%>},{%<variant2%>}}#*
\begin{docKeys}[options%keyvals]{{%<variant1%>},{%<variant2%>}}#*
\end{docKeys}#*
\begin{docPathOperation}{name}{parameters}#*
\begin{docPathOperation}[options%keyvals]{name}{parameters}#*
\end{docPathOperation}#*
\begin{docPathOperation*}{name}{parameters}#*
\begin{docPathOperation*}[options%keyvals]{name}{parameters}#*
\end{docPathOperation*}#*
\begin{docPathOperations}{{%<variant1%>},{%<variant2%>}}#*
\begin{docPathOperations}[options%keyvals]{{%<variant1%>},{%<variant2%>}}#*
\end{docPathOperations}#*
\docValue{name}#*
\docValue[options%keyvals]{name}#*
\docValue*{name}#*
\docValue*[options%keyvals]{name}#*
\docAuxCommand{name}#*
\docAuxCommand[options%keyvals]{name}#*
\docAuxCommand*{name}#*
\docAuxCommand*[options%keyvals]{name}#*
\docAuxEnvironment{name}#*
\docAuxEnvironment[options%keyvals]{name}#*
\docAuxEnvironment*{name}#*
\docAuxEnvironment*[options%keyvals]{name}#*
\docAuxKey{name}#*
\docAuxKey[key path][options%keyvals]{name}#*
\docAuxKey*{name}#*
\docAuxKey*[key path][options%keyvals]{name}#*
\docCounter{name}#*
\docCounter[options%keyvals]{name}#*
\docCounter*{name}#*
\docCounter*[options%keyvals]{name}#*
\docLength{name}#*
\docLength[options%keyvals]{name}#*
\docLength*{name}#*
\docLength*[options%keyvals]{name}#*
\docColor{name}#*
\docColor[options%keyvals]{name}#*
\docColor*{name}#*
\docColor*[options%keyvals]{name}#*
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
\begin{dispListing*}{options%keyvals}#*
\end{dispListing*}#*
\begin{absquote}#*
\end{absquote}#*
\tcbmakedocSubKey{name}{key path}#*
\tcbmakedocSubKeys{name}{key path}#*
\refCom{name}#*
\refCom*{name}#*
\refEnv{name}#*
\refEnv*{name}#*
\refKey{name}#*
\refKey*{name}#*
\refPathOperation{name}#*
\refPathOperation*{name}#*
\refAux{name}#*
\refAuxcs{name}#*
\colDef{text}#*
\colOpt{text}#*
\colFade{text}#*
\tcbdocmarginnote{text}#*
\tcbdocmarginnote[options%keyvals]{text}#*
\tcbdocnew{date}#*
\tcbdocupdated{date}#*

# ---------------------------------------
# << Option Keys >> - Documentation library
# ---------------------------------------
#keyvals:\begin{docCommand},\begin{docCommand*},\begin{docCommands},\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\begin{docKey},\begin{docKey*},\begin{docKeys},\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations},\tcbset
doc name
doc parameter
doc description
doc label
doc index
doc sort index
doc into index#true,false
doc no index
doc new
doc updated
doc new and updated={%<new date%>}{%<update date%>}
doc left=##L
doc right=##L
doc left indent=##L
doc right indent=##L
doc raster
doc head
before doc body
after doc body
#endkeyvals

#keyvals:\begin{docCommand},\begin{docCommand*},\begin{docCommands},\tcbset
before doc body command
after doc body command
doc head command
doc raster command
#endkeyvals

#keyvals:\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\tcbset
before doc body environment
after doc body environment
doc head environment
doc raster environment
#endkeyvals

#keyvals:\begin{docKey},\begin{docKey*},\begin{docKeys},\tcbset
doc keypath
before doc body key
after doc body key
doc head key
doc raster key
#endkeyvals

#keyvals:\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations},\tcbset
before doc body path
after doc body path
doc head path
doc raster path
#endkeyvals

#keyvas:\tcbdocmarginnote,\tcbset
doc marginnote
#endkeyvals

#keyvals:\begin{dispExample*},\begin{dispListing*},\tcbset
docexample/.style=
documentation listing options
documentation listing style
documentation minted options
documentation minted style
documentation minted language
before example
after example
#endkeyvals

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
lower separated#true,false
savedelimiter=
colframe=
colback=
title filled#true,false
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
ignore nobreak#true,false
before nobreak=
parfillskip restore#true,false
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
parbox#true,false
hyphenationfix
hyphenationfix#true,false
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
check odd page#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize#true,false
external=
remake
remake#true,false
reset
only=
code=
void
sidebyside
sidebyside#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch#true,false
verbatim ignore percent
verbatim ignore percent#true,false
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
geometry nodes#true,false
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
attach boxed title to top center
attach boxed title to top right
attach boxed title to bottom left
attach boxed title to bottom center
attach boxed title to bottom right
attach boxed title to top
attach boxed title to top*
attach boxed title to bottom
attach boxed title to bottom*
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
clip watermark#true,false
clip title
clip title#true,false
clip upper
clip upper#true,false
clip lower
clip lower#true,false
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
smart shadow arc#true,false
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
raster force size#true,false
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
listing remove caption#true,false
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
vfill before first#true,false
segmentation at break
segmentation at break#true,false
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
external/externalize#true,false
external/force remake
external/force remake#true,false
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
external/environment with percent#true,false
external/minipage
external/minipage=
external/plain
external/compiler=
external/runs=
external/input source on error
external/input source on error#true,false
external/preclass=
external/PassOptionsToPackage=
external/PassOptionsToClass=
external/clear preclass
external/preamble=
external/preamble tcbset=
external/clear preamble
# Documentation library
keywords bold#true,false
index command=
index command name=
index format=#pgfsection,pgfchapter,pgf,doc,off
index actual=
index quote=
index level=
index default settings/.style=
index german settings/.style=
index annotate#true,false
index colorize#true,false
color command=#%color
color environment=#%color
color key=#%color
color path=#%color
color value=#%color
color counter=#%color
color length=#%color
color color=#%color
color definition=#%color
color option=#%color
color fade=#%color
color hyperlink=#%color
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
doclang/path=
doclang/paths=
doclang/pageshort=
doclang/updated=
doclang/value=
doclang/values=
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
lower separated#true,false
savedelimiter=
colframe=
colback=
title filled#true,false
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
ignore nobreak#true,false
before nobreak=
parfillskip restore#true,false
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
parbox#true,false
hyphenationfix
hyphenationfix#true,false
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
check odd page#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize#true,false
external=
remake
remake#true,false
reset
only=
code=
void
sidebyside
sidebyside#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch#true,false
verbatim ignore percent
verbatim ignore percent#true,false
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
geometry nodes#true,false
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
attach boxed title to top center
attach boxed title to top right
attach boxed title to bottom left
attach boxed title to bottom center
attach boxed title to bottom right
attach boxed title to top
attach boxed title to top*
attach boxed title to bottom
attach boxed title to bottom*
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
clip watermark#true,false
clip title
clip title#true,false
clip upper
clip upper#true,false
clip lower
clip lower#true,false
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
smart shadow arc#true,false
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
raster force size#true,false
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
listing remove caption#true,false
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
vfill before first#true,false
segmentation at break
segmentation at break#true,false
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
lower separated#true,false
savedelimiter=
colframe=
colback=
title filled#true,false
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
ignore nobreak#true,false
before nobreak=
parfillskip restore#true,false
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
parbox#true,false
hyphenationfix
hyphenationfix#true,false
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
check odd page#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize#true,false
external=
remake
remake#true,false
reset
only=
code=
void
sidebyside
sidebyside#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch#true,false
verbatim ignore percent
verbatim ignore percent#true,false
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
geometry nodes#true,false
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
attach boxed title to top center
attach boxed title to top right
attach boxed title to bottom left
attach boxed title to bottom center
attach boxed title to bottom right
attach boxed title to top
attach boxed title to top*
attach boxed title to bottom
attach boxed title to bottom*
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
clip watermark#true,false
clip title
clip title#true,false
clip upper
clip upper#true,false
clip lower
clip lower#true,false
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
smart shadow arc#true,false
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
raster force size#true,false
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
listing remove caption#true,false
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
vfill before first#true,false
segmentation at break
segmentation at break#true,false
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
lower separated#true,false
savedelimiter=
colframe=
colback=
title filled#true,false
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
ignore nobreak#true,false
before nobreak=
parfillskip restore#true,false
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
parbox#true,false
hyphenationfix
hyphenationfix#true,false
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
check odd page#true,false
if odd page=
if odd page or oneside=
if odd page*=
if odd page or oneside*=
shield externalize
shield externalize#true,false
external=
remake
remake#true,false
reset
only=
code=
void
sidebyside
sidebyside#true,false
sidebyside align=#center,top,bottom,center seam,top seam,bottom seam
sidebyside gap=
lefthand width=
righthand width=
lefthand ratio=
righthand ratio=
sidebyside adapt=#none,left,right,both
sidebyside switch
sidebyside switch#true,false
verbatim ignore percent
verbatim ignore percent#true,false
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
geometry nodes#true,false
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
attach boxed title to top center
attach boxed title to top right
attach boxed title to bottom left
attach boxed title to bottom center
attach boxed title to bottom right
attach boxed title to top
attach boxed title to top*
attach boxed title to bottom
attach boxed title to bottom*
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
clip watermark#true,false
clip title
clip title#true,false
clip upper
clip upper#true,false
clip lower
clip lower#true,false
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
smart shadow arc#true,false
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
raster force size#true,false
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
listing remove caption#true,false
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
vfill before first#true,false
segmentation at break
segmentation at break#true,false
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
