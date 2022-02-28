# pst-marble package
# Matthew Bertucci 2/26/2022 for v1.6

#include:pstricks
#include:pst-xkey

\psMarble(width,height)
\psMarble(x0,y0)(x1,y1)
\psMarble[options%keyvals](width,height)
\psMarble[options%keyvals](x0,y0)(x1,y1)

#keyvals:\psMarble#c
actions={%<marbling actions%>}
spractions={%<spray actions%>}
shadings={%<shading actions%>}
background={[%<r g b%>]}
paper={[%<r g b%>]}
drawcontours#true,false
seed=%<seed%>
oversample=%<number%>
overscan=%<number%>
bckg#true,false
colors={[%<r1 g1 b1%>] %<[r2 b2 g2] ...%>}
colors={(%<RrGgBb%>) %<(RrGgBb) ...%>}
viscosity=%<number%>
linewidth=##L
linecolor=#%color
blendmode=%<mode number%>
shapealpha=%<number%>
opacity=%<factor%>
#endkeyvals

\PSTMARBLELoaded#S