# pst-exa package
# Matthew Bertucci 2/20/2022 for v0.06

#include:etoolbox
#include:xcolor
#include:showexpl
#include:accsupp
#include:changepage
#include:tcolorbox
#include:tcolorboxlibrarylistings
#include:tcolorboxlibrarybreakable
#include:tcolorboxlibraryskins

#keyvals:\usepackage/pst-exa#c
swpl
tcb
pdf
#endkeyvals

\begin{PSTcode}#V
\begin{PSTcode}[options%keyvals]#V
\end{PSTcode}

\begin{PSTexample}
\begin{PSTexample}[options%keyvals]
\end{PSTexample}

#keyvals:\begin{PSTcode}#c,\begin{PSTexample}#c
hwidth=##L
graphic={%<includegraphics options%>}{%<imagefile%>}
numbers=#true,none,out,fancy
fcolor=#%color
tcolor=#%color
bcolor=#%color
scolor=#%color
hsep=##L
vsep=##L
pos=#r,l,b,t,e
#endkeyvals

\hwidth#*
\noaccsupp{text}#*

hellgelb#B
colKeys#B
colIdentifier#B
colComments#B
colString#B

\filedate#S
\fileversion#S
