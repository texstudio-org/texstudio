# mathsemantics-optimization package
# Matthew Bertucci 2022/05/08 for v1.0.0

#include:mathsemantics-semantic

\normalCone#*m
\radialCone#*m
\tangentCone#*m
\linearizingCone#*m

\radialcone{sub}{arg}#m
\radialcone[scale%keyvals]{sub}{arg}#m
\tangentcone{sub}{arg}#m
\tangentcone[scale%keyvals]{sub}{arg}#m
\linearizingcone{sub}{arg}#m
\linearizingcone[scale%keyvals]{sub}{arg}#m
\normalcone{sub}{arg}#m
\normalcone[scale%keyvals]{sub}{arg}#m
\polarcone{arg}#m

#keyvals:\radialcone#c,\tangentcone#c,\linearizingcone#c,\normalcone#c
big
Big
bigg
Bigg
auto
none
#endkeyvals