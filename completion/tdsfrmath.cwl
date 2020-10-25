# Yvon Henel, alias Le TeXnicien de surface, 2020-10-24
# Time-stamp: <2020-10-24 18:05:56 Yvon Henel (TdS)>
# tdsfrmath.cwl (v1, 2020-10-24)
# texstudio style file for tdsfrmath (v1.3)
\nuplet{%<valeurs%>}#
\anuplet{%<valeurs%>}#
\parent{%<valeurs%>}#
\accol{%<valeurs%>}#
\crochet{%<valeurs%>}#
\varabs{%<valeurs%>}#
\norme{%<valeur%>}#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
\vecti#
\vectj#
\vectk#
\vectu#
\vectv#
\vecteur{%<texte%>}#
\vecteur*{%<texte%>}#
\V{%<texte%>}#
\V*{%<texte%>}#
\base#
\base[%<dimension : 1, 2 ou 3%>]#
\repere#
\repere[%<dimension : 1, 2 ou 3%>]#
\repere[%<dimension : 1, 2 ou 3%>][%<centre%>]#
\rog#n
\rog[%<dimension : 1, 2 ou 3%>]#n
\rog[%<dimension : 1, 2 ou 3%>][%<centre%>]#n
\ron#n
\ron[%<dimension : 1, 2 ou 3%>]#n
\ron[%<dimension : 1, 2 ou 3%>][%<centre%>]#n
\rond#n
\rond[%<dimension : 1, 2 ou 3%>]#n
\rond[%<dimension : 1, 2 ou 3%>][%<centre%>]#n
\repcom#
\roncom#n
\rondcom#n
\Repere#
\Repere*#
\Rog#n
\Ron#n
\Rond#n
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
\eu{%<exposant%>}#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
\intgen{%<inf%>}{%<sup%>}{%<intégrande%>}#
\integrer{%<inf%>}{%<sup%>}{%<intégrande%>}{%<variable%>}#
\integrale{%<inf%>}{%<sup%>}{%<nom de fonction%>}{%<variable%>}#
\intabfx#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
\plusinf#
\moinsinf#
\interff{%<bornes%>}#
\interoo{%<bornes%>}#
\interfo{%<bornes%>}#
\interof{%<bornes%>}#
\manus{%<une lettre%>}#
\ensemble{%<domaine%>}{%<attributs%>}#
\vide#
\dans#
\donne#
\ppq#
\pgq#
\cnp{%<n%>}{%<p%>}#
# ==========================================================================
#ifOption:suite
\suite#
\suite[%<lettre%>]#
\suitar{%<raison%>}{%<premier%>}#n
\suitar[%<lettre%>]{%<raison%>}{%<premier%>}#n
\suitar{%<raison%>}[%<rang%>]{%<premier%>}#n
\suitar{%<raison%>}{%<premier%>}[%<texte entre%>]#n
\suitar[%<lettre%>]{%<raison%>}[%<rang%>]{%<premier%>}#n
\suitar{%<raison%>}[%<rang%>]{%<premier%>}[%<texte entre%>]#n
\suitar[%<lettre%>]{%<raison%>}[%<rang%>]{%<premier%>}[%<texte entre%>]#n
\suitgeo{%<raison%>}{%<premier%>}#n
\suitgeo[%<lettre%>]{%<raison%>}{%<premier%>}#n
\suitgeo{%<raison%>}[%<rang%>]{%<premier%>}#n
\suitgeo{%<raison%>}{%<premier%>}[%<texte entre%>]#n
\suitgeo[%<lettre%>]{%<raison%>}[%<rang%>]{%<premier%>}#n
\suitgeo{%<raison%>}[%<rang%>]{%<premier%>}[%<texte entre%>]#n
\suitgeo[%<lettre%>]{%<raison%>}[%<rang%>]{%<premier%>}[%<texte entre%>]#n
#endif
# ==========================================================================
#ifOption:taupe
\prodscal{%<deux vecteurs%>}#
\Ker#
\Img#
\tendsversen{%<valeur%>}#m
\devlim{%<ordre du DL%>}#
\devlim[%<en%>]{%<ordre du DL%>}#
\drv{%<fonction%>}{%<variable%>}#
\drv[%<n-ième%>]{%<fonction%>}{%<variable%>}#
\ddrv{%<fonction%>}{%<variable%>}#
\ddrv[%<n-ième%>]{%<fonction%>}{%<variable%>}#
\derpart{%<dessus%>}{%<dessous%>}#
\interent{%<bornes entières%>}#
\interzn#
\parties{%<ensemble%>}#
\argsh#m
\argch#m
\argth#m
#endif