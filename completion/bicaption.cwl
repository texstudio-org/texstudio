# bicaption package
# Matthew Bertucci 2023/03/12 for v1.6

#include:caption

#keyvals:\usepackage/bicaption#c
# options defined in caption3 package
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
# options defined in caption package
list-entry=#default,list-entry,entry
hypcap#true,false
hypcapspace=##L
type=%<float type%>
type*=%<float type%>
subtype=%<float type%>
subtype*=%<float type%>
compatibility#true,false
config=%<file name%>
#endkeyvals

\captionsetup[float type][biling selection]{options%keyvals}
\bicaptionsetup[float type]{lang1 options%keyvals}{lang2 options}
\bicaptionsetup{lang1 options%keyvals}{lang2 options}
\bicaptionsetup*[float type]{lang1 options%keyvals}{lang2 options}#*
\bicaptionsetup*{lang1 options%keyvals}{lang2 options}#*

#keyvals:\captionsetup#c,\captionsetup*#c,\usepackage/bicaption#c,\DeclareCaptionStyle#c,\bicaptionsetup#c,\bicaptionsetup*#c
lang=%<language%>
bi-lang=#both,first,second
bi-slc#true,false
bi-swap#true,false
bi-separator=#none,default,smallskip,medskip,largeskip
#endkeyvals

#ifOption:font=onehalfspacing
#include:setspace
#endif
#ifOption:labelfont=onehalfspacing
#include:setspace
#endif
#ifOption:textfont=onehalfspacing
#include:setspace
#endif
#ifOption:font+=onehalfspacing
#include:setspace
#endif
#ifOption:labelfont+=onehalfspacing
#include:setspace
#endif
#ifOption:textfont+=onehalfspacing
#include:setspace
#endif

#ifOption:font=doublespacing
#include:setspace
#endif
#ifOption:labelfont=doublespacing
#include:setspace
#endif
#ifOption:textfont=doublespacing
#include:setspace
#endif
#ifOption:font+=doublespacing
#include:setspace
#endif
#ifOption:labelfont+=doublespacing
#include:setspace
#endif
#ifOption:textfont+=doublespacing
#include:setspace
#endif

#ifOption:font=sansmath
#include:sansmath
#endif
#ifOption:labelfont=sansmath
#include:sansmath
#endif
#ifOption:textfont=sansmath
#include:sansmath
#endif
#ifOption:font+=sansmath
#include:sansmath
#endif
#ifOption:labelfont+=sansmath
#include:sansmath
#endif
#ifOption:textfont+=sansmath
#include:sansmath
#endif

#ifOption:justification=RaggedRight
#include:ragged2e
#endif
#ifOption:justification=RaggedLeft
#include:ragged2e
#endif

#ifOption:justification=Justified
#include:ragged2e
#endif
#ifOption:justification=Centering
#include:ragged2e
#endif
#ifOption:justification=RaggedRight
#include:ragged2e
#endif
#ifOption:justification=RaggedLeft
#include:ragged2e
#endif

\DeclareBiCaptionSeparator{name}{code}

\bicaption{heading1%text}{heading2%text}
\bicaption[list-entry1]{heading1%text}[list-entry2]{heading2%text}
\bicaption*{heading1%text}{heading2%text}

\bicaptionbox{heading1%text}{heading2%text}{content%text}
\bicaptionbox[list-entry1]{heading1%text}[list-entry2]{heading2%text}{content%text}
\bicaptionbox{heading1%text}{heading2%text}[width][inner-pos]{content%text}
\bicaptionbox[list-entry1]{heading1%text}[list-entry2]{heading2%text}[width][inner-pos]{content%text}
\bicaptionbox*{heading1%text}{heading2%text}{content%text}
\bicaptionbox*{heading1%text}{heading2%text}[width][inner-pos]{content%text}

\bisubcaption{heading1%text}{heading2%text}#*
\bisubcaption[list-entry1]{heading1%text}[list-entry2]{heading2%text}
\bisubcaption*{heading1%text}{heading2%text}

\bisubcaptionbox{heading1%text}{heading2%text}{content%text}
\bisubcaptionbox[list-entry1]{heading1%text}[list-entry2]{heading2%text}{content%text}
\bisubcaptionbox{heading1%text}{heading2%text}[width][inner-pos]{content%text}
\bisubcaptionbox[list-entry1]{heading1%text}[list-entry2]{heading2%text}[width][inner-pos]{content%text}
\bisubcaptionbox*{heading1%text}{heading2%text}{content%text}
\bisubcaptionbox*{heading1%text}{heading2%text}[width][inner-pos]{content%text}

\captionmainlanguage#*
\selectcaptionlanguage{font or list entry}{language}#*

\DeclareCaptionLangOption{name}#*

# compatibility
\DeclareCaptionLanguageOption{name}#S
\subbicaptionbox#S
