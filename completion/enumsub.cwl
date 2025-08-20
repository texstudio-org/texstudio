# enumsub package
# Matthew Bertucci 2025/08/04 for v1.0

#include:enumitem
#include:array
#include:etoolbox

#keyvals:\usepackage/enumsub#c
roman
alpha
arabic
#endkeyvals

\enumsub{item1;item2;...%text}

\setenumsublabelwidth{width}
\setenumsubitemwidth{width}

\AutoSubpartsAligned{item1;item2;...%text}#S
\subparts{item1;item2;...%text}#S
\inlineparts{item1;item2;...%text}#S