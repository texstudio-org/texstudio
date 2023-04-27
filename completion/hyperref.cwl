# hyperref package
# neeraavi 21 Mar 2007
#modified Edson 30-12-2010
#modified Denis Bitouz\'e 14-06-2014
#modified muzimuzhi 18 Jan 2020, 8 May 2020, 8 Jul 2020
#modified Matthew Bertucci 4 April 2023 for v7.00w

#include:iftex
#include:keyval
#include:kvsetkeys
#include:kvdefinekeys
#include:pdfescape
#include:hycolor
#include:letltxmacro
#include:auxhook
#include:kvoptions
#include:intcalc
#include:url
#include:bitset
#include:bigintcalc
#include:atbegshi
#include:atveryend
#include:rerunfilecheck
#include:nameref
#include:etoolbox

#ifOption:backref
#include:backref
#endif
#ifOption:backref=section
#include:backref
#endif
#ifOption:backref=slide
#include:backref
#endif
#ifOption:backref=page
#include:backref
#endif
#ifOption:pagebackref
#include:backref
#endif
#ifOption:pagebackref=true
#include:backref
#endif

#ifOption:colorlinks
#include:color
#endif
#ifOption:colorlinks=true
#include:color
#endif

#ifOption:destlabel
\HyperDestRename{destination}{newname}
#endif
#ifOption:destlabel=true
\HyperDestRename{destination}{newname}
#endif

#ifOption:hyperindex
\hyperindexformat{arg1}{arg2}#*
#endif
#ifOption:hyperindex=true
\hyperindexformat{arg1}{arg2}#*
#endif

\hypersetup{keyvals}
#keyvals:\hypersetup,\usepackage/hyperref#c
addtopdfcreator=%<text%>
allbordercolors=#%color
allcolors=#%color
anchorcolor=#%color
backref=#section,slide,page,none,false
baseurl=%<URL%>
bookmarks#true,false
bookmarksdepth
bookmarksdepth=%<number%>
bookmarksnumbered#true,false
bookmarksopen#true,false
bookmarksopenlevel=%<level%>
bookmarkstype=
breaklinks#true,false
citebordercolor=#%color
citecolor=#%color
CJKbookmarks#true,false
colorlinks#true,false
customdriver=%<file%>
debug#true,false
destlabel#true,false
draft#true,false
driverfallback=%<driver%>
dvipdfm
dvipdfmx
dvipdfmx-outline-open#true,false
dvips
dvipsone
dviwindo
encap=%<character%>
extension=%<file ext%>
filebordercolor=#%color
filecolor=#%color
final#true,false
frenchlinks#true,false
hidelinks
hitex
hyperfigures#true,false
hyperfootnotes#true,false
hyperindex#true,false
hypertex
hypertexnames#true,false
implicit#true,false
linkbordercolor=#%color
linkcolor=#%color
linkfileprefix=%<prefix%>
linktoc=#section,page,all,none
linktocpage#true,false
luatex
menubordercolor=#%color
menucolor=#%color
nativepdf
naturalnames#true,false
nesting#true,false
next-anchor=%<anchor name%>
ocgcolorlinks#true,false
pageanchor#true,false
pagebackref#true,false
pdfa#true,false
pdfauthor=%<author%>
pdfborder=
pdfborderstyle=
pdfcenterwindow#true,false
pdfcreationdate=%<date%>
pdfcreator=%<creator%>
pdfdirection=#L2R,R2L
pdfdisplaydoctitle#true,false
pdfduplex=#Simplex,DuplexFlipShortEdge,DuplexFlipLongEdge
pdfencoding=#pdfdoc,unicode,auto
pdfescapeform#true,false
pdffitwindow#true,false
pdfhighlight=#/I,/N,/O,/P
pdfinfo={%<info keys%>}
pdfkeywords={%<keyword list%>}
pdflang=%<lang id%>
pdflinkmargin=##L
pdfmark
pdfmenubar#true,false
pdfmoddate=%<date%>
pdfnewwindow#true,false
pdfnonfullscreenpagemode
pdfnumcopies=%<integer%>
pdfpageduration=
pdfpagelabels#true,false
pdfpagelayout=#SinglePage,OneColumn,TwoColumnLeft,TwoColumnRight,TwoPageLeft,TwoPageRight
pdfpagemode=#FullScreen,UseNone,UseOutlines,UseOC,UseAttachments,UseThumbs
pdfpagescrop=%<n1 n2 n3 n4%>
pdfpagetransition=#Split,Blinds,Box,Wipe,Dissolve,Glitter,R,Fly,Push,Cover,Uncover,Fade
pdfpicktraybypdfsize#true,false
pdfprintarea=#Mediabox,CropBox,BleedBox,TrimBox,ArtBox
pdfprintclip=#Mediabox,CropBox,BleedBox,TrimBox,ArtBox
pdfprintpagerange=%<n1 n2%>
pdfprintscaling=#None,AppDefault
pdfproducer=%<producer%>
pdfremotestartview=#XYZ,Fit,FitH,FitV,FitR,FitB,FitBH,FitBV
pdfstartpage=%<page number%>
pdfstartview=#XYZ,Fit,FitH,FitV,FitR,FitB,FitBH,FitBV
pdfsubject=%<subject%>
pdftex
pdftitle=%<title%>
pdftoolbar#true,false
pdftrapped=#True,False,Unknown
pdfusetitle#true,false
pdfversion=%<version%>
pdfview=#XYZ,Fit,FitH,FitV,FitR,FitB,FitBH,FitBV
pdfviewarea=#Mediabox,CropBox,BleedBox,TrimBox,ArtBox
pdfviewclip=#Mediabox,CropBox,BleedBox,TrimBox,ArtBox
pdfwindowui#true,false
plainpages#true,false
ps2pdf
psdextra#true,false
raiselinks#true,false
runbordercolor=#%color
runcolor=#%color
setpagesize#true,false
tex4ht
textures
unicode#true,false
urlbordercolor=#%color
urlcolor=#%color
verbose#true,false
vtex
vtexpdfmark
xetex
#endkeyvals

