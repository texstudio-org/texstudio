# seatingchart package
# Matthew Bertucci 2026/07/26 for v1.0.0beta

#include:etoolbox
#include:luacode
#include:tikz
#include:tikzlibraryshapes.geometric

\begin{seatingchart}
\begin{seatingchart}[keyvals]
\end{seatingchart}
\scConfig{keyvals}

#keyvals:\begin{seatingchart},\scConfig
layout=%<institution%>
blackboard#true,false
seat neighbor distance=##L
row distance=##L
rownumbers=#none,left,right,both
rownumber distance=##L
empty seat background color=#%color
empty seat border color=#%color
assigned seat background color=#%color
assigned seat border color=#%color
seat background color=#%color
seat border color=#%color
assigned seat label font=%<font commands%>
assigned seat label color=#%color
#endkeyvals

#keyvals:\begin{seatingchart}
room=%<room%>
shape=#rectangle,arc
rows=%<integer%>
seats per row=%<integer%>
#endkeyvals

\scRemoveSeatAt{row}{seat number}
\scRemoveSeats{list}
\scSetAisle{seat number}
\scSetAisle[start row-end row]{seat number}

\scDrawSeating
\scDrawSeating[keyvals]

#keyvals:\scDrawSeating
seat width=##L
seat height=##L
#endkeyvals

\scSeatingScheme{name}
\scSeatingScheme[keyvals]{name}
\scSeatingScheme*{pattern}
\scSeatingScheme*[keyvals]{pattern}
\scConfigScheme{keyvals}

#keyvals:\scSeatingScheme,\scSeatingScheme*,\scConfigScheme
row sep=%<integer%>
start row=%<integer%>
end row=%<integer%>
row restart after=%<integer%>
aisle counts=%<integer%>
aisle restarts scheme#true,false
ignore aisle#true,false
ignore removed seats#true,false
assigned seat label=%<string%>
#endkeyvals

\scGenerateSeatingList{output file}
\scGenerateSeatingList[input file%file]{output file}
\scGenerateSeatingList*{output file}
\scGenerateSeatingList*[input file%file]{output file}

\scLoadSeatingList{input file%file}
\scLoadSeatingList[keyvals]{input file%file}

#keyvals:\scLoadSeatingList
mode=#sequential,seat,coordinates
header#true,false
#endkeyvals

\scDeclareRoom{room}{keyvals}

#keyvals:\scDeclareRoom
shape=#rectangle,arc
rows=%<integer%>
seats per row=%<integer%>
init
aisle=%<seat number%>
remove={%<list%>}
#endkeyvals

\scAliasRoom{alias}{room}