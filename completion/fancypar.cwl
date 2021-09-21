# fancypar package
# Matthew Bertucci 9/21/2021 for v1.3

#include:xcolor

\fancyparsetup{keyvals}

\NotebookPar{text}
\NotebookPar[options%keyvals]{text}

#keyvals:\NotebookPar,\fancyparsetup
linecolor=#%color
intercolor=#%color
textcolor=#%color
spiralcolor=#%color
interheight=##L
spiral#true,false
nbtextwidth=##L
#endkeyvals

\ZebraPar{text}
\ZebraPar[options%keyvals]{text}

#keyvals:\ZebraPar,\fancyparsetup
colorone=#%color
colortwo=#%color
textcolorone=#%color
textcolortwo=#%color
#endkeyvals
\FancyZColor#*
\FancyZTextColor#*

\DashedPar{text}
\DashedPar[options%keyvals]{text}

#keyvals:\DashedPar,\fancyparsetup
dashsymbol=
dashcolor=#%color
separation=##L
#endkeyvals

\MarkedPar{text}
\MarkedPar[options%keyvals]{text}

#keyvals:\MarkedPar,\fancyparsetup
mark=
position=#left,right
#endkeyvals

\UnderlinedPar{text}
\UnderlinedPar[options%keyvals]{text}

#keyvals:\UnderlinedPar,\fancyparsetup
rulecolor=#%color
#endkeyvals

\FancyPreFormat#*
\FancyFormat#*
\AddFancyFormat#*
