# tikz-mirror-lens package
# 2022/12/28 for v1.0.1
# adapted from cwl written by package author Fernando H. G. Zucatelli
# original: http://mirrors.ctan.org/graphics/pgf/contrib/tikz-mirror-lens/tex/tikz-mirror-lens.cwl

# ======================
# Developed by FHZ -- Brasil
# ======================
#include:tikz
#include:tikzlibrarycalc
#include:tikzlibrarymath
#include:tikzlibrarydecorations
#include:tikzlibrarydecorations.markings

# =======================================================
# Summary of commands
# -- Mirrors
\mirrorSphGauss{f}{p}{o}{epsilon}#n
\mirrorSphGauss[arrows]{f}{p}{o}{epsilon}#n
\mirrorSphGaussCoord{f}{p}{o}{epsilon}#n
\mirrorSphGaussCoord[arrows]{f}{p}{o}{epsilon}#n
\mirrorSphGaussFixed{f}{p}{o}{epsilon}{yM}{xL}{xR}#n
\mirrorSphGaussFixed[arrows]{f}{p}{o}{epsilon}{yM}{xL}{xR}#n
\mirrorSphGaussFixedCoord{f}{p}{o}{epsilon}{yM}{xL}{xR}{Co}#n
\mirrorSphGaussFixedCoord[arrows]{f}{p}{o}{epsilon}{yM}{xL}{xR}{Co}#n
# -- Lens
\lensSphGauss{f}{p}{o}{epsilon}#n
\lensSphGauss[arrows]{f}{p}{o}{epsilon}#n
\lensSphGaussCoord{f}{p}{o}{epsilon}#n
\lensSphGaussCoord[arrows]{f}{p}{o}{epsilon}#n
\lensSphGaussFixed{f}{p}{o}{epsilon}{yM}{xL}{xR}#n
\lensSphGaussFixed[arrows]{f}{p}{o}{epsilon}{yM}{xL}{xR}#n
\lensSphGaussFixedCoord{f}{p}{o}{epsilon}{yM}{xL}{xR}{Co}#n
\lensSphGaussFixedCoord[arrows]{f}{p}{o}{epsilon}{yM}{xL}{xR}{Co}#n
# =======================================================
\mirrorLensObjIma{p}{pp}{o}{i}#n
\mirrorLensCoord{p}{pp}{o}{i}{f}{Co}#n
# =======================================================
\mirrorBase{f}{yM}{minXaxis}{maxXaxis}#n
\mirrorPts{v}{f}{c}#n
\mirrorRays{p}{pp}{o}{i}#n
\mirrorRays[arrows]{p}{pp}{o}{i}#n
# =======================================================
\lensBase{f}{yM}{minXaxis}{maxXaxis}#n
\lensPts{v}{f}{a}#n
\lensRays{p}{pp}{o}{i}#n
\lensRays[arrows]{p}{pp}{o}{i}#n
# =======================================================
\mirrorMath{f}{p}{o}{epsilon}{yM}#n
\lensMath{f}{p}{o}{epsilon}{yM}#n
\lensMathL{f}{p}{o}{epsilon}{yM}#n
# =======================================================

# not documented
\lensSphGaussL{f}{p}{o}{epsilon}#*n
\lensSphGaussL[arrows]{f}{p}{o}{epsilon}#*n
\lensSphGaussLCoord{f}{p}{o}{epsilon}#*n
\lensSphGaussLCoord[arrows]{f}{p}{o}{epsilon}#*n
\lensSphGaussLFixed{f}{p}{o}{epsilon}{yM}{xL}{xR}#*n
\lensSphGaussLFixed[arrows]{f}{p}{o}{epsilon}{yM}{xL}{xR}#*n
\lensSphGaussLFixedCoord{f}{p}{o}{epsilon}{yM}{xL}{xR}{Co}#*n
\lensSphGaussLFixedCoord[arrows]{f}{p}{o}{epsilon}{yM}{xL}{xR}{Co}#*n
