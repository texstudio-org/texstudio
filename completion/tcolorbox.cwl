# tcolorbox package
# thatlittleboy/2018-06-07 for tcolorbox v4.13
# muzimuzhi/30 Aug 2019 for tcolorbox v4.20
#     reduce file size by using clist in "#keyvals:\cmdA,\cmdB"
# Matthew Bertucci updated 2022/06/26 for v5.1.1

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

#ifOption:vignette
## loads option skins
#include:tikz
#endif

#ifOption:breakable
#include:pdfcol
#endif

#ifOption:magazine
## loads option breakable
#include:pdfcol
#endif

#ifOption:poster
## loads options skins, breakable, magazine, and fitting
#include:tikz
#include:pdfcol
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
## make documentation commands regular (w/o #*) if "documentation" option explicitly loaded
\begin{docCommand}{name}{parameters}
\begin{docCommand}[options%keyvals]{name}{parameters}
\end{docCommand}
\begin{docCommand*}{name}{parameters}
\begin{docCommand*}[options%keyvals]{name}{parameters}
\end{docCommand*}
\begin{docCommands}{%<{variant1},{variant2},...%>}
\begin{docCommands}[options%keyvals]{%<{variant1},{variant2},...%>}
\end{docCommands}
\begin{docEnvironment}{name}{parameters}
\begin{docEnvironment}[options%keyvals]{name}{parameters}
\end{docEnvironment}
\begin{docEnvironment*}{name}{parameters}
\begin{docEnvironment*}[options%keyvals]{name}{parameters}
\end{docEnvironment*}
\begin{docEnvironments}{%<{variant1},{variant2},...%>}
\begin{docEnvironments}[options%keyvals]{%<{variant1},{variant2},...%>}
\end{docEnvironments}
\begin{docKey}{name}{parameters}{description}
\begin{docKey}[key path][options%keyvals]{name}{parameters}{description%text}
\end{docKey}
\begin{docKey*}{name}{parameters}{description}
\begin{docKey*}[key path][options%keyvals]{name}{parameters}{description%text}
\end{docKey*}
\begin{docKeys}{%<{variant1},{variant2},...%>}
\begin{docKeys}[options%keyvals]{%<{variant1},{variant2},...%>}
\end{docKeys}
\begin{docPathOperation}{name}{parameters}
\begin{docPathOperation}[options%keyvals]{name}{parameters}
\end{docPathOperation}
\begin{docPathOperation*}{name}{parameters}
\begin{docPathOperation*}[options%keyvals]{name}{parameters}
\end{docPathOperation*}
\begin{docPathOperations}{%<{variant1},{variant2},...%>}
\begin{docPathOperations}[options%keyvals]{%<{variant1},{variant2},...%>}
\end{docPathOperations}
\docValue{name}
\docValue[options%keyvals]{name}
\docValue*{name}
\docValue*[options%keyvals]{name}
\docAuxCommand{name}
\docAuxCommand[options%keyvals]{name}
\docAuxCommand*{name}
\docAuxCommand*[options%keyvals]{name}
\docAuxEnvironment{name}
\docAuxEnvironment[options%keyvals]{name}
\docAuxEnvironment*{name}
\docAuxEnvironment*[options%keyvals]{name}
\docAuxKey{name}
\docAuxKey[key path][options%keyvals]{name}
\docAuxKey*{name}
\docAuxKey*[key path][options%keyvals]{name}
\docCounter{name}
\docCounter[options%keyvals]{name}
\docCounter*{name}
\docCounter*[options%keyvals]{name}
\docLength{name}
\docLength[options%keyvals]{name}
\docLength*{name}
\docLength*[options%keyvals]{name}
\docColor{name}
\docColor[options%keyvals]{name}
\docColor*{name}
\docColor*[options%keyvals]{name}
\cs{name}
\meta{text%plain}
\marg{text%plain}
\oarg{text%plain}
\brackets{text%plain}
\begin{dispExample}
\end{dispExample}
\begin{dispExample*}{options%keyvals}
\end{dispExample*}
\begin{dispListing}#V
\end{dispListing}
\begin{dispListing*}{options%keyvals}#V
\end{dispListing*}
\begin{absquote}
\end{absquote}
\tcbmakedocSubKey{envname}{key path}#N
\tcbmakedocSubKeys{envname}{key path}#N
\refCom{name}
\refCom*{name}
\refEnv{name}
\refEnv*{name}
\refKey{name}
\refKey*{name}
\refPathOperation{name}
\refPathOperation*{name}
\refAux{name}
\refAuxcs{name}
\colDef{text%plain}
\colOpt{text%plain}
\colFade{text%plain}
\tcbdocmarginnote{text}
\tcbdocmarginnote[options%keyvals]{text}
\tcbdocnew{date}
\tcbdocupdated{date}
#endif

#ifOption:many
## loads options skins, breakable, theorems, and xparse
#include:amsmath
#include:tikz
#include:pdfcol
#endif

