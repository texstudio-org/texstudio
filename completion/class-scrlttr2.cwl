# mode: koma letter class (scrlttr2)
# dani/2006-02-21
# Matthew Bertucci updated 2023/04/17 for v3.39

#include:scrkbase
#include:typearea
#include:scrlogo

#keyvals:\KOMAoptions#c
draft=#true,on,yes,false,off,no
overfullrule=#true,on,yes,false,off,no
fontsize=##L
foldmarks=%<setting%>
firsthead=#true,on,yes,false,off,no
fromalign=#center,centered,middle,false,no,off,left,locationleft,leftlocation,locationright,rightlocation,location,right
fromrule=#afteraddress,below,on,true,yes,aftername,false,no,off
symbolicnames=#true,on,yes,false,off,no,marvosym,fontawesome,awesome
fromphone=#true,on,yes,false,off,no
frommobilephone=#true,on,yes,false,off,no
fromfax=#true,on,yes,false,off,no
fromemail=#true,on,yes,false,off,no
fromurl=#true,on,yes,false,off,no
fromlogo=#true,on,yes,false,off,no
addrfield=#backgroundimage,PPbackgroundimage,PPBackgroundImage,PPBackGroundImage,ppbackgroundimage,ppBackgroundImage,ppBackGroundImage,false,off,no,image,Image,PPimage,PPImage,ppimage,ppImage,PP,pp,PPexplicite,PPExplicite,ppexplicite,ppExplicite,topaligned,alignedtop,true,on,yes
backaddress=#true,on,yes,false,off,no,underlined,plain
priority=#false,off,no,manual,B,b,economy,Economy,ECONOMY,B-ECONOMY,B-Economy,b-economy,A,a,priority,Priority,PRIORITY,A-PRIORITY,A-Priority,a-priority
locfield=#narrow,wide
numericaldate=#true,on,yes,false,off,no
refline=#dateleft,dateright,narrow,nodate,wide
subject=#afteropening,beforeopening,centered,left,right,titled,underlined,untitled
enlargefirstpage=#true,on,yes,false,off,no
firstfoot=#true,on,yes,false,off,no
parskip=#false,off,no,full,true,yes,full-,full+,full*,half,half-,half+,half*,never
pagenumber=#bot,foot,botcenter,botcentered,botmittle,footcenter,footcentered,footmiddle,botleft,footleft,botright,footright,center,centered,middle,false,no,off,head,top,headcenter,headcentered,headmiddle,topcenter,topcentered,topmiddle,headleft,topleft,headright,topright,left,right
cleardoublepage=#empty,headings,myheadings,plain,current
footnotes=#multiple,nomultiple
#endkeyvals

