# subcaption package
# Axel Sommerfeldt 04/16/2013
# muzimuzhi/1 Sep 2019, subcaption v1.2
# muzimuzhi/1 Nov 2019, subcaption v1.3
# Matthew Bertucci 12 March 2023, subcaption v1.6
# URL: https://ctan.org/pkg/subcaption

#include:caption

#keyvals:\usepackage/subcaption#c
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

\subcaptionsetup[float type]{options%keyvals}
\subcaptionsetup{options%keyvals}
\subcaptionsetup*[float type]{options%keyvals}#*
\subcaptionsetup*{options%keyvals}#*

#keyvals:\captionsetup#c,\captionsetup*#c,\usepackage/subcaption#c,\DeclareCaptionStyle#c,\subcaptionsetup#c,\subcaptionsetup*#c
# options added or changed in subcaption package
labelformat=#original,empty,simple,brace,parens,autodot,unnumbered,subsimple,subparens
subrefformat=#original,empty,simple,brace,parens,autodot,unnumbered,subsimple,subparens
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

\subcaptionbox{heading%text}{content%text}
\subcaptionbox{heading%text}[width]{content%text}
\subcaptionbox{heading%text}[width][inner-pos]{content%text}
\subcaptionbox[list entry]{heading%text}{content%text}
\subcaptionbox[list entry]{heading%text}[width]{content%text}
\subcaptionbox[list entry]{heading%text}[width][inner-pos]{content%text}
\subcaptionbox*{heading%text}{content%text}
\subcaptionbox*{heading%text}[width]{content%text}
\subcaptionbox*{heading%text}[width][inner-pos]{content%text}

\begin{subfigure}[position][height][inner pos]{width}
\begin{subfigure}[position][height]{width}
\begin{subfigure}[position]{width}
\begin{subfigure}{width}
\begin{subtable}[position][height][inner pos]{width}
\begin{subtable}[position][height]{width}
\begin{subtable}[position]{width}
\begin{subtable}{width}
\end{subfigure}
\end{subtable}

\subcaption{heading%text}
\subcaption[list entry]{heading%text}
\subcaption*{heading%text}

\subref{key}#r
\subref*{key}#r
\thesubfigure
\thesubtable

\phantomsubcaption

\subfloat[list entry][sub-caption]{body%text}
\subfloat[sub-caption]{body%text}
\subfloat{body%text}

\subcaptionlistentry{list entry}
\subcaptiontext{text}
\subcaptiontext[number]{text}
\subcaptiontext*{text}
\subcaptiontext*[number]{text}

\begin{subcaptionblock}{width}
\begin{subcaptionblock}[position]{width}
\begin{subcaptionblock}[position][height]{width}
\begin{subcaptionblock}[position][height][inner pos]{width}#*
\end{subcaptionblock}
\begin{subcaptiongroup}
\end{subcaptiongroup}
\begin{subcaptiongroup*}
\end{subcaptiongroup*}
