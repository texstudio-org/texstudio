# penrose tikzlibrary
# 2022/12/09 for v1.4

#include:tikzlibraryspath3

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
every Penrose tile/.style={%<TikZ keys%>}
Penrose tile %<<n>%>/.style={%<TikZ keys%>}
every Penrose pic/.style={%<TikZ keys%>}
every kite/.style={%<TikZ keys%>}
every dart/.style={%<TikZ keys%>}
every thin rhombus/.style={%<TikZ keys%>}
every thick rhombus/.style={%<TikZ keys%>}
every pentagon 5/.style={%<TikZ keys%>}
every pentagon 3/.style={%<TikZ keys%>}
every pentagon 2/.style={%<TikZ keys%>}
every pentagram/.style={%<TikZ keys%>}
every boat/.style={%<TikZ keys%>}
every diamond/.style={%<TikZ keys%>}
every golden triangle/.style={%<TikZ keys%>}
every reverse golden triangle/.style={%<TikZ keys%>}
every golden gnomon/.style={%<TikZ keys%>}
every reverse golden gnomon/.style={%<TikZ keys%>}
every circle arc/.style={%<TikZ keys%>}
every long arc/.style={%<TikZ keys%>}
Penrose step=##L
#endkeyvals

\BakePenroseTile{name%keyvals}

#keyvals:\BakePenroseTile#c,\pic#c
kite
dart
thin rhombus
thick rhombus
pentagon 5
pentagon 3
pentagon 2
pentagram
boat
diamond
golden triangle
reverse golden triangle
golden gnomon
reverse golden gnomon
%penrosetilename
#endkeyvals

#keyvals:\pic#c
align with=%<tile%> along %<edge%>
align with=%<tile%> along %<edge%> using %<number%>
#endkeyvals

\PenroseDecomposition{type%keyvals}{level}{seed}
\PenroseDecomposition[TikZ keys]{type%keyvals}{level}{seed}

#keyvals:\PenroseDecomposition#c
kite
rhombus
pentagon
ktriangle
rtriangle
#endkeyvals

#keyvals:\path#c
save Penrose path=%<edge%>
#endkeyvals

#keyvals:\tikzset#c
clone Penrose side path={%<target%>}{%<source%>}
clone Penrose tile path={%<target%>}{%<source%>}
#endkeyvals

\DefineTile{name%specialDef}{sides}{coordinates}#s#%penrosetilename

# not documented
\SetPenrosePath{arg}#S
\UsePenroseTile{arg}#S
\UsePenroseTile[opt]{arg}#S
\TransformAlongSide{arg1}{arg2}#S
\CoordinatesAtVertices{arg}#S

# deprecated
\MakePenroseTile{name}#S