# assurelatexmode package
# Matthew Bertucci 2022/05/15 for v5.01

#include:chemstr

\HashWedgeAsSubst(xstart,ystart)(xslope,yslope){length}
\HashWedgeAsSubstTeXLaTeX(xstart,ystart)(xslope,yslope){length}#*
\HashWedgeAsSubstX(xstart,ystart)(xend,yend)
\HashWedgeAsSubstX(xstart,ystart)(xend,yend)[thickness]
\HashWedgeAsSubstXTeXLaTeX(xstart,ystart)(xend,yend)#*
\HashWedgeAsSubstXTeXLaTeX(xstart,ystart)(xend,yend)[thickness]#*
\PutBondLine(xstart,ystart)(xend,yend){thickness}
\PutDashedBond(xstart,ystart)(xend,yend){thickness}
\PutTeXLaTeXLine(xstart,ystart)(xend,yend){thickness}#*
\PutTeXLaTeXdashed(xstart,ystart)(xend,yend){thickness}#*
\WedgeAsSubst(xstart,ystart)(xslope,yslope){length}
\WedgeAsSubstTeXLaTeX(xstart,ystart)(xslope,yslope){length}#*
\WedgeAsSubstX(xstart,ystart)(xend,yend)
\WedgeAsSubstX(xstart,ystart)(xend,yend)[thickness]
\WedgeAsSubstXTeXLaTeX(xstart,ystart)(xend,yend)#*
\WedgeAsSubstX(xstart,ystart)(xend,yend)[thickness]#*
\dashhasheddash
\putRoundArrow{(%<x1,y1%>)(%<x2,y2%>)%<...%>}
\putRoundArrow[%<arrowhead%>]{(%<x1,y1%>)(%<x2,y2%>)%<...%>}
\putRoundArrowTeXLaTeX{(%<x1,y1%>)(%<x2,y2%>)%<...%>}#*
\putRoundArrowTeXLaTeX[%<arrowhead%>]{(%<x1,y1%>)(%<x2,y2%>)%<...%>}#*
\thickLineWidth#*
\thicklines
\thinLineWidth#*
\thinlines
\wedgehasheddash
\wedgehashedwedge

# not documented
\ifmolfront#S
\molfrontfalse#S
\molfronttrue#S