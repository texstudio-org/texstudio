# pst-hsb package
# Matthew Bertucci 2/20/2022 for v0.02

#include:pstricks
#include:pst-plot
#include:pst-xkey

\psparametricplotHSB{tmin}{tmax}{function%definition}
\psparametricplotHSB[options%keyvals]{tmin}{tmax}{function%definition}
\pslineHSB(x1,y1)(x2,y2)
\pslineHSB[options%keyvals](x1,y1)(x2,y2)
\PSThsbLoaded#S