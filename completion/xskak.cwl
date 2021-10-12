# xskak package
# Matthew Bertucci 10/4/2021 for v1.5

#include:chessboard
#include:skak

\newchessgame
\newchessgame[options%keyvals]
\resumechessgame[options%keyvals]

#keyvals:\newchessgame,\resumechessgame,\xskakset,\chessboard
id
id=%<GameID%>
movenr=%<number%>
player=#w,b
moveid=
newvar=%<GameID%>
refid=%<tag%>
refpastmoveid=%<tag%>
refpastmovenr=%<tag%>
refpastplayer=%<tag%>
refnextmoveid=%<tag%>
refnextmovenr=%<tag%>
refnextplayer=%<tag%>
refpast=%<tag%>
refnext=%<tag%>
reffen=%<tag%>
reftag=
#endkeyvals

#keyvals:\newchessgame
result=
white=
black=
whiteelo=
blackelo=
site=
date=
event=
round=
#endkeyvals

#keyvals:\chessboard
lastmoveid
lastmoveid=
#endkeyvals

\xskaknewpgninfo{keyname}
\xskaknewpgninfo[default]{keyname}

\xskakgetgame{type%keyvals}

#keyvals:\xskakgetgame#c
initfen
initplayer
initmovenr
initmoveid
lastfen
lastplayer
lastmovenr
lastmoveid
nextplayer
nextmovenr
nextmoveid
diagramlist
gameid
result
white
black
whiteelo
blackelo
site
event
date
round
#endkeyvals

\xskakget{type%keyvals}

#keyvals:\xskakget#c
pgnpiece
piecechar
piece
pgnlostpiece
lostpiecechar
lostpiece
movefrom
pgnmovefrom
moveto
enpassant
enpassantsquare
castling
longcastling
capture
promotion
promotionpiece
promotionpiecechar
addpieces
clearfields
nextfen
pastfen
san
lan
opennr
comments
movenr
player
moveid
refid
refpastmoveid
refnextmoveid
refpastmovenr
refnextmovenr
refpastplayer
refnextplayer
#endkeyvals

\xskakcomment{text}

\xskakexportgames
\xskakexportgames[options%keyvals]

#keyvals:\xskakexportgames
file=
games={%<list of games%>}
#endkeyvals

\xskakendgamedata#*
\xskakcurrentgameid#*

\xskakset{options%keyvals}

#keyvals:\xskakset
stepmoveid=%<number%>
lastmoveid=%<GameID%>
tag=%<name%>
defaultid=%<GameID%>
defaultresult=
defaultwhite=
defaultblack=
defaultwhiteelo=
defaultblackelo=
defaultsite=
defaultdate=
defaultevent=
defaultround=
defaultmovenr=%<number%>
defaultplayer=#w,b
defaultmoveid=
defaultfen=
#endkeyvals

\xskaktestmoveid{movenr}{player}
\xskakloop{code}
\xskakloop[options%keyvals]{code}

#keyvals:\xskakloop
id=
initmovenr=%<number%>
initplayer=#w,b
initmoveid=
stopmovenr=%<number%>
stopplayer=#w,b
stopmoveid=
step=%<number%>
showlast#true,false
#endkeyvals

\xskakenpassantext#*

\mainline[option%keyvals]{moves}
\variation[option%keyvals]{moves}

#keyvals:\mainline,\variation,\xskakset,\printchessgame
style=
gstyle=
level=%<number%>
glevel=%<number%>
invar
ginvar
outvar
goutvar
#endkeyvals

\xskaknewstyleitem{item}
\xskaknewstyleitem[options%keyvals]{item}

#keyvals:\xskaknewstyleitem
opencommands=%<cmds%>
closecommands=%<cmds%>
beforenumber=%<cmds%>
whiteopen=%<cmds%>
blackopen=%<cmds%>
beforewhite=%<cmds%>
beforeblack=%<cmds%>
afterwhite=%<cmds%>
afterblack=%<cmds%>
beforeNAG=%<cmds%>
beforecomment=%<cmds%>
template=%<item%>
#endkeyvals

\xskaknewstyle{style}
\xskaknewstyle[options%keyvals]{style}
\xskakaddtostyle{style}
\xskakaddtostyle[options%keyvals]{style}

#keyvals:\xskaknewstyle,\xskakaddtostyle
level=%<number%>
styleitem=%<item%>
font=%<cmds%>
xfont=%<cmds%>
#endkeyvals

\printchessgame
\printchessgame[options%keyvals]

#keyvals:\printchessgame
id=%<GameID%>
refid=%<tag%>
initmovenr=%<number%>
initplayer=#w,b
initmoveid=
stopmovenr=%<number%>
stopplayer=#w,b
stopmoveid=
reftag=%<tag%>
#endkeyvals

\xskakaddtoid#*