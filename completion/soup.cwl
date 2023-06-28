# soup package
# Matthew Bertucci 1/18/2021 for v1.0.2

#include:l3keys2e
#include:tikz

#keyvals:\usepackage/soup#c
usetikz#true,false
highlight#true,false
highlightcolor=#%color
linecolor=#%color
#endkeyvals

\begin{alphabetsoup}
\begin{alphabetsoup}[width][height][font]
\begin{alphabetsoup}*#*
\begin{alphabetsoup}*[width][height][font]#*
\end{alphabetsoup}
\begin{Alphabetsoup}
\begin{Alphabetsoup}[width][height][font]
\begin{Alphabetsoup}*#*
\begin{Alphabetsoup}*[width][height][font]#*
\end{Alphabetsoup}

\begin{numbersoup}{max}
\begin{numbersoup}[width][height]{max}[min][font]
\begin{numbersoup}*{max}#*
\begin{numbersoup}*[width][height]{max}[min][font]#*
\end{numbersoup}

\begin{homemadesoup}{symbols}
\begin{homemadesoup}[width][height]{symbols}[font]
\begin{homemadesoup}*{symbols}#*
\begin{homemadesoup}*[width][height]{symbols}[font]#*
\end{homemadesoup}

\hideinsoup{x}{y}{dir}{seq}
\hideinsoup{x}{y}{dir}{seq}[clue]
\hideinsoup*{x}{y}{dir}{seq}
\hideinsoup*{x}{y}{dir}{seq}[clue]

\highlightinsoup{x1}{y1}{x2}{y2}

\listofclues
\listofclues[format]#*
\theclue#*

\showlist#S