# DPcircling package
# Matthew Bertucci 9/11/2021 for v1.0

#include:tikz

\DPcircling{text}
\DPcircling[options%keyvals]{text}
\DPrectangle{text}
\DPrectangle[options%keyvals]{text}
\DPjagged{text}
\DPjagged[options%keyvals]{text}
\DPfanshape{text}
\DPfanshape[options%keyvals]{text}

\DPcircle{text}#*
\DPcircle[options%keyvals]{text}#*
\DPcirc{text}#*
\DPcirc[options%keyvals]{text}#*
\DPrect{text}#*
\DPrect[options%keyvals]{text}#*

\DPcirclingDefault{options%keyvals}

#keyvals:\DPcircling,\DPrectangle,\DPjagged,\DPfanshape,\DPcircle,\DPcirc,\DPrect,\DPcirclingDefault
line color=#%color
line width=##L
width=##L
height=##L
#endkeyvals