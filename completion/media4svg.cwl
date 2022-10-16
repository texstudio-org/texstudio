# media4svg package
# Matthew Bertucci 2022/10/16 for v0.13

#include:pdfbase

\includemedia{poster text%text}{imagefile}#g
\includemedia[options%keyvals]{poster text%text}{imagefile}#g

#keyvals:\includemedia,\usepackage/media4svg#c
draft#true,false
final#true,false
autoplay#true,false
loop#true,false
controls#true,false
mimetype=%<mime type%>
width=##L
height=##L
totalheight=##L
keepaspectratio#true,false
muted#true,false
scale=%<factor%>
url#true,false
embed#true,false
youtube#true,false
vimeo#true,false
#endkeyvals

#keyvals:\includemedia
id=%<label%>
time=%<time offset%>
#endkeyvals
