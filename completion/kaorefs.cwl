# kaorefs package
# Matthew Bertucci 2022/05/26 for v0.9.8

#include:amsthm
#include:varioref
#include:hyperref
#include:cleveref

#keyvals:\usepackage/kaorefs#c
# options passed to varioref
afrikaans
american
arabic
austrian
naustrian
basque
bahasam
brazil
breton
bulgarian
catalan
croatian
czech
danish
dutch
english
esperanto
finnish
french
galician
german
ngerman
greek
icelandic
italian
japanese
magyar
norsk
nynorsk
polish
portuges
romanian
russian
slovak
slovene
spanish
swedish
turkish
ukrainian
francais
germanb
draft
final
space
nospace
# options passed to hyperref
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
linkbordercolor=#%color
linkcolor=#%color
linkfileprefix=%<prefix%>
linktoc=#section,page,all,none
linktocpage#true,false
luatex
menubordercolor=#%color
menucolor=#%color
nativepdf
naturalnames#true,false
nesting#true,false
next-anchor=%<anchor name%>
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
pdfmark
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
unicode#true,false
urlbordercolor=#%color
urlcolor=#%color
verbose#true,false
vtex
vtexpdfmark
xetex
# options passed to cleveref
poorman
sort
compress
sort&compress
nosort
capitalise
capitalize
nameinlink
noabbrev
english
german
ngerman
dutch
french
spanish
italian
russian
ukrainian
norsk
danish
esperanto
swedish
brazilian
catalan
#endkeyvals

\chapternameshort#*
\sectionname#*
\sectionnameshort#*
\subsectionname#*
\subsectionnameplural#*
\subsectionnameshort#*
\figurenameshort#*
\tablenameshort#*
\eqname#*
\eqnameshort#*
\defname#*
\assumname#*
\thmname#*
\propname#*
\lemmaname#*
\remarkname#*
\examplename#*
\exercisename#*

# defines label page:<label> etc. so workaround used
\labpage{pagelabel%specialDef}#s#%kaopagelabel
\labpart{partlabel%specialDef}#s#%kaopartlabel
\labch{chlabel%specialDef}#s#%kaochapterlabel
\labsec{seclabel%specialDef}#s#%kaosectionlabel
\labsubsec{subseclabel%specialDef}#s#%kaosubsectionlabel
\labfig{figlabel%specialDef}#s#%kaofigurelabel
\labtab{tablabel%specialDef}#s#%kaotablelabel
\labeq{eqlabel%specialDef}#s#%kaoequationlabel
\labdef{deflabel%specialDef}#s#%kaodefinitionlabel
\labassum{assumlabel%specialDef}#s#%kaoassumptionlabel
\labthm{thmlabel%specialDef}#s#%kaotheoremlabel
\labprop{proplabel%specialDef}#s#%kaopropositionlabel
\lablemma{lemmalabel%specialDef}#s#%kaolemmalabel
\labremark{remarklabel%specialDef}#s#%kaoremarklabel
\labexample{examplelabel%specialDef}#s#%kaoexamplelabel
\labexercise{exerciselabel%specialDef}#s#%kaoexerciselabel

\refpage{pagelabel%keyvals}
\vrefpage{pagelabel%keyvals}
#keyvals:\refpage#c,\vrefpage#c
%kaopagelabel
#endkeyvals

\arefpart{partlabel%keyvals}
\avrefpart{partlabel%keyvals}
\refpart{partlabel%keyvals}
\vrefpart{partlabel%keyvals}
\nrefpart{partlabel%keyvals}
\frefpart{partlabel%keyvals}
#keyvals:\arefpart#c,\avrefpart#c,\refpart#c,\vrefpart#c,\nrefpart#c,\frefpart#c
%kaopartlabel
#endkeyvals

\refchshort{chlabel%keyvals}
\refch{chlabel%keyvals}
\vrefch{chlabel%keyvals}
\nrefch{chlabel%keyvals}
\frefch{chlabel%keyvals}
#keyvals:\refchshort#c,\refch#c,\vrefch#c,\nrefch#c,\frefch#c
%kaochapterlabel
#endkeyvals

