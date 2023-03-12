# mdframed package
# sdm
# muzimuzhi 12 Mar 2020, mdframed v1.9b

#include:color
#include:etoolbox
#include:kvoptions
#include:needspace
#include:xparse
#include:zref-abspage

#keyvals:\usepackage/mdframed#c
xcolor
framemethod=#default,tex,latex,none,0,tikx,pgf,1,pstricks,ps,postscript,2
#endkeyvals

#ifOption:xcolor
#include:xcolor
#endif
#ifOption:tikz
#include:tikz
#endif
#ifOption:TikZ
#include:tikz
#endif
#ifOption:framemethod=tikz
#include:tikz
#endif
#ifOption:framemethod=pgf
#include:tikz
#endif
#ifOption:framemethod=1
#include:tikz
#endif
#ifOption:pstricks
#include:pstricks
#endif
#ifOption:PSTricks
#include:pstricks
#endif
#ifOption:framemethod=pstricks
#include:pstricks
#endif
#ifOption:framemethod=ps
#include:pstricks
#endif
#ifOption:framemethod=postscript
#include:pstricks
#endif
#ifOption:framemethod=2
#include:pstricks
#endif

\begin{mdframed}
\begin{mdframed}[options%keyvals]
\end{mdframed}

\newmdenv{envname}#N
\newmdenv[options%keyvals]{envname}#N
\renewmdenv{envname}
\renewmdenv[options%keyvals]{envname}
\surroundwithmdframed{env}
\surroundwithmdframed[options%keyvals]{env}
\mdflength{options%keyvals}#*
\mdfsetup{options%keyvals}
\mdfdefinestyle{style name}{options%keyvals}#*
\mdfapptodefinestyle{style name}{options%keyvals}#*

\mdfsubtitle{subtitle}
\mdfsubtitle[options%keyvals]{subtitle}
\mdfsubsubtitle{subtitle}
\mdfsubsubtitle[options%keyvals]{subtitle}

\newmdtheoremenv[options%keyvals]{envname}[numbered like]{caption}#N
\newmdtheoremenv[options%keyvals]{envname}{caption}#N
\newmdtheoremenv[options%keyvals]{envname}{caption}[within]#N
\newmdtheoremenv{envname}[numbered like]{caption}#N
\newmdtheoremenv{envname}{caption}#N
\newmdtheoremenv{envname}{caption}[within]#N
\mdtheorem[options%keyvals]{envname}[numbered like]{caption}#N
\mdtheorem[options%keyvals]{envname}{caption}#N
\mdtheorem[options%keyvals]{envname}{caption}[within]#N
\mdtheorem{envname}[numbered like]{caption}#N
\mdtheorem{envname}{caption}#N
\mdtheorem{envname}{caption}[within]#N

#keyvals:\begin{mdframed},\newmdenv,\renewmdenv,\surroundwithmdframed,\mdfsetup,\mmdfdefinestyle,\mdfapptodefinestyle,\mdfsubtitle,\mdfsubsubtitle,\newmdtheoremenv,\mdtheorem
# length options. These options accept both number (using unit in option "defaultunit") and dimension.
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
hidealllines#true,false
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
pstrickssetting={%<pstricks keys%>}
pstrickappsetting=%<code%>
style=%<style name%>
#endkeyvals

#keyvals:\mdflength
# length options
extratopheight
footenotedistance
frametitleaboveskip
frametitlebelowskip
frametitleleftmargin
frametitlerightmargin
frametitlerulewidth
innerbottommargin
innerleftmargin
innerlinewidth
innermargin
innerrightmargin
innertopmargin
leftmargin
linewidth
middlelinewidth
needspace
outerlinewidth
outermargin
rightmargin
roundcorner
shadowsize
skipabove
skipbelow
splitbottomskip
splittopskip
subsubtitleabovelinewidth
subsubtitleaboveskip
subsubtitlebelowlinewidth
subsubtitlebelowskip
subsubtitleinneraboveskip
subsubtitleinnerbelowskip
subtitleabovelinewidth
subtitleaboveskip
subtitlebelowlinewidth
subtitlebelowskip
subtitleinneraboveskip
subtitleinnerbelowskip
userdefinedwidth
#endkeyvals

\mdfsplitboxwidth#*
\mdfsplitboxtotalwidth#*
\mdfsplitboxheight#*
\mdfsplitboxdepth#*
\mdfsplitboxtotalheight#*
\mdfframetitleboxwidth#*
\mdfframetitleboxtotalwidth#*
\mdfframetitleboxheight#*
\mdfframetitleboxdepth#*
\mdfframetitleboxtotalheight#*
\mdffootnoteboxwidth#*
\mdffootnoteboxtotalwidth#*
\mdffootnoteboxheight#*
\mdffootnoteboxdepth#*
\mdffootnoteboxtotalheight#*
\mdftotallinewidth#*
\mdfboundingboxwidth#*
\mdfboundingboxtotalwidth#*
\mdfboundingboxheight#*
\mdfboundingboxdepth#*
\mdfboundingboxtotalheight#*
\mdfsubtitleheight#*
\mdfsubsubtitleheight#*
\themdfcountframes#*
\mdfframedtitleenv{text}#*
\mdversion#S
\mdframedpackagename#S
\mdfmaindate#S
\mdfrevision#S
