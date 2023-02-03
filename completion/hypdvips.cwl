# hypdvips package
# Matthew Bertucci 2/5/2022 for v3.03

#include:atveryend
#include:bookmark
#include:xcolor
#include:xkeyval

#keyvals:\usepackage/hypdvips#c
autoauthor#true,false
autotitle#true,false
detailedbr#true,false
emptypagelabels#true,false
evenboxes#true,false
fish#true,false
flip#true,false
fullbookmarks#true,false
german#true,false
hypertnotes#true,false
JavaScript#true,false
loabr#true,false
lofbr#true,false
lotbr#true,false
Mac#true,false
mirror#true,false
nlwarning#true,false
openmessage#true,false
quadpoints#true,false
showdests#true,false
smallfootnotes#true,false
tocbr#true,false
#endkeyvals

\attachfile{file}
\attachfile[options%keyvals]{file}

#keyvals:\attachfile
anncreated=%<LaTeX time%>
annmodified=%<LaTeX time%>
author=%<author%>
checksum=%<checksum%>
color=%<<r> <g> <b>%>
created=%<date%>
creator=%<creator%>
description=%<text%>
filetype=%<filetype%>
flags=%<postscript integer%>
icon=#graph,pushpin,paperclip,tag
iconfilename=%<file name%>
mimetype=%<mimtype%>
modified=%<date%>
name=%<file name%>
opacity=%<factor%>
overprint#true,false
rect=%<<llx> <lly> <urx> <ury>%>
resourcefork=%<file name%>
size=%<number%>
subject=%<text%>
text=%<text%>
timezone=%<offset%>
#endkeyvals

\bmstyle{level}{style%keyvals}

#keyvals:\bmstyle#c
bold
italic
color={%<<r> <g> <b>%>}
#endkeyvals

\backrefcolor{color}
\embeddedcolor{color}
\footnotecolor{color}
\tablenotecolor{color}

\backrefbordercolor{R G B}
\embeddedbordercolor{R G B}
\footnotebordercolor{R G B}
\tablenotebordercolor{R G B}

\embedfile{file}
\embedfile[options%keyvals]{file}

#keyvals:\embedfile
checksum=%<checksum%>
created=%<date%>
creator=%<creator%>
description=%<text%>
filetype=%<filetype%>
mimetype=%<mimtype%>
modified=%<date%>
name=%<file name%>
resourcefork=%<file name%>
size=%<number%>
#endkeyvals

\evenboxesstring{text%plain}
\file{file}{description}

\goto{text}
\goto[options%keyvals]{text}

#keyvals:\embedfile
dest=%<destination%>
filename=%<file name%>
id=%<id%>
newwindow#true,false
target=
#endkeyvals

\gotoparent{destination}{text}
\listofattachments
\loaformat{ID}{type}{file}{options}#*
\odest{name}{offset%l}
\openaction{action}
\pagelabel{pagelabel}
\pagelabel[page]{pagelabel}
\runattachment{ID}{text}

\currentpoint{linewidth}#*
\debug{warning%text}#*
\point#*
