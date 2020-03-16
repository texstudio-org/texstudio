# mdframed package
# sdm
# muzimuzhi 12 Mar 2020, mdframed v1.9b

#include:color
#include:etoolbox
#include:kvoptions
#include:needspace
#include:xparse
#include:zref-abspage

#ifOption:xcolor
#include:xcolor
#endif
#ifOption:tikz
#include:tikz
#endif
#ifOption:pstricks
#include:tikz
#endif

\begin{mdframed}
\begin{mdframed}[options%keyvals]
\end{mdframed}

\newmdenv{envname}#N
\newmdenv[options%keyvals]{envname}#N
\renewmdenv{envname}#N
\renewmdenv[options%keyvals]{envname}#N
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
# string options
afterbreak
afterlastframe
aftersingleframe
alignment
backgroundcolor=#%color
beforebreak
beforelastframe
beforesingleframe
defaultunit=#pt,bp,in,cm,mm,em,ex,en,pc,sp
endcode
endinnercode
extra
firstextra
firstframetitle
font
fontcolor=#%color
framefoot
frametitle
frametitlealignment
frametitlebackgroundcolor=#%color
frametitlefont
frametitlefontcolor=#%color
frametitlerulecolor=#%color
frametitlesettings
innerlinecolor=#%color
lastframefoot
linecolor=#%color
middleextra
middlelinecolor=#%color
outerlinecolor=#%color
printheight
psroundlinecolor=#%color
secondextra
settings
shadowcolor=#%color
singleextra
startcode
startinnercode
subsubtitleabovelinecolor=#%color
subsubtitlebackgroundcolor=#%color
subsubtitlebelowlinecolor=#%color
subsubtitlefont
subtitleabovelinecolor=#%color
subtitlebackgroundcolor=#%color
subtitlebelowlinecolor=#%color
subtitlefont
theoremcountersep
theoremseparator
theoremspace
theoremtitlefont
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
tikzsetting
apptotikzsetting
pstrickssetting
pstrickappsetting
style=#defautoptions,%<style name%>
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
