# tabvar package
# Matthew Bertucci 4/18/2022 for v1.7

#include:array
#include:colortbl
#include:varwidth
#include:ifthen
#include:graphicx
#include:ifpdf

#keyvals:\usepackage/tabvar#c
FlechesMP
FlechesPS
#endkeyvals

\begin{tabvar}{cols}#m\array
\end{tabvar}#m

\niveau{départ}{total}
\croit
\decroit
\constante
\dbarre
\discont{valeur gauche}{ou}{valeur droite}
\discont[num]{valeur gauche}{ou}{valeur droite}
\barre{math%formula}
\FlechesPS%<<num>%>
\TVcenter{math%formula}
\TVstretch{valeur}
\TVarrowscale

# not in main documentation
\ardown#S
\arhor#S
\arup#S
\eastarrow#*
\eastarrowi#*
\eastarrowii#*
\eastarrowiii#*
\eastarrowiv#*
\enearrow#*
\enearrowi#*
\enearrowii#*
\enearrowiii#*
\enearrowiv#*
\esearrow#*
\esearrowi#*
\esearrowii#*
\esearrowiii#*
\esearrowiv#*
\FlecheC#*
\FlecheD#*
\FlecheH#*
\FlechesMPfalse#*
\FlechesMPtrue#*
\ifFlechesMP#*
\TVarraycolsep#*
\TVarraystretch#*
\TVarrowscolstretch#*
\TVbox#*
\TVcolorLeftSep#*
\TVcolorRightSep#*
\TVextradepth#*
\TVextraheight#*
\TVextraheight#*
\TVmaxcolwidth#*
\TVnl#*
\TVtabularnewline#*

TVbarrecolor#B
TVcolor#B