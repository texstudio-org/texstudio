# adjmulticol package
# Matthew Bertucci 2/7/2022 for v1.2

#include:multicol

# all options passed to multicol
#keyvals:\usepackage/adjmulticol#c
errorshow
infoshow
balancingshow
markshow
debugshow
grid
colaction
#endkeyvals

\begin{adjmulticols}{number}{inner margin%l}{outer margin%l}
\end{adjmulticols}
\begin{adjmulticols*}{number}{inner margin%l}{outer margin%l}
\end{adjmulticols*}

\adjmulticols#S
\endadjmulticols#S