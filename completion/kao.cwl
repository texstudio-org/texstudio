# kao package
# Matthew Bertucci 2022/05/26 for v0.9.8

#include:etoolbox
#include:calc
#include:xcolor
# loads dvipsnames and table options of xcolor
#include:iftex
#include:xifthen
#include:options
#include:xparse
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
#include:mdframed
#include:pdfpages
#include:subfiles
#include:todonotes
#include:listings
#include:algorithm2e
#include:ccicons
#include:metalogo
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
extratopheight=##L
footenotedistance=##L
frametitleaboveskip=##L
frametitlebelowskip=##L
frametitleleftmargin=##L
frametitlerightmargin=##L
frametitlerulewidth=##L
innerbottommargin=##L
innerleftmargin=##L
innerlinewidth=##L
innermargin=##L
innerrightmargin=##L
innertopmargin=##L
leftmargin=##L
linewidth=##L
middlelinewidth=##L
needspace=##L
outerlinewidth=##L
outermargin=##L
rightmargin=##L
roundcorner=##L
shadowsize=##L
skipabove=##L
skipbelow=##L
splitbottomskip=##L
splittopskip=##L
subsubtitleabovelinewidth=##L
subsubtitleaboveskip=##L
subsubtitlebelowlinewidth=##L
subsubtitlebelowskip=##L
subsubtitleinneraboveskip=##L
subsubtitleinnerbelowskip=##L
subtitleabovelinewidth=##L
subtitleaboveskip=##L
subtitlebelowlinewidth=##L
subtitlebelowskip=##L
subtitleinneraboveskip=##L
subtitleinnerbelowskip=##L
userdefinedwidth=##L
# string options
afterbreak=%<code%>
afterlastframe=%<code%>
aftersingleframe=%<code%>
alignment=
backgroundcolor=#%color
beforebreak=%<code%>
beforelastframe=%<code%>
beforesingleframe=%<code%>
defaultunit=#pt,bp,in,cm,mm,em,ex,en,pc,sp
endcode=%<code%>
endinnercode=%<code%>
extra=%<code%>
firstextra=%<code%>
firstframetitle={%<text%>}
font=%<font commands%>
fontcolor=#%color
framefoot=%<code%>
frametitle={%<text%>}
frametitlealignment
frametitlebackgroundcolor=#%color
frametitlefont=%<font commands%>
frametitlefontcolor=#%color
frametitlerulecolor=#%color
frametitlesettings=%<code%>
innerlinecolor=#%color
lastframefoot=%<code%>
linecolor=#%color
middleextra=%<code%>
middlelinecolor=#%color
outerlinecolor=#%color
printheight=#none,info,warning
psroundlinecolor=#%color
secondextra=%<code%>
settings=%<code%>
shadowcolor=#%color
singleextra=%<code%>
startcode=%<code%>
startinnercode=%<code%>
subsubtitleabovelinecolor=#%color
subsubtitlebackgroundcolor=#%color
subsubtitlebelowlinecolor=#%color
subsubtitlefont=%<font commands%>
subtitleabovelinecolor=#%color
subtitlebackgroundcolor=#%color
subtitlebelowlinecolor=#%color
subtitlefont=%<font commands%>
theoremcountersep=%<separator%>
theoremseparator=%<separator%>
theoremspace=%<space cmd%>
theoremtitlefont=%<font commands%>
# boolean options
bottomline#true,false
draft#true,false
everyline#true,false
footnoteinside#true,false
frametitlebottomline#true,false
frametitleleftline#true,false
frametitlerightline#true,false
frametitlerule#true,false
frametitletopline#true,false
ignorelastdescenders#true,false
leftline#true,false
ntheorem#true,false
repeatframetitle#true,false
rightline#true,false
shadow#true,false
subsubtitleaboveline#true,false
subsubtitlebelowline#true,false
subtitleaboveline#true,false
subtitlebelowline#true,false
suppressfirstparskip#true,false
topline#true,false
usetwoside#true,false
# other options
align=#left,center,right
tikzsetting={%<TikZ keys%>}
apptotikzsetting=%<code%>
style=%<style name%>
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
\rowcolors{row}{odd-row-color}{even-row-color}
\rowcolors[commands]{row}{odd-row-color}{even-row-color}
\rowcolors{row}{color}{color}#S
\rowcolors[commands]{row}{color}{color}#S
\rowcolors*{row}{odd-row-color}{even-row-color}
\rowcolors*[commands]{row}{odd-row-color}{even-row-color}
\rowcolors*{row}{color}{color}#S
\rowcolors*[commands]{row}{color}{color}#S
\showrowcolors
\hiderowcolors
\rownum

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