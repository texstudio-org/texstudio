# caption.cwl
# Edson 2010
# Matthew Bertucci updated 2/26/2022 for v3.6

#include:caption3
#include:ltcaption

\captionsetup[float type]{options%keyvals}
\captionsetup{options%keyvals}
\captionsetup*[float type]{options%keyvals}#*
\captionsetup*{options%keyvals}#*

#keyvals:\captionsetup#c,\captionsetup*#c,\usepackage/caption#c,\DeclareCaptionStyle#c
format=#plain,hang
indention=##L
labelformat=#original,empty,simple,brace,parens
labelsep=#none,colon,period,space,quad,newline,endash
textformat=#empty,simple,period
justification=#justified,centering,centerlast,centerfirst,raggedright,raggedleft,Justified,Centering,RaggedRight,RaggedLeft
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

#keyvals:\usepackage/caption#c
compatibility#true,false
#endkeyvals

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

\clearcaptionsetup[option%keyvals]{float type}
\clearcaptionsetup{float type}

#keyvals:\clearcaptionsetup#c
format
indention
labelformat
labelsep
textformat
justification
singlelinecheck
font
labelfont
textfont
font+
labelfont+
textfont+
margin
width
oneside
twoside
margin*
minmargin
maxmargin
parskip
hangindent
style
skip
position
figureposition
tableposition
list
listformat
name
type
#endkeyvals

\showcaptionsetup{float type}

\caption[list entry]{heading%text}
\caption{heading%text}

\captionof{float type}[list entry]{heading%text}
\captionof{float type}{heading%text}
\captionof*{float type}{heading%text}

\captionlistentry[float type]{list entry}
\captionlistentry{list entry}

\ContinuedFloat
\ContinuedFloat*
\theContinuedFloat#*

\DeclareCaptionFormat{name}{code}
\DeclareCaptionLabelFormat{name}{code}
\bothIfFirst{first arg}{second arg}
\bothIfSecond{first arg}{second arg}
\DeclareCaptionTextFormat{name}{code}
\DeclareCaptionLabelSeparator{name}{code}
\DeclareCaptionJustification{name}{code}
\DeclareCaptionFont{name}{code}
\DeclareCaptionStyle{name}[additional options]{options%keyvals}
\DeclareCaptionStyle{name}{options%keyvals}
\DeclareCaptionListFormat{name}{code}
\DeclareCaptionType[options]{type}[name][list name]
\DeclareCaptionType{type}
\phantomcaption
\setcaptionsubtype{float type}#*
\setcaptionsubtype*{float type}#*
\captionbox#*
\flushsubcaptionlistentries#*
\piccaptiontype{arg}#*
\captiontext{text}
\captiontext[number]{text}
\captiontext*{text}
\captiontext*[number]{text}
\begin{captiongroup}
\end{captiongroup}
\begin{captiongroup*}
\end{captiongroup*}
\begin{captionblock}{width}
\begin{captionblock}[position]{width}
\begin{captionblock}[position][height]{width}
\begin{captionblock}[position][height][inner pos]{width}#*
\end{captionblock}
\setcaptiontype{float type}
\setcaptiontype[options]{float type}
\setcaptiontype*{float type}
\setcaptiontype*[options]{float type}

# only available if longtable package loaded
\begin{longtable*}#S
\end{longtable*}#S
