# association-matrix package
# Matthew Bertucci 2022/10/29 for v1.1

#include:etoolbox
#include:forloop
#include:ifthen
#include:textcomp

\amxrow{key%plain}{text}
\amxcol{key%plain}{text}
\amxassociate{col-key}{row-key}

\amxrows
\amxcols
\amxrowtext{key%plain}
\amxcoltext{key%plain}

\amxgenerate
\amxgenerate[row-key]

\amxsetTopCorner{heading%text}
\amxsetColumnHeading{render-command}
\amxsetRowFormat{render-command}
\amxsetRowFormatHighlighted{render-command}
\amxsetIndicator{indicator}
\amxsetIndicatorHighlighted{hl-indicator}{ot-indicator}
\amxReset

\amxDate#S
\amxVersion#S
