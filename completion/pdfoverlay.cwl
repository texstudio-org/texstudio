# pdfoverlay package
# Matthew Bertucci 11/3/2021 for v1.2b

#include:graphicx

\pdfoverlaySetPDF{pdf file%file}

\pdfoverlaySetGraphicsOptions{options%keyvals}

#keyvals:\pdfoverlaySetGraphicsOptions
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

\pdfoverlayIncludeToPage{page number}
\pdfoverlayIncludeToLastPage
\pdfoverlaySkipToPage{page number}
\pdfoverlayPauseOutput
\pdfoverlayResumeOutput
