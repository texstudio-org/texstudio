# tkz-elements package
# Matthew Bertucci 2025/09/26 for v4.25c

#include:iftex

\tkzGetNodes
\tkzDrawLuaEllipse(pt1,pt2,pt3)
\tkzDrawLuaEllipse[options%keyvals](pt1,pt2,pt3)
\tkzDrawCoordinates(type)
\tkzDrawCoordinates[options%keyvals](type)
\tkzDrawPath(type)
\tkzDrawPath[options%keyvals](type)
\tkzGetNodesMP{mp file}
\tkzPrintNumber{number}
\tkzPrintNumber[precision]{number}
\tkzPN{number}
\tkzPN[precision]{number}
\tkzDrawSegmentsFromPaths(start,end)
\tkzDrawSegmentsFromPaths[options%keyvals](start,end)
\tkzUseLua{lua code%definition}
\tkzDrawFromPointToPath(TikZ point,Lua path)
\tkzDrawFromPointToPath[options%keyvals](TikZ point,Lua path)
\tkzDrawPointsFromPath(path,basename)
\tkzDrawPointsFromPath[options](path,basename)
\tkzGetPointFromPath(Lua path,index){point name}
\tkzGetPointsFromPath(path,basename)
\tkzGetPointsFromPath[options%keyvals](path,basename)
\tkzDrawCirclesFromPaths(centers,through)
\tkzDrawCirclesFromPaths[options%keyvals](centers,through)
\tkzPathCount(Lua path){macro name}
\tkzEraseLuaObj{object}
\tkzDrawPointOnCurve(arg)
\tkzDrawPointOnCurve[options](arg)
\percentchar#*

# deprecated
\begin{tkzelements}#S
\end{tkzelements}#S
