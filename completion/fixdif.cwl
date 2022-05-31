# fixdif package
# Matthew Bertucci 2022/05/29 for v1.0

#keyvals:\usepackage/fixdif#c
rm
normal
partial
nopartial
#endkeyvals

\resetdfont{math font cmd%cmd}
\letdif{cmd}{csname}#d
\letdif*{cmd}{csname}#d
\newdif{cmd}{def}#d
\newdif*{cmd}{def}#d
\renewdif{cmd}{def}#d
\renewdif*{cmd}{def}#d