# bicaption package
# Matthew Bertucci 11/24/2021 for v1.3

#include:caption

#keyvals:\usepackage/bicaption#c
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

\captionsetup[float type][biling selection]{options%keyvals}

#keyvals:\captionsetup#c,\usepackage/bicaption#c
lang=%<language%>
bi-lang=#both,first,second
bi-slc#true,false
bi-swap#true,false
bi-separator=#none,default,smallskip,medskip,largeskip
listtype+=%<list type ext%>
#endkeyvals

\DeclareBiCaptionSeparator{name}{code}

\bicaption{heading1%text}{heading2%text}
\bicaption[list-entry1]{heading1%text}[list-entry2]{heading2%text}
\bicaption*{heading1%text}{heading2%text}

\bicaptionbox{heading1%text}{heading2%text}{contents}
\bicaptionbox[list-entry1]{heading1%text}[list-entry2]{heading2%text}{contents}
\bicaptionbox{heading1%text}{heading2%text}[width][inner-pos]{contents}
\bicaptionbox[list-entry1]{heading1%text}[list-entry2]{heading2%text}[width][inner-pos]{contents}#*
\bicaptionbox*{heading1%text}{heading2%text}{contents}
\bicaptionbox*{heading1%text}{heading2%text}[width][inner-pos]{contents}

\bisubcaption{heading1%text}{heading2%text}#*
\bisubcaption[list-entry1]{heading1%text}[list-entry2]{heading2%text}#*
\bisubcaption*{heading1%text}{heading2%text}#*

\bisubcaptionbox{heading1%text}{heading2%text}{contents}#*
\bisubcaptionbox[list-entry1]{heading1%text}[list-entry2]{heading2%text}{contents}#*
\bisubcaptionbox{heading1%text}{heading2%text}[width][inner-pos]{contents}#*
\bisubcaptionbox[list-entry1]{heading1%text}[list-entry2]{heading2%text}[width][inner-pos]{contents}#*
\bisubcaptionbox*{heading1%text}{heading2%text}{contents}#*
\bisubcaptionbox*{heading1%text}{heading2%text}[width][inner-pos]{contents}#*

\captionmainlanguage#*
\selectcaptionlanguage{font or list entry}{language}#*

\DeclareCaptionLangOption{name}#*