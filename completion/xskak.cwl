# xskak package
# Matthew Bertucci 2022/05/21 for v1.5

#include:skak
#include:xifthen
#include:etoolbox
#include:chessboard

#keyvals:\usepackage/xskak#c
nopdfmatch
#endkeyvals

\newchessgame
\newchessgame[options%keyvals]
\resumechessgame[options%keyvals]

#keyvals:\newchessgame,\resumechessgame,\xskakset,\chessboard
id
id=%<GameID%>
movenr=%<number%>
player=#w,b
moveid=%<⟨number⟩⟨w or b⟩%>
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
reftag=%<tag%>
%xskakkey
#endkeyvals

#keyvals:\newchessgame
result=%<result%>
white=%<name%>
black=%<name%>
whiteelo=%<rating%>
blackelo=%<rating%>
site=%<site%>
date=%<date%>
event=%<event name%>
round=%<round%>
#endkeyvals

#keyvals:\chessboard
stepmoveid=%<number%>
lastmoveid
lastmoveid=%<GameID%>
#endkeyvals

\xskaknewpgninfo{keyname%specialDef}#s#%xskakkey
\xskaknewpgninfo[default]{keyname%specialDef}

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
parentid
result
white
black
whiteelo
blackelo
site
event
date
round
%xskakkey
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
check
mate
move
nag
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
defaultresult=%<result%>
defaultwhite=%<name%>
defaultblack=%<name%>
defaultwhiteelo=%<rating%>
defaultblackelo=%<rating%>
defaultsite=%<site%>
defaultdate=%<date%>
defaultevent=%<event name%>
defaultround=%<round%>
defaultmovenr=%<number%>
defaultplayer=#w,b
defaultmoveid=%<⟨number⟩⟨w or b⟩%>
defaultfen=%<FEN%>
#endkeyvals

\xskaktestmoveid{movenr}{player}
\xskakloop{code}
\xskakloop[options%keyvals]{code}

#keyvals:\xskakloop
id=%<GameID%>
initmovenr=%<number%>
initplayer=#w,b
initmoveid=%<⟨number⟩⟨w or b⟩%>
stopmovenr=%<number%>
stopplayer=#w,b
stopmoveid=%<⟨number⟩⟨w or b⟩%>
step=%<number%>
showlast#true,false
#endkeyvals

\xskakenpassanttext#*

\mainline[option%keyvals]{moves}
\variation[option%keyvals]{moves}

#keyvals:\mainline,\variation,\xskakset,\printchessgame
style=%<style name%>
gstyle=%<style name%>
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
initmoveid=%<⟨number⟩⟨w or b⟩%>
stopmovenr=%<number%>
stopplayer=#w,b
stopmoveid=%<⟨number⟩⟨w or b⟩%>
reftag=%<tag%>
#endkeyvals

\chessdiagramname#*
\xskakaddtoid#*

# not documented
\ifxskakboolcapture#S
\ifxskakboolcastling#S
\ifxskakboolcheck#S
\ifxskakboolcomment#S
\ifxskakboolenpassant#S
\ifxskakboollongcastling#S
\ifxskakboolmate#S
\ifxskakboolnag#S
\ifxskakboolpromotion#S
\ifxskakboolvar#S
\ifxskakpdfmatch#S
\ParseCastlingAA(arg)#S
\skaklongmoves#S
\variationmovemode#*
\xskakboolcapturefalse#S
\xskakboolcapturetrue#S
\xskakboolcastlingfalse#S
\xskakboolcastlingtrue#S
\xskakboolcheckfalse#S
\xskakboolchecktrue#S
\xskakboolcommentfalse#S
\xskakboolcommenttrue#S
\xskakboolenpassantfalse#S
\xskakboolenpassanttrue#S
\xskakboollongcastlingfalse#S
\xskakboollongcastlingtrue#S
\xskakboolmatefalse#S
\xskakboolmatetrue#S
\xskakboolnagfalse#S
\xskakboolnagtrue#S
\xskakboolpromotionfalse#S
\xskakboolpromotiontrue#S
\xskakboolvarfalse#S
\xskakboolvartrue#S
\xskakmovehyphen#*
\xskakpdfmatchfalse#S
\xskakpdfmatchtrue#S
