# causets package
# Matthew Bertucci 2/7/2022 for v1.2

#include:tikz
# loads arrows.meta tikzlibrary

#keyvals:\usepackage/causets#c
tiny
small
large
huge
gray
black
blue
neon
gray colors
black colors
blue colors
neon colors
linked
unlinked
cap linked
arrow linked
brokenly linked
continuously linked
spatially linked
spatially unlinked
permutation
labeled
unlabeled
labeled u
unlabeled u
labeled v
unlabeled v
#endkeyvals

\tikzcausetsset{options%keyvals}

\pcauset{permutation}
\pcauset[options%keyvals]{permutation}
\pcausetP{permutation}
\pcausetP[options%keyvals]{permutation}
\pcausetL{permutation}
\pcausetL[options%keyvals]{permutation}
\pcausetX{permutation}
\pcausetX[options%keyvals]{permutation}

\rcauset{permutation}{event pairs}
\rcauset[options%keyvals]{permutation}{event pairs}
\rcausetP{permutation}{event pairs}
\rcausetP[options%keyvals]{permutation}{event pairs}
\rcausetL{permutation}{event pairs}
\rcausetL[options%keyvals]{permutation}{event pairs}
\rcausetX{permutation}{event pairs}
\rcausetX[options%keyvals]{permutation}{event pairs}

\causet{permutation}{event pairs}
\causet[options%keyvals]{permutation}{event pairs}
\causetP{permutation}{event pairs}
\causetP[options%keyvals]{permutation}{event pairs}
\causetL{permutation}{event pairs}
\causetL[options%keyvals]{permutation}{event pairs}
\causetX{permutation}{event pairs}
\causetX[options%keyvals]{permutation}{event pairs}

\causetFence{number}
\causetFence[options%keyvals]{number}
\causetClosedFence{number}
\causetClosedFence[options%keyvals]{number}
\causetCrown
\causetCrown[options%keyvals]

#keyvals:\tikzcausetsset#c,\pcauset#c,\pcausetP#c,\pcausetL#c,\pcausetX#c,\rcauset#c,\rcausetP#c,\rcausetL#c,\rcausetX#c,\causet#c,\causetP#c,\causetL#c,\causetX#c,\causetFence#c,\causetClosedFence#c,\causetCrown#c
tiny
small
normal
large
huge
tile size=##L
region line width=##L
grid line width=##L
event size=##L
link width=##L
broken link gap=##L
text scale=%<factor%>
region color=#%color
grid color=#%color
tile color=#%color
ulabel color=#%color
vlabel color=#%color
event color=#%color
label color=#%color
link color=#%color
spatial link color=#%color
region={%<options%>}
grid={%<options%>}
tiles={%<options%>}
events={%<options%>}
links={%<options%>}
link starts={%<options%>}
link ends={%<options%>}
link pauses={%<options%>}
link resumes={%<options%>}
cap links
arrow links
spatial links={%<options%>}
all labels={%<options%>}
labels={%<options%>}
ulabels={%<options%>}
vlabels={%<options%>}
#endkeyvals

\ifcausetsDrawPermutation#*
\causetsDrawPermutationtrue#*
\causetsDrawPermutationfalse#*
\ifcausetsDrawLinks#*
\causetsDrawLinkstrue#*
\causetsDrawLinksfalse#*
\ifcausetsBreakLinks#*
\causetsBreakLinkstrue#*
\causetsBreakLinksfalse#*
\ifcausetsDrawSpatialLinks#*
\causetsDrawSpatialLinkstrue#*
\causetsDrawSpatialLinksfalse#*
\ifcausetsDrawLabels#*
\causetsDrawLabelstrue#*
\causetsDrawLabelsfalse#*
\ifcausetsDrawULabels#*
\causetsDrawULabelstrue#*
\causetsDrawULabelsfalse#*
\ifcausetsDrawVLabels#*
\causetsDrawVLabelstrue#*
\causetsDrawVLabelsfalse#*

\causetfile{imagefile}#g
\causetfile[options%keyvals]{imagefile}#g

#keyvals:\causetfile
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

\causetspath#*
\drawpcauset{permutation}#*
\drawrcauset{permutation}{event pairs}#*
\drawcauset{permutation}{event pairs}#*