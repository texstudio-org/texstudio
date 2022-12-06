# proofread package
# Matthew Bertucci 11/2/2021 for v1.04

#include:marginnote
#include:setspace
#include:soul
#include:tikz
#include:tikzlibrarycalc
#include:tikzlibrarydecorations.pathmorphing

#keyvals:\usepackage/proofread#c
onehalfspacing
doublespacing
corrected
uncorrected
frame
#endkeyvals

\skp
\skp[number]
\del{phrase%text}
\yel{phrase%text}
\yel[comment%text]{phrase%text}
\add{phrase%text}
\rep{phrase%text}{replacement}
\com{comment%text}
\hilite{phrase%text}
\hilite[options%keyvals]{phrase%text}

#keyvals:\hilite#c
fill=#%color
draw=#%color
opacity=
fill opacity=
draw opacity=
line width=##L
#endkeyvals
