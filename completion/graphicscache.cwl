# graphicscache package
# Matthew Bertucci 2022/12/20 for v0.4

#include:graphicx
#include:xstring
#include:filemod
#include:letltxmacro
#include:pgfopts
#include:pgffor
#include:ifplatform
#include:pdftexcmds
#include:ltxcmds

\includegraphicscache{options%keyvals}{imagefile}#*g
\includegraphicscache[graphicx options]{options%keyvals}{imagefile}#*g

#keyvals:\usepackage/graphicscache#c,\includegraphics,\includegraphicscache
compress=#false,flat,jpeg
dpi=%<number%>
qfactor=%<number%>
listing#true,false
render#true,false
cachedir=%<directory%>
#endkeyvals
