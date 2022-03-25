# psgo package
# Matthew Bertucci 3/14/2022 for v0.17

#include:pstricks
#include:pst-node
#include:calc
#include:ifthen

\begin{psgoboard}#\pictureHighlight
\begin{psgoboard}[size]
\end{psgoboard}
\begin{psgoboard*}#\pictureHighlight
\begin{psgoboard*}[size]
\end{psgoboard*}
\setgounit{length}

\stone{color%plain}{column}{row}
\stone[marker]{color%plain}{column}{row}
\move{column}{row}
\move[marker]{column}{row}
\move*{column}{row}
\move*[marker]{column}{row}
\pass
\pass*

\markpos{marker}{column}{row}
\markma
\marktr
\markcr
\marksq
\marklb{text%plain}
\marksl
\markdd

\goline{column1}{row1}{column2}{row2}
\goarrow{column1}{row1}{column2}{row2}

\begin{psgopartialboard}{(%<x1,y1%>)(%<x2,y2%>)}#\pictureHighlight
\begin{psgopartialboard}[%<size%>]{(%<x1,y1%>)(%<x2,y2%>)}
\end{psgopartialboard}
\begin{psgopartialboard*}{(%<x1,y1%>)(%<x2,y2%>)}#\pictureHighlight
\begin{psgopartialboard*}[%<size%>]{(%<x1,y1%>)(%<x2,y2%>)}
\end{psgopartialboard*}

# not documented
\psgo#*
\begin{gomoves}#*
\end{gomoves}#*
\blackstone{column}{row}#*
\blackstone[marker]{column}{row}#*
\factor#*
\golabelformat{text}#*
\goxposition{column}#*
\goxunit#*
\goyposition{row}#*
\goyunit#*
\hatchangle#*
\mdd{column1}{row1}{column2}{row2}#*
\movenostar{column}{row}#*
\movenostar[marker]{column}{row}#*
\movestar{column}{row}#*
\movestar[marker]{column}{row}#*
\nomark#*
\passnostar#*
\passstar#*
\placesymbol{symbol}{column}{row}#*
\pointbox{text}#*
\psgollx#*
\psgollxval#*
\psgolly#*
\psgollyval#*
\psgosetboardsizes#*
\psgourx#*
\psgourxval#*
\psgoury#*
\psgouryval#*
\stmark#*
\stmarkbox#*
\theboardsize#*
\thegomove#*
\thegotmpc#*
\tmplx#S
\tmply#S
\tmpxa#S
\tmpxb#S
\tmpya#S
\tmpyb#S
\toggleblackmove#*
\whitestone{column}{row}#*
\whitestone[marker]{column}{row}#*
\xoffset#*
\xpositionmarks{counter}{value}#*
\ypos#*
\ypositionmarks{counter}{value}#*