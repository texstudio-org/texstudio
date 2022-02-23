# pst-spinner package
# Matthew Bertucci 2/22/2022 for v1.02

#include:pstricks
#include:pst-node
#include:pst-xkey

\psFidgetSpinner
\psFidgetSpinner(x,y)
\psFidgetSpinner[options%keyvals]
\psFidgetSpinner[options%keyvals](x,y)

#keyvals:\psFidgetSpinner#c
R=%<radius%>
color0=#%color
color1=#%color
color2=#%color
color3=#%color
colorMask=#%color
rotation=%<degrees%>
mask#true,false
customize#true,false
customizeMask#true,false
image=%<imagefile%>
fillcolor=#%color
linecolor=#%color
linewidth=##L
#endkeyvals

\pstspinnerFV#S
\PSTSPINNERLoaded#S
honeydew#B