# xespotcolor package
# Matthew Bertucci 1/20/2022 for v2.1

#include:xetex
#include:iftex
#include:graphics
#include:color

#ifOption:xcolor
#include:xcolor
#endif

#keyvals:\usepackage/xespotcolor#c
hks
pantone
xcolor
#endkeyvals

\NewSpotColorSpace{name}
\AddSpotColor{colorspace}{color}{pdf name}{specification}
\SpotSpace
\SetPageColorSpace{colorspace}
\SpotColor{color}{number}

\SetPageColorResource{resource}#*

\csgrab{arg1}{arg2}#S
\colorprofilecnt#S
\mycolorprofilename#S
\mycolorprofile#S
\mycolor#S
\tempcs#S