# animate package
# Matthew Bertucci 2022/08/12 for v2022/08/04

#include:ifthen
#include:iftex
#include:ifdraft
#include:calc
#include:pdfbase
#include:graphics
#include:zref-abspage
#include:ocgbase

#keyvals:\usepackage/animate#c
dvipdfmx
xetex
dvisvgm
export
autoplay
autopause
autoresume
loop
palindrome
draft
final
controls
controls=#all,true,on,none,false,off
controlsaligned=#left,left+%<<indent>%>,center,right,right+%<<indent>%>
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
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
buttonsize=##L
buttonbg=%<color array%>
buttonfg=%<color array%>
buttonalpha=%<opacity%>
step
nomouse
type=%<file ext%>
method=#icon,widget,ocg
poster
poster=#first,last,none,%<number%>
alttext=#none,%<alt description%>
#endkeyvals

\animategraphics{frame rate}{file basename}{first}{last}
\animategraphics[options%keyvals]{frame rate}{file basename}{first}{last}

\begin{animateinline}{frame rate}
\begin{animateinline}[options%keyvals]{frame rate}
\end{animateinline}

\newframe
\newframe[frame rate]
\newframe*
\newframe*[frame rate]

\multiframe{number of frames}{variables}{content%definition}
\multiframebreak

#keyvals:\animategraphics#c,\begin{animateinline}#c
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
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
controls=#all,true,on,none,false,off
controlsaligned=#left,left+%<<indent>%>,center,right,right+%<<indent>%>
buttonsize=##L
buttonbg=%<color array%>
buttonfg=%<color array%>
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