\href[options%keyvals]{URL}{text%plain}#U
\href{URL}{text%plain}#U

#keyvals:\href
pdfremotestartview=#XYZ,Fit,FitH,FitV,FitR,FitB,FitBH,FitBV
pdfnewwindow#true,false
page=%<number%>
ismap#true,false
nextactionraw={%<PDF code%>}
#endkeyvals

\AddToDocumentProperties{property}{value}#*
\AddToDocumentProperties[category]{property}{value}#*
\GetDocumentProperties{property}#*

\MakeLinkTarget{counter}
\MakeLinkTarget[prefix]{counter}
\MakeLinkTarget*{target name}
\NextLinkTarget{target name}
\LinkTargetOn
\LinkTargetOff
\SetLinkTargetFilter{filter code}

\url{URL}#U
\nolinkurl{URL}#U
\hyperbaseurl{URL}#U
\hyperimage{imageURL%URL}{text}#U
\hyperdef{category}{name}{text}
\hyperref{URL}{category}{name}{text}#M
# trick for commandExtract, for now
\hyperref[label%ref]{URL}{category}{name}{text}#M
\hyperref[label%ref]{text}
\hyperref{text}
\hyperlink{target name}{link text%text}
\hypertarget{target name}{anchor text%text}

\phantomsection

\hyperget{anchor}{label}
\autopageref{label}#r
\autopageref*{label}#r
\autoref{label}#r
\autoref*{label}#r
\thispdfpagelabel
\pdfstringdef{macroname%cmd}{TeXstring}#d
\begin{NoHyper}
\end{NoHyper}
\pdfbookmark{text}{name}
\pdfbookmark[level]{text}{name}
\currentpdfbookmark{text}{name}
\subpdfbookmark{text}{name}
\belowpdfbookmark{text}{name}
\texorpdfstring{TEXstring}{PDFstring}
\pdfstringdefDisableCommands{hooks}
\hypercalcbp{dimen specification}

\Acrobatmenu{menuoption}{text}

\begin{Form}
\begin{Form}[options%keyvals]
\end{Form}
#keyvals:\begin{Form}
action=%<URL%>
encoding=%<encoding%>
method=#post,get
#endkeyvals

