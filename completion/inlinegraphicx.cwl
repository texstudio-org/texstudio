# inlinegraphicx package
# Matthew Bertucci 2026/10/03 for v0.20d

#include:graphicx

#keyvals:\usepackage/inlinegraphicx#c
inherit#true,false
#endkeyvals

\inlinegraphics{imagefile}#g
\inlinegraphics<includegraphics keys>{imagefile}#g
\inlinegraphics[keyvals]<includegraphics keys>{imagefile}#g
\inlinegraphics[keyvals]{imagefile}#g
\inlinegraphics*{imagefile}#g
\inlinegraphics*<includegraphics keys>{imagefile}#g
\inlinegraphics*[keyvals]<includegraphics keys>{imagefile}#g
\inlinegraphics*[keyvals]{imagefile}#g
\inlinegraphicxsetup{keyvals}
\safeincludegraphics{imagefile}#g
\safeincludegraphics[includegraphics keys]{imagefile}#g
\inlinegraphicspath{dir-list%definition}