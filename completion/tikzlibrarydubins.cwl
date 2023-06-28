# dubins tikzlibrary
# 2022/12/06 for v3.0.1

#include:tikzlibrarycalc
#include:etoolbox

\ifpgfmathcond{condition}#*
\dubinspath{options}#*
\dubinspathset{options}#*
\dubinspathcalc{options}#*