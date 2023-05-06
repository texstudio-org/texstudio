# playcards package
# Matthew Bertucci 2023/05/01 for v0.2

#include:simplekv
#include:graphicx
#include:tikz
#include:tikzlibrarypatterns
#include:tikzlibraryshadows
#include:contour

#keyvals:\usepackage/playcards#c
anttor
#endkeyvals

#ifOption:anttor
#include:anttor
#endif

\drawcardsrecto{text}
\drawcardsrecto[options%keyvals]{text}

#keyvals:\drawcardsrecto
borders#true,false
trame#true,false
corners#true,false
backgroundImg#true,false
textColor=#%color
backgroundColor=#%color
contentsFontSize=%<number%>
circleRay=%<number%>
#endkeyvals

\drawcardsverso{text}
\drawcardsverso[options%keyvals]{text}

#keyvals:\drawcardsverso
backgroundImg#true,false
trame#true,false
contentsFontSize=%<number%>
#endkeyvals

# not documented
\cardbackgroundverso[opt]{arg}#S
\cardbackgroundverso{arg}#S
\cardborder#S
\cardcontent[opt]{arg}#S
\cardcontent{arg}#S
\cardcorner{arg}#S
\carddebug#S
\cardheight#S
\cardheightbody#S
\cardmargin#S
\cardpadding#S
\cardwidth#S
\cardwidthbody#S
\drawcardrecto[opt]{arg}#S
\drawcardrecto{arg}#S
\drawcardverso[opt]{arg}#S
\drawcardverso{arg}#S
\shapeCard#S
\shapeCardBody#S
\shapeMargin#S
\strippadding#S
\stripwidth#S
\textlineskip#S
\textsize#S