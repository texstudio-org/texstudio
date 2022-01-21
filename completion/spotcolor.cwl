# spotcolor package
# Matthew Bertucci 1/18/2022 for v1.2

#include:graphics

#keyvals:\usepackage/spotcolor#c
hks
pantone
#endkeyvals

\NewSpotColorSpace{name}
\AddSpotColor{colorspace}{color}{pdf name}{specification}
\SpotSpace
\SetPageColorSpace{colorspace}
\SpotColor{color}{number}

\SetPageColorResource{resource}#*
\thecolorprofile#*
\thecolor#*

\act#S
\csgrab{arg1}{arg2}#S
\obj#S
\tempcs#S

\ifhks#*
\hkstrue#*
\hksfalse#*
\ifpantone#*
\pantonetrue#*
\pantonefalse#*