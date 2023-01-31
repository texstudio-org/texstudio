# attachfile package
# mario 09/06/2007; Matthew Bertucci 9/19/2021 for v1.9
# URL: http://tug.ctan.org/tex-archive/macros/latex/contrib/attachfile/

#include:ifpdf
#include:keyval
#include:calc
#include:color
#include:hyperref

# attachfile passes options to hyperref
#keyvals:\usepackage/attachfile#c
addtopdfcreator=%<text%>
allbordercolors=#%color
allcolors=#%color
anchorcolor=#%color
backref=#section,slide,page,none,false
baseurl=%<URL%>
bookmarks#true,false
bookmarksdepth
bookmarksdepth=%<number%>
bookmarksnumbered#true,false
bookmarksopen#true,false
bookmarksopenlevel=%<level%>
bookmarkstype=
breaklinks#true,false
citebordercolor=#%color
citecolor=#%color
CJKbookmarks#true,false
colorlinks#true,false
customdriver=%<file%>
debug#true,false
destlabel#true,false
draft#true,false
driverfallback=%<driver%>
dvipdfm
dvipdfmx
dvipdfmx-outline-open#true,false
dvips
dvipsone
dviwindo
encap=%<character%>
extension=%<file ext%>
filebordercolor=#%color
filecolor=#%color
final#true,false
frenchlinks#true,false
hidelinks
hyperfigures#true,false
hyperfootnotes#true,false
hyperindex#true,false
hypertex
hypertexnames#true,false
implicit#true,false
latex2html
linkbordercolor=#%color
linkcolor=#%color
linkfileprefix=%<prefix%>
linktoc=#section,page,all,none
linktocpage#true,false
localanchorname#true,false
menubordercolor=#%color
menucolor=#%color
nativepdf#true,false
naturalnames#true,false
nesting#true,false
ocgcolorlinks#true,false
pageanchor#true,false
pagebackref#true,false
pdfa#true,false
pdfauthor=%<author%>
pdfborder=
pdfborderstyle=
pdfcenterwindow#true,false
pdfcreationdate=%<date%>
pdfcreator=%<creator%>
pdfdirection=#L2R,R2L
pdfdisplaydoctitle#true,false
pdfduplex
pdfencoding=#pdfdoc,unicode,auto
pdfescapeform#true,false
pdffitwindow#true,false
pdfhighlight=#/I,/N,/O,/P
pdfinfo={%<info keys%>}
pdfkeywords={%<keyword list%>}
pdflang=%<lang id%>
pdflinkmargin=##L
pdfmark#true,false
pdfmenubar#true,false
pdfmoddate=%<date%>
pdfnewwindow#true,false
pdfnonfullscreenpagemode
pdfnumcopies=%<integer%>
pdfpageduration=
pdfpagelabels#true,false
pdfpagelayout=#SinglePage,OneColumn,TwoColumnLeft,TwoColumnRight,TwoPageLeft,TwoPageRight
pdfpagemode=#FullScreen,UseNone,UseOutlines,UseOC,UseAttachments,UseThumbs
pdfpagescrop=
pdfpagetransition=#Split,Blinds,Box,Wipe,Dissolve,Glitter,R,Fly,Push,Cover,Uncover,Fade
pdfpicktraybypdfsize#true,false
pdfprintarea=#Mediabox,CropBox,BleedBox,TrimBox,ArtBox
pdfprintclip=#Mediabox,CropBox,BleedBox,TrimBox,ArtBox
pdfprintpagerange=
pdfprintscaling=#None,AppDefault
pdfproducer=%<producer%>
pdfremotestartview=#XYZ,Fit,FitH,FitV,FitR,FitB,FitBH,FitBV
pdfstartpage=%<page number%>
pdfstartview=#XYZ,Fit,FitH,FitV,FitR,FitB,FitBH,FitBV
pdfsubject=%<subject%>
pdftex
pdftitle=%<title%>
pdftoolbar#true,false
pdftrapped=#True,False,Unknown
pdfusetitle
pdfversion=%<version%>
pdfview=#XYZ,Fit,FitH,FitV,FitR,FitB,FitBH,FitBV
pdfviewarea=#Mediabox,CropBox,BleedBox,TrimBox,ArtBox
pdfviewclip=#Mediabox,CropBox,BleedBox,TrimBox,ArtBox
pdfwindowui#true,false
plainpages#true,false
ps2pdf
psdextra#true,false
raiselinks#true,false
runbordercolor=#%color
runcolor=#%color
setpagesize#true,false
tex4ht
textures
typexml#true,false
unicode#true,false
urlbordercolor=#%color
urlcolor=#%color
verbose#true,false
vtex
xetex
#endkeyvals

\attachfile{file}
\attachfile[options%keyvals]{file}
\noattachfile
\noattachfile[options%keyvals]
\notextattachfile{text}
\notextattachfile[options%keyvals]{text}
\textattachfile{file}{text}
\textattachfile[options%keyvals]{file}{text}
\attachfilesetup{options%keyvals}

#keyvals:\attachfile,\attachfilesetup,\noattachfile,\notextattachfile,\textattachfile
appearance#true,false
author=%<text%>
color=%<<red> <green> <blue>%>
created=%<PDF date%>
date=%<PDF date%>
description=%<text%>
icon=#Graph,Paperclip,PushPin,Tag
mimetype=%<type/subtype%>
modified=%<PDF date%>
print#true,false
size=%<integer%>
subject=%<text%>
timezone=%<offset%>
zoom#true,false
#endkeyvals
