# chordbars package
# Matthew Bertucci 12/20/2021 for v1.1

#include:calc
#include:ifthen
#include:pgfmath
#include:tikz
#include:tikzlibrarymath
#include:tikzlibraryshapes
#include:tkz-euclide

\begin{chordbar}{num of bars}{name}
\begin{chordbar}[repetitions]{num of bars}{name}#*
\end{chordbar}

\chordf{note}
\chordh{note1}{note2}
\repeatBar
\repeatBarPair
\addHalfBar{note}

\chordline{note}{num of bars}{name}

\countbarsYes
\countbarsNo
\sharp
\flat
\songtitle
\printNbBars
\bpm{number}
\resetchordbars

\theNumMesure#*
\theNumPart#*
\theCurrentBarInLine#*
\theCurrentBar#*
\theCurrentLine#*
\NumberOfBarsPerLine#*
\barsize#*
\chordFontSize#*
\bpbfour#*
\bpbthree#*
\vspacebefore#*
\vspaceafter#*
\NbBarsInitialLine#*
\bpb#*
\delta#*
\nbbars#*
\newchordline#*
\tempoBPM#*
\titleFontSize#*
\OLDflat#S
\OLDsharp#S
