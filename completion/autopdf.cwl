# autopdf package
# Matthew Bertucci 2/8/2022 for v1.1

#include:keyval
#include:ifthen
#include:ifpdf
#include:ifplatform
#include:graphicx

\autopdfoptions{options%keyvals}

#keyvals:\usepackage/autopdf#c,\autopdfoptions
from=%<file extension%>
to=%<file extension%>
logfile
nologfile
showcmds#true,false
cleanup#true,false
scale#true,false
margin=##L
resolution=%<dpi%>
gscmd=%<GhostScript cmd%>
gmidentifycmd=%<GraphicsMagick cmd%>
gmconvertcmd=%<GraphicsMagick cmd%>
#endkeyvals

\autopdfinclude
\autopdfendinclude

\autopdfpsfrag{tag}{content%text}
\autopdfpsfrag[options%keyvals]{tag}{content%text}

\autopdfpsfoptions{options%keyvals}

#keyvals:\autopdfpsfrag,\autopdfpsfoptions
texpos=%<LaTeX ref point%>
epspos=%<PS ref point%>
scale=%<factor%>
angle=%<degrees%>
add=%<text%>
#endkeyvals

\DELETE#S
\LEFT#S
\REDIRTO#S
\RIGHT#S
\SILENT#S