#ifOption:most
## loads all options except minted and documentation
#include:amsmath
#include:incgraph
#include:listings
#include:listingsutf8
#include:pdftexcmds
#include:shellesc
#include:tikz
#include:pdfcol
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
#include:pdfcol
## make documentation commands regular (w/o #*) if "all" option explicitly loaded
\begin{docCommand}{name}{parameters}
\begin{docCommand}[options%keyvals]{name}{parameters}
\end{docCommand}
\begin{docCommand*}{name}{parameters}
\begin{docCommand*}[options%keyvals]{name}{parameters}
\end{docCommand*}
\begin{docCommands}{%<{variant1},{variant2},...%>}
\begin{docCommands}[options%keyvals]{%<{variant1},{variant2},...%>}
\end{docCommands}
\begin{docEnvironment}{name}{parameters}
\begin{docEnvironment}[options%keyvals]{name}{parameters}
\end{docEnvironment}
\begin{docEnvironment*}{name}{parameters}
\begin{docEnvironment*}[options%keyvals]{name}{parameters}
\end{docEnvironment*}
\begin{docEnvironments}{%<{variant1},{variant2},...%>}
\begin{docEnvironments}[options%keyvals]{%<{variant1},{variant2},...%>}
\end{docEnvironments}
\begin{docKey}{name}{parameters}{description}
\begin{docKey}[key path][options%keyvals]{name}{parameters}{description%text}
\end{docKey}
\begin{docKey*}{name}{parameters}{description}
\begin{docKey*}[key path][options%keyvals]{name}{parameters}{description%text}
\end{docKey*}
\begin{docKeys}{%<{variant1},{variant2},...%>}
\begin{docKeys}[options%keyvals]{%<{variant1},{variant2},...%>}
\end{docKeys}
\begin{docPathOperation}{name}{parameters}
\begin{docPathOperation}[options%keyvals]{name}{parameters}
\end{docPathOperation}
\begin{docPathOperation*}{name}{parameters}
\begin{docPathOperation*}[options%keyvals]{name}{parameters}
\end{docPathOperation*}
\begin{docPathOperations}{%<{variant1},{variant2},...%>}
\begin{docPathOperations}[options%keyvals]{%<{variant1},{variant2},...%>}
\end{docPathOperations}
\docValue{name}
\docValue[options%keyvals]{name}
\docValue*{name}
\docValue*[options%keyvals]{name}
\docAuxCommand{name}
\docAuxCommand[options%keyvals]{name}
\docAuxCommand*{name}
\docAuxCommand*[options%keyvals]{name}
\docAuxEnvironment{name}
\docAuxEnvironment[options%keyvals]{name}
\docAuxEnvironment*{name}
\docAuxEnvironment*[options%keyvals]{name}
\docAuxKey{name}
\docAuxKey[key path][options%keyvals]{name}
\docAuxKey*{name}
\docAuxKey*[key path][options%keyvals]{name}
\docCounter{name}
\docCounter[options%keyvals]{name}
\docCounter*{name}
\docCounter*[options%keyvals]{name}
\docLength{name}
\docLength[options%keyvals]{name}
\docLength*{name}
\docLength*[options%keyvals]{name}
\docColor{name}
\docColor[options%keyvals]{name}
\docColor*{name}
\docColor*[options%keyvals]{name}
\cs{name}
\meta{text%plain}
\marg{text%plain}
\oarg{text%plain}
\brackets{text%plain}
\begin{dispExample}
\end{dispExample}
\begin{dispExample*}{options%keyvals}
\end{dispExample*}
\begin{dispListing}#V
\end{dispListing}
\begin{dispListing*}{options%keyvals}#V
\end{dispListing*}
\begin{absquote}
\end{absquote}
\tcbmakedocSubKey{name}{key path}
\tcbmakedocSubKeys{name}{key path}
\refCom{name}
\refCom*{name}
\refEnv{name}
\refEnv*{name}
\refKey{name}
\refKey*{name}
\refPathOperation{name}
\refPathOperation*{name}
\refAux{name}
\refAuxcs{name}
\colDef{text%plain}
\colOpt{text%plain}
\colFade{text%plain}
\tcbdocmarginnote{text}
\tcbdocmarginnote[options%keyvals]{text}
\tcbdocnew{date}
\tcbdocupdated{date}
#endif

