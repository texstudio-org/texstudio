# asymptote package
# Matthew Bertucci 2025/02/18 for v1.38

#include:keyval
#include:ifthen
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

\asylatexdir#*
\asydir#*

# not documented
\ASYasydir#S
\ASYattachfalse#S
\ASYattachtrue#S
\ASYbox#S
\ASYdimen#S
\AsyExtension#S
\AsyFile#S
\ASYheight#S
\ASYinlinefalse#S
\ASYinlinetrue#S
\ASYkeepAspectfalse#S
\ASYkeepAspecttrue#S
\ASYlatexdir#S
\Asymptote#S
\ASYPDFfalse#S
\ASYPDFtrue#S
\ASYprefix#S
\AsyPreStream#S
\AsyStream#S
\ASYviewportheight#S
\ASYviewportwidth#S
\ASYwidth#S
\csarg{arg1}{arg2}#S
\CurrentAsymptote#S
\fixstar#S
\globalASYdefs#S
\ifASYattach#S
\ifASYinline#S
\ifASYkeepAspect#S
\ifASYPDF#S
\Jobname#S
\ProcessAsymptote{arg}#S
\ProcessAsymptoteLine#S
\rawJobname#S
\theasy#S
\ThisAsymptote#S
\unquoteJobname#S
\WriteAsyLine{arg}#S
\WriteGlobalAsyLine{arg}#S
\xAsymptote#S