\addrchar{initial letter}
\addrentry{last name}{first name}{address}{phone}{F1}{F2}{F3}{F4}{key%plain}
\addtolengthplength[factor]{length}{pseudo-length%keyvals}
\addtolengthplength{length}{pseudo-length%keyvals}
\addtoplength[factor]{pseudo-length%keyvals}{value}
\addtoplength{pseudo-length%keyvals}{value}
\addtoreffields{name}
\AtBeginLetter{code}#*
\AtEndLetter{code}#*
\bankname#*
\begin{addmargin*}[inner indent%l]{indent%l}
\begin{addmargin*}{indent%l}
\begin{addmargin}[left indent%l]{indent%l}
\begin{addmargin}{indent%l}
\begin{labeling}[delimiter]{widest pattern}
\begin{labeling}{widest pattern}
\begin{letter}[options%keyvals]{recipient}
\begin{letter}{recipient}
\cc{distribution list%text}
\ccname#*
\ClassName#*
\cleardoubleemptypage
\cleardoubleevenemptypage
\cleardoubleevenpage
\cleardoubleevenpageusingstyle{pagestyle%keyvals}
\cleardoubleevenplainpage
\cleardoubleevenstandardpage
\cleardoubleoddemptypage
\cleardoubleoddpage
\cleardoubleoddpageusingstyle{pagestyle%keyvals}
\cleardoubleoddplainpage
\cleardoubleoddstandardpage
\cleardoublepageusingstyle{pagestyle%keyvals}
\cleardoubleplainpage
\cleardoublestandardpage
\closing{concluding text%text}
\customername#*
\datename#*
\defaultreffields
\deffootnote[mark width%l]{indent%l}{parindent%l}{definition}#*
\deffootnote{indent%l}{parindent%l}{definition}#*
\deffootnotemark{definition}#*
\descfont#*
\emailname#*
\encl{enclosures%text}
\enclname#*
\end{addmargin*}
\end{addmargin}
\end{labeling}
\end{letter}
\faxname#*
\footfont#*
\foreachemptykomavar{list of variables}{command}#*
\foreachkomavar{list of variables}{command}#*
\foreachkomavarifempty{list of variables}{then code}{else code}#*
\foreachnonemptykomavar{list of variables}{command}#*
\headfont#*
\headfromname#*
\headtoname#*
\Ifkomavar{name}{then code}{else code}#*
\Ifkomavarempty*{name}{true}{false}#*
\Ifkomavarempty{name}{true}{false}#*
\Ifplength{pseudo-length}{then code}{else code}#*
\Ifthispageodd{true code}{false code}#*
\ifthispagewasodd#*
\invoicename#*
\KOMAClassFileName#*
\KOMAClassName#*
\labelinglabel{arg}#*
\labelitemfont#*
\letterlastpage#*
\LetterOptionNeedsPapersize{option name}{paper size}
\letterpagemark#*
\letterpagestyle#*
\LoadLetterOption{name%keyvals}
\LoadLetterOptions{list of names%keyvals}
\marginline{margin note%text}
\maybesffamily
\mobilephonename#*
\multfootsep#*
\multiplefootnotemarker#*
\multiplefootnoteseparator#*
\myrefname#*
\newkomavar*[description]{name}
\newkomavar*{name}
\newkomavar[description]{name}
\newkomavar{name}
\newplength{name}#*
\opening{salutation%text}
\pagename#*
\phonename#*
\pnumfont#*
\ps
\raggedfootnote#*
\raggedsignature#*
\raggedsubject#*
\removereffields
\setfootnoterule[thickness]{length}#*
\setfootnoterule{length}#*
\setkomavar*{name%keyvals}{description%text}
\setkomavar*{name%keyvals}{description%text}
\setkomavar{name%keyvals}[description%text]{content%text}
\setkomavar{name%keyvals}{content%text}
\setlengthtoplength[factor]{length}{pseudo-length%keyvals}
\setlengthtoplength{length}{pseudo-length%keyvals}
\setparsizes{indent%l}{distance%l}{last-line end space}#*
\setplength[factor]{pseudo-length%keyvals}{value}
\setplength{pseudo-length%keyvals}{value}
\setplengthtodepth[factor]{pseudo-length%keyvals}{content}
\setplengthtodepth{pseudo-length%keyvals}{content}
\setplengthtoheight[factor]{pseudo-length%keyvals}{content}
\setplengthtoheight{pseudo-length%keyvals}{content}
\setplengthtototalheight[factor]{pseudo-length%keyvals}{content}
\setplengthtototalheight{pseudo-length%keyvals}{content}
\setplengthtowidth[factor]{pseudo-length%keyvals}{content}
\setplengthtowidth{pseudo-length%keyvals}{content}
\startbreaks#*
\stopbreaks#*
\stopletter#*
\subjectname#*
\textmaybesf{text}
\thefootnotemark#*
\thisletter#*
\thispagewasoddfalse#*
\thispagewasoddtrue#*
\usekomavar*[command]{name%keyvals}
\usekomavar*{name%keyvals}
\usekomavar[command]{name%keyvals}
\usekomavar{name%keyvals}
\useplength{pseudo-length%keyvals}
\wwwname#*
\yourmailname#*
\yourrefname#*

# if visualize.lco is loaded with \LoadLetterOption or \LoadLetterOptions
\showfields{field list%keyvals}#*
#keyvals:\showfields
test
head
foot
address
location
refline
#endkeyvals
\setshowstyle{style%keyvals}#*
#keyvals:\setshowstyle
frame
rule
edges
#endkeyvals
\edgesize#*
\showenvelope(width,height)(h-offset,v-offset)#*
\showenvelope(width,height)(h-offset,v-offset)[instructions]#*
\showISOenvelope{format%keyvals}#*
\showISOenvelope{format%keyvals}[instructions]#*
#keyvals:\showISOenvelope#c
C4
C5
C5/6
DL
C6
#endkeyvals
\showUScommercial{format%keyvals}#*
\showUScommercial{format%keyvals}[instructions]#*
#keyvals:\showUScommercial#c
9
10
#endkeyvals
\showUScheck#*
\showUScheck[instructions]#*
\unitfactor#*