# << Libraries >>
\tcbuselibrary{%<library%>%keys}
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
\newtcolorbox[init options]{envname}[args][default]{options%keyvals}#N
\renewtcolorbox{envname}{options%keyvals}
\renewtcolorbox[init options]{envname}[args][default]{options%keyvals}
\DeclareTColorBox{envname}{xargs}{options%keyvals}#N
\DeclareTColorBox[init options]{envname}{xargs}{options%keyvals}#*N
\NewTColorBox{envname}{xargs}{options%keyvals}#N
\NewTColorBox[init options]{envname}{xargs}{options%keyvals}#*N
\RenewTColorBox{envname}{xargs}{options%keyvals}#N
\RenewTColorBox[init options]{envname}{xargs}{options%keyvals}#*N
\ProvideTColorBox{envname}{xargs}{options%keyvals}#N
\ProvideTColorBox[init options]{envname}{xargs}{options%keyvals}#*N
\DeclareTotalTColorBox{cmd}{xargs}{options%keyvals}{content}#d
\DeclareTotalTColorBox[init options]{cmd}{xargs}{options%keyvals}{content}#*d
\NewTotalTColorBox{cmd}{xargs}{options%keyvals}{content}#d
\NewTotalTColorBox[init options]{cmd}{xargs}{options%keyvals}{content}#*d
\RenewTotalTColorBox{cmd}{xargs}{options%keyvals}{content}#d
\RenewTotalTColorBox[init options]{cmd}{xargs}{options%keyvals}{content}#*d
\ProvideTotalTColorBox{cmd}{xargs}{options%keyvals}{content}#d
\ProvideTotalTColorBox[init options]{cmd}{xargs}{options%keyvals}{content}#*d
\newtcbox{cmd}{options%keyvals}#d
\newtcbox[init options]{cmd}[args][default]{options%keyvals}#d
\renewtcbox{cmd}{options%keyvals}#d
\renewtcbox[init options]{cmd}[args][default]{options%keyvals}#d
\DeclareTCBox{cmd}{xargs}{options%keyvals}#d
\DeclareTCBox[init options]{cmd}{xargs}{options%keyvals}#*d
\NewTCBox{cmd}{xargs}{options%keyvals}#d
\NewTCBox[init options]{cmd}{xargs}{options%keyvals}#*d
\RenewTCBox{cmd}{xargs}{options%keyvals}#d
\RenewTCBox[init options]{cmd}{xargs}{options%keyvals}#*d
\ProvideTCBox{cmd}{xargs}{options%keyvals}#d
\ProvideTCBox[init options]{cmd}{xargs}{options%keyvals}#*d
\DeclareTotalTCBox{cmd}{xargs}{options%keyvals}{content}#d
\DeclareTotalTCBox[init options]{cmd}{xargs}{options%keyvals}{content}#*d
\NewTotalTCBox{cmd}{xargs}{options%keyvals}{content%text}#d
\NewTotalTCBox[init options]{cmd}{xargs}{options%keyvals}{content%text}#*d
\RenewTotalTCBox{cmd}{xargs}{options%keyvals}{content%text}#d
\RenewTotalTCBox[init options]{cmd}{xargs}{options%keyvals}{content%text}#*d
\ProvideTotalTCBox{cmd}{xargs}{options%keyvals}{content%text}#d
\ProvideTotalTCBox[init options]{cmd}{xargs}{options%keyvals}{content%text}#*d
\tcboxverb{verbatim box content%definition}
\tcboxverb[options%keyvals]{verbatim box content%definition}
\tcolorboxenvironment{envname}{options%keyvals}

# << Title >>
\tcbtitletext
\tcbtitle

# << Subtitle >>
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

# << Skins >>
\tcbsubskin{name}{base skin}{options%keyvals}
\tcbheightspace#L
\tcbtextwidth#L
\tcbtextheight#L
\tcbsegmentstate
\tcboxedtitlewidth#L
\tcboxedtitleheight#L
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
\tcboverlaplower#L

tcbcolframe#B
tcbcolback#B
tcbcolbacktitle#B
tcbcolbacklower#B
tcbcolupper#B
tcbcollower#B
tcbcoltitle#B

# << Inclusion of Boxed Image Files >>
\tcbincludegraphics{imagefile}#g
\tcbincludegraphics[options%keyvals]{imagefile}#g
\imagename
\tcbincludepdf{file}#i
\tcbincludepdf[options%keyvals]{file}#i
\imagepage
\pdfpages

# << TikZ image and picture fill extensions; Aux macros >>
#keyvals:\node#c,\draw#c,\path#c,\begin{scope}#c,\begin{tikzpicture}#c,\tikz#c,\tikzset#c
fill plain image=%<file name%>
fill plain image*=%<file name%>
fill plain picture*={%<code%>}
fill stretch image=%<file name%>
fill stretch image*={%<graphics options%>}{%<file%>}
fill stretch picture={%<code%>}
fill overzoom image=%<file name%>
fill overzoom image*={%<graphics options%>}{%<file%>}
fill overzoom picture={%<code%>}
fill zoom image=%<file name%>
fill zoom image*={%<graphics options%>}{%<file%>}
fill zoom picture={%<code%>}
fill shrink image=%<file name%>
fill shrink image*={%<graphics options%>}{%<file%>}
fill shrink picture=
fill tile image=%<file name%>
fill tile image*={%<graphics options%>}{%<file%>}
fill tile picture={%<code%>}
fill tile picture*={%<graphics options%>}{%<file%>}
fill image opacity=%<fraction%>
fill image scale=%<fraction%>
fill image options={%<graphics options%>}
#endkeyvals
\tcbpatcharcangular
\tcbpatcharcround
\tcbsettowidthofnode{register}{node}
\tcbsetmacrotowidthofnode{macro%cmd}{node}#d
\tcbsettoheightofnode{register}{node}
\tcbsetmacrotoheightofnode{macro%cmd}{node}#d
\tcbhypernode{macro}{node}

# << Vignette >>
\tcbvignette{options%keyvals}

# << Rasters >>
\begin{tcbraster}
\begin{tcbraster}[options%keyvals]
\end{tcbraster}
\thetcbrasternum
\thetcbrastercolumn
\thetcbrasterrow
\begin{tcbitemize}
\begin{tcbitemize}[options%keyvals]
\end{tcbitemize}
\tcbitem
\tcbitem[options%keyvals]
\begin{tcboxedraster}{box options}
\begin{tcboxedraster}[raster options%keyvals]{box options}
\end{tcboxedraster}
\begin{tcboxeditemize}{box options}
\begin{tcboxeditemize}[raster options%keyvals]{box options}
\end{tcboxeditemize}

