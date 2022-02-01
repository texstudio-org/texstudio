# tikzbricks package
# Matthew Bertucci 8/12/2021

#include:tikz
#include:tikz-3dplot

\brick{length%plain}{width%plain}
\brick[options%keyvals]{length%plain}{width%plain}

#keyvals:\brick#c
color=#%color
frontcolor=#%color
topcolor=#%color
sidecolor=#%color
studcolor=#%color
brickheight=%<number%>
bricklength=%<number%>
brickwidth=%<number%>
studradius=%<number%>
studheight=%<number%>
studtext={%<text%>}
#endkeyvals

\begin{wall}
\end{wall}
\wallbrick{length%plain}{width%plain}
\wallbrick[options%keyvals]{length%plain}{width%plain}
\newrow

#keyvals:\wallbrick#c
color=#%color
#endkeyvals

\thebrickx#*
\thebricky#*
\thebrickz#*

\tmpscaleA#S
\tmpscaleB#S
\tmpscaleC#S
\tmpscaleD#S
\tmp#S
\scalingfactor#S
