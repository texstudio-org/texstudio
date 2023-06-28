# tudapub class
# Matthew Bertucci 2022/08/17 for v3.27

#include:l3keys2e
#include:URspecialopts
#include:class-scrartcl
#include:tudarules
#include:tudafonts
#include:scrlayer-scrpage
#include:geometry
#include:tudacolors
#include:trimclip
#include:graphicx
#include:hyperref

#keyvals:\documentclass/tudapub#c
class=#article,report,book
color=#%color
accentcolor=#%color
textaccentcolor=#%color
identbarcolor=#%color
marginpar
custommargins=#true,false,geometry
fontsize=##L
ruledheaders=#false,none,chapter,section,true,all
type=#publication,thesis,intern
headline=#true,false,automark
colorback=#true,false,title,body,head
pdfa#true,false
twocolumn#true,false
BCOR=%<Länge%>
logo=#head,body,top,bottom
paper=#a0,a1,a2,a3,a4,a5,a6
IMRAD#true,false
logofile=%<Dateipfad%>
title=#default,small,large
department=mecheng
departmentlogofile=%<Dateipfad%>
BCORtitlepage#true,false
#endkeyvals

#ifOption:class=report
#include:class-scrreprt
#endif
#ifOption:class=scrreprt
#include:class-scrreprt
#endif

#ifOption:class=book
#include:class-scrbook
#endif
#ifOption:class=scrbook
#include:class-scrbook
#endif

#ifOption:pdfa
#include:pdfx
#endif
#ifOption:pdfa=true
#include:pdfx
#endif

#ifOption:department=mecheng
TUDa-Primary1#B
TUDa-Primary2#B
TUDa-Secondary1#B
TUDa-Secondary2#B
TUDa-Secondary3#B
TUDa-Secondary4#B
TUDa-Secondary5#B
TUDa-Secondary6#B
TUDa-Arrow#B
# from tudamecheng.cfg
#include:pgf
\MechEngArrow{Länge}
\MechEngArrow*{Länge}
#endif

\titlegraphic{graphics code}
\titlegraphic*{graphics code}
\addTitleBox{text}
\addTitleBoxLogo{imagefile}#g
\addTitleBoxLogo*{graphics code}

\AddSponsor{logo}
\sponsors{logo code}
\begin{abstract}[language]

\Metadata{keyvals}
#keyvals:\Metadata#c
author=%<name%>
title=%<text%>
subject=%<text%>
date=%<YYYY-MM-DD%>
keywords=%<word1 \sep word2 \sep ...%>
#endkeyvals
\sep

\IMRADlabel{label}

#keyvals:\pagestyle#c,\thispagestyle#c
TUDa.headings
#endkeyvals

\frontmatter
\mainmatter
\backmatter

\SetPaperID{Buchstabe}{tiefgestelle Nummer}

\institution{Einrichtung}#*
\titleimage{graphics code}#*
\authorandname#*

# only available for thesis type (from tudathesis.cfg)
\departmentname#*
\departmentfullname#*
\drtext{text}
\titleintro{text}
\titleaddendum{text}
\author[short name]{name}
\studentID{Matrikelnummer}
\department{Kürzel/Bezeichnung}
\department[Ersatztext]{Kürzel/Bezeichnung}
\department*{Text zwischen Typ und Autor}
\department*[Text für die Box]{Text zwischen Typ und Autor}
\institute{Einrichtung}
\group{Arbeitsgruppe}
\birthplace{Geburtsort}
\reviewer{Name1 \and Name2}
\reviewer[Ersatzbezeichner]{Name1 \and Name2}
\reviewer*{Name1 \and Name2}
\reviewer*[Bezeichner1,Bezeichner2]{Name1 \and Name2}
\examdate{Datum}
\submissiondate{Datum}
\tuprints{keyvals}
\affidavit
\affidavit[keyvals]
\begin{affidavit*}{Überschrift%text}
\begin{affidavit*}[Babel-Sprachoption]{Überschrift%text}
\end{affidavit*}
\AffidavitSignature
\AffidavitSignature[keyvals]
\SignatureBox{text}#*
\SignatureBox[width]{text}#*
\setupReviewName{Ersatzwort für „Gutachten“}
\setupReviewName[num]{Referent}
\setupReviewName*{Bezeicher1,Bezeicher2,...}