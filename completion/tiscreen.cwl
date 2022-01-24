# tiscreen package
# Matthew Bertucci 1/22/2022

#include:array
#include:lcd
#include:tcolorbox
#include:tikz
#include:xcolor

#keyvals:\usepackage/tiscreen#c
color
#endkeyvals

\tiscreenX
\tiscreenY

tiscreenfg#B
tiscreenbg#B
tibtngray#B
tibtnyellow#B
tibtngreen#B
tibtnwhite#B
tibtnblue#B
tibtncaseblack#B

\tiscreen|%<line1%>|%< ... |lineN|%>
\tibtn{bgcolor}{text}
\tibtn[textcolor]{bgcolor}{text}
\tibtn[color]{color}{text}#S
\tibtnextra{content%text}{text1%text}{text2%text}
\tibtnsecond
\tibtnalpha
\tibtnmatrix
\tibtnmatrixextra