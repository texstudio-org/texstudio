# icon-appr package
# Matthew Bertucci 2022/05/10 for v1.2.1

#include:xkeyval
#include:ifpdf
#include:ifxetex
#include:ifluatex
#include:eforms
#include:graphicx
#include:datatool

\begin{embedding}
\end{embedding}

\embedIcon{imagefile}#g
\embedIcon[options%keyvals]{imagefile}#g

#keyvals:\embedIcon
name=%<name%>
hyopts={%<\includegraphics keys%>}
placement=%<field%>
placement={[%<0|1|2%>]%<field%>}
#endkeyvals

\csOf{name}
\heightOf{name}
\widthOf{name}

\ReqPkg#S
\begin{sortedlist}#*
\end{sortedlist}#*
\sortitem{arg}#*
\sortitem[opt]{arg}#*