# << Listings, minted >>
\begin{tcblisting}{options%keyvals}#V
\end{tcblisting}
\begin{tcboutputlisting}#V
\end{tcboutputlisting}
\tcbinputlisting{options%keyvals}
\tcbuselistingtext
\tcbuselistinglisting
\tcbusetemplisting
\newtcblisting{envname}{options%keyvals}#N
\newtcblisting[init options]{envname}[args][default]{options%keyvals}#N
\renewtcblisting{envname}{options%keyvals}#N
\renewtcblisting[init options]{envname}[args][default]{options%keyvals}#N
\DeclareTCBListing{envname}{xargs}{options%keyvals}#N
\DeclareTCBListing[init options]{envname}{xargs}{options%keyvals}#*N
\NewTCBListing{envname}{xargs}{options%keyvals}#N
\NewTCBListing[init options]{envname}{xargs}{options%keyvals}#*N
\RenewTCBListing{envname}{xargs}{options%keyvals}#N
\RenewTCBListing[init options]{envname}{xargs}{options%keyvals}#*N
\ProvideTCBListing{envname}{xargs}{options%keyvals}#N
\ProvideTCBListing[init options]{envname}{xargs}{options%keyvals}#*N
\newtcbinputlisting{cmd}{options%keyvals}#d
\newtcbinputlisting[init options]{cmd}[args][default]{options%keyvals}#d
\renewtcbinputlisting{cmd}{options%keyvals}#d
\renewtcbinputlisting[init options]{cmd}[args][default]{options%keyvals}#d
\DeclareTCBInputListing{cmd}{xargs}{options%keyvals}#d
\DeclareTCBInputListing[init options]{cmd}{xargs}{options%keyvals}#*d
\NewTCBInputListing{cmd}{xargs}{options%keyvals}#d
\NewTCBInputListing[init options]{cmd}{xargs}{options%keyvals}#*d
\RenewTCBInputListing{cmd}{xargs}{options%keyvals}#d
\RenewTCBInputListing[init options]{cmd}{xargs}{options%keyvals}#*d
\ProvideTCBInputListing{cmd}{xargs}{options%keyvals}#d
\ProvideTCBInputListing[init options]{cmd}{xargs}{options%keyvals}#*d

# << Theorems >>
\newtcbtheorem{envname}{display name}{options%keyvals}{prefix}#N
\newtcbtheorem[init options]{envname}{display name}{options%keyvals}{prefix}#N
\renewtcbtheorem{envname}{display name}{options%keyvals}{prefix}
\renewtcbtheorem[init options]{envname}{display name}{options%keyvals}{prefix}
\tcboxmath{mathematical box content%formula}
\tcboxmath[options%keyvals]{mathematical box content%formula}
\tcbhighmath{mathematical box content%formula}
\tcbhighmath[options%keyvals]{mathematical box content%formula}

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
\boxarraygetsize{macro%cmd}#d
\boxarraygetsize[name]{macro%cmd}#d
\useboxarray{index}
\useboxarray[name]{index}
\usetcboxarray{index}{options%keyvals}
\usetcboxarray[name]{index}{options%keyvals}
\consumeboxarray{index}
\consumeboxarray[name]{index}
\consumetcboxarray{index}{options%keyvals}
\consumetcboxarray[name]{index}{options%keyvals}
\boxarraygetbox{macro%cmd}{index}#d
\boxarraygetbox[name]{macro%cmd}{index}#d
\ifboxarrayempty{index}{true}{false}
\ifboxarrayempty[name]{index}{true}{false}
\boxarraygetwidth{macro%cmd}{index}#d
\boxarraygetwidth[name]{macro%cmd}{index}#d
\boxarraygetheight{macro%cmd}{index}#d
\boxarraygetheight[name]{macro%cmd}{index}#d
\boxarraygetdepth{macro%cmd}{index}#d
\boxarraygetdepth[name]{macro%cmd}{index}#d
\boxarraygettotalheight{macro%cmd}{index}#d
\boxarraygettotalheight[name]{macro%cmd}{index}#d

# << Posters >>
\begin{tcbposter}
\begin{tcbposter}[options%keyvals]
\end{tcbposter}
\tcbposterwidth#L
\tcbposterheight#L
\tcbpostercolspacing#L
\tcbposterrowspacing#L
\tcbpostercolumns
\tcbposterrows
\tcbpostercolwidth#L
\tcbposterrowheight#L
\tcbposterset{options%keyvals}
\posterbox{placement}{box content%text}
\posterbox[options%keyvals]{placement}{box content%text}
\begin{posterboxenv}{placement}
\begin{posterboxenv}[options%keyvals]{placement}
\end{posterboxenv}

