# mpgraphics package
# Matthew Bertucci 2/19/2022 for v0.3

#include:graphicx
#include:color
#include:moreverb
#include:xkeyval
#include:ifplatform
#include:iftex
#include:ifpdf

#keyvals:\usepackage/mpgraphics#c
metapost={%<MetaPost options%>}
epstopdf={%<epstopdf options%>}
compilation=#on,off
debug=#on,off
runs=%<integer%>
#endkeyvals

\begin{mpdisplay}
\end{mpdisplay}
\begin{mpinline}
\end{mpinline}
\begin{mpdefs}
\end{mpdefs}
\begin{ltxpreamble}
\end{ltxpreamble}

\mpgOff
\mpgOn

\NoProcess
\NoProcess[ranges]

\configure[mpgraphic][keyvals]

#keyvals:\configure
width=##L
height=##L
scale=%<factor%>
color=#%color
linecolor=#%color
background=#%color
linewidth=##L
rulesep=##L
#endkeyvals

\ArrayIterator{array}{arg}#*
\Array{name}[length%plain]{arg}#*
\BeforeMPDEFSStream#*
\BeforeMPGStream#*
\DeclareArray{name}#*
\MPDEFSverbatimwrite{file}#*
\MPGCutFile#*
\MPGgraphicsProcess#*
\MPGgraphicsinclude#*
\MPGinlinegraphicsinclude#*
\MPGverbatimwrite{file}#*
\NotIfFileExists{file}{code}#*
\OnlyIfFileExists{file}{code}#*
\addToArray{array}{arg}#*
\clearArray{array}#*
\endMPDEFSverbatimwrite#*
\endMPGhook#*
\endMPGverbatimwrite#*
\getArraylength{array}#*
\hyphencheck%<<arg1>%>-%<<arg2>%>-%<<arg3>%>#*
\mpgfigname#*
\mpgnoprocess#*
\theArrayIndex#*
\theCtr#*
\thearraylength#*
\thempgfig#*
\therecordCtr#*
\thezeroCtr#*