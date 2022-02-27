# subcaption package
# Axel Sommerfeldt 04/16/2013
# muzimuzhi/1 Sep 2019, subcaption v1.2
# muzimuzhi/1 Nov 2019, subcaption v1.3
# Matthew Bertucci 26 Feb 2022 for v1.5
# URL: https://ctan.org/pkg/subcaption

#include:caption

#keyvals:\usepackage/subcaption#c
format=#plain,hang
indention=##L
labelformat=#original,empty,simple,brace,parens
labelsep=#none,colon,period,space,quad,newline,endash
textformat=#empty,simple,period
justification=#justified,centering,centerlast,centerfirst,raggedright,RaggedRight,raggedleft
singlelinecheck#true,false
font=#scriptsize,footnotesize,small,normalsize,large,Large,normalfont,up,it,sl,sc,md,bf,rm,sf,tt,singlespacing,onehalfspacing,doublespacing,normalcolor,normal
labelfont=#scriptsize,footnotesize,small,normalsize,large,Large,normalfont,up,it,sl,sc,md,bf,rm,sf,tt,singlespacing,onehalfspacing,doublespacing,normalcolor,normal
textfont=#scriptsize,footnotesize,small,normalsize,large,Large,normalfont,up,it,sl,sc,md,bf,rm,sf,tt,singlespacing,onehalfspacing,doublespacing,normalcolor,normal
font+=#scriptsize,footnotesize,small,normalsize,large,Large,normalfont,up,it,sl,sc,md,bf,rm,sf,tt,singlespacing,onehalfspacing,doublespacing,normalcolor,normal
labelfont+=#scriptsize,footnotesize,small,normalsize,large,Large,normalfont,up,it,sl,sc,md,bf,rm,sf,tt,singlespacing,onehalfspacing,doublespacing,normalcolor,normal
textfont+=#scriptsize,footnotesize,small,normalsize,large,Large,normalfont,up,it,sl,sc,md,bf,rm,sf,tt,singlespacing,onehalfspacing,doublespacing,normalcolor,normal
margin=##L
width=##L
oneside
twoside
margin*=##L
minmargin=##L
maxmargin=##L
parskip=##L
hangindent=##L
style=#base,default
skip=##L
position=#top,above,bottom,below,auto
figureposition=#top,above,bottom,below,auto
tableposition=#top,above,bottom,below,auto
list=#on,off,true,false
listformat=#empty,simple,parens,subsimple,subparens
name=%<name%>
type=%<float type%>
#endkeyvals

#keyvals:\captionsetup#c,\usepackage/subcaption#c
subrefformat=#original,empty,simple,brace,parens
#endkeyvals

\subcaptionbox{heading%text}{contents}
\subcaptionbox{heading%text}[width]{contents}#*
\subcaptionbox{heading%text}[width][inner pos]{contents}
\subcaptionbox[list entry]{heading%text}{contents}
\subcaptionbox[list entry]{heading%text}[width]{contents}#*
\subcaptionbox[list entry]{heading%text}[width][inner pos]{contents}
\subcaptionbox*{heading%text}{contents}
\subcaptionbox*{heading%text}[width]{contents}#*
\subcaptionbox*{heading%text}[width][inner pos]{contents}

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

\DeclareCaptionSubType{type}
\DeclareCaptionSubType[numbering scheme]{type}
\DeclareCaptionSubType*{type}
\DeclareCaptionSubType*[numbering scheme]{type}

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
