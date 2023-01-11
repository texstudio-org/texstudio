# se2fonts package
# Matthew Bertucci 2023/01/10 for v2.0.0

#include:unicode-math
#include:libertinus-otf

\pdftexengine#*
\xetexengine#*
\luatexengine#*
\ifengineTF{engine}{then block}{else block}#*
\ifengineT{engine}{then block}#*
\ifengineF{engine}{else block}#*
