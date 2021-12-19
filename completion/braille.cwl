# braille package
# Matthew Bertucci 12/16/2021 for v0.22

#keyvals:\usepackage/braille#c
puttinydots
useemptybox
compact
8dots
mirror
#endkeyvals

\braille{braille text}
\braillebox{positions}

\brailleunit#*
\brailledot#*

\ifbrailleputtinydots#*
\brailleputtinydotstrue#*
\brailleputtinydotsfalse#*
\ifbrailleeightdots#*
\brailleeightdotstrue#*
\brailleeightdotsfalse#*
\ifbraillecompact#*
\braillecompacttrue#*
\braillecompactfalse#*
\ifbrailleuseemptybox#*
\brailleuseemptyboxtrue#*
\brailleuseemptyboxfalse#*
\ifbraillemirror#*
\braillemirrortrue#*
\braillemirrorfalse#*