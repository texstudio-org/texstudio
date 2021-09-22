# association-matrix package
# Matthew Bertucci 9/16/2021 for v1.0

#include:xparse
#include:l3keys2e

\amxrow{key%plain}{text}
\amxcol{key%plain}{text}
\amxassociate{col-key}{row-key}

\amxrows#*
\amxcols#*
\amxrowtext{key%plain}#*
\amxcoltext{key%plain}#*

\amxgenerate
\amxgenerate[row-key]

\amxsetTopCorner{text}
\amxsetColumnHeading{cmd}
\amxsetColumnHeadingHighlighted{cmd}
\amxsetIndicator{indicator}
\amxsetIndicatorHighlighted{hl-indicator}{ot-indicator}
\amxReset