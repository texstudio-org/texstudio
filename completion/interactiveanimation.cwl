# interactiveanimation package
# Matthew Bertucci 12/30/2021 for v0.2

#include:ifpdf
#include:keyval

\begin{animation}{width}{height}
\end{animation}

\begin{aframe}{frame name}{imagefile}#g
\begin{aframe}{frame name}{imagefile,filepage}#g
\end{aframe}

\controlbutton{caption%text}{target frame}{options%keyvals}
\controlbutton[sequence file,start page]{caption%text}{target frame}{options%keyvals}
\controlbutton[sequence file,start page,end page]{caption%text}{target frame}{options%keyvals}

#keyvals:\controlbutton#c
X=#start,center,end,%<coord%>
Y=#start,center,end,%<coord%>
position=#left,right,above,below,center,from
width=%<integer%>
height=%<integer%>
scale=%<factor%>
hidden
transparent
span=%<milliseconds%>
keep
#endkeyvals