# pxcjkcat package
# Matthew Bertucci 2025/02/19 for v1.6

#include:uplatex
#include:keyval

#keyvals:\usepackage/pxcjkcat#c
ccv1
ccv2
ccv3
ccv4
ccv5
ccv+
real
nomode
#endkeyvals

\cjkcategorymode{mode%keyvals}

#keyvals:\cjkcategorymode#c,\usepackage/pxcjkcat#c
forcecjk
default
prefercjk
prefercjkvar
japanese
japanesevar
prefernoncjk
#endkeyvals

\cjkcategory{block}{category}
\showcjkcategory#*
\getcjktokenmode
\thecjktokenmode
\setcjktokenmode{value}
\withcjktokendisabled{code}
\withcjktokenenabled{code}
\withcjktokenforced{code}
\withcjktokendisabledex{code}
\withcjktokenenabledex{code}
\withcjktokenforcedex{code}
