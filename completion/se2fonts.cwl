# se2fonts package
# Matthew Bertucci 2023/09/12 for v3.2.0

#include:unicode-math
#include:libertinus-otf
#include:inconsolata-nerd-font

\pdftexengine#*
\xetexengine#*
\luatexengine#*
\ifengineTF{engine}{then block}{else block}#*
\ifengineT{engine}{then block}#*
\ifengineF{engine}{else block}#*
