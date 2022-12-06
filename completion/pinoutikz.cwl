# pinoutikz package
# Matthew Bertucci 11/22/2021 for v1.1.0

#include:ifthen
#include:lmodern
#include:xstring
#include:upquote
#include:amsmath
#include:amssymb
#include:amsfonts
#include:forarray
#include:arrayjob
#include:pgf
#include:tikz
#include:tikzlibraryshapes.misc
#include:tikzlibraryshapes.geometric

\PDIP(pincount){pinarray}
\pctPDIP(pincount){pinarray}

\TQFP(pincount){pinarray}
\pctTQFP(pincount){pinarray}

\PLCC(pincount){pinarray}
\pctPLCC(pincount){pinarray}

\pinoutikzname#S
\pinoutikzversion#S
\pinoutikzdate#S

\FormatPinLabel{arg}#*
\CASE(arg1){arg2}#*
\PIN[arg1](arg2){arg3}{arg4}#*
\GENFOUREDGE(arg1){arg2}{arg3}{arg4}#*
\pardefault#*
\neverindent#*
\autoindent#*
