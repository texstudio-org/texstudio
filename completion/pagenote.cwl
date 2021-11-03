# pagenote package
# Matthew Bertucci 11/3/2021 for v1.1a

#include:ifmtarg

\makepagenote
\printnotes
\printnotes*
\pagenote{text}
\pagenote[id]{text}

\notenumintext{number}#*
\noteentry{note number}{id}{text}{page number}#*
\prenoteinnotes#*
\noteidinnotes{note number}{id}#*
\pageinnotes{page number}#*
\noteinnotes{text}#*
\postnoteinnotes#*
\notedivision#*
\notesname#*

\addtonotes{text}
\pagenotesubhead{number}{title%plain}

\chaptername#*
\sectionname#*
\pagename#*
\ifpnhaschapter#*
\pnhaschapterfalse#*
\pnhaschaptertrue#*
\ifpnpageopt#*
\pnpageoptfalse#*
\pnpageopttrue#*
\ifpncontopt#*
\pncontoptfalse#*
\pncontopttrue#*
\thepagenote#*
\ifmakingpagenotes#*
\makingpagenotesfalse#*
\makingpagenotestrue#*
\pnofilewarn#*