# messagepassing package
# Matthew Bertucci 3/14/2022 for v1.0

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
\newprocesswithlength{name}{length%plain}
\processlength{name}{length%plain}
\newprocesswithstateinterval{name}{state name}
\newprocesswithcrash{name}{length%plain}{crash coord name}
\drawtimeline{length%plain}
\send{sender}{send time}{receiver}{receive time}
\sendwithname{sender}{send time}{receiver}{receive time}{label}
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
\colouredboxcolor{color}
\oobcolor{color}
\themaxtime#*
\theprocessnb#*
\iftimeline#*
\timelinetrue#*
\timelinefalse#*
