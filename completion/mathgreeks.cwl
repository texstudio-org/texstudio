# mathgreeks package
# Matthew Bertucci 2024/05/05 for v1.1

#include:kvoptions
#include:etoolbox
#include:amstext

#keyvals:\usepackage/mathgreeks#c
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

\setmathgreeks{keyvals}

#keyvals:\usepackage/mathgreeks#c,\setmathgreeks
greekup#true,false
Greekup#true,false
TeX#true,false
ISO#true,false
upright#true,false
style=#TeX,ISO,upright
#endkeyvals

\mathgreeksfont{keyvals}

#keyvals:\mathgreeksfont
fontspec=%<font name%>
unicode-math=%<font name%>
enc=%<encoding%>
fam=%<family%>
series=%<series%>
shape=%<shape%>
#endkeyvals

\greektable

\itGamma#m
\itDelta#m
\itTheta#m
\itLambda#m
\itXi#m
\itPi#m
\itSigma#m
\itUpsilon#m
\itPhi#m
\itPsi#m
\itOmega#m
\italpha#m
\itbeta#m
\itgamma#m
\itdelta#m
\itepsilon#m
\itzeta#m
\iteta#m
\ittheta#m
\itiota#m
\itkappa#m
\itlambda#m
\itmu#m
\itnu#m
\itxi#m
\itpi#m
\itrho#m
\itsigma#m
\ittau#m
\itupsilon#m
\itphi#m
\itchi#m
\itpsi#m
\itomega#m
\itvarepsilon#m
\itvartheta#m
\itvarpi#m
\itvarrho#m
\itvarsigma#m
\itvarphi#m

\upGamma#m
\upDelta#m
\upTheta#m
\upLambda#m
\upXi#m
\upPi#m
\upSigma#m
\upUpsilon#m
\upPhi#m
\upPsi#m
\upOmega#m
\upalpha#m
\upbeta#m
\upgamma#m
\updelta#m
\upepsilon#m
\upzeta#m
\upeta#m
\uptheta#m
\upiota#m
\upkappa#m
\uplambda#m
\upmu#m
\upnu#m
\upxi#m
\uppi#m
\uprho#m
\upsigma#m
\uptau#m
\upupsilon#m
\upphi#m
\upchi#m
\uppsi#m
\upomega#m
\upvarepsilon#m
\upvartheta#m
\upvarpi#m
\upvarrho#m
\upvarsigma#m
\upvarphi#m

# requires 'savegreeks' option
\backGamma#Sm
\backDelta#Sm
\backTheta#Sm
\backLambda#Sm
\backXi#Sm
\backPi#Sm
\backSigma#Sm
\backUpsilon#Sm
\backPhi#Sm
\backPsi#Sm
\backOmega#Sm
\backalpha#Sm
\backbeta#Sm
\backgamma#Sm
\backdelta#Sm
\backepsilon#Sm
\backzeta#Sm
\backeta#Sm
\backtheta#Sm
\backiota#Sm
\backkappa#Sm
\backlambda#Sm
\backmu#Sm
\backnu#Sm
\backxi#Sm
\backpi#Sm
\backrho#Sm
\backsigma#Sm
\backtau#Sm
\backupsilon#Sm
\backphi#Sm
\backchi#Sm
\backpsi#Sm
\backomega#Sm
\backvarepsilon#Sm
\backvartheta#Sm
\backvarpi#Sm
\backvarrho#Sm
\backvarsigma#Sm
\backvarphi#Sm

# not documented
\SaveGreeks#S
