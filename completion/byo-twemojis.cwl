# byo-twemojis package
# Matthew Bertucci 10/5/2021 for v1.0

#include:tikz
#include:xstring
#include:etoolbox

\byoTwemoji{elmt1;elmt2;...}
\byoTwemoji[options%keyvals]{elmt1;elmt2;...}

#keyvals:\byoTwemoji#c
let White=
let WhiteGray=
let LightGray=
let Gray=
let DarkGray=
let Black=
let LightBrown=
let Brown=
let Yellow=
let DarkYellow=
let LightOrange=
let Orange=
let DarkOrange=
let LightRose=
let Rose=
let LightRed=
let Red=
let DarkRed=
let WineRed=
let DarkWineRed=
let LightBlue=
let Blue=
let DarkBlue=
let LightGreen=
let Green=
let DarkGreen=
let LightPurple=
let Purple=
let Shadow=
set White=
set WhiteGray=
set LightGray=
set Gray=
set DarkGray=
set Black=
set LightBrown=
set Brown=
set Yellow=
set DarkYellow=
set LightOrange=
set Orange=
set DarkOrange=
set LightRose=
set Rose=
set LightRed=
set Red=
set DarkRed=
set WineRed=
set DarkWineRed=
set LightBlue=
set Blue=
set DarkBlue=
set LightGreen=
set Green=
set DarkGreen=
set LightPurple=
set Purple=
set Shadow=
#endkeyvals

byoTwemojiWhite#B
byoTwemojiWhiteGray#B
byoTwemojiLightGray#B
byoTwemojiGray#B
byoTwemojiDarkGray#B
byoTwemojiBlack#B
byoTwemojiLightBrown#B
byoTwemojiBrown#B
byoTwemojiYellow#B
byoTwemojiDarkYellow#B
byoTwemojiLightOrange#B
byoTwemojiOrange#B
byoTwemojiDarkOrange#B
byoTwemojiLightRose#B
byoTwemojiRose#B
byoTwemojiLightRed#B
byoTwemojiRed#B
byoTwemojiDarkRed#B
byoTwemojiWineRed#B
byoTwemojiDarkWineRed#B
byoTwemojiLightBlue#B
byoTwemojiBlue#B
byoTwemojiDarkBlue#B
byoTwemojiLightGreen#B
byoTwemojiGreen#B
byoTwemojiDarkGreen#B
byoTwemojiLightPurple#B
byoTwemojiPurple#B
byoTwemojiShadow#B

\forElementInList{macro}{list}#*
\byoTwemojiShadowTransparency#*
\twemojiDefaultHeight#*
\defineByoTwemojiElement{elmt name}{elmt TikZ paths}#*
\byoTwemojiElement{%<name%>!%<TikZ options%>}#*
