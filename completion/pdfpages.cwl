# pdfpages package
# mario 09/06/2007, Tim Hoffmann 25/02/2017
# muzimuzhi 29 Apr 2020, pdfpages v0.5q
# Matthew Bertucci 11 Oct 2022 for v0.5w
# URL: http://tug.ctan.org/tex-archive/macros/latex/contrib/pdfpages/

#include:eso-pic
#include:atbegshi
#include:pdflscape
#include:graphicx
#include:ifthen
#include:calc
#include:count1to

#keyvals:\usepackage/pdfpages#c
final
draft
demo
nodemo
enable-survey
#endkeyvals

\includepdf[options%keyvals]{filename%file}
\includepdf{filename%file}
\includepdfmerge[options%keyvals]{file-list%definition}
\includepdfmerge{file-list%definition}
\includepdfset{global options%keyvals}
\threadinfodict#*
\AddToSurvey#*

#keyvals:\includepdf,includepdfmerge,\includepdfset
pages={%<page range%>}
nup=%<xnup%>x%<ynup%>
landscape#true,false
delta=%<delx%> %<dely%>
deltax=%<delx%>
deltay=%<dely%>
offset=%<offx%> %<offy%>
frame#true,false
column#true,false
columnstrict#true,false
openright#true,false
openrighteach#true,false
pagecommand=%<code%>
turn#true,false
noautoscale#true,false
fitpaper#true,false
reflect#true,false
reflect*#true,false
signature=%<size%>
signature*=%<size%>
booklet#true,false
picturecommand=%<code%>
picturecommand*=%<code%>
pagetemplate=%<page number%>
templatesize={%<width%>}{%<height%>}
rotateoversize#true,false
doublepages#true,false
doublepagestwist#true,false
doublepagestwistodd#true,false
doublepagestwist*#true,false
doublepagestwistodd*#true,false
duplicatepages=%<integer%>
lastpage=%<page number%>
link#true,false
linkname=%<default linkname%>
thread#true,false
threadname=%<name%>
linktodoc#true,false
linkfit=#Fit,FitH,FitV,FitB,FitBH,FitBV,Region
linktodocfit=
newwindow#true,false
linkfilename=%<name%>
addtotoc={%<page num,section,level,heading,label%>}
addtolist={%<page num,type,heading,label%>}
survey#true,false
survey-nolink#true,false
xr-prefix=%<prefix%>
# options passed to \includegraphics
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