\TextField{label}#/Form
\TextField[parameters%keyvals]{label}#/Form
\CheckBox{label}#/Form
\CheckBox[parameters%keyvals]{label}#/Form
\ChoiceMenu{label}{choices}#/Form
\ChoiceMenu[parameters%keyvals]{label}{choices}#/Form
\PushButton{label}#/Form
\PushButton[parameters%keyvals]{label}#/Form
\Submit{label}#/Form
\Submit[parameters%keyvals]{label}#/Form
\Reset{label}#/Form
\Reset[parameters%keyvals]{label}#/Form
#keyvals:\TextField,\CheckBox,\ChoiceMenu,\PushButton,\Submit,\Reset
accesskey=%<key%>
align=#0,1,2
altname=%<altname%>
backgroundcolor=#%color
bordercolor=#%color
bordersep=##L
borderstyle=#S,B,D,I,U
borderwidth=##L
calculate={%<JavaScript code%>}
calculatesortkey=%<key%>
charsize=##L
checkboxsymbol=%<symbol%>
checked#true,false
color=#%color
combo#true,false
default=%<default value%>
disabled#true,false
format={%<JavaScript code%>}
height=##L
hidden#true,false
keystroke={%<JavaScript code%>}
mappingname=%<name%>
maxlen=%<number%>
menulength=%<number%>
multiline#true,false
name=%<name%>
onblur={%<JavaScript code%>}
onchange={%<JavaScript code%>}
onclick={%<JavaScript code%>}
ondbclick={%<JavaScript code%>}
onfocus={%<JavaScript code%>}
onkeydown={%<JavaScript code%>}
onkeypress={%<JavaScript code%>}
onkeyup={%<JavaScript code%>}
onmousedown={%<JavaScript code%>}
onmousemove={%<JavaScript code%>}
onmouseout={%<JavaScript code%>}
onmouseover={%<JavaScript code%>}
onmouseup={%<JavaScript code%>}
onselect={%<JavaScript code%>}
password#true,false
popdown#true,false
radio#true,false
radiosymbol=%<symbol%>
readonly#true,false
rotation=%<multiple of 90%>
tabkey=%<key%>
validate={%<JavaScript code%>}
value=%<init value%>
width=##L
#endkeyvals

\LayoutTextField{label}{field}#*
\LayoutChoiceField{label}{field}#*
\LayoutCheckField{label}{field}#*
\MakeRadioField{width}{height}#*
\MakeCheckField{width}{height}#*
\MakeTextField{width}{height}#*
\MakeChoiceField{width}{height}#*
\MakeButtonField{text}#*
\DefaultHeightofSubmit#*
\DefaultWidthofSubmit#*
\DefaultHeightofReset#*
\DefaultWidthofReset#*
\DefaultHeightofCheckBox#*
\DefaultWidthofCheckBox#*
\DefaultHeightofChoiceMenu#*
\DefaultWidthofChoiceMenu#*
\DefaultHeightofText#*
\DefaultHeightofTextMultiline#*
\DefaultWidthofText#*
\DefaultOptionsofSubmit#*
\DefaultOptionsofReset#*
\DefaultOptionsofPushButton#*
\DefaultOptionsofCheckBox#*
\DefaultOptionsofText#*
\DefaultOptionsofListBox#*
\DefaultOptionsofComboBox#*
\DefaultOptionsofPopdownBox#*
\DefaultOptionsofRadio#*

\AfterBeginDocument{code}#*
\AMSautorefname#*
\appendixautorefname#*
\chapterautorefname#*
\equationautorefname#*
\FancyVerbLineautorefname#*
\figureautorefname#*
\footnoteautorefname#*
\Hfootnoteautorefname#*
\Hurl{URL}#*U
\HyperDestLabelReplace{dest}#*
\HyperDestNameFilter{arg}#*
\hypergetpageref{label}#*r
\hypergetref{label}#*r
\hyperlinkfileprefix{prefix}#*
\hyperpage{arg}#*
\HyperRaiseLinkDefault#*
\HyperRaiseLinkHook#*
\IfHyperBoolean{options}{true}{false}#*
\IfHyperBooleanExists{option}{true}{false}#*
\ifpdfstringunicode{unicode chars}{chars}#*
\Itemautorefname#*
\itemautorefname#*
\MakeLowercaseUnsupportedInPdfStrings{text}#*
\MakeUppercaseUnsupportedInPdfStrings{text}#*
\MaybeStopEarly#*
\MaybeStopNow#*
\nohyperpage{arg}#*
\pageautorefname#*
\paragraphautorefname#*
\partautorefname#*
\pdfstringdefPostHook#*
\pdfstringdefPreHook#*
\pdfstringdefWarn{arg}#*
\sectionautorefname#*
\setpdflinkmargin{length}#*
\subparagraphautorefname#*
\subsectionautorefname#*
\subsubsectionautorefname#*
\tableautorefname#*
\theHchapter#*
\theHenumi#*
\theHenumii#*
\theHenumiii#*
\theHenumiv#*
\theHequation#*
\theHfigure#*
\theHHfootnote#*
\theHHmpfootnote#*
\theHItem#*
\theHmpfootnote#*
\theHparagraph#*
\theHpart#*
\theHsection#*
\theHsubparagraph#*
\theHsubsection#*
\theHsubsubsection#*
\theHtable#*
\theHtheorem#*
\theHthm#* 
\theoremautorefname#*
\unichar{char num}#*
\XeTeXLinkBox{contents}#*
\XeTeXLinkMargin#*
