# havannah package
# Matthew Bertucci 10/1/2021

#include:tikz

\begin{HavannahBoard}#\picture
\begin{HavannahBoard}[options%keyvals]#\picture
\end{HavannahBoard}

#keyvals:\begin{HavannahBoard},\begin{InnerHavannahBoard}
board size=%<integer%>
coordinate style=#little golem,classical
hex height=##L
show coordinates#true,false
show hexes#true,false
#endkeyvals

\begin{HexBoard}#\picture
\begin{HexBoard}[options%keyvals]#\picture
\end{HexBoard}

#keyvals:\begin{HexBoard},\begin{InnerHexBoard}
board size=%<integer%>
top left color=#white,black
hex height=##L
show coordinates#true,false
show hexes#true,false
#endkeyvals

\begin{InnerHavannahBoard}#/tikzpicture
\begin{InnerHavannahBoard}[options%keyvals]#/tikzpicture
\end{InnerHavannahBoard}#/tikzpicture
\begin{InnerHexBoard}#/tikzpicture
\begin{InnerHexBoard}[options%keyvals]#/tikzpicture
\end{InnerHexBoard}#/tikzpicture

#keyvals:\begin{InnerHavannahBoard},\begin{InnerHexBoard}
prefix=
x=
y=
#endkeyvals

\HLetterCoordinates#*
\HCoordinateStyle#*
\HDrawHex#*

\HGame{moves}#/HavannahBoard,HexBoard,tikzpicture
\HGame[options%keyvals]{moves}#/HavannahBoard,HexBoard,tikzpicture

#keyvals:\HGame
first move label=
first player=#white,black
numbered moves#true,false
relative stone size=
#endkeyvals

\HStoneGroup{moves}#/HavannahBoard,HexBoard,tikzpicture
\HStoneGroup[options%keyvals]{moves}#/HavannahBoard,HexBoard,tikzpicture

#keyvals:\HStoneGroup
color=#white,black,transparent
label=
relative stone size=
#endkeyvals

\HMoveNumberStyle#*
\HWhiteStone#*
\HBlackStone#*
\HTransparentStone#*
\HBeforeOddMove#*
\HBeforeEvenMove#*
\HBeforeStone#*

\HHexGroup{hexes}#/HavannahBoard,HexBoard,tikzpicture
\HHexGroup[options%keyvals]{hexes}#/HavannahBoard,HexBoard,tikzpicture

#keyvals:\HHexGroup
label=
#endkeyvals