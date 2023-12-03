# argumentation package
# Matthew Bertucci 2023/12/03 for v1.1

#include:pgfopts
#include:tikz
#include:tikzlibrarypositioning
#include:tikzlibrarydecorations.markings

#keyvals:\usepackage/argumentation#c
namestyle=#normal,italics,bold,bolditalics,monospace
argumentstyle=#standard
attackstyle=#standard,large
supportstyle=#standard,dashed,double
#endkeyvals

\setargumentstyle{style}
\setattackstyle{style}
\setsupportstyle{style}

\begin{af}#\pictureHightlight
\begin{af}[options]#\pictureHightlight
\end{af}

\argument{id}{name}
\argument[options]{id}{name}
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
\afname{id}{name}
\afname[options]{id}{name}
\annotation{id}{text}
\annotation[options]{id}{text}

# not documented
\argstyle{text}#S
