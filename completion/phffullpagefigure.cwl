# phffullpagefigure package
# Matthew Bertucci 10/6/2021 for v0.7.0

#include:etoolbox
#include:ifoddpage
#include:afterpage
#include:placeins
#include:pdfpages

\begin{fullpagefigure}
\begin{fullpagefigure}[position%keyvals]
\end{fullpagefigure}

\figcontent{code}#/fullpagefigure
\figpdf{file}#/fullpagefigure
\figpdf[options%keyvals]{file}#/fullpagefigure

#keyvals:\figpdf
pages=
nup=%<xnup%>x%<ynup%>
landscape#true,false
delta=%<delx%> %<dely%>
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
threadname=
linktodoc#true,false
linkfit=
linktodocfit=
newwindow#true,false
linkfilename=
addtotoc=
addtolist=
survey#true,false
survey-nolink#true,false
xr-prefix=
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
#endkeyvals

\figpageside{option%keyvals}#/fullpagefigure

#keyvals:\figpageside
even
odd
#endkeyvals

\figplacement{position%keyvals}#/fullpagefigure

#keyvals:\figplacement,\begin{fullpagefigure}
b
t
p
#endkeyvals

\figcapmaxheight{length}#*/fullpagefigure
\fullpagefigurecaptionfmt#*
\FlushAllFullPageFigures
\FlushAllFullPageFigures[clear cmd]
\phffpfFloatBarrier#*