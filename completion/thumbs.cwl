# thumbs package
# Matthew Bertucci 2025/01/18 for v1.1d

#include:xcolor
#include:picture
#include:alphalph
#include:rerunfilecheck
#include:pagecolor
#include:undolabl

#keyvals:\usepackage/thumbs#c
linefill=#line,dots
minheight=##L
height=#auto
width=#auto
distance=##L
topthumbmargin=##L
bottomthumbmargin=##L
eventxtindent=##L
oddtxtexdent=##L
evenmarkindent=##L
oddmarkexdent=##L
evenprintvoffset=##L
leftindexruleplus=##L
frame=##L
frameinnercolor=#%color
thumblink=#none,title,page,titleandpage,line,rule
nophantomsection#true,false
plainthumbsoverview#true,false
ignorehoffset#true,false
ignorevoffset#true,false
verbose#true,false
draft#true,false
hidethumbs#true,false
righttoleft#true,false
#endkeyvals

#ifOption:verbose
\thumbsinfo
#endif
#ifOption:verbose=true
\thumbsinfo
#endif

\addthumb{title%plain}{display text}{color}{background color}
\addtitlethumb{title%plain}{display text}{color}{background color}{label}#l
\stopthumb
\continuethumb
\thumbsoverview{mark%text}
\thumbsoverviewback{mark%text}
\thumbsoverviewverso{mark%text}#*
\thumbsoverviewdouble{mark%text}#*
\thumbnewcolumn
\addthumbsoverviewtocontents{level}{entry%text}
\thumbsnophantom

\clearotherdoublepage#S
\thumbcontents#S
\thumborigaddthumb#S
\thumbsorigglossary#S
\thumbsorigindex#S
\thumbsoriglabel#S
\thumbsoverviewprint#S
\theThumbsPage#S
\begin{thumbspicture}#S
\begin{thumbspicture}[opt]#S
\end{thumbspicture}#S