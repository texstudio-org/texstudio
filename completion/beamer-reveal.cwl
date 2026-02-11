# beamer-reveal package
# Matthew Bertucci 2026/02/11 for v1.09

#include:tikz
#include:tikzlibrarycalc
#include:currfile

#keyvals:\usepackage/beamer-reveal#c
width=%<pixels%>
height=%<pixels%>
embed
loop
autoslide=%<integer%>
#endkeyvals

\video \at (%<x,y%>) {%<filename%>}
\video[%<options%>] \at (%<x,y%>) {%<filename%>}
\video<%<overlay spec%>> \at (%<x,y%>) {%<filename%>}
\video<%<overlay spec%>>[%<options%>] \at (%<x,y%>) {%<filename%>}
\audio \at (%<x,y%>) {%<filename%>}
\audio[%<options%>] \at (%<x,y%>) {%<filename%>}
\audio<%<overlay spec%>> \at (%<x,y%>) {%<filename%>}
\audio<%<overlay spec%>>[%<options%>] \at (%<x,y%>) {%<filename%>}
\iframe \at (%<x,y%>) {%<filename%>}
\iframe[%<options%>] \at (%<x,y%>) {%<filename%>}
\iframe<%<overlay spec%>> \at (%<x,y%>) {%<filename%>}
\iframe<%<overlay spec%>>[%<options%>] \at (%<x,y%>) {%<filename%>}
\image \at (%<x,y%>) {%<filename%>}
\image[%<options%>] \at (%<x,y%>) {%<filename%>}
\image<%<overlay spec%>> \at (%<x,y%>) {%<filename%>}
\image<%<overlay spec%>>[%<options%>] \at (%<x,y%>) {%<filename%>}
\animation \at (%<x,y%>) {%<content%>}
\animation[%<options%>] \at (%<x,y%>) {%<content%>}
\animation<%<overlay spec%>> \at (%<x,y%>) {%<content%>}
\animation<%<overlay spec%>>[%<options%>] \at (%<x,y%>) {%<content%>}
\still \at (%<x,y%>) {%<content%>}
\still[%<options%>] \at (%<x,y%>) {%<content%>}
\still<%<overlay spec%>> \at (%<x,y%>) {%<content%>}
\still<%<overlay spec%>>[%<options%>] \at (%<x,y%>) {%<content%>}
\at#S

# not documented
\extractloleft{arg}#S
\extractupright{arg}#S
\xloleft#S
\xupright#S
\yloleft#S
\yupright#S