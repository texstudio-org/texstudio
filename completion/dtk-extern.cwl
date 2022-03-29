# dtk-extern package
# Matthew Bertucci 3/27/2022 for v0.16

#include:fancyvrb
#include:graphicx
#include:marginnote
#include:shellesc
#include:xkeyval

\begin{externalDocument}{Dateiname}
\begin{externalDocument}[Optionen%keyvals]{Dateiname}
\end{externalDocument}

\begin{ErstelleGrafik}{Dateiname}#*
\begin{ErstelleGrafik}[Optionen%keyvals]{Dateiname}#*
\end{ErstelleGrafik}#*

#keyvals:\begin{externalDocument},\begin{ErstelleGrafik}
compiler=%<compiler%>
runsequence=%<runsequence%>
runs=%<number%>
grfOptions={%<\includegraphics options%>}
lstOptions={%<listings options%>}
docType=%<type%>
caption=%<text%>
label=##l
pages={%<pages%>}
mpwidth=##L
usefancyvrb#true,false
showFilename#true,false
code#true,false
force#true,false
crop#true,false
biber#true,false
xindex#true,false
xindexOptions={%<xindex options%>}
includegraphic#true,false
inline#true,false
frame#true,false
float#true,false
cleanup#true,false
copyToExampleDir#true,false
align=%<alignment commands%>
ExamplesDir=%<name%>
#endkeyvals

\ResetKeys

\LineWidth#*
\DoubleperCent#*
\dtkExternDateiname#*
\perCent#*