# suftesi class
# Matthew Bertucci 12/13/2021 for v3.2.0

#include:xkeyval
#include:class-book
#include:fontsize
#include:geometry
#include:enumitem
# loads inline option of enumitem
#include:caption
#include:multicol
#include:emptypage
#include:microtype
#include:color
#include:iftex
#include:etoolbox
#include:crop
#include:fontenc
# loads T1 option of fontenc
#include:substitutefont
#include:titlesec
#include:appendix
#include:titletoc
#include:fancyhdr

## Default font setup ##
#include:cochineal
#include:inconsolata
#include:biolinum
#include:newtxmath
# from cochineal option of newtxmath
\fAlt#*m
\rhoAlt#*m

## Class options ##
#ifOption:fewfootnotes=true
#include:zref-perpage
#endif
#ifOption:fewfootnotes
#include:zref-perpage
#endif

#ifOption:defaultfont=standard
#include:lmodern
#endif

#ifOption:defaultfont=palatino
#include:textcomp
#include:newpxtext
#include:newpxmath
#endif

#ifOption:defaultfont=libertine
#include:textcomp
#include:libertine
#include:libertinust1math
#endif

#ifOption:defaultfont=compatibility
#include:mathpazo
#include:beramono
#endif

#ifOption:mathfont=extended
#include:amsthm
#include:mathalpha
# from cal=boondoxo option of mathalpha
\mathcal{text%plain}#m
\mathbfcal{text%plain}#m
#endif

#ifOption:greekfont=artemisia
\greektext{text}
\textgreek{text}#*
#endif
#ifOption:greekfont=porson
\greektext{text}
\textgreek{text}#*
#endif
#ifOption:greekfont=bodoni
\greektext{text}
\textgreek{text}#*
#endif
#ifOption:greekfont=cbgreek
\greektext{text}
\textgreek{text}#*
#endif

#ifOption:style=FSPLa
#include:cclicenses
\FSPLcolophon{name}
#endif
#ifOption:style=FSPLb
#include:cclicenses
\FSPLcolophon{name}
#endif
#ifOption:style=FSPLc
#include:cclicenses
\FSPLcolophon{name}
#endif

#keyvals:\documentclass/suftesi#c
structure=#book,article,collection
pagelayout=#standard,standardaureo,periodical,periodicalaureo,compact,compactaureo,supercompact,supercompactaureo,pocketa,pocketb,pocketc
version=#screen,cscreen,draft,final
parindent=##L
defaultfont=#none,cochineal,libertine,palatino,standard
fontsize=##L
smallcapsstyle=#low,upper
mathfont=#none,minimal,extended
greekfont=#none,artemisia,porson,bodoni,cbgreek
partfont=#roman,italic,smallcaps
chapfont=#roman,italic,smallcaps
secfont=#roman,italic,smallcaps
subsecfont=#roman,italic,smallcaps
subsubsecfont=#roman,italic,smallcaps
parfont=#roman,italic,smallcaps
subparfont=#roman,italic,smallcaps
partstyle=#left,center,right,parleft,parcenter,parright
chapstyle=#left,center,right,parleft,parcenter,parright
secstyle=#left,center,right,parleft,parcenter,parright
subsecstyle=#left,center,right,parleft,parcenter,parright
subsubsecstyle=#left,center,right,parleft,parcenter,parright
parstyle=#left,center,right,parleft,parcenter,parright
subparstyle=#left,center,right,parleft,parcenter,parright
partnumstyle=#arabic,roman,Roman,dotarabic,dotroman,dotRoman
chapnumstyle=#arabic,roman,Roman,dotarabic,dotroman,dotRoman
secnumstyle=#arabic,roman,Roman,dotarabic,dotroman,dotRoman
subsecnumstyle=#arabic,roman,Roman,dotarabic,dotroman,dotRoman
subsubsecnumstyle=#arabic,roman,Roman,dotarabic,dotroman,dotRoman
parnumstyle=#arabic,roman,Roman,dotarabic,dotroman,dotRoman
subparnumstyle=#arabic,roman,Roman,dotarabic,dotroman,dotRoman
partpage#true,false
tocstyle=#standard,dotted,ragged,leftpage
compacttoc=#sec,subsec,subsubsec,par,subpar
tocpartfont=#roman,italic,smallcaps
tocchapfont=#roman,italic,smallcaps
tocsecfont=#roman,italic,smallcaps
tocsubsecfont=#roman,italic,smallcaps
tocsubsubsecfont=#roman,italic,smallcaps
tocparfont=#roman,italic,smallcaps
tocsubparfont=#roman,italic,smallcaps
twocolcontents=#toc,lof,lot,toclof,toclot,loflot,all
partialtoc#true,false
headerstyle=#inner,center,plain,authortitleinner,authortitlecenter
headerfont=#roman,italic,smallcaps
draftdate#true,false
footnotestyle=#bulged,hung,dotted,superscript
fewfootnotes#true,false
marginpar#true,false
captionstyle=#standard,sanserif,italic,smallcaps
liststyle=#bulged,aligned,indented
quotestyle=#center,right,justify
quotesize=#tiny,tinyr,tinyrr,tinyrrr,scriptsizer,scriptsizerr,scriptsizerrr,footnotesizer,footnotesizerr,footnotesizerrr,smallr,smallrr,smallrrr,normalsizer,normalsizerr,normalsizerrr,larger,largerr,largerrr,Larger,Largerr,Largerrr,LARGEr,LARGErr,LARGErrr,huger,hugerr,hugerrr,Huger,Hugerr,Hugerrr,HUGE,HUGEr,HUGErr,HUGErrr
style=#roman1,roman2,roman3,roman4,roman5,roman6italic1,italic2,italic3,italic4,italic5,italic6,italic7,italic8,italic9,italic10,italic11,italic12,smallcaps1,smallcaps2,smallcaps3,smallcaps4,smallcaps5,smallcaps6,smallcaps7,smallcaps8,smallcaps9,smallcaps10,smallcaps11,smallcaps12
maketitlestyle=#suftesi,standard
reverseauthortitle#true,false
titlefont=#roman,italic,smallcaps
authorfont=#roman,italic,smallcaps
datefont=#roman,italic,smallcaps
authortitlealign=#left,center,right
toctitlefont=#roman,italic,smallcaps
tocauthorfont=#roman,italic,smallcaps
#endkeyvals

