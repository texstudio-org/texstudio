# argumentation package
# Matthew Bertucci 2024/09/26 for v1.3

#include:amsbsy
#include:amsmath
#include:pgfopts
#include:xspace
#include:xcolor
#include:tikz
#include:tikzlibrarypositioning
#include:tikzlibrarydecorations.markings

#keyvals:\usepackage/argumentation#c
namestyle=#none,math,bold,monospace,monoemph
argumentstyle=#standard,large,thick,gray,colored
attackstyle=#standard,large,modern
supportstyle=#standard,dashed,double
macros=true
#endkeyvals

#ifOption:macros=true
\AF
\arguments
\attacks
\AFcomplete
\afref{label}#r
\fullafref{label}#r
#endif

\setargumentstyle{style}
\setattackstyle{style}
\setsupportstyle{style}
\setannotationstyle{style}

\begin{af}#\pictureHightlight
\begin{af}[options]#\pictureHightlight
\end{af}

\argument{name}
\argument(id){name}
\argument[options](id){name}
\argument[options]{name}
\attack{id1}{id2}
\attack[options]{id1}{id2}
\dualattack{id1}{id2}
\dualattack[options]{id1}{id2}
\selfattack{id}
\selfattack[options]{id}
\support{id1}{id2}
\support[options]{id1}{id2}
\annotatedattack{id1}{id2}{value}
\annotatedattack[options]{id1}{id2}{value}
\afname{name}
\afname(id){name}
\afname[options](id){name}
\afname[options]{name}
\annotation{id}{text}
\annotation[options]{id}{text}

aigyellow#B
aigblue#B

# not documented
\argstyle{text}#S
\theaf#S
\theargument#S
\ifmacros#S
