# eemeir package
# Matthew Bertucci 2022/10/02 for v1.1

#include:xspace

#keyvals:\usepackage/eemeir#c
male
female
#endkeyvals

\E
\E*
\Em
\Em*
\Eir
\Eir*
\Eirs
\Eirs*
\swapgender
\swapgender[person]
\begin{swapgender}
\begin{swapgender}[person]
\end{swapgender}
\newwordpair{command}{male%text}{female%text}#d
\renewwordpair{command}{male%text}{female%text}
\ifmale
\male
\male[person]
\female
\female[person]
\askforgender
\askforgender[person]