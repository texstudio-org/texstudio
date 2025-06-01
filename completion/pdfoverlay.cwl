# pdfoverlay package
# Matthew Bertucci 2024/12/21 for v1.3

#include:graphicx

\pdfoverlaySetPDF{pdf file%file}

\pdfoverlaySetGraphicsOptions{options%keyvals}

#keyvals:\pdfoverlaySetGraphicsOptions
actualtext={%<text%>}
alt={%<alt text%>}
artifact#true,false
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

# expl3 interface
\pdfoverlay_include_to_last_page:#/%expl3
\pdfoverlay_include_to_page:n {%<⟨page number⟩%>}#/%expl3
\pdfoverlay_pause_output:#/%expl3
\pdfoverlay_resume_output:#/%expl3
\pdfoverlay_set_graphics_options:n {%<⟨options⟩%>}#/%expl3
\pdfoverlay_set_pdf:n {%<⟨pdf file⟩%>}#/%expl3
\pdfoverlay_skip_to_page:n {%<⟨page number⟩%>}#/%expl3