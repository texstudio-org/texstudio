# causets package
# Matthew Bertucci 2023/03/06 for v1.4

#include:tikz
# loads arrows.meta tikzlibrary

#keyvals:\usepackage/causets
tiny
smaller
small
large
larger
huge
gray
black
blue
neon
linked
unlinked
caps
arrows
continuous
spatial
external
permutation
labeled
unlabeled
ulabeled
uunlabeled
vlabeled
vunlabeled
#endkeyvals

#ifOption:external
#include:tikzlibraryexternal
#endif

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
\causetCrown{number}
\causetCrown[options%keyvals]{number}

#keyvals:\tikzcausetsset#c,\pcauset#c,\pcausetP#c,\pcausetL#c,\pcausetX#c,\rcauset#c,\rcausetP#c,\rcausetL#c,\rcausetX#c,\causet#c,\causetP#c,\causetL#c,\causetX#c,\causetFence#c,\causetCrown#c
all labels={%<TikZ keys%>}
arrow links
baseline=##L
black colors
blue colors
broken link gap=##L
brokenly linked
cap links
continuously linked
event=%<value%>
event color=#%color
event outline=##L
event size=##L
events={%<TikZ keys%>}
gray colors
grid color=#%color
grid line width=##L
grid={%<TikZ keys%>}
huge
label=%<text%>
label color=#%color
labeled
labels={%<TikZ keys%>}
large
link color=#%color
link ends={%<TikZ keys%>}
link pauses={%<TikZ keys%>}
link resumes={%<TikZ keys%>}
link starts={%<TikZ keys%>}
link width=##L
links={%<TikZ keys%>}
name=%<name%>
name external#true,false
name prefix=%<prefix%>
neon colors
normal
offset=%<integer%>
padding=##L
permutation
region color=#%color
region line width=##L
region={%<TikZ keys%>}
replaced events={%<TikZ keys%>}
replaced labels={%<TikZ keys%>}
set prefix=%<prefix%>
show permutation
small
spatial link color=#%color
spatial links={%<TikZ keys%>}
spatially linked
text font=%<font commands%>
text scale=%<factor%>
tile color=#%color
tile size=##L
tiles={%<TikZ keys%>}
tiny
ulabel color=#%color
ulabels={%<TikZ keys%>}
very large
very small
vlabel color=#%color
vlabels={%<TikZ keys%>}
#endkeyvals

\causetTileSize#*
\causetRegionLine#*
\causetGridLine#*
\causetEventSize#*
\causetLinkWidth#*
\causetBrokenLinkGap#*

\ifcausetsDrawPermutation#S
\causetsDrawPermutationtrue#*
\causetsDrawPermutationfalse#*
\ifcausetsDrawLinks#S
\causetsDrawLinkstrue#*
\causetsDrawLinksfalse#*
\ifcausetsBreakLinks#S
\causetsBreakLinkstrue#*
\causetsBreakLinksfalse#*
\ifcausetsDrawSpatialLinks#S
\causetsDrawSpatialLinkstrue#*
\causetsDrawSpatialLinksfalse#*
\ifcausetsDrawLabels#S
\causetsDrawLabelstrue#*
\causetsDrawLabelsfalse#*
\ifcausetsDrawULabels#S
\causetsDrawULabelstrue#*
\causetsDrawULabelsfalse#*
\ifcausetsDrawVLabels#S
\causetsDrawVLabelstrue#*
\causetsDrawVLabelsfalse#*
\ifcausetsNameExternal#S
\causetsNameExternaltrue#*
\causetsNameExternalfalse#*

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

\drawpcauset{permutation}#*
\drawrcauset{permutation}{event pairs}#*
\drawcauset{permutation}{event pairs}#*
