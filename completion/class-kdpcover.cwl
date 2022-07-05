# kdpcover class
# Matthew Bertucci 2022/07/04 for v0.3.0

#include:iexec
#include:xkeyval
#include:anyfontsize
#include:tikz
#include:microtype
#include:xcolor
#include:graphicx
#include:calc
#include:setspace
#include:geometry
#include:textpos

#keyvals:\documentclass/kdpcover#c
6x9
7x10
8x10
pages=%<integer%>
barless
pdf=%<PDF file%>
#endkeyvals

\putSpine{text}
\putSpine[imagefile]{text}#g
\putPicture{imagefile}#g
\putVolume{number}
\putPrice{price}
\putBack{text}
\putTitle{text}
\putAuthor{name}
\putTLDR{text}
\putVersion{version}
\putCopyright{year}{name}