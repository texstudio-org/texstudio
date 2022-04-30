# image-gallery class
# Matthew Bertucci 2022/04/29 for v1.0j

#include:graphicx
#include:keyval
#include:url
#include:geometry

#keyvals:\documentclass/image-gallery#c
dummy
nocaption
# options passed to article class
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

#ifOption:dummy
#include:color
#endif

\makeGallery{file}#i
\gallerySetup{options%keyvals}

#keyvals:\gallerySetup
width=##L
height=##L
top=##L
bottom=##L
left=##L
right=##L
rows=%<integer%>
columns=%<integer%>
autorotate#true,false
#endkeyvals









