# kswrapfig package
# ponte-vecchio 2023-01-17 for v0.004

#include:environ
#include:calc
#include:keycommand
#include:xifthen
#include:picinpar
#include:picins

#keyvals:\usepackage/kswrapfig#c
insboxonly
clscaption
insbox
#endkeyvals

\kswrapfig{imagefile}{text}#g
\kswrapfig[options%keyvals]{imagefile}{text}#g
#keyvals:\kswrapfig#c
Pos=#r,l
Width=##L
InPos=#r,c,l
Sep=##L
Indent=##L
Lower=##L
Caption={%<text%>}
LastLineSkip=##L
FirstLineSkip=##L
List=%<env name%>
VAdjust=##L
UseBox#true,false
#endkeyvals

\kswrapfigline[options%keyvals]{imagefile}{text}#g
#keyvals:\kswrapfigline#c
Line=%<num lines%>
Pos=#r,l,c
CaptionName=%<env name%>
Width=##L
InPos=#r,c,l
Sep=##L
Indent=##L
Lower=##L
Caption={%<text%>}
LastLineSkip=##L
FirstLineSkip=##L
List=%<env name%>
VAdjust=##L
UseBox#true,false
#endkeyvals

#ifOption:insboxonly
#include:ksinsbox
#endif

#ifOption:insbox
#include:ksinsbox
#endif

\tightlist

# not documented
\begin{KSwrapfig}{options}{imagefile}#Sg
\end{KSwrapfig}#S
\begin{KSwrapfigline}{options}{imagefile}#Sg
\end{KSwrapfigline}#S
