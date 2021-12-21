# mhequ package
# Matthew Bertucci 12/20/2021 for v1.7

#keyvals:\usepackage/mhequ#c
righttag
lefttag
numberall
fleqn
leqno
#endkeyvals

\begin{equ}#\math
\begin{equ}[label]#l\math
\end{equ}

\begin{equs}#\math,array
\begin{equs}[label]#l\math,array
\begin{equs}[num of cols][label]#l\math,array
\end{equs}

\tag{text}#m
\notag
\minilab{label}#l
\setlabtype{style}
\intertext{text}
\multicol{num of cols}{content}
\text{text}

\computelength{arg}#*
\getlength{arg}#*
\next{arg}#*
\MHcenter#*
\MHbig#*
\openup#*
\displaylines{arg}#*
\MHsavelabel{arg}#*
\sublabeltype#*
\MHgobble#*
\comm#*
\strutdepth#*
\begin{equa}#S\math,array
\begin{equa}[label]#Sl\math,array
\begin{equa}[num of cols][label]#Sl\math,array
\end{equa}#S