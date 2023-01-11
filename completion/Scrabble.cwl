# Scrabble package
# Matthew Bertucci 2023/01/10 for v0.1.3

#include:tikz
#include:pgf
#include:pgffor
#include:xstring
#include:simplekv
#include:listofitems
#include:tikzlibrarycalc
#include:tikzlibraryshapes.geometric

\ScrabbleBoard
\ScrabbleBoard[keys%keyvals]
\ScrabbleBoard<language>
\ScrabbleBoard<language>[keys%keyvals]
\begin{EnvScrabble}
\begin{EnvScrabble}[keys%keyvals]
\begin{EnvScrabble}<language>
\begin{EnvScrabble}<language>[keys%keyvals]
\end{EnvScrabble}

#keyvals:\ScrabbleBoard,\begin{EnvScrabble}
Scale=%<factor%>
ScaleLabels=%<factor%>
Border#true,false
Labels#true,false
Help#true,false
#endkeyvals

\PlateauScrabble
\PlateauScrabble[clés%keyvals]
\PlateauScrabble<langue>
\PlateauScrabble<langue>[clés%keyvals]
\begin{EnvScrabbleFR}
\begin{EnvScrabbleFR}[clés%keyvals]
\begin{EnvScrabbleFR}<language>
\begin{EnvScrabbleFR}<language>[clés%keyvals]
\end{EnvScrabbleFR}

#keyvals:\PlateauScrabble,\begin{EnvScrabbleFR}
Echelle=%<factor%>
EchelleLabels=%<factor%>
Cadre#true,false
Labels#true,false
Aide#true,false
#endkeyvals

\ScrabblePutWord{letters}{x,y}
\ScrabblePutWord[orientation%keyvals]{letters}{x,y}
\ScrabblePlaceMot{lettres}{x,y}
\ScrabblePlaceMot[orientation%keyvals]{lettres}{x,y}

#keyvals:\ScrabblePutWord,\ScrabblePlaceMot
H
V
#endkeyvals

# not documented
\AlphabetMajuscule#S
\AlphabetMinuscule#S
\PLSCRBBLEechelle#S
\PLSCRBBLEechelleLabel#S
\PLSCRBBLElangue#S
\PointsScrabbleDE#S
\PointsScrabbleEN#S
\PointsScrabbleES#S
\PointsScrabbleFR#S
\PtsScrbDE#S
\PtsScrbEN#S
\PtsScrbES#S
\PtsScrbFR#S
\scrabblescorelettre[langue]{arg}#S
\scrabblescorelettre{arg}#S
\SCRBLCD#S
\SCRBLCD[langue]#S
\SCRBLCT#S
\SCRBLCT[langue]#S
\SCRBMCD#S
\SCRBMCD[langue]#S
\SCRBMCT#S
\SCRBMCT[langue]#S