# << Fitting >>
\tcboxfit{box content%text}
\tcboxfit[options%keyvals]{box content%text}
\newtcboxfit{cmd}{options%keyvals}#d
\newtcboxfit[init options]{cmd}[args][default]{options%keyvals}#d
\renewtcboxfit{cmd}{options%keyvals}#d
\renewtcboxfit[init options]{cmd}[args][default]{options%keyvals}#d
\DeclareTCBoxFit{cmd}{xargs}{options%keyvals}#d
\DeclareTCBoxFit[init options]{cmd}{xargs}{options%keyvals}#*d
\NewTCBoxFit{cmd}{xargs}{options%keyvals}#d
\NewTCBoxFit[init options]{cmd}{xargs}{options%keyvals}#*d
\RenewTCBoxFit{cmd}{xargs}{options%keyvals}#d
\RenewTCBoxFit[init options]{cmd}{xargs}{options%keyvals}#*d
\ProvideTCBoxFit{cmd}{xargs}{options%keyvals}#d
\ProvideTCBoxFit[init options]{cmd}{xargs}{options%keyvals}#*d
\DeclareTotalTCBoxFit{cmd}{xargs}{options%keyvals}{content%text}#d
\DeclareTotalTCBoxFit[init options]{cmd}{xargs}{options%keyvals}{content%text}#*d
\NewTotalTCBoxFit{cmd}{xargs}{options%keyvals}{content%text}
\NewTotalTCBoxFit[init options]{cmd}{xargs}{options%keyvals}{content%text}#*
\RenewTotalTCBoxFit{cmd}{xargs}{options%keyvals}{content%text}#d
\RenewTotalTCBoxFit[init options]{cmd}{xargs}{options%keyvals}{content%text}#*d
\ProvideTotalTCBoxFit{cmd}{xargs}{options%keyvals}{content%text}#d
\ProvideTotalTCBoxFit[init options]{cmd}{xargs}{options%keyvals}{content%text}#*d
\tcbfitdim#L
\tcbfontsize{factor}
\tcbfitsteps

# << External >>
\tcbEXTERNALIZE#*
\begin{tcbexternal}{name}#*
\begin{tcbexternal}[options%keyvals]{name}#*
\end{tcbexternal}#*
\begin{extcolorbox}{name}#*
\begin{extcolorbox}[options%keyvals]{name}[tcolorbox options]#*
\end{extcolorbox}#*
\begin{extikzpicture}{name}#*
\begin{extikzpicture}[options%keyvals]{name}[tikz options]#*
\end{extikzpicture}#*
\tcbifexternal{true}{false}#*
\newtcbexternalizeenvironment{newenv%envname}{env}{options%keyvals}{begin}{end}#*N
\renewtcbexternalizeenvironment{newenv%envname}{env}{options%keyvals}{begin}{end}#*
\newtcbexternalizetcolorbox{newenv%envname}{env}{options%keyvals}{begin end options}#*N
\renewtcbexternalizetcolorbox{newenv%envname}{env}{options%keyvals}{begin end options}#*N
\tcbiffileprocess{condition}{source}{md5-file}{target}{true}{false}#*

# << Documentation >>
\begin{docCommand}{name}{parameters}#*
\begin{docCommand}[options%keyvals]{name}{parameters}#*
\end{docCommand}#*
\begin{docCommand*}{name}{parameters}#*
\begin{docCommand*}[options%keyvals]{name}{parameters}#*
\end{docCommand*}#*
\begin{docCommands}{%<{variant1},{variant2},...%>}#*
\begin{docCommands}[options%keyvals]{%<{variant1},{variant2},...%>}#*
\end{docCommands}#*
\begin{docEnvironment}{name}{parameters}#*
\begin{docEnvironment}[options%keyvals]{name}{parameters}#*
\end{docEnvironment}#*
\begin{docEnvironment*}{name}{parameters}#*
\begin{docEnvironment*}[options%keyvals]{name}{parameters}#*
\end{docEnvironment*}#*
\begin{docEnvironments}{%<{variant1},{variant2},...%>}#*
\begin{docEnvironments}[options%keyvals]{%<{variant1},{variant2},...%>}#*
\end{docEnvironments}#*
\begin{docKey}{name}{parameters}{description}#*
\begin{docKey}[key path][options%keyvals]{name}{parameters}{description%text}#*
\end{docKey}#*
\begin{docKey*}{name}{parameters}{description}#*
\begin{docKey*}[key path][options%keyvals]{name}{parameters}{description%text}#*
\end{docKey*}#*
\begin{docKeys}{%<{variant1},{variant2},...%>}#*
\begin{docKeys}[options%keyvals]{%<{variant1},{variant2},...%>}#*
\end{docKeys}#*
\begin{docPathOperation}{name}{parameters}#*
\begin{docPathOperation}[options%keyvals]{name}{parameters}#*
\end{docPathOperation}#*
\begin{docPathOperation*}{name}{parameters}#*
\begin{docPathOperation*}[options%keyvals]{name}{parameters}#*
\end{docPathOperation*}#*
\begin{docPathOperations}{%<{variant1},{variant2},...%>}#*
\begin{docPathOperations}[options%keyvals]{%<{variant1},{variant2},...%>}#*
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
\meta{text%plain}#*
\marg{text%plain}#*
\oarg{text%plain}#*
\brackets{text%plain}#*
\begin{dispExample}#*
\end{dispExample}#*
\begin{dispExample*}{options%keyvals}#*
\end{dispExample*}#*
\begin{dispListing}#*V
\end{dispListing}#*
\begin{dispListing*}{options%keyvals}#*V
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
\colDef{text%plain}#*
\colOpt{text%plain}#*
\colFade{text%plain}#*
\tcbdocmarginnote{text}#*
\tcbdocmarginnote[options%keyvals]{text}#*
\tcbdocnew{date}#*
\tcbdocupdated{date}#*

Option#B
Definition#B
ExampleFrame#B
ExampleBack#B
Hyperlink#B
Fade#B

# ------------------------------
# << Option Keys >> - Standard
# ------------------------------

