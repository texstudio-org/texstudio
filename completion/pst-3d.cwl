# mode: pst-3d.sty
# dani/2006-02-22
# Matthew Bertucci 2022-02-20 for v1.11

#include:pstricks
#include:pst-xkey

\psAffinTransform[options%keyvals]{transformation matrix}{stuff}
\psAffinTransform{transformation matrix}{stuff}
\pssetzlength{cmd}{dim}#*
\psshadow[options%keyvals]{stuff}
\psshadow{stuff}
\pstilt[options%keyvals]{angle}{stuff}
\psTilt[options%keyvals]{angle}{stuff}
\pstilt{angle}{stuff}
\psTilt{angle}{stuff}
\PSTthreeDLoaded#S
\ThreeDput(x,y,z){stuff}
\ThreeDput[options%keyvals](x,y,z){stuff}
