# filecontentsdef package
# Matthew Bertucci 11/17/2021 for v1.5

\begin{filecontentsdef}{file}{macro%cmd}#d
\end{filecontentsdef}
\begin{filecontentsdef*}{file}{macro%cmd}#d
\end{filecontentsdef*}
\begin{filecontentsgdef}{file}{macro%cmd}#d
\end{filecontentsgdef}
\begin{filecontentsgdef*}{file}{macro%cmd}#d
\end{filecontentsgdef*}
\begin{filecontentsdefstarred}{file}{macro%cmd}#*d
\end{filecontentsdefstarred}#*
\begin{filecontentsgdefstarred}{file}{macro%cmd}#*d
\end{filecontentsgdefstarred}#*

\begin{filecontentsdefmacro}{macro%cmd}#d
\end{filecontentsdefmacro}
\begin{filecontentsgdefmacro}{macro%cmd}#d
\end{filecontentsgdefmacro}

\filecontentsprint{macro}

\FCDprintenvname
\FCDprintenvoptions

\filecontentsprintviascan{macro}

\filecontentsexec{code}

\begin{filecontentshere}{file}
\end{filecontentshere}
\begin{filecontentshere*}{file}
\end{filecontentshere*}
\filecontentsheremacro

\filecontentsdef#*
\endfilecontentsdef#*
\filecontentsgdef#*
\endfilecontentsgdef#*
\filecontentsdefstarred#*
\endfilecontentsdefstarred#*
\filecontentsgdefstarred#*
\endfilecontentsgdefstarred#*
\filecontentsdefmacro#*
\endfilecontentsdefmacro#*
\filecontentsgdefmacro#*
\endfilecontentsgdefmacro#*
\filecontentshere#*
\endfilecontentshere#*
\filecontentsherestarred#*
\endfilecontentsherestarred#*

\FCDtabtofile#*
\FCDtabtomacro#*
\FCDformfeedtofile#*
\FCDformfeedtomacro#*