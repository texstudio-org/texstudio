# index package
# Matthew Bertucci 11/5/2021 for v4.1beta

\newindex{author tag}{output ext}{input ext}{title%plain}
\newindex[number cmd]{author tag}{output ext}{input ext}{title%plain}
\renewindex{author tag}{output ext}{input ext}{title%plain}
\renewindex[number cmd]{author tag}{output ext}{input ext}{title%plain}
\printindex
\printindex[tag]
\index*{entry}
\index[tag]{entry}
\shortindexingon
\shortindexingoff
\begin{shortindexingon}
\end{shortindexingon}
\proofmodetrue
\proofmodefalse
\indexproofstyle{code}
\disableindex
\seename#*
\see{text}{page number}