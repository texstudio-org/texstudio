# folarrow package
# Matthew Bertucci 2026/10/19 for v20261010.0

#include:pict2e
#include:graphics

#keyvals:\usepackage/folarrow#c
lite#true,false
#endkeyvals

\folarrowsetup{options%keyvals}

#keyvals:\usepackage/folarrow#c,\folarrowsetup
span=%<number%>
lean=%<number%>
gap=%<number%>
shift=%<number%>
thickness=##L
glyphs#true,false
#endkeyvals

\folrightarrow#m
\folleftarrow#m
\foldownarrow#m
\foluparrow#m

\xfolrightarrow{superscript}#m
\xfolrightarrow[subscript]{superscript}#m
\xfolleftarrow{superscript}#m
\xfolleftarrow[subscript]{superscript}#m

\folpad{arg}#m

# tikz-cd support
#keyvals:\arrow#c,\ar#c,\rar#c,\lar#c,\dar#c,\uar#c,\drar#c,\urar#c,\dlar#c,\ular#c
foliated
#endkeyvals