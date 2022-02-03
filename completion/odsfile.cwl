# odsfile package
# Matthew Bertucci 2/2/2022 for v0.6

#include:luacode
#include:xkeyval

\includespread
\includespread[options%keyvals]

#keyvals:\includespread#c,\loadodsfile#c
file=%<file name%>
sheet=%<sheet name%>
range=%<cell1:cell2%>
columns=#head,top,{%<val1,val2,...%>}
columnbreak=%<command%>
rowseparator=#tableline,hline,newline,%<command%>
template=#%<template name%>,{%<code%>}
coltypes=%<coltypes%>
rowtemplate=#%<template name%>,{%<code%>}
multicoltemplate=#%<template name%>,{%<code%>}
#endkeyvals

\tabletemplate{name}{code}
\begin{AddRow}
\begin{AddRow}[row number]
\end{AddRow}
\AddString{text}{position}
\AddNumber{number}{position}
\loadodsfile{file}#i
\loadodsfile[options%keyvals]{file}#i
\savespreadsheet