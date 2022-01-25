# textfit package
# Matthew Bertucci 1/24/2022 for v5

#keyvals:\usepackage/textfit#c
noisy
magstep
#endkeyvals

\scaletoheight{height}{content%text}
\scaletowidth{width}{content%text}

\ifScalebyMagsteps#*
\ScalebyMagstepstrue#*
\ScalebyMagstepsfalse#*
\ifNoisyFitting#*
\NoisyFittingtrue#*
\NoisyFittingfalse#*
\magsteps#*
\Fontname#*

\docdate#S
\filedate#S
\fileversion#S