# pst-moire package
# Matthew Bertucci 2/26/2022 for v2.2

#include:pstricks
#include:pst-xkey
#include:multido

\psmoire(x,y)
\psmoire[options%keyvals](x,y)

#keyvals:\psmoire#c
type=#Fresnel,linear,radial,circle,square,Newton,Bouasse,Gauss,dot,chess
rotate=%<degrees%>
Rmax=%<length in cm%>
scale=%<factor%>
Alpha=%<degrees%>
E=%<distance in cm%>
n=%<number%>
T=%<distance in mm%>
linewidth=##L
linecolor=#%color
dotstyle=%<style%>
dotsize=##L
#endkeyvals

\addtomoirelisttype{name}

\psRandomDotPatterns
\psRandomDotPatterns[options%keyvals]

#keyvals:\psRandomDotPatterns#c
NumberDots=%<integer%>
coefficients=%<a b θ x0 y0%>
srand=%<random seed%>
layer#true,false
revlayer#true,false
linecolor=#%color
fillcolor=#%color
unit=%<number%>
#endkeyvals

\psRandomDot(x,y)
\psRandomDot[options%keyvals](x,y)

#keyvals:\psRandomDot#c
hole=#round,square
r=%<radius in pts%>
p=%<distance in pts%>
rotate=%<degrees%>
k=%<dispersion factor%>
symbole=%<digit or letter%>
PSfont=%<PS font name%>
fontsize=%<size in pts%>
vadjust=%<number%>
hadjust=%<number%>
#endkeyvals

\psGlassPattern
\psGlassPattern[options%keyvals]

#keyvals:\psGlassPattern#c
function=%<function%>
layers#true,false
linecolor=#%color
fillcolor=#%color
dotsize=##L
dotstyle=%<style%>
unit=%<number%>
algebraic
#endkeyvals

\variablesMoirages#*