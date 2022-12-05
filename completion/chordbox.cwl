# chordbox package
# Matthew Bertucci 2022/09/26 for v1.0

#include:tikz
#include:tikzlibraryshapes.misc
#include:tikzlibrarybackgrounds
#include:xifthen
#include:xstring

\chordbox{chord-name%formula}{fret-positions}
\chordbox[base-fret]{chord-name%formula}{fret-positions}
\bchordbox{chord-name%formula}{fret-positions}{barre-frets}
\bchordbox[base-fret]{chord-name%formula}{fret-positions}{barre-frets}

# not documented
\begin{chordboxenv}{basefret}{chord-name%formula}{fret-positions}#*
\end{chordboxenv}#*
\numfrets#S
\pitch#S
\nodetext#S
\frettext#S
\fretnum#S
