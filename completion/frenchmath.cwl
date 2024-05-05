# frenchmath package
# Matthew Bertucci 2024/05/05 for v3.0

#include:mathrsfs
#include:amssymb
#include:amsopn
#include:xspace
#include:etoolbox
#include:ibrackets
#include:decimalcomma
#include:mathgreeks

#keyvals:\usepackage/frenchmath#c
capsit
noibrackets
# options passed to mathgreeks
lgrmath
lgrmath=%<font name%>
fontspec
fontspec=%<font name%>
unicode-math
unicode-math=%<font name%>
upgreek
upgreek=#Euler,Symbol,Symbolsmallscale
mathdesign
mathdesign=#Utopia,Garamond,Charter
kpfonts
kpfonts=#normal,light
fourier#true,false
pxfonts#true,false
txfonts#true,false
libertinus#true,false
concrete#true,false
cmbright#true,false
savegreeks#true,false
otherfonts#true,false
libsans#true,false
lowercase#true,false
uppercase#true,false
#endkeyvals

\curs{text%plain}#m
\ssi
\Oij
\Oijk
\Ouv
\Oij*
\Oijk*
\Ouv*
\ijk

\infeg#m
\supeg#m
\vide#m
\paral#m
\paral*#m
\cmod#m
\pgcd#m
\ppcm#m
\card#m
\Card#m
\Ker#m
\Hom#m
\rg#m
\Vect#m
\ch#m
\sh#m
\th
\cosec#m
\cosech#m

\DeclareMathUp{cmd}#*d
\AMSvarnothing#S
\apply#S
