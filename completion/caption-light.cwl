# caption-light package
# Matthew Bertucci 2022/05/24 for v1.0a

#include:caption3

# options defined by caption3 package
#keyvals:\usepackage/caption-light#c
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

# options defined by caption-light package
#keyvals:\captionsetup#c,\captionsetup*#c,\usepackage/caption-light#c,\DeclareCaptionStyle#c
type=%<float type%>
type*=%<float type%>
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

\caption*{heading%text}
\captionof{float type}[list entry]{heading%text}
\captionof{float type}{heading%text}
\captionof*{float type}{heading%text}
\setcaptiontype{float type}
\setcaptiontype*{float type}