# remove #*'s if visualize loaded with class option
#ifOption:visualize
#include:eso-pic
\showfields{field list%keyvals}
\setshowstyle{style%keyvals}
\edgesize
\showenvelope(width,height)(h-offset,v-offset)
\showenvelope(width,height)(h-offset,v-offset)[instructions]
\showISOenvelope{format%keyvals}
\showISOenvelope{format%keyvals}[instructions]
\showUScommercial{format%keyvals}
\showUScommercial{format%keyvals}[instructions]
\showUScheck
\showUScheck[instructions]
\unitfactor
#endif

#keyvals:\setkomavar#c,\setkomavar*#c,\usekomavar#c,\usekomavar*#c
addresseeimage
backaddress
backaddressseparator
ccseparator
customer
date
emailseparator
enclseparator
faxseparator
firstfoot
firsthead
fromaddress
frombank
fromemail
fromfax
fromlogo
frommobilephone
fromname
fromphone
fromurl
fromzipcode
invoice
location
myref
nextfoot
nexthead
phoneseparator
place
placeseparator
PPdatamatrix
PPcode
signature
specialmail
subject
subjectseparator
title
toaddress
toname
yourmail
yourref
zipcodeseparator
#endkeyvals

#keyvals:\useplength#c,\setplength#c,\addtoplength#c,\setlengthtoplength#c,\addtolengthplength#c,\setplengthtowidth#c,\setplengthtoheight#c,\setplengthtodepth#c,\setplengthtototalheight#c
backaddrheight
bfoldmarklength
bfoldmarkvpos
firstfoothpos
firstfootvpos
firstfootwidth
firstheadhpos
firstheadvpos
firstheadwidth
foldmarkhpos
foldmarkvpos
fromrulethickness
fromrulewidth
lfoldmarkhpos
lfoldmarklength
locheight
lochpos
locvpos
locwidth
mfoldmarklength
mfoldmarkvpos
pfoldmarklength
PPdatamatrixvskip
PPheadheight
PPheadwidth
refaftervskip
refhpos
refvpos
refwidth
sigbeforevskip
sigindent
specialmailindent
specialmailrightindent
subjectaftervskip
subjectbeforevskip
additional verti
subjectvpos
tfoldmarklength
tfoldmarkvpos
toaddrheight
toaddrhpos
toaddrindent
toaddrvpos
toaddrwidth
#endkeyvals

#keyvals:\setkomafont#c,\addtokomafont#c,\usekomafont#c,\usesizeofkomafont#c,\usefamilyofkomafont#c,\useseriesofkomafont#c,\useshapeofkomafont#c,\useencodingofkomafont#c,\usefontofkomafont#c
addressee
backaddress
descriptionlabel
foldmark
footnote
footnotelabel
footnotereference
footnoterule
fromaddress
fromname
fromrule
itemizelabel
labelinglabel
labelingseparator
labelitemi
labelitemii
labelitemiii
labelitemiv
pagefoot
pagehead
pageheadfoot
pagenumber
pagination
placeanddate
refname
refvalue
specialmail
lettersubject
lettertitle
toaddress
toname
#endkeyvals

#keyvals:\LoadLetterOption#c,\LoadLetterOptions#c
DIN
DINmtext
KakuLL
KOMAold
NF
NipponEH
NipponEL
NipponLH
NipponLL
NipponRL
SN
SNleft
UScommercial9
UScommercial9DW
#endkeyvals

#keyvals:\cleardoublepageusingstyle#c,\cleardoubleoddpageusingstyle#c,\cleardoubleevenpageusingstyle#c
empty
headings
myheadings
plain
#endkeyvals

# deprecated
\adrchar{initial letter}#S
\adrentry{last name}{first name}{address}{phone}{F1}{F2}{comment}{key%plain}#S
\ifkomavar#S
\ifkomavarempty#S
\ifthispageodd#S
\firsthead#S
\firstfoot#S
\nexthead#S
\nextfoot#S

## makelabels v1.0 (makelabels.lco) ##
#ifOption:makelabels
\makelabels
\selectlabeltype{type%keyvals}
\selectlabeltype[integer]{type%keyvals}
#keyvals:\selectlabeltype#c
avery_5162
#endkeyvals
\startlabels#*
\mlabel{arg1}{arg2}#*
\mlabeltype{integer}{type}#*
#endif

## scrlttr2copy v0.3a (copy.lco) ##
#ifOption:copy
#include:xcolor
#include:graphicx
\LetterCopyMarker#*
\copyname#*
#endif
