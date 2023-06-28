# jkmath package
# Matthew Bertucci 2/3/2022

#include:array
#include:amsmath
#include:physics

#keyvals:\usepackage/jkmath#c
subsetorder
subsetnonorder
subsetnonamb
bbsets
bfsets
#endkeyvals

\oldsubset#*m
\oldsupset#*m

#ifOption:subsetorder
\stsubset#m
\stsupset#m
#endif

#ifOption:subsetnonorder
\stsubset#m
\stsupset#m
#endif

#ifOption:subsetnonamb
\stsubset#m
\stsupset#m
#endif

#ifOption:bbsets
\N#m
\Z#m
\Q#m
\R#m
\C#m
\F#m
\Aff#m
\PP#m
#endif

#ifOption:bfsets
\N#m
\Z#m
\Q#m
\R#m
\C#m
\F#m
\Aff#m
\PP#m
#endif

\begin{system}{cols}#m\array
\end{system}#m

\begin{augmentedmatrix}{n}{m}#m\array
\end{augmentedmatrix}#m
\apmqty{n}{contents}#m
\ipmqty{m}{contents}#m

\lparens
\rparens

\oointerval{arg}
\ccinterval{arg}
\ocinterval{arg}
\cointerval{arg}

\set{arg}#m
\where#m
\restr{arg}#m

\stirlingfirstkind{top}{bottom}#m
\stirlingsecondkind{top}{bottom}#m

\legendre{top}{bottom}#m
\jacobi{top}{bottom}#m

\mobius
\cech
\erdos