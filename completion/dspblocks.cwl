# dspblocks package
# Matthew Bertucci 2022/07/21 for v1.0

#include:calc
#include:fp
#include:pst-xkey
#include:fmtcount
#include:ifthen

\begin{dspBlocks}{x}{y}#\array
\end{dspBlocks}

\BDConnHNext{n}{m}
\BDConnH{n}{m}{p}{label text}
\BDConnH[options%keyvals]{n}{m}{p}{label text}
\BDConnV{n}{m}{q}{label text}
\BDConnV[options%keyvals]{n}{m}{q}{label text}

\BDsplit
\BDadd
\BDsub
\BDmul

\BDdelay
\BDdelayN{N}

\BDfilter{label text}
\BDfilterMulti{label text}
\BDlowpass
\BDlowpass[size%l]

\BDsampler
\BDsamplerFramed
\BDsamplerFramed[size%l]

\BDsinc
\BDsinc[size%l]

\BDupsmp{N}
\BDdwsmp{N}

\BDwidth#L