# lua-tikz3dtools package
# Matthew Bertucci 2025/07/15 for v1.0.0

#include:tikz
#include:tikzlibrarydecorations.markings

# from lua-tikz3dtools-expl3-command-definitions
\appendcurve
\appendcurve[options%keyvals]
\appendlabel
\appendlabel[options%keyvals]
\appendplane
\appendplane[options%keyvals]
\appendpoint
\appendpoint[options%keyvals]
\appendsurface
\appendsurface[options%keyvals]
\rendersegments

# from lua-tikz3dtools-tikz-keys
# no user commands

# from lua-tikz3dtools-latex2e-command-definitions
\appendprism
\appendprism[options%keyvals]
\drawlabel[options%keyvals]{coord1}{coord2}{vector}{rel pos}{offset coord}{text}
\drawlabel{coord1}{coord2}{vector}{rel pos}{offset coord}{text}
\drawmark
\drawmark[options%keyvals]
\drawpoint[options%keyvals]{coord}
\drawpoint{coord}
\drawvector[options%keyvals]{coord1}{coord2}
\drawvector{coord1}{coord2}