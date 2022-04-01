# Yvon Henel, alias Le TeXnicien de surface, 2020-10-24
# Time-stamp: <2020-10-24 18:05:56 Yvon Henel (TdS)>
# tdsfrmath.cwl (v1, 2020-10-24)
# texstudio style file for tdsfrmath (v1.3)

#include:ifthen
#include:xkeyval
#include:xstring
#include:amsmath
#include:amssymb
#include:xspace
#include:xargs
#include:suffix
#include:mathrsfs

#keyvals:\usepackage/tdsfrmath#c
ArgArcMaj#true,false
avecmathdesign#true,false
calcomd=%<csname%>
caloptn=%<option%>
calpack=%<package%>
CharPoCal#true,false
CharPoGdT#true,false
ensdeco=#ehsb,ebsb,ehsh,ebsh,sbeb,sheh
gdtcomd=%<csname%>
gdtoptn=%<option%>
gdtpack=%<package%>
nupletsep=#virgule,pointvirgule
placesigne=#haut,bas
SepDefEnsExt#true,false
suite#true,false
suitedeco#true,false
taupe#true,false
#endkeyvals

\nuplet{valeurs%formula}
\anuplet{valeurs%formula}
\rnuplet{valeurs}#m
\rnuplet{valeurs}[écart]#m
\rnuplet[md]{valeurs}#m
\rnuplet[md]{valeurs}[écart]#m
\parent{valeurs%formula}
\accol{valeur%formula}
\crochet{valeur%formula}
\varabs{valeur%formula}
\norme{valeur%formula}
\EncloreExtensible{délim-gauche%formula}{délim-droite%formula}{texte%formula}#*
\EncloreExtensible[md]{délim-gauche%formula}{délim-droite%formula}{texte%formula}#*
\EnsembleDeNombre{lettre}{sup%formula}{arg3}{arg4}#*
\grastab{lettre}#*
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
\C
\C[sup%formula]
\N
\N[sup%formula]
\Q
\Q[sup%formula]
\R
\R[sup%formula]
\Z
\Z[sup%formula]
\K
\K[sup%formula]
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
\definirvecteur{a%formula}{n}{m}
\definirvecteur[bb]{a%formula}{n}{m}
\redefinirvecteur{a%formula}{n}{m}
\redefinirvecteur[bb]{a%formula}{n}{m}
\vecti
\vectj
\vectk
\vectu
\vectv
\vecteur{texte%formula}
\vecteur{texte%formula}[espace-après]
\vecteur[espace-avant]{texte%formula}
\vecteur[espace-avant]{texte%formula}[espace-après]
\vecteur*{texte%formula}
\vecteur*{texte%formula}[espace-après]
\vecteur*[espace-avant]{texte%formula}
\vecteur*[espace-avant]{texte%formula}[espace-après]
\V{texte%formula}
\V{texte%formula}[espace-après]
\V[espace-avant]{texte%formula}
\V[espace-avant]{texte%formula}[espace-après]
\V*{texte%formula}
\V*{texte%formula}[espace-après]
\V*[espace-avant]{texte%formula}
\V*[espace-avant]{texte%formula}[espace-après]
\base
\base[%<dimension : 1, 2 ou 3%>]
\repere
\repere[%<dimension : 1, 2 ou 3%>]
\repere[%<dimension : 1, 2 ou 3%>][%<centre%>]
\rog#n
\rog[%<dimension : 1, 2 ou 3%>]#n
\rog[%<dimension : 1, 2 ou 3%>][%<centre%>]#n
\ron#n
\ron[%<dimension : 1, 2 ou 3%>]#n
\ron[%<dimension : 1, 2 ou 3%>][%<centre%>]#n
\rond#n
\rond[%<dimension : 1, 2 ou 3%>]#n
\rond[%<dimension : 1, 2 ou 3%>][%<centre%>]#n
\repcom
\roncom#n
\rondcom#n
\Repere
\Repere*
\Rog#n
\Ron#n
\Rond#n
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
\E
\eu{exposant%formula}
\I
\D
\FixeAvanceDx{nombre}#*
\FixeReculIntegrande{nombre}#*
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
\intgen{inf%formula}{sup%formula}{intégrande%formula}
\intgen[md]{inf%formula}{sup%formula}{intégrande%formula}
\intgen[md][recul]{inf%formula}{sup%formula}{intégrande%formula}
\integrer{inf%formula}{sup%formula}{intégrande%formula}{variable%formula}
\integrer[md]{inf%formula}{sup%formula}{intégrande%formula}{variable%formula}
\integrer[md][recul]{inf%formula}{sup%formula}{intégrande%formula}{variable%formula}
\integrale{inf%formula}{sup%formula}{nom de fonction%formula}{variable%formula}
\integrale[md]{inf%formula}{sup%formula}{nom de fonction%formula}{variable%formula}
\integrale[md][recul]{inf%formula}{sup%formula}{nom de fonction%formula}{variable%formula}
\intabfx
\intabfx[md]
\intabfx[md][recul]
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
\plusinf
\moinsinf
\interff{bornes%formula}
\interoo{bornes%formula}
\interfo{bornes%formula}
\interof{bornes%formula}
\intferab#*
\manus{%<une lettre%>}
\ensemble{domaine%formula}{attributs%formula}
\ensemble{domaine%formula}{attributs%formula}[espace-après]
\ensemble[espace-avant]{domaine%formula}{attributs%formula}
\ensemble[espace-avant]{domaine%formula}{attributs%formula}[espace-après]
\vide
\dans#m
\donne#m
\ppq
\pgq
\cnp{n%formula}{p%formula}
\mdfrac{numerator%formula}{denominator%formula}
\mfrac{numerator%formula}{denominator%formula}
# ==========================================================================

