# productbox package
# Matthew Bertucci 9/11/2021 for v1.1

#include:tikz

\begin{ProductBox}
\begin{ProductBox}[options%keyvals]
\end{ProductBox}
\ProductBoxSet{options%keyvals}

#keyvals:\begin{ProductBox},\ProductBoxSet
style=
3D
3d
threeD
shadow#true,false
mirror#true,false
flare#true,false
flareDiameter=##L
fold
earSize=##L
foldLine=#%color
foldOpacity=
front
back
left
right
top
bottom
empty
scale=
view=
edgeColor=#%color
faceSep=##L
width=##L
height=##L
depth=##L
clean#true,false
clip#true,false
#endkeyvals

\begin{FrontFace}#/ProductBox
\begin{FrontFace}[options%keyvals]#/ProductBox
\end{FrontFace}#/ProductBox
\begin{BackFace}#/ProductBox
\begin{BackFace}[options%keyvals]#/ProductBox
\end{BackFace}#/ProductBox
\begin{LeftFace}#/ProductBox
\begin{LeftFace}[options%keyvals]#/ProductBox
\end{LeftFace}#/ProductBox
\begin{RightFace}#/ProductBox
\begin{RightFace}[options%keyvals]#/ProductBox
\end{RightFace}#/ProductBox
\begin{TopFace}#/ProductBox
\begin{TopFace}[options%keyvals]#/ProductBox
\end{TopFace}#/ProductBox
\begin{BottomFace}#/ProductBox
\begin{BottomFace}[options%keyvals]#/ProductBox
\end{BottomFace}#/ProductBox

#keyvals:\begin{FrontFace},\begin{BackFace},\begin{LeftFace},\begin{RightFace},\begin{TopFace},\begin{BottomFace}
color=#%color
top color=#%color
bottom color=#%color
left color=#%color
right color=#%color
middle color=#%color
inner color=#%color
outer color=#%color
#endkeyvals

\begin{Front}#\picture
\end{Front}#\picture
\begin{Back}#\picture
\end{Back}#\picture
\begin{Left}#\picture
\end{Left}#\picture
\begin{Right}#\picture
\end{Right}#\picture
\begin{Top}#\picture
\end{Top}#\picture
\begin{Bottom}#\picture
\end{Bottom}#\picture

\ProductBoxThreeDStartHook#*
\ProductBoxThreeDEndHook#*