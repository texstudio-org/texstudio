# hawkdraw package
# Matthew Bertucci 2026/06/14 for v0.2.0

#include:l3draw

\begin{hawkdraw}#\pictureHighlight
\begin{hawkdraw}[options%keyvals]
\end{hawkdraw}

\begin{scope}
\begin{scope}[options%keyvals]
\end{scope}

\clip %<〈path spec〉%>;
\clip[%<options%>] %<〈path spec〉%>;
\fill %<〈path spec〉%>;
\fill[%<options%>] %<〈path spec〉%>;
\getfirstpoint
\getfirstslope
\getintersectioncircles[integer]{point1}{dimen1}{point2}{dimen2}
\getintersectioncircles{point1}{dimen1}{point2}{dimen2}
\getintersectionlinecircle[integer]{point1}{point2}{point3}{dimen}
\getintersectionlinecircle{point1}{point2}{point3}{dimen}
\getintersectionlines{point1}{point2}{point3}{point4}
\getlastpoint
\getlastslope
\getpathlength{token list}
\getpointx{point}
\getpointy{point}
\getpoint{point}
\hawkdrawarrayitem{string}{integer}
\hawkdrawarrayset{string}{comma list}
\hawkdrawmap[options%keyvals]{code}
\hawkdrawmap{code}
\hawkdrawset{options%keyvals}
\map {%<code%>};
\map[%<options%>] {%<code%>};
\node %<〈node spec〉%> {%<content%>};
\node[%<options%>] %<〈node spec〉%> {%<content%>};
\path %<〈path spec〉%>;
\path[%<options%>] %<〈path spec〉%>;
\point[%<options%>] ;
\stroke %<〈path spec〉%>;
\stroke[%<options%>] %<〈path spec〉%>;