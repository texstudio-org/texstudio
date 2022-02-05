# asymptote package
# Matthew Bertucci 2/4/2022 for v1.36

#include:keyval
#include:ifthen
#include:color
#include:graphicx
#include:ifpdf
#include:ifxetex
#include:catchfile

#keyvals:\usepackage/asymptote#c
inline
attach
#endkeyvals

\begin{asy}
\begin{asy}[options%keyvals]
\end{asy}

\asyinclude{imagefile}#g
\asyinclude[options%keyvals]{imagefile}#g

\asysetup{options%keyvals}

#keyvals:\begin{asy},\asyinclude,\asysetup
width=##L
height=##L
keepAspect#true,false
viewportwidth=##L
viewportheight=##L
attach#true,false
inline#true,false
#endkeyvals

\begin{asydef}
\end{asydef}

\ASYanimategraphics{frame rate}{file}{first}{last}#*
\ASYanimategraphics[options%keyvals]{frame rate}{file}{first}{last}#*

#keyvals:\ASYanimategraphics#c
label=%<label%>
type=%<file ext%>
poster
poster=#first,last,none,%<number%>
every=%<number%>
autopause
autoplay
autoresume
loop
palindrome
step
width=##L
height=##L
totalheight=##L
keepaspectratio
scale=%<factor%>
bb=%<llx lly urx ury%>
viewport=%<llx lly urx ury%>
trim=%<left bottom right top%>
clip
hiresbb
interpolate
pagebox=
controls=#all,true,on,none,false,off
controlsaligned=
buttonsize=##L
buttonbg=#%color
buttonfg=#%color
buttonalpha=%<opacity%>
draft
final
nomouse
method=#icon,widget,ocg
measure
alttext=#none,%<alt description%>
begin={%<begin code%>}
end={%<end code%>}
timeline=%<file%>
#endkeyvals

\Asymptote#*
\ASYbox#*
\ASYdimen#*
\theasy#*
\AsyStream#*
\AsyPreStream#*
\ifASYinline#*
\ASYinlinetrue#*
\ASYinlinefalse#*
\ifASYattach#*
\ASYattachtrue#*
\ASYattachfalse#*
\ifASYkeepAspect#*
\ASYkeepAspecttrue#*
\ASYkeepAspectfalse#*
\asylatexdir#*
\asydir#*
\ASYasydir#*
\ASYlatexdir#*
\ASYprefix#*
\ifASYPDF#*
\ASYPDFtrue#*
\ASYPDFfalse#*
\AsyExtension#*
\WriteAsyLine{arg}#*
\globalASYdefs#*
\WriteGlobalAsyLine{arg}#*
\ProcessAsymptote{arg}#*
\CurrentAsymptote#*
\xAsymptote#*
\ProcessAsymptoteLine#*
\ThisAsymptote#*
\AsyFile#*
\ASYwidth#*
\ASYheight#*
\ASYviewportwidth#*
\ASYviewportheight#*

\csarg{arg1}{arg2}#S
\unquoteJobname#S
\rawJobname#S
\fixstar#S
\argtwo#S
\asy#S
\endasy#S
\asydef#S
\Jobname#S