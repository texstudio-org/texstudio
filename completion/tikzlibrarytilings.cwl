# tilings tikzlibrary
# 2023/06/06 for v2.0

#include:tikzlibraryspath3

\DefineTile{name%specialDef}{sides}{vertices}#s#%penrosetilename

\BakeTile{name%keyvals}

#keyvals:\BakeTile#c,\pic#c
%penrosetilename
#endkeyvals

\TilingDecomposition{type%keyvals}{level}{seed}
\TilingDecomposition[TikZ keys]{type%keyvals}{level}{seed}

#keyvals:\TilingDecomposition#c
kite
rhombus
pentagon
ktriangle
rtriangle
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
every tile/.style={%<TikZ keys%>}
tile %<<n>%>/.style={%<TikZ keys%>}
every circle arc/.style={%<TikZ keys%>}
every long arc/.style={%<TikZ keys%>}
tiling step=##L
first tile/.style={%<TikZ keys%>}
#endkeyvals

#keyvals:\pic#c
align with=%<tile%> along %<edge%>
align with=%<tile%> along %<edge%> using %<number%>
#endkeyvals

#keyvals:\path#c
save tiling path=%<edge%>
#endkeyvals

#keyvals:\tikzset#c
clone tiling side path={%<target%>}{%<source%>}
clone tile path={%<target%>}{%<source%>}
#endkeyvals

# not documented
\SetTilingPath{arg}#S
\TransformAlongSide{arg1}{arg2}#S
\TransformAlongSide*{arg1}{arg2}#S
\CoordinatesAtVertices{arg}#S
\UseTile{arg}#S
\UseTile[opt]{arg}#S
