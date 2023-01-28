# fixdif package
# Matthew Bertucci 2022/07/15 for v1.3

#keyvals:\usepackage/fixdif#c
rm
normal
partial
nopartial
#endkeyvals

\resetdfont{math font cmd%cmd}
\letdif{cmd}{csname}#d
\letdif*{cmd}{csname}#d
\partialnondif#*m
\newdif{cmd}{def}#d
\newdif*{cmd}{def}#d
\renewdif{cmd}{def}#d
\renewdif*{cmd}{def}#d
\mathdif{symbol}#m
\mathdif*{symbol}#m
