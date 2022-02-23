# pst-thick package
# Matthew Bertucci 2/22/2022 for v1.0

#include:pstricks
#include:pst-plot
#include:pst-node
#include:pst-xkey

\psthick{t1}{t2}{function%definition}

#keyvals:\psthick#c
E=%<number%>
K=%<number%>
stylethick=#vide,thickline,onlythecurvered,onlythecurveblue,thicklineblue,rainbow,solide,serpent
curveonly#true,false
stylecurve1=#vide,thickline,onlythecurvered,onlythecurveblue,thicklineblue,rainbow,solide,serpent
stylecurve2=#vide,thickline,onlythecurvered,onlythecurveblue,thicklineblue,rainbow,solide,serpent
#endkeyvals

darkgreen#B

\fonctionSinus{period}{amplitude}
\CalculsCurves#*