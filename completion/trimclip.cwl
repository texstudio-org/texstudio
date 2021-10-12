# trimclip package
# Matthew Bertucci 10/5/2021 for v1.2

#include:graphicx
#include:collectbox
#include:adjcalc

#ifOption:pgf
#include:pgf
#endif

\trimbox{trim specs}{content%text}
\trimbox*{trim specs}{content%text}
\begin{trimbox}{trim specs}
\end{trimbox}
\begin{trimbox*}{trim specs}
\end{trimbox*}

\clipbox{clip specs}{content%text}
\clipbox*{clip specs}{content%text}
\begin{clipbox}{clip specs}
\end{clipbox}
\begin{clipbox*}{clip specs}
\end{clipbox*}

\marginbox{margin specs}{content%text}
\marginbox*{margin specs}{content%text}
\begin{marginbox}{margin specs}
\end{marginbox}
\begin{marginbox*}{margin specs}
\end{marginbox*}