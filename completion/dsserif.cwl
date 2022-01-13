# dsserif package
# Matthew Bertucci 11/2/2021 for v1.031

#include:xkeyval

#keyvals:\usepackage/dsserif#c
scale=%<factor%>
scaled=%<factor%>
bfbb
bbsymbols
symbols
#endkeyvals

\mathbb{text%plain}#m
\mathbfbb{text%plain}#m
\mathbbb{text%plain}#*m

#ifOption:bbsymbols
\bbdotlessi#m
\bbdotlessj#m
\imathbb#m
\jmathbb#m
\bbGamma#m
\bbDelta#m
\bbTheta#m
\bbLambda#m
\bbPi#m
\bbSigma#m
\bbPhi#m
\bbPsi#m
\bbOmega#m
#endif

#ifOption:symbols
\bbdotlessi#m
\bbdotlessj#m
\imathbb#m
\jmathbb#m
\bbGamma#m
\bbDelta#m
\bbTheta#m
\bbLambda#m
\bbPi#m
\bbSigma#m
\bbPhi#m
\bbPsi#m
\bbOmega#m
#endif

\txtbbGamma#*
\txtbbDelta#*
\txtbbTheta#*
\txtbbLambda#*
\txtbbPi#*
\txtbbSigma#*
\txtbbPhi#*
\txtbbPsi#*
\txtbbOmega#*
\txtbbdotlessi#*
\txtbbdotlessj#*
