# mousik package
# Matthew Bertucci 2026/08/25 for v0.1

#include:harmony
#include:musixtex
#include:tikz
#include:tikzlibrarybackgrounds

\begin{mousik}#\pictureHighlight
\begin{mousik}[options%keyvals]#\pictureHighlight
\end{mousik}

\begin{Slurred}{begin height}{end height}
\begin{Slurred}[options%keyvals]{begin height}{end height}
\end{Slurred}
\begin{Crescendo}
\begin{Crescendo}[options%keyvals]
\end{Crescendo}
\begin{Decrescendo}
\begin{Decrescendo}[options%keyvals]
\end{Decrescendo}

\begin{mousikSlurred}{begin height}{end height}#*
\begin{mousikSlurred}[options%keyvals]{begin height}{end height}#*
\end{mousikSlurred}#*
\begin{mousikCrescendo}#*
\begin{mousikCrescendo}[options%keyvals]#*
\end{mousikCrescendo}#*
\begin{mousikDecrescendo}#*
\begin{mousikDecrescendo}[options%keyvals]#*
\end{mousikDecrescendo}#*

\mousikInit
\mousikInit[options%keyvals]

\Acc[options%keyvals]{type}{height}
\Accs[options%keyvals]{type/height,...}
\AccSpace
\AccSpace[number]
\Accs{type/height,...}
\Acc{type}{height}
\Appog[options%keyvals]{duration}{height}
\Appogs[options%keyvals]{duration/height,...}
\Appogs{duration/height,...}
\Appog{duration}{height}
\Artic[options%keyvals]{type}{height}
\Artics[options%keyvals]{type/height,...}
\Artics{type/height,...}
\Artic{type}{height}
\Barline
\Barline[options%keyvals]
\BreakLine
\Clef
\Clef[options%keyvals]
\Dotted[options%keyvals]{height}
\Dotted{height}
\Dynamics[options%keyvals]{text}
\Dynamics{text}
\Key{number}
\LowerStaff
\MixedKey{old}{new}
\NoKey{number}
\Note[options%keyvals]{duration}{height}
\NoteSpace
\NoteSpace[number]
\Note{duration}{height}
\Rest[options%keyvals]{duration}
\Rest{duration}
\Slur[options%keyvals]{begin height}{end height}
\Slur{begin height}{end height}
\Space
\Space[number]
\Symbol[options%keyvals]{type}
\Symbol{type}
\Tempo[options%keyvals]{duration}{tempo}
\Tempo{duration}{tempo}
\Text[options%keyvals]{text}
\Text{text}
\Tie[options%keyvals]{height}
\Tie{height}
\TimeSig[options%keyvals]{upper}{lower}
\TimeSig{upper}{lower}
\UpperStaff

\mousikAcc[options%keyvals]{type}{height}#*
\mousikAccs[options%keyvals]{type/height,...}#*
\mousikAccSpace#*
\mousikAccSpace[number]#*
\mousikAccs{type/height,...}#*
\mousikAcc{type}{height}#*
\mousikAppog[options%keyvals]{duration}{height}#*
\mousikAppogs[options%keyvals]{duration/height,...}#*
\mousikAppogs{duration/height,...}#*
\mousikAppog{duration}{height}#*
\mousikArtic[options%keyvals]{type}{height}#*
\mousikArtics[options%keyvals]{type/height,...}#*
\mousikArtics{type/height,...}#*
\mousikArtic{type}{height}#*
\mousikBarline#*
\mousikBarline[options%keyvals]#*
\mousikBreakLine#*
\mousikClef#*
\mousikClef[options%keyvals]#*
\mousikDotted[options%keyvals]{height}#*
\mousikDotted{height}#*
\mousikDynamics[options%keyvals]{text}#*
\mousikDynamics{text}#*
\mousikKey{number}#*
\mousikLowerStaff#*
\mousikMixedKey{old}{new}#*
\mousikNoKey{number}#*
\mousikNote[options%keyvals]{duration}{height}#*
\mousikNoteSpace#*
\mousikNoteSpace[number]#*
\mousikNote{duration}{height}#*
\mousikRest[options%keyvals]{duration}#*
\mousikRest{duration}#*
\mousikSlur[options%keyvals]{begin height}{end height}#*
\mousikSlur{begin height}{end height}#*
\mousikSpace#*
\mousikSpace[number]#*
\mousikSymbol[options%keyvals]{type}#*
\mousikSymbol{type}#*
\mousikTempo[options%keyvals]{duration}{tempo}#*
\mousikTempo{duration}{tempo}#*
\mousikText[options%keyvals]{text}#*
\mousikText{text}#*
\mousikTie[options%keyvals]{height}#*
\mousikTie{height}#*
\mousikTimeSig[options%keyvals]{upper}{lower}#*
\mousikTimeSig{upper}{lower}#*
\mousikUpperStaff#*