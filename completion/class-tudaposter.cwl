# tudaposter class
# Matthew Bertucci 2022/08/17 for v3.27

#include:l3keys2e
#include:class-scrartcl
#include:scrlayer
#include:scrlayer-notecolumn
#include:tudafonts
#include:tudarules
#include:tudacolors
#include:qrcode
#include:tikz
#include:geometry

#keyvals:\documentclass/tudaposter#c
color=#%color
accentcolor=#%color
textaccentcolor=#%color
identbarcolor=#%color
logo=#head,body
footer#true,false
paper=#a0,a1,a2,a3,a4
fontsize=##L
logofile=%<Dateipfad%>
type=announcement
indenttext#true,false
marginpar#true,false
title=#default,large,small
colorback#true,false
colorsubtitle#true,false
#endkeyvals

\contentwidth#L
\contentheight#L
\SetMarginpar{content%text}
\SetMarginpar[options%keyvals]{content%text}
#keyvals:\SetMarginpar
valign=
overlap#true,false
#endkeyvals
\titleinfo{text}
\titlegraphic{graphics code}
\addTitleBox{text}
\addTitleBoxLogo{imagefile}#g
\addTitleBoxLogo*{graphics code}
\footer{text}
\footerqrcode{URL}#U
\footerqrcodeimg{graphics code}
\infofont
\infotext{text}
\authorandname#*