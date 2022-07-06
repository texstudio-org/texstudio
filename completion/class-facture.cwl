# facture class
# Matthew Bertucci 2022/07/05 for v1.2.2

#include:fontspec
#include:xunicode
#include:polyglossia
#include:numprint
#include:fltpoint
#include:tikz
#include:graphicx
#include:fancyhdr
#include:array
#include:longtable
#include:colortbl
#include:advdate
#include:xargs

#keyvals:\documentclass/facture#c
sansTVA
sansremise
#endkeyvals

\TVAdefaut{taux}
\type{type}
\numero{numero}
\date{JJ/MM/AAAA}
\datelimite{nbjours}
\nomemet{texte%text}
\adresseemet{texte%text}
\pied{texte%text}
\dest{adresse%text}
\fact{adresse%text}
\codedest{code}
\entete

\begin{facture}
\end{facture}
\ligne{produit%text}{prix unitaire HT}
\ligne{produit%text}{prix unitaire HT}[remise]
\ligne{produit%text}{prix unitaire HT}[remise][taux de TVA]
\ligne{produit%text}[quantité]{prix unitaire HT}
\ligne{produit%text}[quantité]{prix unitaire HT}[remise]
\ligne{produit%text}[quantité]{prix unitaire HT}[remise][taux de TVA]
\postTotaux

# not documented
\HT#S
\TTC#S
\TVA#S
\TVAtxt#*
\afficheTVA{numero}
\codeclient#*
\datelimitetxt#*
\datetxt#*
\epaisseurcadre#*
\facturation#*
\facturetxt#*
\largeurChiffres#*
\largeurChiffresAvecTVA#*
\largeurDescriptif#*
\largeurTVA#*
\libelle{text}#*
\lignesansTVA{arg1}{arg2}{arg3}{arg4}{arg5}#*
\livraison#*
\livraisonfacturation#*
\ntxt#*
\prix#S
\prixHT#*
\prixTTC#*
\prixtxt#*
\produit#*
\quantite#*
\remise#*
\tot#S
\totHT#S
\totHTtxt#*
\totTTC#S
\totTTCtxt#*
\totTVA#S
\totTVAtxt#*
\tottxt#*
\unite#*

entetes#B
encadre#B

\ifsansTVA#S
\sansTVAtrue#S
\sansTVAfalse#S
\ifsansremise#S
\sansremisetrue#S
\sansremisefalse#S