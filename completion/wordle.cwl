# wordle package
# Matthew Bertucci 2023/07/13 for v0.1.0

#include:tikz
#include:simplekv
#include:xstring

## English version
\begin{WordleGrid}{word%text}
\begin{WordleGrid}[keyvals]{word%text}
\end{WordleGrid}

#keyvals:\begin{WordleGrid}
Colors={%<back,misplaced,good%>}
Rounded=%<number%>
Unit=%<number%>
Font=%<font commands%>
ColorLetters=#%color
BorderColor=#%color
Letters#true,false
Style=
Thickness=%<number%>
#endkeyvals

## French version
\begin{GrilleSutom}{mot%text}
\begin{GrilleSutom}[clés%keyvals]{mot%text}
\end{GrilleSutom}

#keyvals:\begin{GrilleSutom}
Couleurs={%<fond,mal placée,bien placée%>}
Arrondi=%<nombre%>
Unite=%<nombre%>
Police=%<font commands%>
CouleurLettres=#%color
CouleurBordure=#%color
Lettres#true,false
Style=
Epaisseur=%<number%>
#endkeyvals

# not documented
\SutomCouleurs#S
\SutomRounded#S
\SutomUnit#S
\SutomFonte#S
\SutomFonteColor#S
\SutomStyle#S
\SutomWidth#S
\SutomBorder#S
WordleBack#B
WordleBad#B
WordleGood#B