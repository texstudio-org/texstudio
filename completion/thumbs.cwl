# thumbs package
# Matthew Bertucci 11/29/2021 for v1.0q

#include:kvoptions
#include:atbegshi
#include:xcolor
#include:picture
#include:alphalph
#include:pageslts
#include:pagecolor
#include:rerunfilecheck
#include:infwarerr
#include:ltxcmds
#include:atveryend

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
thumblink=#none,title,page,titleandpage,line,rule
nophantomsection#true,false
ignorehoffset#true,false
ignorevoffset#true,false
verbose#true,false
draft#true,false
hidethumbs#true,false
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
