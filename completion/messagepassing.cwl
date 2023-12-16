# messagepassing package
# Matthew Bertucci 2023/12/15 for v1.2

#include:tikz
#include:tikzlibraryquotes
#include:tikzlibrarycalc
#include:float

#keyvals:\usepackage/messagepassing#c
vertical
annotatevertical
#endkeyvals

\begin{messagepassing}#\pictureHighlight
\begin{messagepassing}[TikZ options]
\begin{messagepassing}[TikZ options][caption%text]
\begin{messagepassing}[TikZ options][caption%text][placement]
\begin{messagepassing}[TikZ options][caption%text][placement][label]#l
\end{messagepassing}
\newprocess{name}
\newprocess{name}[display name]
\newprocesswithlength{name}{length%plain}
\newprocesswithlength{name}[display name]{length%plain}
\processlength{name}{length%plain}
\newprocesswithstateinterval{name}{state name}
\newprocesswithstateinterval{name}[display name]{state name}
\newprocesswithcrash{name}{length%plain}{crash coord name}
\newprocesswithcrash{name}[display name]{length%plain}{crash coord name}
\drawtimeline{length%plain}
\send{sender}{send time}{receiver}{receive time}
\sendwithname{sender}{send time}{receiver}{receive time}{label}
\sendwithname{sender}{send time}{receiver}{receive time}{label}[label options]
\sendoutofband{sender}{send time}{receiver}{receive time}{label}
\crash{process}{time}{name}
\restart{name}{date}{duration}
\checkpoint{process}{time}{name%formula}
\checkpointspecial{process}{time}{name%formula}{label}
\stateinterval{process}{time}{name%formula}
\stateintervalspecial{process}{time}{name%formula}{label}
\colouredbox{process1}{process2}{start time}{end time}{label}
\annotate{process}{time}{text}
\annotatexplicit{process}{time}{text}{name}
\sendwithstateinterval{sender}{send time}{receiver}{receive time}{name%formula}
\sendwithstateintervalandname{sender}{send time}{receiver}{receive time}{name%formula}{message name}
\sendwithstateintervalandname{sender}{send time}{receiver}{receive time}{name%formula}{message name}[label options]
\colouredboxcolour{color}
\oobcolour{color}

# not documented
\themaxtime#S
\theprocessnb#S
\iftimeline#S
\timelinetrue#S
\timelinefalse#S
