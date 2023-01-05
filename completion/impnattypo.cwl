# impnattypo package
# Matthew Bertucci 1/25/2022 for v1.5

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
#endkeyvals

\usecolor{color}#*
