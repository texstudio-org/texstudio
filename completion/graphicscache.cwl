# graphicscache package
# Matthew Bertucci 2/4/2022 for v0.3

#include:graphicx
#include:xstring
#include:filemod
#include:letltxmacro
#include:pgfopts
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