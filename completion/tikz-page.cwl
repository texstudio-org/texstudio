# tikz-page package
# Matthew Bertucci 12/22/2021 for v1.0

#include:calc
#include:fancyhdr
#include:graphicx
#include:tikz
#include:tikzlibraryplotmarks
#include:tikzlibrarycalc
#include:tikzlibraryshapes
#include:tikzlibrarypositioning
#include:tikzlibrarydecorations.text

#keyvals:\usepackage/tikz-page#c
textpos
#endkeyvals

#ifOption:textpos
#include:textpos
#endif

\tpflip{odd page code}{even page code}
\tikzpageputanchorsdefaults
\tikzpageputanchorsbody
\tikzpageputanchorsmarginpar
\tikzpageputanchorsheader
\tikzpageputanchorsfooter
\tikzpageputanchorstop
\tikzpageputanchorsright
\tikzpageputanchorsbottom
\tikzpageputanchorsleft
\tikzpageputanchors
\tpshowframes
\tpfancyhdrdefault
\tikzpage

\pkgfiledate#S
\pkgfileversion#S
