# mode: subfig.sty
# dani/2006-02-18
# edited Matthew Bertucci 2022/05/03 for v1.3

#include:keyval
#include:caption

#keyvals:\usepackage/subfig#c
caption#true,false
config=%<file name%>
font=#scriptsize,footnotesize,small,normalsize,large,Large,normalfont,up,it,sl,sc,md,bf,rm,sf,tt,singlespacing,onehalfspacing,doublespacing,normalcolor,normal
labelfont=#scriptsize,footnotesize,small,normalsize,large,Large,normalfont,up,it,sl,sc,md,bf,rm,sf,tt,singlespacing,onehalfspacing,doublespacing,normalcolor,normal
textfont=#scriptsize,footnotesize,small,normalsize,large,Large,normalfont,up,it,sl,sc,md,bf,rm,sf,tt,singlespacing,onehalfspacing,doublespacing,normalcolor,normal
style=#default,ruled
singlelinecheck#true,false
format=#default,hang
indention=##L
hangindent=##L
width=##L
margin=##L
parskip=##L
justification=#justified,centering,centerlast,centerfirst,raggedright,raggedleft,Justified,Centering,RaggedRight,RaggedLeft
labelformat=#original,empty,simple,brace,parens
aboveskip=##L
belowskip=##L
labelsep=#none,colon,period,space,quad,newline,endash
position=#top,above,bottom,below,auto
#endkeyvals

# keys added to caption interface
#keyvals:\usepackage/subfig#c,\captionsetup#c,\captionsetup*#c,\DeclareCaptionStyle#c
lofdepth=%<integer%>
lotdepth=%<integer%>
listofformat=#empty,simple,parens,subsimple,subparens
subrefformat=#empty,simple,parens,subsimple,subparens
listofindent=##L
listofnumwidth=##L
farskip=##L
captionskip=##L
topadjust=##L
nearskip=##L
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

# subfigure compatibility
#ifOption:config=altsf
\subfigure{body%text}
\subfigure[subcaption%text]{body%text}
\subfigure[listentry%text][subcaption%text]{body%text}
\subtable{body%text}
\subtable[subcaption%text]{body%text}
\subtable[listentry%text][subcaption%text]{body%text}
\Subref{label}#r
#endif

\newsubfloat{float name}
\newsubfloat[kv-list]{float name}
\DeclareCaptionListOfFormat{keyword}{code}
\DeclareSubrefFormat{keyword}{code}
\subfloat{body%text}
\subfloat[subcaption%text]{body%text}
\subfloat[listentry%text][subcaption%text]{body%text}
\subref{label}#r
\subref*{label}#r
\listsubcaptions
\thesubfigure#*
\thesubtable#*
\subfigurename#*
\subtablename#*
\theKVtest#S
\ifhyperrefloaded#S
\hyperrefloadedtrue#S
\hyperrefloadedfalse#S
\ifmaincaptiontop#S
\maincaptiontoptrue#S
\maincaptiontopfalse#S
