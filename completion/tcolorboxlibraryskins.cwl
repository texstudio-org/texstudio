# skins tcolorboxlibrary
# 2023/02/10 for v6.0.0

#include:tikz
#include:tikzfill.image

#keyvals:\path#c,\draw#c
tcb fill frame
tcb fill interior
tcb fill title
#endkeyvals

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

# << Inclusion of Boxed Image Files >>
\tcbincludegraphics{imagefile}#g
\tcbincludegraphics[options%keyvals]{imagefile}#g
\imagename
\tcbincludepdf{file}
\tcbincludepdf[options%keyvals]{file}
\imagepage
\pdfpages

#keyvals:\tcbset,\tcbincludegraphics,\tcbincludepdf
graphics options={%<graphics options%>}
graphics directory=%<directory%>
graphics pages=%<selection%>
graphics orientation=#as-is,landscape,landscape*,portrait,portrait*
#endkeyvals

# << TikZ Auxiliary Macros >>
\tcbsettowidthofnode{register}{node}
\tcbsetmacrotowidthofnode{macro%cmd}{node}#d
\tcbsettoheightofnode{register}{node}
\tcbsetmacrotoheightofnode{macro%cmd}{node}#d
\tcbhypernode{macro}{node}

#keyvals:\tcbset,\begin{tcolorbox},\tcbsetforeverylayer,\tcbox,\newtcolorbox,\renewtcolorbox,\newtcbox,\renewtcbox,\tcolorboxenvironment,\tcbsubtitle,\tcbsidebyside,\tcbsubskin,\tcbincludegraphics,\tcbincludepdf,\begin{tcbraster},\begin{tcbitemize},\tcbitem,\begin{tcboxedraster},\begin{tcboxeditemize},\begin{tcblisting},\tcbinputlisting,\newtcblisting,\renewtcblisting,\newtcbinputlisting,\renewtcbinputlisting,\NewTcbTheorem,\newtcbtheorem,\RenewTcbTheorem,\renewtcbtheorem,\ProvideTcbTheorem,\DeclareTcbTheorem,\tcboxmath,\tcbhighmath,\usetcboxarray,\consumetcboxarray,\posterbox,\begin{posterboxenv},\tcboxfit,\newtcboxfit,\renewtcboxfit,\DeclareTColorBox,\NewTColorBox,\RenewTColorBox,\ProvideTColorBox,\DeclareTotalTColorBox,\NewTotalTColorBox,\RenewTotalTColorBox,\ProvideTotalTColorBox,\DeclareTCBox,\NewTCBox,\RenewTCBox,\ProvideTCBox,\DeclareTotalTCBox,\NewTotalTCBox,\RenewTotalTCBox,\ProvideTotalTCBox,\DeclareTCBListing,\NewTCBListing,\RenewTCBListing,\ProvideTCBListing,\DeclareTCBInputListing,\NewTCBInputListing,\RenewTCBInputListing,\ProvideTCBInputListing,\DeclareTCBoxFit,\NewTCBoxFit,\RenewTCBoxFit,\ProvideTCBoxFit,\DeclareTotalTCBoxFit,\NewTotalTCBoxFit,\RenewTotalTCBoxFit,\ProvideTotalTCBoxFit,\tcboxverb,\begin{docCommand},\begin{docCommand*},\begin{docCommands},\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\begin{docKey},\begin{docKey*},\begin{docKeys},\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations},\docValue,\docValue*,\docAuxCommand,\docAuxCommand*,\docAuxEnvironment,\docAuxEnvironment*,\docAuxKey,\docAuxKey*,\docCounter,\docCounter*,\docLength,\docLength*,\docColor,\docColor*,\begin{dispExample*},\begin{dispListing*},\tcbdocmarginnote
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
#endkeyvals
