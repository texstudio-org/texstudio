# ksbaduk package
# ponte-vecchio 2023-01-17 for v0.6.4

#keyvals:\usepackage/ksbaduk#c
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
\BadukpanSize{%<number%>}%definition
\BadukpanColor{%<color%>%color}%definition
\BackgroundColor{%<color%>%color}%definition
\NumberFont{%<font%>%font}%definition

## 2.3 Environment

\StartBaduk
\StartBadukClip{%<pos%>%position}
\StopBaduk

\begin{ksbadukpan}
\begin{ksbadukpan}[%<options%>%keyvals][%<pos%>%keyvals]
\end{ksbadukpan}

## 2.5 Stones without labels
\Black{%<pos%>}#/ksbadukpan
\BlackFirst{%<pos, pos, ...%>}#/ksbadukpan
\Blacks{%<pos, pos, ...%>}#/ksbadukpan
\White{%<pos%>}#/ksbadukpan
\WhiteFirst{%<pos, pos, ...%>}#/ksbadukpan
\Whites{%<pos, pos, ...%>}#/ksbadukpan

## 2.6 Stones with ordered labels
\BlackN{%<pos%>}{%<number%>}#/ksbadukpan
\BlackFirstN{%<pos, pos, ...%>}#/ksbadukpan
\BlackFirstN*{%<pos, pos, ...%>}#/ksbadukpan
\BlackFirstN{%<pos, pos, ...%>}[%<number%>]#/ksbadukpan
\WhiteN{%<pos%>}{%<number%>}#/ksbadukpan
\WhiteFirstN{%<pos, pos, ...%>}#/ksbadukpan
\WhiteFirstN*{%<pos, pos, ...%>}#/ksbadukpan
\WhiteFirstN{%<pos, pos, ...%>}[%<number%>]#/ksbadukpan

## 2.7 Marking the stones
\BlackM{%<pos%>}#/ksbadukpan
\BlackMs{%<pos, pos, ...%>}#/ksbadukpan
\BlackC{%<pos%>}#/ksbadukpan
\BlackCs{%<pos, pos, ...%>}#/ksbadukpan
\BlackD{%<pos%>}#/ksbadukpan
\BlackDs{%<pos, pos, ...%>}#/ksbadukpan
\WhiteM{%<pos%>}#/ksbadukpan
\WhiteMs{%<pos, pos, ...%>}#/ksbadukpan
\WhiteC{%<pos%>}#/ksbadukpan
\WhiteCs{%<pos, pos, ...%>}#/ksbadukpan
\WhiteD{%<pos%>}#/ksbadukpan
\WhiteDs{%<pos, pos, ...%>}#/ksbadukpan

## 2.8 Other commands
\KSBadukContinue
\KSBadukContinue*
\ClearHistory

## 2.9 Clearing stones
\RemoveStone{%<pos%>}#/ksbadukpan
\RemoveStone[%<color%>%keyvals]{%<pos%>}#/ksbadukpan
\RemoveStone{%<pos, pos, ...%>}#/ksbadukpan

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
\WhiteNText{%<num%>}#/ksbadukpan
\BlackNText{%<num%>}#/ksbadukpan
\WhiteMText#/ksbadukpan
\BlackMText#/ksbadukpan
\WhiteCText#/ksbadukpan
\BlackCText#/ksbadukpan
#endif