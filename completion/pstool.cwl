# pstool package
# Matthew Bertucci 2/22/2022 for v1.5e

#include:catchfile
#include:color
#include:ifpdf
#include:ifplatform
#include:filemod
#include:graphicx
#include:psfrag
#include:shellesc
#include:suffix
#include:trimspaces
#include:xkeyval

\pstool{imagefile}{input definitions}#g
\pstool[options%keyvals]{imagefile}{input definitions}#g
\pstool*{imagefile}{input definitions}#g
\pstool*[options%keyvals]{imagefile}{input definitions}#g
\pstool!{imagefile}{input definitions}#g
\pstool![options%keyvals]{imagefile}{input definitions}#g

\psfragfig{imagefile}{input definitions}#g
\psfragfig[options%keyvals]{imagefile}{input definitions}#g
\psfragfig*{imagefile}{input definitions}#g
\psfragfig*[options%keyvals]{imagefile}{input definitions}#g
\psfragfig!{imagefile}{input definitions}#g
\psfragfig![options%keyvals]{imagefile}{input definitions}#g

#keyvals:\pstool,\pstool*,\pstool!,\psfragfig,\psfragfig*,\psfragfig!
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

\pstoolsetup{options%keyvals}

#keyvals:\usepackage/pstool#c,\pstoolsetup,\pstool,\pstool*,\pstool!,\psfragfig,\psfragfig*,\psfragfig!
macro-file=%<file name%>
process=#auto,all,none
crop=#preview,pdfcrop
suffix={%<suffix%>}
cleanup={%<file extensions%>}
mode=#batch,nonstop,errorstop
latex-options={%<LaTeX options%>}
dvips-options={%<dvips options%>}
ps2pdf-options={%<ps2pdf options%>}
pdfcrop-options={%<pdfcrop options%>}
bitmap=#auto,lossy,lossless
crossref#true,false
#endkeyvals

\EndPreamble