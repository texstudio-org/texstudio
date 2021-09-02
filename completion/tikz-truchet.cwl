# tikz-truchet package
# Matthew Bertucci 9/1/2021 for v1.0

#include:tikz

\truchetsquare{Center}{NE}{NW}{SW}{SE}
\truchetsquare[(x,y)]{Center}{NE}{NW}{SW}{SE}
\diagonalsquare{NE}{NW}{SW}{SE}
\diagonalsquare[(x,y)]{NE}{NW}{SW}{SE}
\tileA
\tileA[(x,y)]
\tileB
\tileB[(x,y)]
\tileC
\tileC[(x,y)]
\tileD
\tileD[(x,y)]
\truchethex{Center}{NW}{W}{SW}{SE}{E}{NW}
\truchethex[(x,y)]{Center}{NW}{W}{SW}{SE}{E}{NW}
\truchetsplithex
\truchetsplithex[(x,y)]
\begin{rotatehex}{degrees}
\end{rotatehex}
\truchetcube{Bottom}{Front}{Right}{Back}{Left}{Right}
\truchetcube[(x,y)]{Bottom}{Front}{Right}{Back}{Left}{Right}