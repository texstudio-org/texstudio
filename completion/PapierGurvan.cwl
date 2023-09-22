# PapierGurvan package
# Matthew Bertucci 2023/09/12 for v0.1.0

#include:tikz
#include:simplekv
#include:xstring
#include:setspace
#include:tikzlibrarycalc
#include:tikzlibrarypositioning

GurvanBleuFonce#B
GurvanBleuCiel#B
\ColGgurvan#*

\PapierGurvan[clés%keyvals]
\PapierGurvan[clés%keyvals]<couleur>
\begin{EnvGurvan}
\begin{EnvGurvan}<couleur>
\begin{EnvGurvan}[clés%keyvals]
\begin{EnvGurvan}[clés%keyvals]<couleur>
\end{EnvGurvan}

#keyvals:\PapierGurvan,\begin{EnvGurvan}
NbCarreaux=%<nbCol%>x%<nbLig%>
Unite=%<nombre%>
Marge=%<nombre%>
AffBarres#true,false
Interligne=%<nombre%>
CouleurBarre=#%color
#endkeyvals

\EcrireLigneGurvan{texte%text}
\EcrireLigneGurvan<alignement>{texte%text}
\EcrireLigneGurvan[clés%keyvals]{texte%text}
\EcrireLigneGurvan[clés%keyvals]<alignement>{texte%text}
\PasseLigneGurvan

#keyvals:\EcrireLigneGurvan
DecalH=%<nombre%>
DecalV=##L
Echelle=%<nombre%>
#endkeyvals

\begin{PleinePageGurvan}
\begin{PleinePageGurvan}[clés%keyvals]
\end{PleinePageGurvan}

#keyvals:\begin{PleinePageGurvan}
Interligne=%<nombre%>
Papier=#A4,A5
CoulLignes=#%color
CoulFondClair=#%color
CoulFondFonce=#%color
Marges=%<MargeGauche%>/%<MargeDroite%>
NumLignes#true,false
#endkeyvals

\LigneGurvan{texte%text}
\LigneGurvan<alignement>{texte%text}
\LigneGurvan[clés%keyvals]{texte%text}
\LigneGurvan[clés%keyvals]<alignement>{texte%text}
\LigneGurvan[clés%keyvals]<alignement>(ajustement){texte%text}

#keyvals:\LigneGurvan
Couleur=#%color
Ligne=%<numéro%>
Echelle=%<nombre%>
DecalBord=%<nombre%>
TaillePolice=%<nombre%>
#endkeyvals

\ParagrapheGurvan{texte%text}
\ParagrapheGurvan<alignement>{texte%text}
\ParagrapheGurvan[clés%keyvals]{texte%text}
\ParagrapheGurvan[clés%keyvals]<alignement>{texte%text}
\ParagrapheGurvan[clés%keyvals]<alignement>(ajustement){texte%text}

#keyvals:\ParagrapheGurvan
Couleur=#%color
Ligne=%<numéro%>
Echelle=%<nombre%>
DecalBord=%<nombre%>
Espacement=
#endkeyvals

# not documented
\thelggurvan#S