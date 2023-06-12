# postit package
# Matthew Bertucci 2023/06/12 for v0.1.3

#include:tcolorbox
#include:simplekv
#include:xstring
#include:settobox
#include:varwidth
#include:tcolorboxlibraryskins
#include:tikzlibrarycalc
#include:tikzlibrarypositioning
#include:tikzlibrarydecorations
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibrarybabel

## French versions of commands ##
\begin{PostIt}
\begin{PostIt}<options tcbox>
\begin{PostIt}[clés%keyvals]
\begin{PostIt}[clés%keyvals]<options tcbox>
\end{PostIt}

#keyvals:\begin{PostIt}
RappelPostIt=%<nom%>
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

## English version of environment ##
\begin{PostItNote}
\begin{PostItNote}<tcbox options>
\begin{PostItNote}[options%keyvals]
\begin{PostItNote}[options%keyvals]<tcbox options>
\end{PostItNote}

#keyvals:\begin{PostItNote}
StorePostIt=%<name%>
Width=##L
Color=#%color
Height=##L
Render=#tcbox,tikz,tikz2
Rotate=%<degrees%>
Shadow#true,false
Border#true,false
Corner#true,false
Pin=#Paperclip,Pushpin,None,Scotch
PinColor=#%color
PinScale=%<factor%>
PinShift=%<number%>
Title=%<text%>
FontTitle=%<font commands%>
ExtraRightMargin=##L
AlignV=#top,center,bottom
AlignH=#left,center,right,justify
AlignPostIt=#top,center,bottom
#endkeyvals

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
\PostItRappel#S