#keyvals:\tcbset,\begin{tcolorbox},\tcbsetforeverylayer,\tcbox,\newtcolorbox,\renewtcolorbox,\newtcbox,\renewtcbox,\tcolorboxenvironment,\tcbsubtitle,\tcbsidebyside,\tcbsubskin,\tcbincludegraphics,\tcbincludepdf,\begin{tcbraster},\begin{tcbitemize},\tcbitem,\begin{tcboxedraster},\begin{tcboxeditemize},\begin{tcblisting},\tcbinputlisting,\newtcblisting,\renewtcblisting,\newtcbinputlisting,\renewtcbinputlisting,\newtcbtheorem,\renewtcbtheorem,\tcboxmath,\tcbhighmath,\usetcboxarray,\consumetcboxarray,\posterbox,\begin{posterboxenv},\tcboxfit,\newtcboxfit,\renewtcboxfit,\DeclareTColorBox,\NewTColorBox,\RenewTColorBox,\ProvideTColorBox,\DeclareTotalTColorBox,\NewTotalTColorBox,\RenewTotalTColorBox,\ProvideTotalTColorBox,\DeclareTCBox,\NewTCBox,\RenewTCBox,\ProvideTCBox,\DeclareTotalTCBox,\NewTotalTCBox,\RenewTotalTCBox,\ProvideTotalTCBox,\DeclareTCBListing,\NewTCBListing,\RenewTCBListing,\ProvideTCBListing,\DeclareTCBInputListing,\NewTCBInputListing,\RenewTCBInputListing,\ProvideTCBInputListing,\DeclareTCBoxFit,\NewTCBoxFit,\RenewTCBoxFit,\ProvideTCBoxFit,\DeclareTotalTCBoxFit,\NewTotalTCBoxFit,\RenewTotalTCBoxFit,\ProvideTotalTCBoxFit,\tcboxverb,\begin{docCommand},\begin{docCommand*},\begin{docCommands},\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\begin{docKey},\begin{docKey*},\begin{docKeys},\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations},\docValue,\docValue*,\docAuxCommand,\docAuxCommand*,\docAuxEnvironment,\docAuxEnvironment*,\docAuxKey,\docAuxKey*,\docCounter,\docCounter*,\docLength,\docLength*,\docColor,\docColor*,\begin{dispExample*},\begin{dispListing*},\tcbdocmarginnote
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

### << vignette library keys >> ###
underlay vignette
underlay vignette={%<vignette options%>}
underlay raise shading vignette
underlay raise shading vignette={%<vignette options%>}
underlay raise fading vignette
underlay raise fading vignette={%<vignette options%>}
underlay shade in vignette
underlay shade in vignette={%<vignette options%>}
finish vignette
finish vignette={%<vignette options%>}
finish raised fading vignette
finish raised fading vignette={%<vignette options%>}
finish fading vignette
finish fading vignette={%<vignette options%>}

### << raster library keys >> ###
raster multicolumn=%<number%>
raster multirow=%<number%>

### << theorem library keys >> ###
separator sign=%<sign%>
separator sign colon
separator sign dash
separator sign none
description delimiters=
description delimiters parenthesis
description delimiters none
description color
description color=#%color
description font
description font=%<text%>
description formatter
description formatter=%<macro%>
terminator sign=%<sign%>
terminator sign colon
terminator sign dash
terminator sign none
label separator=%<separator%>
theorem full label supplement={%<style%>}
theorem label supplement={%<style%>}
theorem hanging indent=##L
theorem name and number
theorem number and name
theorem name
theorem number
theorem={%<display name%>}{%<counter%>}{%<title%>}{%<marker%>}
highlight math style={%<options%>}
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

### << magazine library keys >> ###
reset box array
reset box array=%<name%>
store to box array
store to box array=%<name%>
reset and store to box array
reset and store to box array=%<name%>
do not store to box array

### << poster library keys >> ###
placeholder

### << fitting library keys >> ###
fit
fit to=%<width%> and %<height%>
fit to height=##L
fit basedim=##L
fit skip=%<factor%>
fit fontsize macros
fit height plus=##L
fit width plus=##L
fit width from=%<min%> to %<max%>
fit height from=%<min%> to %<max%>
fit algorithm=#fontsize,fontsize*,areasize,areasize*,hybrid,hybrid*,squeeze
fit maxstep=%<number%>
fit maxfontdiff=##L
fit maxfontdiffgap=##L
fit maxwidthdiff=##L
fit maxwidthdiffgap=##L
fit warning=#off,on,final

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
#endkeyvals

## tcbox special keys
#keyvals:\tcbset,\tcbsetforeverylayer,\tcbox,\newtcbox,\renewtcbox,\tcboxmath,\tcbhighmath,\usetcboxarray,\consumetcboxarray,\tcboxfit,\newtcboxfit,\renewtcboxfit,\DeclareTCBox,\NewTCBox,\RenewTCBox,\ProvideTCBox,\DeclareTotalTCBox,\NewTotalTCBox,\RenewTotalTCBox,\ProvideTotalTCBox,\tcboxverb,\DeclareTCBoxFit,\NewTCBoxFit,\RenewTCBoxFit,\ProvideTCBoxFit,\DeclareTotalTCBoxFit,\NewTotalTCBoxFit,\RenewTotalTCBoxFit,\ProvideTotalTCBoxFit
tcbox raise=##L
tcbox raise base
on line
verbatim
tcbox width=#auto,auto limited,forced center,forced left,forced right,minimum center,minimum left,minimum right
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Graphics
# ---------------------------------------
#keyvals:\tcbset,\tcbincludegraphics,\tcbincludepdf
graphics options={%<graphics options%>}
graphics directory=%<directory%>
graphics pages=%<selection%>
graphics orientation=#as-is,landscape,landscape*,portrait,portrait*
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Vignette
# ---------------------------------------
#keyvals:\tcbvignette
xmin=##L
xmax=##L
ymin=##L
ymax=##L
lower left corner={%<x,y%>}
upper right corner={%<x,y%>}
inside node=%<name%>
outside node=%<name%>
over node=%<name%>
over node offset=##L
north size=##L
south size=##L
east size=##L
west size=##L
vertical size=##L
horizontal size=##L
size=##L
north style={%<TikZ options%>}
south style={%<TikZ options%>}
east style={%<TikZ options%>}
west style={%<TikZ options%>}
scope={%<TikZ options%>}
raised color=#%color
lowered color=#%color
color from=%<inner%> to %<outer%>
base color=#%color
draw method=#direct,clipped
fade in={%<TikZ options%>}
fade out={%<TikZ options%>}
semi fade in={%<TikZ options%>}
semi fade out={%<TikZ options%>}
#endkeyvals

