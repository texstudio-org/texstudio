# mode: pst-fill.sty
# dani/2006-02-22
# Matthew Bertucci 2022-02-20 for v1.02

#include:pstricks
#include:pst-xkey

#keyvals:\usepackage/pst-fill#c
tiling
#endkeyvals

\psboxfill{stuff}
\PstTiling

\txfillDict#*
\pstFillSetDefaults#*
\PSTboxfillLoaded#S
