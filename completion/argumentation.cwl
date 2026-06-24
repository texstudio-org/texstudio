# argumentation package
# Matthew Bertucci 2026/06/23 for v1.7

#include:amsbsy
#include:amsmath
#include:pgfopts
#include:xspace
#include:xcolor
#include:tikz
#include:tikzlibrarypositioning
#include:tikzlibrarydecorations.markings
#include:tikzlibrarycalc

#keyvals:\usepackage/argumentation#c
namestyle=#none,math,bold,monospace,monoemph
argumentstyle=#standard,large,thick,gray,colored
attackstyle=#standard,large,modern
supportstyle=#marked,dashed,double
indexing=#none,numeric,alphabetic
macros#true,false
beamer#true,false
indexing=#none,numeric,alphabetic
junction dist=##L
#endkeyvals

#ifOption:macros
\AF
\arguments
\attacks
\AFcomplete
\afref{label}#r
\fullafref{label}#r
#endif
#ifOption:macros=true
\AF
\arguments
\attacks
\AFcomplete
\afref{label}#r
\fullafref{label}#r
#endif

#ifOption:beamer
\aflabeling{af-label}{argument list}
\afextension{af-label}{argument list}
\afreduct{af-label}{argument list}
\afrestriction{af-label}{argument list}
#endif
#ifOption:beamer=true
\aflabeling{af-label}{argument list}
\afextension{af-label}{argument list}
\afreduct{af-label}{argument list}
\afrestriction{af-label}{argument list}
#endif

\setargumentstyle{style}
\setattackstyle{style}
\setsupportstyle{style}
\setannotationstyle{style}
\setafstyle{style}
\setargumentcolorscheme{outer color}{inner color}

\newafenvironment{envname}{macro}#N

\begin{af}#\pictureHightlight
\begin{af}[options]#\pictureHightlight
\end{af}
\begin{af*}#\pictureHightlight
\begin{af*}[options]#\pictureHightlight
\end{af*}

\argument{name}
\argument(id){name}
\argument[options](id){name}
\argument[options]{name}
\attack{id1}{id2}
\attack{id1}{id2}(annotation%text)
\attack[options]{id1}{id2}
\attack[options]{id1}{id2}(annotation%text)
\dualattack{id1}{id2}
\dualattack[options]{id1}{id2}
\selfattack{id}
\selfattack[options]{id}
\support{id1}{id2}
\support{id1}{id2}(annotation%text)
\support[options]{id1}{id2}
\support[options]{id1}{id2}(annotation%text)
\setattack{sourcelist}{id}
\setattack{sourcelist}{id}(annotation%text)
\setattack[options]{sourcelist}{id}
\setattack[options]{sourcelist}{id}(annotation%text)
\setsupport{sourcelist}{id}
\setsupport{sourcelist}{id}(annotation%text)
\setsupport[options]{sourcelist}{id}
\setsupport[options]{sourcelist}{id}(annotation%text)
\afname{name}
\afname(id){name}
\afname[options](id){name}
\afname[options]{name}
\annotation{id}{text}
\annotation[options]{id}{text}

aigyellow#B
aigblue#B

# not documented
\theaf#S
\ifmacros#S

# deprecated
\annotatedattack{id1}{id2}{value}#S
\annotatedattack[options]{id1}{id2}{value}#S