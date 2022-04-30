# nnext package
# Matthew Bertucci 2022/04/30 for v0.0

#include:ifthen
#include:xspace

#keyvals:\usepackage/nnext#c
linguex
expex
noparens
#endkeyvals

\Next
\NNext
\Last
\LLast

#ifOption:expex
\nextx
\anextx
\lastx
\blastx
\bblastx
#endif

\printtmpcounter{value}#*
\settmpcounter{value}#*
\thetmpcounter#*