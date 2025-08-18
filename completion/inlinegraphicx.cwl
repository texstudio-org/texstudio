# inlinegraphicx package
# Matthew Bertucci 2025/08/18 for v0.1.1

#include:graphicx
#include:calc
#include:simplekv

\inlinegraphics{imagefile}#g
\inlinegraphics<includegraphics keys>{imagefile}#g
\inlinegraphics[keyvals]<includegraphics keys>{{imagefile}#g
\inlinegraphics[keyvals]{imagefile}#g
\inlinegraphics*{imagefile}#g
\inlinegraphics*<includegraphics keys>{imagefile}#g
\inlinegraphics*[keyvals]<includegraphics keys>{{imagefile}#g
\inlinegraphics*[keyvals]{imagefile}#g

# not documented
\totheightinlinegraphicx#S
\depthinlinegraphicx#S
\inlinedepthgraphicsscale#S
