# se2fonts package
# Matthew Bertucci 2022/09/29 for v1.1.1

#include:fontspec
#include:unicode-math

#keyvals:\usepackage/se2fonts#c
fontmode=#original,replacement,auto
#endkeyvals

\pdftexengine#*
\xetexengine#*
\luatexengine#*
\ifengineTF{engine}{then block}{else block}#*
\ifengineT{engine}{then block}#*
\ifengineF{engine}{else block}#*