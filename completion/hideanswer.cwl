# hideanswer package
# Matthew Bertucci 2022/06/29 for v1.0

#include:color

\sethideanswer
\unsethideanswer
\hideanswer{text}
\hideanswer*{text}
\begin{hideanswerdiv}
\end{hideanswerdiv}
\begin{hideanswerdiv*}
\end{hideanswerdiv*}
\smashanswer{text}
\smashanswer*{text}
\begin{smashanswerdiv}
\end{smashanswerdiv}
\begin{smashanswerdiv*}
\end{smashanswerdiv*}
\hidegraphics{imagefile}#g
\hidegraphics[options%keyvals]{imagefile}#g
\hidegraphics*{imagefile}#g
\hidegraphics*[options%keyvals]{imagefile}#g
\smashgraphics{imagefile}#g
\smashgraphics[options%keyvals]{imagefile}#g
\smashgraphics*{imagefile}#g
\smashgraphics*[options%keyvals]{imagefile}#g
\switchanswer{sethide-text%text}{unsethide-text%text}
\switchanswer*{unsethide-text%text}{sethide-text%text}

#keyvals:\hidegraphics,\hidegraphics*,\smashgraphics,\smashgraphics*
alt={%<alt text%>}
bb=%<llx lly urx ury%>
bbllx=
bblly=
bburx=
bbury=
natwidth=
natheight=
hiresbb#true,false
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
viewport=%<llx lly urx ury%>
trim=%<llx lly urx ury%>
angle=%<degrees%>
origin=
width=##L
height=##L
totalheight=##L
keepaspectratio#true,false
scale=%<factor%>
clip#true,false
draft#true,false
type=%<file type%>
ext=%<file extension%>
read=%<read-file extension%>
command=
quiet
page=%<page number%>
interpolate#true,false
decodearray={%<color array%>}
#endkeyvals