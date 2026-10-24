# hawkdraw package
# Matthew Bertucci 2026/10/19 for v0.11.0

#include:l3draw

\begin{hawkdraw}#\pictureHighlight
\begin{hawkdraw}[options%keyvals]
\end{hawkdraw}
\begin{hawkdrawsoftmask}{string}
\begin{hawkdrawsoftmask}{string}[options%keyvals]
\end{hawkdrawsoftmask}
\begin{scope}
\begin{scope}[options%keyvals]
\end{scope}

\clip{path spec}
\clip[options%keyvals]{path spec}
\fill{path spec}
\fill[options%keyvals]{path spec}
\getfirstpoint
\getfirstslope
\getintersectioncircles[integer]{point1}{dimen1}{point2}{dimen2}
\getintersectioncircles{point1}{dimen1}{point2}{dimen2}
\getintersectionlinecircle[integer]{point1}{point2}{point3}{dimen}
\getintersectionlinecircle{point1}{point2}{point3}{dimen}
\getintersectionlines{point1}{point2}{point3}{point4}
\getlastpoint
\getlastslope
\getpageheight
\getpagewidth
\getpathlength{token list}
\getpointx{point}
\getpointy{point}
\getpoint{point}
\hawkdrawarrayitem{string}{integer}
\hawkdrawarrayset{string}{comma list}
\hawkdrawmap[options%keyvals]{code}
\hawkdrawmap{code}
\hawkdrawset{options%keyvals}
\map{code}
\map[options%keyvals]{code}
\node{content%text}
\node[options%keyvals]{content%text}
\path{path spec}
\path[options%keyvals]{path spec}
\point{name}
\point[options%keyvals]{name}
\stroke{path spec}
\stroke[options%keyvals]{path spec}