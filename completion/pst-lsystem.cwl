# pst-lsystem package
# Matthew Bertucci 2/26/2022 for v0.02

#include:pstricks
#include:pst-xkey

\pslsystem(x,y)
\pslsystem[options%keyvals](x,y)

#keyvals:\pslsystem#c
F=%<Rule F → (F)%>
X=%<Rule X → (F,X,Y)%>
Y=%<Rule Y → (F,X,Y)%>
Start=%<Startrule S → (F,X,Y)%>
Angle=%<degrees%>
N=%<number of recursive calls%>
Ftype=#1,2,3,4
BaseLength=##L
usecolor=#0,1,2,3,4
linecolor=#%color
#endkeyvals

\PSTlsystemLoaded#S