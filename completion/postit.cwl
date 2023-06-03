# postit package
# Matthew Bertucci 2023/05/31 for v0.1.0

#include:tcolorbox
#include:simplekv
#include:xstring
#include:tcolorboxlibraryskins

\begin{PostIt}
\begin{PostIt}<options tcbox>
\begin{PostIt}[clés%keyvals]
\begin{PostIt}[clés%keyvals]<options tcbox>
\end{PostIt}

#keyvals:\begin{PostIt}
Largeur=##L
Couleur=#%color
Hauteur=##L
Inclinaison=%<nombre%>
Ombre#true,false
Bordure#true,false
Coin#true,false
Attache=#Trombone,Punaise,Non
CouleurAttache=#%color
DecalAttache=##L
AlignementV=#top,center,bottom
AlignementH=#left,center,right,justify
AlignementPostIt=#top,center,bottom
#endkeyvals

\MiniPostIt{contenu%text}
\MiniPostIt[color]{contenu%text}
\MiniPostIt*{contenu%text}
\MiniPostIt*[color]{contenu%text}

\CoinPostIt#S
\TrombonePostIt#S
\EpinglePostIt#S
\PostItLarg#S
\PostItCoul#S
\PostItCoulClip#S
\PostItCoulScaleClip#S
\PostItIncline#S
\PostItHauteur#S
\PostItDeclClip#S
\PostItDeco#S
\PostItAlignV#S
\PostItAlignH#S
\PostItAlignPostIt#S