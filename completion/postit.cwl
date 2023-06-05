# postit package
# Matthew Bertucci 2023/06/05 for v0.1.1

#include:tcolorbox
#include:simplekv
#include:xstring
#include:settobox
#include:tcolorboxlibraryskins
#include:tikzlibrarycalc
#include:tikzlibrarypositioning
#include:tikzlibrarydecorations
#include:tikzlibrarydecorations.pathmorphing

\begin{PostIt}
\begin{PostIt}<options tcbox>
\begin{PostIt}[clés%keyvals]
\begin{PostIt}[clés%keyvals]<options tcbox>
\end{PostIt}

#keyvals:\begin{PostIt}
Largeur=##L
Couleur=#%color
Hauteur=##L
Rendu=#tcbox,tikz,tikzv2
Inclinaison=%<nombre%>
Ombre#true,false
Bordure#true,false
Coin#true,false
Attache=#Trombone,Punaise,Non,Scotch
CouleurAttache=#%color
DecalAttache=%<nombre%>
Titre=%<texte%>
PoliceTitre=%<font commands%>
ExtraMargeDroite=##L
AlignementV=#top,center,bottom
AlignementH=#left,center,right,justify
AlignementPostIt=#top,center,bottom
#endkeyvals

\MiniPostIt{contenu%text}
\MiniPostIt[color]{contenu%text}
\MiniPostIt*{contenu%text}
\MiniPostIt*[color]{contenu%text}

# not documented
\CoinPostIt#S
\TrombonePostIt#S
\ScotchPostIt#S
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
\PostItRender#S
\PostItExtraMargin#S
\PostItTitre#S
\PostItPoliceTitre#S
\maboitepostit#S
\HauteurEssaiTexte#S
\OffsetOmbreA#S
\OffsetOmbreB#S
\OffsetOmbreC#S
\MarginHGPostIt#S
\MarginHDPostIt#S
\MarginVHPostIt#S
\MarginVBPostIt#S
\LargeurStotch#S
\HauteurScotch#S
\PostItBorder#S
