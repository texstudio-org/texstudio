# FUpowerdot class
# Matthew Bertucci 2022/06/03 for v0.02a

#include:class-powerdot
# loads table option of xcolor
#include:fontenc
# loads T1 option of fontenc
#include:babel
# loads ngerman option of babel
#include:pifont
#include:breakurl
#include:graphicx
#include:calc
#include:tabularx
#include:helvet
#include:ragged2e
# loads newcommands option of ragged2e

# passes all options to powerdot class
#keyvals:\documentclass/FUpowerdot#c
mode=#present,print,handout
nohandoutpagebreaks
nohandoutframes
paper=#screen,a4paper,letterpaper,smartboard,169
orient=#landscape,portrait
display=#slides,slidesnotes,notes
size=#8pt,9pt,10pt,11pt,12pt,14pt,17pt,20pt
fleqn
leqno
nopsheader
hlentries#true,false
hlsections#true,false
pauseslide
clock
#endkeyvals

#ifOption:clock
#include:pdfbase
#endif
#ifOption:clock=true
#include:pdfbase
#endif

FUblue#B
FUgreen#B
FUred#B
FUorange#B
FUgray#B

\inst{text}
\framelogo{graphics code}
\insertframelogo#*
\titlelogo{graphics code}
\inserttitlelogo#*
\fachbereich{fachbereich}
\insertfachbereich#*
\subtitle{text}
\insertsubtitle#*
\institute{institute}
\insertinstitute#*
\titlegraphic{imagefile}#g
\titlegraphic[options%keyvals]{imagefile}#g
\inserttitlegraphic#*

#keyvals:\titlegraphic
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

\begin{titleslide}{title}
\begin{titleslide}[options%keyvals]{title}
\end{titleslide}
\begin{basic}{title}#*
\begin{basic}[options%keyvals]{title}#*
\end{basic}#*
\begin{wideslide}{title}
\begin{wideslide}[options%keyvals]{title}
\end{wideslide}
\begin{slide}{title}
\begin{slide}[options%keyvals]{title}
\end{slide}
\begin{sectionslide}{title}
\begin{sectionslide}[options%keyvals]{title}
\end{sectionslide}
\begin{sectionwideslide}{title}
\begin{sectionwideslide}[options%keyvals]{title}
\end{sectionwideslide}

# from table option of xcolor
#include:colortbl

# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n

# from ngerman option of babel
\captionsngerman#*
\datengerman#*
\extrasngerman#*
\noextrasngerman#*
\dq
\ntosstrue#*
\ntossfalse#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*
\mdqon#*
\mdqoff#*
#repl:"a ä
#repl:"e ë
#repl:"i ï
#repl:"o ö
#repl:"u ü
#repl:"A Ä
#repl:"E Ë
#repl:"I Ï
#repl:"O Ö
#repl:"U Ü
#repl:"s ß
#repl:"z ß
#repl:"S SS
#repl:"Z SZ
#repl:"|
#repl:"= -
#repl:"~ -
#repl:""
#repl:"/ /
#repl:"` „
#repl:"' “
#repl:"< «
#repl:"> »

# from newcommands option of ragged2e
\LaTeXcentering#*
\LaTeXraggedleft#*
\LaTeXraggedright#*
\begin{LaTeXflushleft}#*
\end{LaTeXflushleft}#*
\begin{LaTeXflushleft}#*
\end{LaTeXflushright}#*
\begin{LaTeXcenter}#*
\end{LaTeXcenter}#*
