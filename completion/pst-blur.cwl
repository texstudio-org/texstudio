# mode: pst-blur.sty
# dani/2006-02-22
# Matthew Bertucci 2022-02-20 for v2.0

#include:pstricks
#include:pst-xkey

\psblurbox{stuff}
\psblurbox[options%keyvals]{stuff}
\ifpsblur#*
\psblurtrue#*
\psblurfalse#*
\PstBlurLoaded#S