#keyvals:\tcbset
vig/xmin=##L
vig/xmax=##L
vig/ymin=##L
vig/ymax=##L
vig/lower left corner={%<x,y%>}
vig/upper right corner={%<x,y%>}
vig/inside node=%<name%>
vig/outside node=%<name%>
vig/over node=%<name%>
vig/over node offset=##L
vig/north size=##L
vig/south size=##L
vig/east size=##L
vig/west size=##L
vig/vertical size=##L
vig/horizontal size=##L
vig/size=##L
vig/north style={%<TikZ options%>}
vig/south style={%<TikZ options%>}
vig/east style={%<TikZ options%>}
vig/west style={%<TikZ options%>}
vig/scope={%<TikZ options%>}
vig/raised color=#%color
vig/lowered color=#%color
vig/color from=%<inner%> to %<outer%>
vig/base color=#%color
vig/draw method=#direct,clipped
vig/fade in={%<TikZ options%>}
vig/fade out={%<TikZ options%>}
vig/semi fade in={%<TikZ options%>}
vig/semi fade out={%<TikZ options%>}
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Raster
# ---------------------------------------
#keyvals:\tcbset,\begin{tcbraster},\begin{tcbitemize},\begin{tcboxedraster},\begin{tcboxeditemize}
### << Raster library keys >> ###
raster columns=%<number%>
raster rows=%<number%>
raster width=##L
raster width flush left=##L
raster width center=##L
raster width flush right=##L
raster height=##L
raster before skip=##L
raster after skip=##L
raster equal skip=##L
raster left skip=##L
raster right skip=##L
raster column skip=##L
raster row skip=##L
raster halign=#left,center,right
raster valign=#top,center,bottom
raster equal height
raster equal height=#none,rows,all
raster equal height group=%<id%>
raster force size#true,false
raster reset
raster every box/.style={%<options%>}
raster odd column/.style={%<options%>}
raster even column/.style={%<options%>}
raster column 1/.style={%<options%>}
raster column 2/.style={%<options%>}
raster column 3/.style={%<options%>}
raster column 4/.style={%<options%>}
raster odd row/.style={%<options%>}
raster even row/.style={%<options%>}
raster row 1/.style={%<options%>}
raster row 2/.style={%<options%>}
raster row 3/.style={%<options%>}
raster row 4/.style={%<options%>}
raster odd number/.style={%<options%>}
raster even number/.style={%<options%>}
raster number 1/.style={%<options%>}
raster number 2/.style={%<options%>}
raster number 3/.style={%<options%>}
raster number 4/.style={%<options%>}
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Listings
# ---------------------------------------

#keyvals:\tcbset,\begin{tcblisting},\tcbinputlisting,\newtcblisting,\renewtcblisting,\newtcbinputlisting,\renewtcbinputlisting,\DeclareTCBListing,\NewTCBListing,\RenewTCBListing,\ProvideTCBListing,\DeclareTCBInputListing,\NewTCBInputListing,\RenewTCBInputListing,\ProvideTCBInputListing
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

# ---------------------------------------
# << Option Keys >> - Posters
# ---------------------------------------
#keyvals:\begin{tcbposter},\tcbposterset
poster={%<poster options%>}
coverage={%<options%>}
no coverage
boxes={%<options%>}
fontsize=##L
#endkeyvals

#keyvals:\tcbset,\posterbox,\begin{posterboxenv}
posterset/poster={%<poster options%>}
posterset/coverage={%<options%>}
posterset/no coverage
posterset/boxes={%<options%>}
posterset/fontsize=##L
poster/columns=%<number%>
poster/rows=%<number%>
poster/colspacing=##L
poster/rowspacing=##L
poster/showframe#true,false
poster/width=##L
poster/height=##L
poster/prefix=%<name%>
posterloc/name=%<name%>
posterloc/column=%<number%>
posterloc/column*=%<number%>
posterloc/span=%<number%>
posterloc/row=%<number%>
posterloc/rowspan=%<number%>
posterloc/fixed height
posterloc/below=%<name%>
posterloc/above=%<name%>
posterloc/at=%<name%>
posterloc/between=%<name1%> and %<name2%>
posterloc/sequence=%<sequence%>
posterloc/xshift=##L
posterloc/yshift=##L
#endkeyvals

# ---------------------------------------
# << Option Keys >> - External
# ---------------------------------------

