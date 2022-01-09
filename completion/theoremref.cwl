# theoremref package
# Matthew Bertucci 1/8/2021

#keyvals:\usepackage/theoremref#c
lowercase
reftex
#endkeyvals

\thlabel{key}#l
\thref{labellist}#r
\thnameref{label}#r

#ifOption:reftex
\th\label{key}
\th\ref{label}
#endif