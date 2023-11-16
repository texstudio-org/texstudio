# WriteOnGrid package
# Matthew Bertucci 2023/11/15 for v0.1.5

#include:tikz
#include:simplekv
#include:xstring
#include:tikzlibrarycalc
#include:tikzlibrarypositioning
#include:setspace

TyrianPurple#B
PapierRose#B
PapierGris#B
\ColSeyes
\ColRuled

\DispGrid[keyvals]
\DispGrid[keyvals]<color>

\begin{EnvGrid}[keyvals]
\begin{EnvGrid}[keyvals]<color>
\end{EnvGrid}

#keyvals:\DispGrid,\begin{EnvGrid}
NumSquares=%<<cols>x<rows>%>
Unit=%<number%>
Margin=%<number%>
DispBar#true,false
Enlarge=%<L/R%>
Border#true,false
Grid=#5x5,Seyes,Ruled
Seyes#true,false
#endkeyvals

\WriteLine{text}
\WriteLine<alignment>{text}
\WriteLine[keyvals]{text}
\WriteLine[keyvals]<alignment>{text}

#keyvals:\WriteLine
OffsetH=%<num squares%>
OffsetV=##L
Scale=%<factor%>
#endkeyvals

\PassLine

# French versions of commands
\CoulSeyes
\CoulRuled

\AffQuadrillage[clés%keyvals]
\AffQuadrillage[clés%keyvals]<color>

\begin{EnvQuadrillage}[clés%keyvals]
\begin{EnvQuadrillage}[clés%keyvals]<color>
\end{EnvQuadrillage}

#keyvals:\AffQuadrillage,\begin{EnvQuadrillage}
NbCarreaux=%<<nbCol>x<nbLig>%>
Unite=%<nombre%>
Marge=%<nombre%>
AffBarre#true,false
Elargir=%<L/R%>
Cadre#true,false
Grille=#5x5,Seyes,Ruled
ReglureSeyes=%<nombre%>
CouleurBarreSeyes=#%color
#endkeyvals

\EcrireLigne{text}
\EcrireLigne<alignement>{text}
\EcrireLigne[clés%keyvals]{text}
\EcrireLigne[clés%keyvals]<alignement>{text}

#keyvals:\EcrireLigne
DecalH=%<nombre carreaux%>
DecalV=##L
Echelle=%<factor%>
#endkeyvals

\PasseLigne

\begin{PleinePageSeyes}
\begin{PleinePageSeyes}[options%keyvals]
\end{PleinePageSeyes}

#keyvals:\begin{PleinePageSeyes}
CouleurP=#%color
CouleurS=#%color
CouleurMarge=#%color
NumLignes#true,false
ReglureSeyes=%<nombre%>
FormatPapier=#A4,A5,lxh
#endkeyvals

\LignePapierSeyes{text}
\LignePapierSeyes[options%keyvals]{text}
\LignePapierSeyes[options%keyvals]<alignement>(ajustement){text}

#keyvals:\LignePapierSeyes
Couleur=#%color
Ligne=%<numéro%>
Echelle=%<nombre%>
Largeur=%<nombre%>
#endkeyvals

\CadreNoteSeyes{numligne}
\CadreNoteSeyes[hauteur]{numligne}

\ParagraphePapierSeyes{text}
\ParagraphePapierSeyes[options%keyvals]{text}
\ParagraphePapierSeyes[options%keyvals]<alignement>(ajustement){text}

#keyvals:\ParagraphePapierSeyes
Couleur=#%color
Ligne=%<numéro%>
Echelle=%<nombre%>
Espacement=%<nombre%>
Largeur=%<nombre%>
#endkeyvals

\begin{PleinePageCinqCinq}
\begin{PleinePageCinqCinq}[options%keyvals]
\end{PleinePageCinqCinq}

#keyvals:\begin{PleinePageCinqCinq}
Couleur=#%color
CouleurMarge=#%color
NumLignes#true,false
FormatPapier=#A4,A5,lxh
#endkeyvals

\LignePapierCinqCinq{text}
\LignePapierCinqCinq[options%keyvals]{text}
\LignePapierCinqCinq[options%keyvals]<alignement>(ajustement){text}

#keyvals:\LignePapierCinqCinq
Couleur=#%color
Ligne=%<numéro%>
Echelle=%<nombre%>
Largeur=%<nombre%>
#endkeyvals

\CadreNoteCinqCinq{numligne}
\CadreNoteCinqCinq[hauteur]{numligne}

\ParagraphePapierCinqCinq{text}
\ParagraphePapierCinqCinq[options%keyvals]{text}
\ParagraphePapierCinqCinq[options%keyvals]<alignement>(ajustement){text}

#keyvals:\ParagraphePapierCinqCinq
Couleur=#%color
Ligne=%<numéro%>
Echelle=%<nombre%>
Espacement=%<nombre%>
Largeur=%<nombre%>
#endkeyvals

\begin{PleinePageRuled}
\begin{PleinePageRuled}[options%keyvals]
\end{PleinePageRuled}

#keyvals:\begin{PleinePageRuled}
Couleur=#%color
CouleurMarge=#%color
NumLignes#true,false
FormatPapier=#A4,A5,lxh
#endkeyvals

\LignePapierRuled{text}
\LignePapierRuled[options%keyvals]{text}
\LignePapierRuled[options%keyvals]<alignement>(ajustement){text}

#keyvals:\LignePapierRuled
Couleur=#%color
Ligne=%<numéro%>
Echelle=%<nombre%>
Largeur=%<nombre%>
#endkeyvals

\CadreNoteRuled{numligne}
\CadreNoteRuled[hauteur]{numligne}

\ParagraphePapierRuled{text}
\ParagraphePapierRuled[options%keyvals]{text}
\ParagraphePapierRuled[options%keyvals]<alignement>(ajustement){text}

#keyvals:\ParagraphePapierRuled
Couleur=#%color
Ligne=%<numéro%>
Echelle=%<nombre%>
Espacement=%<nombre%>
Largeur=%<nombre%>
#endkeyvals

# not documented
\CCFullCoul#S
\CCFullCoulM#S
\CCLigne#S
\CCLigneCouleur#S
\CCLigneEchelle#S
\CCLigneLarg#S
\CCPar#S
\CCParBase#S
\CCParCouleur#S
\CCParEchelle#S
\CCParLarg#S
\QuadCoulA#S
\QuadCoulB#S
\QuadCoulSeyes#S
\QuadEchelle#S
\QuadElar#S
\QuadElarD#S
\QuadElarG#S
\QuadNbCar#S
\QuadNbLig#S
\QuadReglureSeyes#S
\QuadType#S
\RuledFullCoul#S
\RuledFullCoulMarge#S
\RuledLigne#S
\RuledLigneCouleur#S
\RuledLigneEchelle#S
\RuledLigneLarg#S
\RuledPar#S
\RuledParBase#S
\RuledParCouleur#S
\RuledParEchelle#S
\RuledParLarg#S
\SeyesFullCoulM#S
\SeyesFullCoulP#S
\SeyesFullCoulS#S
\SeyesLigne#S
\SeyesLigneCouleur#S
\SeyesLigneEchelle#S
\SeyesLigneLarg#S
\SeyesPar#S
\SeyesParBase#S
\SeyesParCouleur#S
\SeyesParEchelle#S
\SeyesParLarg#S
\thelgquadri#S
\ValeurCarreau#S
