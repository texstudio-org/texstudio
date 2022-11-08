# se2fonts package
# Matthew Bertucci 2022/11/08 for v1.3.0

#include:fontspec
#include:unicode-math

#keyvals:\usepackage/se2fonts#c
fmode=#original,replacement,auto
#endkeyvals

\pdftexengine#*
\xetexengine#*
\luatexengine#*
\ifengineTF{engine}{then block}{else block}#*
\ifengineT{engine}{then block}#*
\ifengineF{engine}{else block}#*
