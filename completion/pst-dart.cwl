# pst-dart package
# Matthew Bertucci 2/22/2022 for v0.03

#include:pstricks
#include:multido
#include:pst-xkey

\psDartBoard
\psDartBoard(x,y)
\psDartBoard[options%keyvals]
\psDartBoard[options%keyvals](x,y)

#keyvals:\psDartBoard#c
fontsize=##L
unit=%<number%>
viewpoint=%<x y z%>
preCode=%<code%>
postCode=%<code%>
#endkeyvals

\psDart(x,y)
\psDart[options%keyvals](x,y)

#keyvals:\psDart#c
rot=%<degrees%>
unit=%<number%>
dartcolor=#%color
#endkeyvals

Red#B
Green#B
gold#B