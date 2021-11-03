# pdfoverlay package
# Matthew Bertucci 11/3/2021 for v1.2b

#include:graphicx

\pdfoverlaySetPDF{pdf file}

\pdfoverlaySetGraphicsOptions{options%keyvals}

#keyvals:\pdfoverlaySetGraphicsOptions
bb=
bbllx=
bblly=
bburx=
bbury=
natwidth=
natheight=
hiresbb#true,false
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
viewport=
trim=
angle=
origin=
width=##L
height=##L
totalheight=##L
keepaspectratio#true,false
scale=
clip#true,false
draft#true,false
type=
ext=
read=
command=
quiet
page=
interpolate#true,false
decodearray=
#endkeyvals

\pdfoverlayIncludeToPage{page number}
\pdfoverlayIncludeToLastPage
\pdfoverlaySkipToPage{page number}
\pdfoverlayPauseOutput
\pdfoverlayResumeOutput