# draftmark package
# Matthew Bertucci 12/13/2021 for v1.2

#include:atbegshi
#include:etextools
#include:fix-cm
#include:graphicx
#include:ltxnew
#include:picture
#include:xcolor
#include:xifthen
#include:xkeyval

#keyvals:\usepackage/draftmark#c
draft#true,false
final#true,false
allpages#true,false
evenpages#true,false
oddpages#true,false
pages=%<num1-num2%>
page=%<num%>
#endkeyvals

\draftmarksetup{options%keyvals}

#keyvals:\usepackage/draftmark#c,\draftmarksetup
mark=%<text%>
angle=%<degrees%>
scale=%<factor%>
grayness=%<factor%>
color=#%color
fontfamily=%<family%>
fontsize=##L
xcoord=%<number%>
ycoord=%<number%>
coordunit=%<unit%>
showcenter#true,false
acceptrange#true,false
#endkeyvals

\fileauthor#S
\filedate#S
\filedesc#S
\filetime#S
\fileversion#S
\readRCS#S
\x#S