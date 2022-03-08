# graphfig package
# Matthew Bertucci 3/4/2022 for v2.2

#include:graphics

#keyvals:\usepackage/graphfig#c
subfigure
AllowH
#endkeyvals

#ifOption:subfigure
#include:subfigure
#endif

#ifOption:AllowH
#include:float
#endif

\begin{Figure}{caption%text}
\begin{Figure}{caption%text}[label]#l
\begin{Figure}[placement]{caption%text}
\begin{Figure}[placement]{caption%text}[label]#l
\end{Figure}

\graphfile{imagefile}#g
\graphfile{imagefile}[subcaption%text]#g
\graphfile[width]{imagefile}#g
\graphfile[width]{imagefile}[subcaption%text]#g
\graphfile*{imagefile}#g
\graphfile*{imagefile}[subcaption%text]#g
\graphfile*[height]{imagefile}#g
\graphfile*[height]{imagefile}[subcaption%text]#g

\FigureDefaultPlacement{placement}

\thesubfigure#*
\docdate#S
\FileName#S
\filedate#S
\filedescr#S
\fileversion#S