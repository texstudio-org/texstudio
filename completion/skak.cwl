# skak package
# Matthew Bertucci 10/5/2021 for v1.5.3

#include:chessfss
#include:calc
#include:textcomp

\newgame
\mainline{moves}
\variation{moves}
\showboard
\hidemoves{moves}
\storegame{name}
\restoregame{name}
\savegame{name}
\loadgame{name}
\notationoff
\notationon
\showinverseboard
\wmove{move}
\bmove{move}
\lastmove{move}
\showonlywhite
\showonlyblack
\showonly{piece1,piece2,...}
\showallbut{piece1,piece2,...}
\fenboard{instructions}
\styleA
\styleB
\styleC
\variationstyle
\mainlinestyle
\longmoves
\shortmoves
\newskaklanguage{language}{pieces}
\skaklanguage[language]
\boardasfen
\EnPassantSquare#*
\variationcurrent#*
\continuevariation#*
\continuevariationcurrent#*
\tinyboard
\smallboard
\normalboard
\largeboard
\notationOn#*
\notationOff#*
\movecomment{moves}
\showall
\showonlypawns
\WhiteToMove{code for white}{code for black}#*

#ifOption:ps
#include:pstricks
#include:pst-node
\showmoverOn#*
\showmoverOff#*
\showmoveron
\showmoveroff
\printarrow{from}{to}
\highlight[marker]{square list}
\printknightmove{from}{to}
#endif