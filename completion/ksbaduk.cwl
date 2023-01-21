# ksbaduk package
# ponte-vecchio 2023-01-17 for v0.6.4

#include:tikz

#keyvals:\usepackage/ksbaduk#c,\begin{ksbadukpan}#c
ball
plain
badukpancolor=#%color
badukpansize=%<number%>
posmark
imageback
imagefile=%<file%>
textcmds
numberfont=%<font%>
tmarkfont=%<font%>
#endkeyvals

## 2.2 Global options
\BadukpanSize{%<number%>}
\BadukpanColor{color}
\BackgroundColor{color}
\NumberFont{%<font%>}

## 2.3 Environment
\StartBaduk
\StartBadukClip{%<pos%>}
\StopBaduk

\begin{ksbadukpan}
\begin{ksbadukpan}[%<options%>][%<pos%>]
\end{ksbadukpan}

## 2.5 Stones without labels
\Black{%<pos%>}#/ksbadukpan
\BlackFirst{%<pos, ...%>}#/ksbadukpan
\Blacks{%<pos, ...%>}#/ksbadukpan
\White{%<pos%>}#/ksbadukpan
\WhiteFirst{%<pos, ...%>}#/ksbadukpan
\Whites{%<pos, ...%>}#/ksbadukpan

## 2.6 Stones with ordered labels
\BlackN{%<pos%>}{%<number%>}#/ksbadukpan
\BlackFirstN{%<pos, ...%>}#/ksbadukpan
\BlackFirstN*{%<pos, ...%>}#/ksbadukpan
\BlackFirstN{%<pos, ...%>}[%<number%>]#/ksbadukpan
\WhiteN{%<pos%>}{%<number%>}#/ksbadukpan
\WhiteFirstN{%<pos, ...%>}#/ksbadukpan
\WhiteFirstN*{%<pos, ...%>}#/ksbadukpan
\WhiteFirstN{%<pos, ...%>}[%<number%>]#/ksbadukpan

## 2.7 Marking the stones
\BlackM{%<pos%>}#/ksbadukpan
\BlackMs{%<pos, ...%>}#/ksbadukpan
\BlackC{%<pos%>}#/ksbadukpan
\BlackCs{%<pos, ...%>}#/ksbadukpan
\BlackD{%<pos%>}#/ksbadukpan
\BlackDs{%<pos, ...%>}#/ksbadukpan
\WhiteM{%<pos%>}#/ksbadukpan
\WhiteMs{%<pos, ...%>}#/ksbadukpan
\WhiteC{%<pos%>}#/ksbadukpan
\WhiteCs{%<pos, ...%>}#/ksbadukpan
\WhiteD{%<pos%>}#/ksbadukpan
\WhiteDs{%<pos, ...%>}#/ksbadukpan
\Blanket{%<pos%>}{%<text%>}#/ksbadukpan
\TextMark{%<pos%>}{%<text%>}#/ksbadukpan

## 2.8 Other commands
\KSBadukContinue
\KSBadukContinue*
\ClearHistory

## 2.9 Clearing stones
\RemoveStone{%<pos%>}#/ksbadukpan
\RemoveStone[B|W%keyvals]{pos}#/ksbadukpan
\RemoveStone{%<pos, ...%>}#/ksbadukpan

#keyvals:\RemoveStone#c
B
W
#endkeyvals

## 2.10 Splitting the badukpan
\KSpar
\ProceedNextScene{%<cmds%>}#/ksbadukpan
\ProceedNextSceneComment{%<description%>}#/ksbadukpan

## 2.11 Saving and loading games
\SaveKSBaduk{%<game name%>}
\LoadKSBaduk{%<game name%>}
\DeleteSavedKSBaduk{%<game name%>}

## 2.12 Using the sgf (Smart Game Format)
\SGFLine{%<sgf line%>}#/ksbadukpan
\ResetSGFCounter#/ksbadukpan
\ResetSFGCounter[%<number%>]#/ksbadukpan

## 2.13 Text commands
#ifOption:textcmds
\WhiteNText{%<number%>}#/ksbadukpan
\BlackNText{%<number%>}#/ksbadukpan
\WhiteMText#/ksbadukpan
\BlackMText#/ksbadukpan
\WhiteCText#/ksbadukpan
\BlackCText#/ksbadukpan
#endif

# not documented
\Bb#S
\BlackFirstNumber{arg1}{arg2}#S
\DeleteSavedKSGo{game name}#S
\GobanColor{color}#S
\GobanSize{size}#S
\KSGoContinue#S
\LoadKSGo{game name}#S
\SaveKSGo{game name}#S
\StartGo#S
\StartGoClip{pos}#S
\StopGo#S
\Wb#S
\WhiteFirstNumber{arg1}{arg2}#S
