# caption3 package
# Matthew Bertucci 2022/05/24 for v2.3b

#include:keyval

\captionsetup[float type]{options%keyvals}
\captionsetup{options%keyvals}
\captionsetup*[float type]{options%keyvals}#*
\captionsetup*{options%keyvals}#*
\DeclareCaptionStyle{name%specialDef}[additional options]{options%keyvals}#s#%captionstyle
\DeclareCaptionStyle{name%specialDef}{options%keyvals}#s#%captionstyle

#keyvals:\captionsetup#c,\captionsetup*#c,\usepackage/caption#c,\DeclareCaptionStyle#c
aboveskip=##L
belowskip=##L
box=#empty,none,parbox,colorbox
boxcolor=#%color
boxsep=##L
calcmargin*=##L
calcmargin=##L
calcwidth*=##L
calcwidth=##L
debug
figurename=%<name%>
figureposition=#top,above,bottom,below,auto
figurewithin=%<counter%>
figurewithout
font+=#scriptsize,footnotesize,small,normalsize,large,Large,LARGE,huge,Huge,smaller,larger,none,normalfont,up,it,sl,sc,md,bf,rm,sf,tt,singlespacing,onehalfspacing,doublespacing,{stretch=%<factor%>},normalcolor,{color=%<color%>},normal,{hypersetup=%<options%>},sansmath
font=#scriptsize,footnotesize,small,normalsize,large,Large,LARGE,huge,Huge,smaller,larger,none,normalfont,up,it,sl,sc,md,bf,rm,sf,tt,singlespacing,onehalfspacing,doublespacing,{stretch=%<factor%>},normalcolor,{color=%<color%>},normal,{hypersetup=%<options%>},sansmath
format=#plain,hang
hangindent=##L
indention=##L
justification=#justified,centering,centerlast,centerfirst,raggedright,raggedleft,Justified,Centering,RaggedRight,RaggedLeft
labelfont+=#scriptsize,footnotesize,small,normalsize,large,Large,LARGE,huge,Huge,smaller,larger,none,normalfont,up,it,sl,sc,md,bf,rm,sf,tt,singlespacing,onehalfspacing,doublespacing,{stretch=%<factor%>},normalcolor,{color=%<color%>},normal,{hypersetup=%<options%>},sansmath
labelfont=#scriptsize,footnotesize,small,normalsize,large,Large,LARGE,huge,Huge,smaller,larger,none,normalfont,up,it,sl,sc,md,bf,rm,sf,tt,singlespacing,onehalfspacing,doublespacing,{stretch=%<factor%>},normalcolor,{color=%<color%>},normal,{hypersetup=%<options%>},sansmath
labelformat=#original,empty,simple,brace,parens,autodot,unnumbered
labelsep=#none,colon,period,space,quad,newline,endash,gobble,gobbletwo
list=#on,off,true,false
listfigurename=%<name%>
listformat=#empty,simple,parens,subsimple,subparens,period,subperiod
listtablename=%<name%>
listtype=%<list type%>
listtype+=%<list type ext%>
lofdepth=%<integer%>
lotdepth=%<integer%>
margin*=##L
margin=##L
maxmargin=##L
minmargin=##L
name=%<name%>
oneside
parbox=#empty,none,parbox,colorbox
parindent=##L
parskip=##L
position=#top,above,bottom,below,auto
singlelinecheck#true,false
skip=##L
strut=#on,off
style=#%captionstyle
style*=#%captionstyle
tablename=%<name%>
tableposition=#top,above,bottom,below,auto
tablewithin=%<counter%>
tablewithout
textfont+=#scriptsize,footnotesize,small,normalsize,large,Large,LARGE,huge,Huge,smaller,larger,none,normalfont,up,it,sl,sc,md,bf,rm,sf,tt,singlespacing,onehalfspacing,doublespacing,{stretch=%<factor%>},normalcolor,{color=%<color%>},normal,{hypersetup=%<options%>},sansmath
textfont=#scriptsize,footnotesize,small,normalsize,large,Large,LARGE,huge,Huge,smaller,larger,none,normalfont,up,it,sl,sc,md,bf,rm,sf,tt,singlespacing,onehalfspacing,doublespacing,{stretch=%<factor%>},normalcolor,{color=%<color%>},normal,{hypersetup=%<options%>},sansmath
textformat=#empty,simple,period
twoside#true,false
width*=##L
width=##L
within=%<counter%>
without
#endkeyvals

