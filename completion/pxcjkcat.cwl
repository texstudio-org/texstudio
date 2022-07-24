# pxcjkcat package
# Matthew Bertucci 2022/07/22 for v1.4

#include:uplatex
#include:keyval

#keyvals:\usepackage/pxcjkcat#c
ccv1
ccv2
ccv3
ccv4
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