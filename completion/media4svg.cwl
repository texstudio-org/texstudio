# media4svg package
# Matthew Bertucci 2/1/2022 for v0.6

#include:l3keys2e

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
#endkeyvals

#keyvals:\includemedia
id=%<label%>
time=%<time offset%>
#endkeyvals