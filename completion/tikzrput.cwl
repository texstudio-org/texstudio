# tikzrput package
# Matthew Bertucci 2/12/2022 for v1.1

#include:tikz
#include:iftex

\rput(x,y){object%text}
\rput[refpoint](x,y){object%text}
\rput{angle}(x,y){object%text}
\rput[refpoint]{angle}(x,y){object%text}

\tikzrputPtVirCode#*
\tikzrputAtCode#*
\tikzrputTwoPtCode#*
\mybox#S