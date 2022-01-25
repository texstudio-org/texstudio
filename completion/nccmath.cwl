# nccmath package
# Matthew Bertucci 1/23/2022 for v1.3

#include:amsmath

#keyvals:\usepackage/nccmath#c
mediummath
# options passed to amsmath
intlimits
nointlimits
sumlimits
nosumlimits
namelimits
nonamelimits
leqno
reqno
centertags
tbtags
cmex10
fleqn
alignedleftspaceyes
alignedleftspaceno
alignedleftspaceyesifneg
#endkeyvals

\intertext[distance%l]{word or phrase%text}#m

\begin{fleqn}
\begin{fleqn}[margin]
\end{fleqn}
\begin{ceqn}
\end{ceqn}

\begin{darray}{cols}#m\array
\begin{darray}[pos%keyvals]{cols}#m\array
\end{darray}

#keyvals:\begin{darray}
l
c
r
#endkeyvals

\dmulticolumn{count}{preamble}{formula}#/darray
\useshortskip
\nr
\nr[dist%l]
\nr*
\nr*[dist%l]
\mrel{formula}#m
\underrel{base}{bottom}#m
\medmath{formula}#m
\medop{operator}#m
\medint{operator}#m
\medintcorr{length}
\mfrac{num}{den}#m
\mbinom{above}{below}#m
\begin{medsize}#m
\end{medsize}#m
\begin{mmatrix}#m\array
\end{mmatrix}#m

\eq{formula}
\eq*{formula}
\eqs{formulas%formula}
\eqs[dist%l]{formulas%formula}
\eqs*{formulas%formula}
\eqs*[dist%l]{formulas%formula}
\eqalign{formulas%formula}
\eqalign*{formulas%formula}