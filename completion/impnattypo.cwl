# impnattypo package
# Matthew Bertucci 2026/06/02 for v1.6

#include:ifluatex
#include:kvoptions
#include:xcolor
#include:luatexbase
#include:luacode

#keyvals:\usepackage/impnattypo#c
draft#true,false
frenchchapters#true,false
hyphenation#true,false
nosingleletter#true,false
parindent#true,false
lastparline#true,false
homeoarchy#true,false
rivers#true,false
homeoarchywordcolor=#%color
homeoarchycharcolor=#%color
nosinglelettercolor=#%color
lastparlinecolor=#%color
riverscolor=#%color
homeoarchymaxwords=%<integer%>
homeoarchymaxchars=%<integer%>
lastparlineminlength=##L
#endkeyvals

\lastparlineminlength#*
\usecolor{color}#*