\partfont{definition}
\chapfont{definition}
\secfont{definition}
\subsecfont{definition}
\subsubsecfont{definition}
\parfont{definition}
\subparfont{definition}
\partnumfont{definition}
\chapnumfont{definition}
\secnumfont{definition}
\subsecnumfont{definition}
\subsubsecnumfont{definition}
\parnumfont{definition}
\subparnumfont{definition}

\breakintoc
\breakinbody
\breakinbodyleft

\chapterintro
\chapterintroname{name}

\tocpartfont{definition}
\tocchapfont{definition}
\tocsecfont{definition}
\tocsubsecfont{definition}
\tocsubsubsecfont{definition}
\tocparfont{definition}
\tocsubparfont{definition}
\tocpartnumfont{definition}
\tocchapnumfont{definition}
\tocsecnumfont{definition}
\tocsubsecnumfont{definition}
\tocsubsubsecnumfont{definition}
\tocparnumfont{definition}
\tocsubparnumfont{definition}
\toclabelwidth{level}{width}
\tocpartname{definition}

#ifOption:printpartialtoc
\printpartialtoc
\partialtocsecfont{definition}
\partialtocsubsecfont{definition}
\partialtocsubsubsecfont{definition}
\partialtocparfont{definition}
\partialtocsubparfont{definition}
\partialtocseclabelfont{definition}
\partialtocsubseclabelfont{definition}
\partialtocsubsubseclabelfont{definition}
\partialtocparlabelfont{definition}
\partialtocsubparlabelfont{definition}
\partialtocsize{definition}
\partialtocbeforespace{space%l}
\partialtocafterpace{space%l}
\partialtocbeforecode{definition}
\partialtocaftercode{definition}
\partialtocafterspace{space%l}
\partialtocseclabel{definition}
\partialtocsubseclabel{definition}
\partialtocsubsubseclabel{definition}
\startchappartialtoc#*
\startsecpartialtoc#*
#endif
#ifOption:printpartialtoc=true
\printpartialtoc
\partialtocsecfont{definition}
\partialtocsubsecfont{definition}
\partialtocsubsubsecfont{definition}
\partialtocparfont{definition}
\partialtocsubparfont{definition}
\partialtocseclabelfont{definition}
\partialtocsubseclabelfont{definition}
\partialtocsubsubseclabelfont{definition}
\partialtocparlabelfont{definition}
\partialtocsubparlabelfont{definition}
\partialtocsize{definition}
\partialtocbeforespace{space%l}
\partialtocafterpace{space%l}
\partialtocbeforecode{definition}
\partialtocaftercode{definition}
\partialtocafterspace{space%l}
\partialtocseclabel{definition}
\partialtocsubseclabel{definition}
\partialtocsubsubseclabel{definition}
\startchappartialtoc#*
\startsecpartialtoc#*
#endif

\xfootnote{text}
\xfootnote[symbol]{text}

\title[short title]{text}
\titlefont{definition}
\authorfont{definition}
\datefont{definition}

\makecover
\makecover[TikZ options]

\Cauthor{text}
\Ctitle{text}
\Csubtitle{text}
\Ceditor{text}
\Cfoot{text}
\Cpagecolor{color}
\Ctextcolor{color}
\Cfootcolor{color}

\colophon{name}{additional info%text}
\colophon[OS]{name}{additional info%text}
\bookcolophon{copyright notice%text}{attribution%text}#*
\artcolophon{content%text}#*
\finalcolophon{content%text}#*

#ifOption:structure=collection
\collectiontitlepage
\collectiontitle{text}
\collectioneditor{text}
\fulljournal
\issue{text}
\issuename{text}
\journalname{text}
\journalnumber{text}
\journalvolume{text}
\journalwebsite{text}
\journalyear{text}
\theissue
\thejournalnumber
\thejournalvolume
\thearticle
\begin{article}
\end{article}
#endif

\SUFfntscale#*
\adjtoclabelsep#*
\adjtocpagesep#*
\appendicesname#*
\doi{DOI}#*
\isbn{ISBN}#*
\itlabel{arg}#*
\lmfntscale#*
\sectionsep#*

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

# from T1 option of fontenc
\DH#n
\NG#n
\dj#n
\ng#n
\k{arg}#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\quotedblbase#n
\quotesinglbase#n
\textquotedbl#n
\DJ#n
\th#n
\TH#n
\dh#n
\Hwithstroke#*n
\hwithstroke#*n
\textogonekcentered{arg}#*n
\guillemetleft#n
\guillemetright#n

# deprecated or not relevant
\origtableofcontents#S
\oldmarginpar#S
\headbreak#S
\hemph#S
\begin{bibliografia}#S
\end{bibliografia}#S
\begin{sigle}#S
\end{sigle}#S
\frontispiece#S
\losname#S
\texorpdfstring#S
\xheadbreak#S
\yheadbreak#S