\refsecshort{seclabel%keyvals}
\refsec{seclabel%keyvals}
\vrefsec{seclabel%keyvals}
\nrefsec{seclabel%keyvals}
\frefsec{seclabel%keyvals}
#keyvals:\refsecshort#c,\refsec#c,\vrefsec#c,\nrefsec#c,\frefsec#c
%kaosectionlabel
#endkeyvals

\refsubsecshort{subseclabel%keyvals}
\refsubsec{subseclabel%keyvals}
\vrefsubsec{subseclabel%keyvals}
\nrefsubsec{subseclabel%keyvals}
\frefsubsec{subseclabel%keyvals}
#keyvals:\refsubsecshort#c,\refsubsec#c,\vrefsubsec#c,\nrefsubsec#c,\frefsubsec#c
%kaosubsectionlabel
#endkeyvals

\reffigshort{figlabel%keyvals}
\reffig{figlabel%keyvals}
\vreffig{figlabel%keyvals}
#keyvals:\reffigshort#c,\reffig#c,\vreffig#c
%kaofigurelabel
#endkeyvals

\reftab{tablabel%keyvals}
\vreftab{tablabel%keyvals}
#keyvals:\reftab#c,\vreftab#c
%kaotablelabel
#endkeyvals

\refeqshort{eqlabel%keyvals}
\refeq{eqlabel%keyvals}
\vrefeq{eqlabel%keyvals}
#keyvals:\refeqshort#c,\refeq#c,\vrefeq#c
%kaoequationlabel
#endkeyvals

\refdef{deflabel%keyvals}
\vrefdef{deflabel%keyvals}
#keyvals:\refdef#c,\vrefdef#c
%kaodefinitionlabel
#endkeyvals

\refassum{assumlabel%keyvals}
\vrefassum{assumlabel%keyvals}
#keyvals:\refassum#c,\vrefassum#c
%kaoassumptionlabel
#endkeyvals

\refthm{thmlabel%keyvals}
\vrefthm{thmlabel%keyvals}
#keyvals:\refthm#c,\vrefthem#c
%kaotheoremlabel
#endkeyvals

\refprop{proplabel%keyvals}
\vrefprop{proplabel%keyvals}
#keyvals:\refprop#c,\vrefprop#c
%kaopropositionlabel
#endkeyvals

\reflemma{lemmalabel%keyvals}
\vreflemma{lemmalabel%keyvals}
#keyvals:\reflemma#c,\vreflemma#c
%kaolemmalabel
#endkeyvals

\refremark{remarklabel%keyvals}
\vrefremark{remarklabel%keyvals}
#keyvals:\refremark#c,\vrefremark#c
%kaoremarklabel
#endkeyvals

\refexample{examplelabel%keyvals}
\vrefexample{examplelabel%keyvals}
#keyvals:\refexample#c,\vrefexample#c
%kaoexamplelabel
#endkeyvals

\refexercise{exerciselabel%keyvals}
\vrefexercise{exerciselabel%keyvals}
#keyvals:\refexercise#c,\vrefexercise#c
%kaoexerciselabel
#endkeyvals

\oldvpageref{label}#Sr

# from options passed to hyperref
#ifOption:backref
#include:backref
#endif
#ifOption:backref=section
#include:backref
#endif
#ifOption:backref=slide
#include:backref
#endif
#ifOption:backref=page
#include:backref
#endif
#ifOption:pagebackref
#include:backref
#endif
#ifOption:pagebackref=true
#include:backref
#endif

#ifOption:colorlinks
#include:color
#endif
#ifOption:colorlinks=true
#include:color
#endif

#ifOption:destlabel
\HyperDestRename{destination}{newname}
#endif
#ifOption:destlabel=true
\HyperDestRename{destination}{newname}
#endif

#ifOption:hyperindex
\hyperindexformat{arg1}{arg2}#*
#endif
#ifOption:hyperindex=true
\hyperindexformat{arg1}{arg2}#*
#endif




