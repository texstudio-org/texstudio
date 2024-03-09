# chordbars package
# Matthew Bertucci 2024/03/08 for v1.3.2

#include:calc
#include:ifthen
#include:wasysym
#include:relsize
#include:pgfmath
#include:tikz
#include:tikzlibrarymath
#include:tikzlibraryshapes
#include:tkz-euclide

\begin{chordbar}{num of bars}{name}
\begin{chordbar}[repetitions]{num of bars}{name}#*
\end{chordbar}
\begin{chordbar*}{num of bars}{name}
\begin{chordbar*}[repetitions]{num of bars}{name}#*
\end{chordbar*}

\addHalfBar{note}
\addMeasures{number}
\addN
\bpm{number}
\chordf{note}
\chordh{note1}{note2}
\chordline{note}{num of bars}{name}
\countbarsNo
\countbarsYes
\dim
\flat
\MajS
\printNbBars
\repeatBar
\repeatBarPair
\resetchordbars
\sharp
\songtitle
\susF

\barsize#*
\bpbfour#*
\bpbthree#*
\chordFontSize#*
\NumberOfBarsPerLine#*
\ycoeff#*

\bpb#S
\nbbars#S
\NbBarsInitialLine#S
\newchordline#S
\OLDflat#S
\OLDsharp#S
\tempoBPM#S
\theCurrentBar#S
\theCurrentBarInLine#S
\theCurrentLine#S
\theNumMesure#S
\theNumPart#S
\titleFontSize#S
\vspaceafter#S
\vspacebefore#S
