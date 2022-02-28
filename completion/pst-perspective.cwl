# pst-perspective package
# Matthew Bertucci 2/27/2022 for v1.05

#include:pstricks
#include:pst-grad
#include:pstricks-add

\pstransTS(x,y){A}{A'}
\pstransTS[options%keyvals](x,y){A}{A'}
\pstransTSX(x,y){A}{A'}
\pstransTSX[options%keyvals](x,y){A}{A'}
\pstransTSK(x,y){length}{A}{A'}
\pstransTSK[options%keyvals](x,y){length}{A}{A'}
\psboxTS(x,y,z){x length}{y width}{z height}{color}
\psboxTS[options%keyvals](x,y,z){x length}{y width}{z height}{color}
\psCircleTS{radius}
\psCircleTS[options%keyvals]{radius}
\psCircleTSX{radius}
\psCircleTSX[options%keyvals]{radius}
\psArcTS{radius}{start angle}{end angle}
\psArcTS[options%keyvals]{radius}{start angle}{end angle}
\psArcTSX{radius}{start angle}{end angle}
\psArcTSX[options%keyvals]{radius}{start angle}{end angle}
\psZylinderTS{radius}{height}
\psZylinderTS[options%keyvals]{radius}{height}
\ba
\punkte#S
\punkteA#S
\punkteB#S
\punkteC#S
\punkteD#S
\PSTperspectiveLoaded#S