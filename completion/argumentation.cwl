# argumentation package
# Matthew Bertucci 2023/11/07 for v1.0

#include:options
#include:tikz
#include:tikzlibrarypositioning
#include:tikzlibrarydecorations.markings

#keyvals:\usepackage/argumentation#c
namestyle=#italics,bold,bolditalics
argumentstyle=#standard,retro
attackstyle=#standard,retro
#endkeyvals

\begin{af}#\pictureHightlight
\begin{af}[options]#\pictureHightlight
\end{af}
\begin{miniaf}#\pictureHightlight
\begin{miniaf}[options]#\pictureHightlight
\end{miniaf}

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
\afname{id}{name}
\afname[options]{id}{name}

# not documented
\argstyle{text}#S
\setargumentstyle{options}#S
\setattackstyle{options}#S
\setloopstyle{options}#S
\adjustargumentstyle{options}#S
\adjustattackstyle{options}#S
\resetargumentstyle#S
\resetattackstyle#S
\resetloopstyle#S