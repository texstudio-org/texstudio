# chessboard package
# Matthew Bertucci 10/4/2021 for v1.9

#include:chessfss
#include:xifthen
#include:ifpdf
#include:tikz
#include:etoolbox

\chessboard
\chessboard[options%keyvals]
\setchessboard{options%keyvals}
\storechessboardstyle{name}{options%keyvals}

#keyvals:\chessboard,\setchessboard,\storechessboardstyle,\newchessgame,\resumechessgame
style=
maxfield=%<field%>
zero#true,false
clearboard=
cleararea=%<area%>
clearfile=%<file%>
clearfiles=%<files%>
clearrank=%<rank%>
clearranks={%<list of ranks%>}
clearfield=%<field%>
clearfields={%<list of fields%>}
setpieces={%<list of positions%>}
addpieces={%<list of positions%>}
setwhite={%<list of positions%>}
addwhite={%<list of positions%>}
setblack={%<list of positions%>}
addblack={%<list of positions%>}
setfen=%<FEN%>
addfen=%<FEN%>
startfen=%<field%>
startfill=%<field%>
stopfill=%<field%>
fillarea=%<area%>
storefen=%<name%>
savefen=%<filename%>
startstore=%<field%>
stopstore=%<field%>
storearea=%<area%>
mover=#w,b
castling=
enpassant=%<field%>
halfmove=%<integer%>
fullmove=%<integer%>
getpiecelists
restorefen=%<name%>
loadfen=%<name%>
language=
marginleftwidth=##L
marginrightwidth=##L
margintopwidth=##L
marginbottomwidth=##L
hmarginwidth=##L
vmarginwidth=##L
marginwidth=##L
marginleft#true,false
marginright#true,false
margintop#true,false
marginbottom#true,false
hmargin#true,false
vmargin#true,false
margin#true,false
borderleftwidth=##L
borderrightwidth=##L
bordertopwidth=##L
borderbottomwidth=##L
hborderwidth=##L
vborderwidth=##L
borderwidth=##L
borderleft#true,false
borderright#true,false
bordertop#true,false
borderbottom#true,false
hborder#true,false
vborder#true,false
border#true,false
borderleftcolor=#%color
borderrightcolor=#%color
bordertopcolor=#%color
borderbottomcolor=#%color
hbordercolor=#%color
vbordercolor=#%color
bordercolor=#%color
boardfontsize=##L
fontsize=##L
tinyboard
smallboard
normalboard
largeboard
boardfontfamily=
boardfontseries=
boardfontencoding=
clearfontcolors
whitefieldmaskcolor=#%color
blackfieldmaskcolor=#%color
fieldmaskcolor=#%color
whitefieldcolor=#%color
blackfieldcolor=#%color
fieldcolor=#%color
whiteonwhitepiecemaskcolor=#%color
whiteonblackpiecemaskcolor=#%color
blackonwhitepiecemaskcolor=#%color
blackonblackpiecemaskcolor=#%color
whitepiecemaskcolor=#%color
blackpiecemaskcolor=#%color
onwhitepiecemaskcolor=#%color
onblackpiecemaskcolor=#%color
piecemaskcolor=#%color
whitepiececolor=#%color
blackpiececolor=#%color
piececolor=#%color
setfontcolors
addfontcolors
emphstyle=%<cmds%>
coloremph#true,false
coloremphstyle=%<cmds%>
emphboard
empharea=%<area%>
emphareas={%<list of areas%>}
emphfile=%<file%>
emphfiles={%<list of files%>}
emphrank=%<rank%>
emphranks={%<list of ranks%>}
emphfield=%<field%>
emphfields={%<list of fields%>}
labelleft#true,false
labelright#true,false
labeltop#true,false
labelbottom#true,false
hlabel#true,false
vlabel#true,false
label#true,false
labelleftwidth=##L
labelrightwidth=##L
hlabelwidth=##L
labelleftlift=##L
labelrightlift=##L
hlabellift=##L
labeltoplift=##L
labelbottomlift=##L
vlabellift=##L
labelleftfont=%<font cmd%>
labelrightfont=%<font cmd%>
labeltopfont=%<font cmd%>
labelbottomfont=%<font cmd%>
hlabelfont=%<font cmd%>
vlabelfont=%<font cmd%>
labelfont=%<font cmd%>
labelfontsize=##L
labelleftformat=%<cmds%>
labelrightformat=%<cmds%>
labeltopformat=%<cmds%>
labelbottomformat=%<cmds%>
hlabelformat=%<cmds%>
vlabelformat=%<cmds%>
labelformat=%<cmds%>
showmover#true,false
moversize=##L
moverlift=##L
movertoplift=##L
moverbottomlift=##L
movershift=##L
movertopshift=##L
moverbottomshift=##L
moverstyle=#circle,triangle,squarearrow,unknown
print#true,false
startprint=%<field%>
stopprint=%<field%>
printarea=%<field%>
inverse#true,false
hideboard
hidearea=%<area%>
hideareas={%<list of areas%>}
hidefile=%<file%>
hidefiles={%<list of files%>}
hiderank=%<rank%>
hideranks={%<list of ranks%>}
hidefield=%<field%>
hidefields{%<list of fields%>}
hidepiece=%<piece char%>
hidepieces={%<list of piece chars%>}
hidewhite
hideblack
hideall
showboard
showarea=%<area%>
showareas={%<list of areas%>}
showfile=%<file%>
showfiles={%<list of files%>}
showrank=%<rank%>
showranks={%<list of ranks%>}
showfield=%<field%>
showfields={%<list of fields%>}
showpiece=%<piece char%>
showpieces={%<list of piece chars%>}
showwhite
showblack
showall
pgf#true,false
markboard
markarea=%<area%>
markareas={%<list of areas%>}
markfile=%<file%>
markfiles={%<list of files%>}
markrank=%<rank%>
markranks={%<list of ranks%>}
markfield=%<field%>
markfields={%<list of fields%>}
backboard
backarea=%<area%>
backareas={%<list of areas%>}
backfile=%<file%>
backfiles={%<list of files%>}
backrank=%<rank%>
backranks={%<list of ranks%>}
backfield=%<field%>
backfields={%<list of fields%>}
markregions={%<list of regions%>}
markregion={%<list of regions%>}
backregions={%<list of regions%>}
backregion={%<list of regions%>}
markmoves={%<list of moves%>}
markmove={%<list of moves%>}
backmoves={%<list of moves%>}
backmove={%<list of moves%>}
markstyle=
backstyle=
pgfstyle=
color=#%color
pgfcolor=#%color
opacity=
pgfopacity=
fillopacity=
pgffillopacity=
strokeopacity=
pgfstrokeopacity=
padding=##L
pgfpadding=##L
arrow=%<arrow type%>
pgfarrow=%<arrow type%>
shortenstart=##L
pgfshortenstart=##L
shortenend=##L
pgfshortenend=##L
shorten=##L
pgfshorten=##L
linewidth=##L
pgflinewidth=##L
marklinewidth=##L
backlinewidth=##L
cornerarc=##L
pgfcornerarc=##L
backcornerarc=##L
addpgf=%<pgf cmds%>
usepgf
usepgf=#back,mark,all,both,none
pgfborder
pgfborder=%<area%>
colorbackboard
colorbackarea=%<area%>
colorbackareas={%<list of areas%>}
colorbackfile=%<file%>
colorbackfiles={%<list of files%>}
colorbackrank=%<rank%>
colorbackranks={%<list of ranks%>}
colorbackfield=%<field%>
colorbackfields={%<list of fields%>}
colorwhitebackfields={%<list of fields%>}
colorblackbackfields={%<list of fields%>}
clearpgf
clearbackpgf
clearmarkpgf
clip
clip=
markclip
markclip=
backclip
backclip=
trimarea
trimare=%<area%>
captrimtoprint#true,false
trim#true,false
trimtocolor=#white,black,false
psset#true,false
psskak#true,false
text=
#endkeyvals

\cblistK
\cblistQ
\cblistR
\cblistB
\cblistN
\cblistP
\cblistk
\cblistq
\cblistr
\cblistb
\cblistn
\cblistp

\cbDefineLanguage{language}#*
\cbDefineTranslation{piece letter}{new piece letter}#*
\cbDefineMoverStyle{name}{white top}{white bot}{black top}{black bot}#*
\cbDefineMoverStyle[cmds]{name}{white top}{white bot}{black top}{black bot}#*
\cbDefinePgfFieldStyle{name}{definition}#*
\cbDefinePgfRegionStyle{name}{definition}#*
\cbDefinePgfMoveStyle{name}{definition}#*
\cbDefineNewPiece{color}{char}{on white}{on black}#*
\cbDefineNewPiece[game]{color}{char}{on white}{on black}#*
\printarea#*
\board#*
\currentbk#*
\currentbq#*
\currentwk#*
\currentwq#*