# mode: pst-text.sty
# dani/2006-02-22
# Matthew Bertucci 2022-02-20 for v1.02

#include:pstricks

\pstextpath[pos](x,y){graphics object}{text}
\pstextpath(x,y){graphics object}{text}

\pscharpath{text}
\pscharpath[options%keyvals]{text}
\pscharpath*{text}
\pscharpath*[options%keyvals]{text}

\pscharclip{text}#*
\pscharclip[options%keyvals]{text}#*
\pscharclip*{text}#*
\pscharclip*[options%keyvals]{text}#*
\endpscharclip#*

\begin{pscharclip}{text}
\begin{pscharclip}[options%keyvals]{text}
\end{pscharclip}
\begin{pscharclip*}{text}
\begin{pscharclip*}[options%keyvals]{text}
\end{pscharclip*}

\psCircleText{text}
\psCircleText[options%keyvals]{text}
\psCircleText(x,y){text}
\psCircleText[options%keyvals](x,y){text}

\psWarp{text}
\psWarp[options%keyvals]{text}
\psWarp(x,y){text}
\psWarp[options%keyvals](x,y){text}

\TPoffset#*
\PSTextPathLoaded#S
