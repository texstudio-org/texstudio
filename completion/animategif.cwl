# animategif package
# Matthew Bertucci 2026/10/07 for v1.0.0

#include:animate
#include:graphicx
#include:luatex

\animategifsetup{options%keyvals}
\animategif{imagefile}#g
\animategif[options%keyvals]{imagefile}#g

#keyvals:\animategifsetup,\animategif
optimize#true,false
keyframe=%<integer%>
frames=%<a-b%>
step=%<integer%>
downsample=%<integer%>
speed=%<factor%>
fps=%<rate%>
plays=%<integer%>
still
still=
label=%<name%>
cachedir=%<directory%>
handout=#still,animate
#endkeyvals