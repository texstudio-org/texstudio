# kvmap package
# Matthew Bertucci 11/19/2021 for v0.3.5

#include:amsmath
#include:tikz

\kvmapsetup{options%keyvals}

\begin{kvmap}#\picture,pictureHighlight
\begin{kvmap}[options%keyvals]#\picture
\end{kvmap}

#keyvals:\kvmapsetup#c,\begin{kvmap}#c
bundle/invert#true,false
bundle/hinvert#true,false
bundle/vinvert#true,false
bundle/overlapmargins=##L
bundle/color=#%color
bundle/reducespace=##L
#endkeyvals

\begin{kvmatrix}{variables%formula}#\math,array
\end{kvmatrix}

\kvlist{width}{height}{elements%formula}{variables%formula}

\bundle{x1}{y1}{x2}{y2}
\bundle[options%keyvals]{x1}{y1}{x2}{y2}

#keyvals:\bundle
invert#true,false
hinvert#true,false
vinvert#true,false
overlapmargins=##L
color=#%color
reducespace=##L
#endkeyvals