\clearcaptionsetup[option%keyvals]{float type}
\clearcaptionsetup{float type}
\clearcaptionsetup*[option%keyvals]{float type}#*
\clearcaptionsetup*{float type}#*
\clearcaptionsetup*[option%keyvals]{float type}#*

#keyvals:\clearcaptionsetup#c,\clearcaptionsetup*#c
aboveskip
belowskip
box
boxcolor
boxsep
calcmargin
calcmargin*
calcwidth
calcwidth*
figurename
figureposition
figurewithin
figurewithout
font
font+
format
hangindent
indention
justification
labelfont
labelfont+
labelformat
labelsep
list
listfigurename
listformat
listtablename
listtype
listtype+
lofdepth
lotdepth
margin
margin*
maxmargin
minmargin
name
oneside
parbox
parindent
parskip
position
singlelinecheck
skip
strut
style
style*
subtype
subtype*
tablename
tableposition
tablewithin
tablewithout
textfont
textfont+
textformat
twoside
type
type*
width
width*
within
without
#endkeyvals

\centerfirst
\centerlast
\showcaptionsetup{float type}
\bothIfFirst{first arg}{second arg}
\bothIfSecond{first arg}{second arg}

\DeclareCaptionFont{name}{code}
\DeclareCaptionFormat{name}{code}
\DeclareCaptionFormat*{name}{code}
\DeclareCaptionJustification{name}{code}
\DeclareCaptionLabelFormat{name}{code}
\DeclareCaptionLabelSeparator{name}{code}
\DeclareCaptionLabelSeparator*{name}{code}
\DeclareCaptionListFormat{name}{code}
\DeclareCaptionTextFormat{name}{code}
\DeclareCaptionSubType{type}
\DeclareCaptionSubType[numbering scheme]{type}
\DeclareCaptionSubType*{type}
\DeclareCaptionSubType*[numbering scheme]{type}

\AfterCaptionPackage{code}#*
\AtBeginCaption{code}#*
\AtCaptionPackage{code}#*
\AtEndCaption{code}#*
\DeclareCaptionOption{name}{code}#*
\DeclareCaptionOption*{name}{code}#*
\DeclareCaptionOptionNoValue{name}{code}#*
\DeclareCaptionOptionNoValue*{name}{code}#*
\SetCaptionDefault{option}{default}#*
\SetCaptionDefault*{option}{default}#*
\SetCaptionFallback{option}{fallback value}#*
\captionfont#*
\captionlabelfont#*
\captiontextfont#*
\captionmargin#*
\captionsize#*

# not documented
\DeclareCaptionType[options%keyvals]{envname}#*N
\DeclareCaptionType{envname}#*N
\DeclareCaptionBox{name}{code}#*
\DeclareCaptionLength{name}{length}#*
\DeclareCaptionSinglelinecheck{name}{code}#*
\ForEachCaptionSubType{subtype list}{code}#*
\ForEachCaptionType{type list}{code}#*
\IfCaptionOptionCheck{true code}{false code}#*
\captionnewline#*
\DeclareCaptionPosition{name}{code}
\DeclareCaptionAutoPosition#*
\captionlisttype#*
\ifsinglelinecaption#*
\singlelinecaptionfalse#*
\singlelinecaptiontrue#*
\AtCaptionSingleLineCheck{code}#*

#keyvals:\DeclareCaptionType
fileext=%<file extension%>
listname=%<list name%>
name=%<name%>
placement=%<combination of htbp%>
within=%<<counter> or none%>
chapterlistsgaps=#on,off
without
planb#true,false
planb-fileext=%<file extension%>
#endkeyvals