#keyvals:\begin{tcbexternal},\begin{extcolorbox},\begin{extikzpicture},\newtcbexternalizeenvironment,\renewtcbexternalizeenvironment,\newtcbexternalizetcolorbox,\renewtcbexternalizetcolorbox
runner=%<file name%>
prefix=%<text%>
externalize#true,false
force remake#true,false
!
-
name=%<name%>
safety=%<length%>
environment=%<envname%>
environment with percent#true,false
minipage
minipage=##L
plain
compiler=%<text%>
runs=%<number%>
input source on error#true,false
preclass={%<code%>}
PassOptionsToPackage={%<options%>}{%<package%>}
PassOptionsToClass={%<options%>}{%<class%>}
clear preclass
preamble={%<code%>}
preamble tcbset={%<options%>}
clear preamble
#endkeyvals

#keyvals:\tcbset
external/runner=%<file name%>
external/prefix=%<text%>
external/externalize#true,false
external/force remake#true,false
external/!
external/-
external/name=%<name%>
external/safety=%<length%>
external/environment=%<envname%>
external/environment with percent#true,false
external/minipage
external/minipage=##L
external/plain
external/compiler=%<text%>
external/runs=%<number%>
external/input source on error#true,false
external/preclass={%<code%>}
external/PassOptionsToPackage={%<options%>}{%<package%>}
external/PassOptionsToClass={%<options%>}{%<class%>}
external/clear preclass
external/preamble={%<code%>}
external/preamble tcbset={%<options%>}
external/clear preamble
#endkeyvals

#keyvals:\begin{dispExample*}
externalize example=%<name%>
externalize example!=%<name%>
#endkeyvals

# ---------------------------------------
# << Option Keys >> - Documentation library
# ---------------------------------------
#keyvals:\tcbset,\begin{docCommand},\begin{docCommand*},\begin{docCommands},\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\begin{docKey},\begin{docKey*},\begin{docKeys},\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations}
doc name=%<name%>
doc parameter=%<parameters%>
doc description=%<description%>
doc label=%<text%>
doc index=%<text%>
doc sort index=%<text%>
doc into index#true,false
doc no index
doc new=%<date%>
doc updated=%<date%>
doc new and updated={%<new date%>}{%<update date%>}
doc left=##L
doc right=##L
doc left indent=##L
doc right indent=##L
doc raster={%<options%>}
doc head={%<options%>}
before doc body={%<code%>}
after doc body={%<code%>}
#endkeyvals

#keyvals:\begin{docCommand},\begin{docCommand*},\begin{docCommands},\tcbset
before doc body command={%<code%>}
after doc body command={%<code%>}
doc head command={%<options%>}
doc raster command={%<options%>}
#endkeyvals

#keyvals:\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\tcbset
before doc body environment={%<code%>}
after doc body environment={%<code%>}
doc head environment={%<options%>}
doc raster environment={%<options%>}
#endkeyvals

#keyvals:\begin{docKey},\begin{docKey*},\begin{docKeys},\tcbset
doc keypath=%<key path%>
before doc body key={%<code%>}
after doc body key={%<code%>}
doc head key={%<options%>}
doc raster key={%<options%>}
#endkeyvals

#keyvals:\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations},\tcbset
before doc body path={%<code%>}
after doc body path={%<code%>}
doc head path={%<options%>}
doc raster path={%<options%>}
#endkeyvals

#keyvas:\tcbset
doc marginnote={%<options%>}
#endkeyvals

#keyvals:\begin{dispExample*},\begin{dispListing*},\tcbset
docexample/.style={%<options%>}
documentation listing options={%<listings keys%>}
documentation listing style=%<listings style%>
documentation minted options={%<minted keys%>}
documentation minted style=%<minted style%>
documentation minted language=%<language%>
before example={%<code%>}
after example={%<code%>}
#endkeyvals

#keyvals:\tcbset,\begin{docCommand},\begin{docCommand*},\begin{docCommands},\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\begin{docKey},\begin{docKey*},\begin{docKeys},\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations},\docValue,\docValue*,\docAuxCommand,\docAuxCommand*,\docAuxEnvironment,\docAuxEnvironment*,\docAuxKey,\docAuxKey*,\docCounter,\docCounter*,\docLength,\docLength*,\docColor,\docColor*,\begin{dispExample*},\begin{dispListing*}
keywords bold#true,false
index command=%<macro%>
index command name=%<name%>
index format=#pgfsection,pgfchapter,pgf,doc,off
index actual=%<character%>
index quote=%<character%>
index level=%<character%>
index default settings/.style=
index german settings/.style=
index annotate#true,false
index colorize#true,false
index gather colors#true,false
index gather commands#true,false
index gather counters#true,false
index gather environments#true,false
index gather keys#true,false
index gather lengths#true,false
index gather paths#true,false
index gather values#true,false
index gather all
index gather none
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
doclang/color=%<text%>
doclang/colors=%<text%>
doclang/commands=%<text%>
doclang/counter=%<text%>
doclang/environment=%<text%>
doclang/environments=%<text%>
doclang/environment content=%<text%>
doclang/index=%<text%>
doclang/key=%<text%>
doclang/keys=%<text%>
doclang/length=%<text%>
doclang/lengths=%<text%>
doclang/new=%<text%>
doclang/path=%<text%>
doclang/paths=%<text%>
doclang/pageshort=%<text%>
doclang/updated=%<text%>
doclang/value=%<text%>
doclang/values=%<text%>
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