#ifOption:suite
\suite
\suite[texte%formula]
\suite*
\suite*[deco%formula]
\suite*[deco%formula][texte%formula]
\suitar{raison%formula}{premier%formula}#n
\suitar[texte%formula]{raison%formula}{premier%formula}#n
\suitar{raison%formula}[rang%formula]{premier%formula}#n
\suitar{raison%formula}{premier%formula}[entre%formula]#n
\suitar[texte%formula]{raison%formula}[rang%formula]{premier%formula}#n
\suitar{raison%formula}[rang%formula]{premier%formula}[entre%formula]#n
\suitar[texte%formula]{raison%formula}[rang%formula]{premier%formula}[entre%formula]#n
\suitar*{raison%formula}{premier%formula}#n
\suitar*[texte%formula]{raison%formula}{premier%formula}#n
\suitar*{raison%formula}[rang%formula]{premier%formula}#n
\suitar*{raison%formula}{premier%formula}[entre%formula]#n
\suitar*[texte%formula]{raison%formula}[rang%formula]{premier%formula}#n
\suitar*{raison%formula}[rang%formula]{premier%formula}[entre%formula]#n
\suitar*[texte%formula]{raison%formula}[rang%formula]{premier%formula}[entre%formula]#n
\suitgeo{raison%formula}{premier%formula}#n
\suitgeo[texte%formula]{raison%formula}{premier%formula}#n
\suitgeo{raison%formula}[rang%formula]{premier%formula}#n
\suitgeo{raison%formula}{premier%formula}[entre%formula]#n
\suitgeo[texte%formula]{raison%formula}[rang%formula]{premier%formula}#n
\suitgeo{raison%formula}[rang%formula]{premier%formula}[entre%formula]#n
\suitgeo[texte%formula]{raison%formula}[rang%formula]{premier%formula}[entre%formula]#n
\suitgeo*{raison%formula}{premier%formula}#n
\suitgeo*[texte%formula]{raison%formula}{premier%formula}#n
\suitgeo*{raison%formula}[rang%formula]{premier%formula}#n
\suitgeo*{raison%formula}{premier%formula}[entre%formula]#n
\suitgeo*[texte%formula]{raison%formula}[rang%formula]{premier%formula}#n
\suitgeo*{raison%formula}[rang%formula]{premier%formula}[entre%formula]#n
\suitgeo*[texte%formula]{raison%formula}[rang%formula]{premier%formula}[entre%formula]#n
#endif

# ==========================================================================

#ifOption:taupe
#include:stmaryrd
\prodscal{deux vecteurs%formula}
\Ker#m
\Img#m
\tendversen{%<valeur%>}#m
\devlim{ordre du DL%formula}
\devlim[en%formula]{ordre du DL%formula}
\drv{fonction%formula}{variable%formula}
\drv[n-ième]{fonction%formula}{variable%formula}
\ddrv{fonction%formula}{variable%formula}
\ddrv[n-ième]{fonction%formula}{variable%formula}
\derpart{dessus%formula}{dessous%formula}
\interent{bornes entières%formula}
\interent{bornes entières%formula}[espace-après]
\interent[md]{bornes entières%formula}
\interent[md]{bornes entières%formula}[espace-après]
\interent[md][espace-avant]{bornes entières%formula}
\interent[md][espace-avant]{bornes entières%formula}[espace-après]
\interzn
\interzn[md]
\interzn[md][espace-avant]
\interzn[md][espace-avant][espace-après]
\parties{ensemble%formula}
\parties[n]{ensemble%formula}
\argsh#m
\argch#m
\argth#m
#endif

\TdSMDerPartSepar#*
\TdSMnuplet{arg}#*m
\TdSMReculParenthese#*
\TdSMsepdefens#*
\filedate#S
\fileversion#S
