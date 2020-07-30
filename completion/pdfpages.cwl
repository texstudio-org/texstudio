# pdfpages package
# mario 09/06/2007, Tim Hoffmann 25/02/2017
# muzimuzhi 29 Apr 2020, pdfpages v0.5q
# URL: http://tug.ctan.org/tex-archive/macros/latex/contrib/pdfpages/

#include:eso-pic
#include:atbegshi
#include:pdflscape
#include:graphicx
#include:ifthen
#include:calc
#include:count1to

\includepdf[options%keyvals]{filename}
\includepdf{filename}
\includepdfmerge[options%keyvals]{file-list}
\includepdfmerge{file-list}
\includepdfset{global options%keyvals}
\threadinfodict#*

#keyvals:\includepdf,includepdfmerge,\includepdfset
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
## and all the \includegraphics options
#endkeyvals
