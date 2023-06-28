# europasscv class
# Matthew Bertucci 2022/07/24 for v2020-10-31

#include:lastpage
#include:iftex
#include:inputenc
#include:fontenc
# loads T1 option of fontenc
#include:array
#include:fancyhdr
#include:xcolor
#include:url
#include:soul
#include:setspace
#include:geometry
#include:textcomp
#include:enumitem
#include:hyperref
#include:colortbl
#include:graphicx
#include:substr
#include:keyval
#include:xstring
#include:xifthen

#keyvals:\documentclass/europasscv#c
english
italian
spanish
french
danish
german
finnish
portuguese
swedish
norsk
dutch
catalan
polish
hungarian
estonian
icelandic
lithuanian
czech
slovak
latvian
slovenian
romanian
maltese
bulgarian
greek
galician
serbian
turkish
narrow
bigfont
black
nologo
notitle
nototpages
nodocument
debug
# options passed to article class
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

#ifOption:debug
#include:showframe
#endif

\begin{europasscv}
\end{europasscv}
\begin{ecvitemize}
\end{ecvitemize}
\begin{ecvenumerate}
\end{ecvenumerate}

\convertstring{arg}#*
\difflength#*
\ecladdressee[vspace%l]{name}{organization}{address}{city}
\ecladdressee{name}{organization}{address}{city}
\eclcitydatesubject[vspace%l]{city}{date}{subject%text}
\eclcitydatesubject{city}{date}{subject%text}
\eclclosingsalutation[vspace%l]{text}
\eclclosingsalutation{text}
\eclIconwidth{width}#*
\eclitem[vspace%l]{text}#*
\eclitem{text}#*
\eclmaincontent[vspace%l]{opening%text}{content%text}{closing%text}
\eclmaincontent{opening%text}{content%text}{closing%text}
\eclopeningsalutation[vspace%l]{text}
\eclopeningsalutation{text}
\eclpersonalinfo
\eclpersonalinfo[vspace%l]
\eclsignature
\eclsignature[imagefile]#g
\eclsignature[imagefile][name]#g
\ecvaddress{address}
\ecvBasic
\ecvbigitem[vspace%l]{left%text}{right%text}
\ecvbigitem{left%text}{right%text}
\ecvblueitem[vspace%l]{left%text}{right%text}
\ecvblueitem{left%text}{right%text}
\ecvbluenormalstyle{text}#*
\ecvbluestyle{text}#*
\ecvbullet#*
\ecvcoloredtitle
\ecvColSep{sep}#*
\ecvcurrvitae
\ecvdateofbirth{date%text}
\ecvdigitalcompetence{info-processing}{communication}{content-creation}{safety}{prob-solving}
\ecvemail{email%URL}#U
\ecvExtraRowHeight{height}#*
\ecvfax{number}
\ecvfont{font}
\ecvfootername{name}
\ecvfootnote{text}
\ecvgender{gender%text}
\ecvgithubpage{URL}#U
\ecvgitlabpage{URL}#U
\ecvgitpage{URL}#U
\ecvhighlight{text}
\ecvhighlightcell{text}
\ecvhomepage{URL}#U
\ecvim{service}{username}
\ecvIndependent
\ecvitem[vspace%l]{left%text}{right%text}
\ecvitem{left%text}{right%text}
\ecvlangrow[vspace%l]{language}{listening}{reading}{speaking-interaction}{speaking-production}{writing}{width}#*
\ecvlangrow{language}{listening}{reading}{speaking-interaction}{speaking-production}{writing}{width}#*
\ecvlanguage[vspace%l]{language}{listening}{reading}{speaking-interaction}{speaking-production}{writing}
\ecvlanguage{language}{listening}{reading}{speaking-interaction}{speaking-production}{writing}
\ecvlanguagecertificate{certificate%text}
\ecvlanguagefooter
\ecvlanguagefooter[vspace%l]
\ecvlanguageheader
\ecvlanguageheader[vspace%l]
\ecvlargenormalstyle{text}#*
\ecvLargenormalstyle{text}#*
\ecvlastlanguage[vspace%l]{language}{listening}{reading}{speaking-interaction}{speaking-production}{writing}
\ecvlastlanguage{language}{listening}{reading}{speaking-interaction}{speaking-production}{writing}
\ecvLeftColumnWidth{width}#*
\ecvlinkedinpage{URL}#U
\ecvLogoOffset{offset}#*
\ecvLogoWidth{width}#*
\ecvmobile{number}
\ecvmothertongue[vspace%l]{language}
\ecvmothertongue{language}
\ecvname{name}
\ecvnationality{nationality%text}
\ecvNoHorRule#*
\ecvorcid[options%keyvals]{ORCID}
\ecvorcid{ORCID}
\ecvpage{number}#*
\ecvpersonalinfo
\ecvpersonalinfo[vspace%l]
\ecvpicture[options%keyvals]{imagefile}#g
\ecvpicture{imagefile}#g
\ecvpictureleft[options%keyvals]{imagefile}#g
\ecvpictureleft{imagefile}#g
\ecvpictureright[options%keyvals]{imagefile}#g
\ecvpictureright{imagefile}#g
\ecvProficient
\ecvRuleWidth{width}#*
\ecvsection[vspace%l]{title}#L2
\ecvsection{title}#L2
\ecvsectionstyle{text}#*
\ecvtelephone{number}
\ecvtitle[vspace%l]{left%text}{right%text}
\ecvtitle{left%text}{right%text}
\ecvTitleKern{kern}#*
\ecvtitlelevel[vspace%l]{left%text}{right%text}{degree level}
\ecvtitlelevel{left%text}{right%text}{degree level}
\ecvtitlestyle{text}#*
\ecvupdatecurrentskip{arg1}{arg2}#*
\ecvWithHorRule#*
\ecvworkphone{number}
\makesub{arg}#*
\newecvitemize{envname}{orig envname}#*N
\processlinks{arg}#*
\readwords#*
\selectecvfont#*
\toemail{arg}#*
\tourl{arg}#*

#keyvals:\ecvorcid
label
link
#endkeyvals

#keyvals:\ecvpictureleft,\ecvpictureright,\ecvpicture
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

ecvhighlightcellcolor#B
ecvhighlightcolor#B
ecvlanglinkcolor#B
ecvrulecolor#B
ecvsectioncolor#B
ecvtablebordercolor#B
ecvtextcolor#B

# deprecated
\ecvAOne#S
\ecvATwo#S
\ecvBOne#S
\ecvBTwo#S
\ecvCEF{arg1}{arg2}#S
\ecvCOne#S
\ecvCTwo#S
\ecvfirstname{arg}#S
\ecvlastname{arg}#S

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