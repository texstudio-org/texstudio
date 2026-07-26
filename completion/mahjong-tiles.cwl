# mahjong-tiles package
# Matthew Bertucci 2026/07/02 for v2.2.0

#include:graphicx
#include:xcolor
#include:tikz
#include:stackengine

\mahjongtilessetup{options%keyvals}
\mahjong{tiles}
\mahjong[height|keyvals%keyvals]{tiles}
\mahjong[height|keyvals%keyvals][scale]{tiles}
\mahjong[height|keyvals%keyvals][scale][color]{tiles}
\mahjong[height|keyvals%keyvals][scale][color][keyvals%plain]{tiles}
\mahjongriver{tiles}
\mahjongriver[height|keyvals%keyvals]{tiles}
\mahjongriver[height|keyvals%keyvals][scale]{tiles}
\mahjongriver[height|keyvals%keyvals][scale][color]{tiles}
\mahjongriver[height|keyvals%keyvals][scale][color][keyvals%plain]{tiles}

#keyvals:\mahjongtilessetup,\mahjong,\mahjongriver,\usepackage/mahjong-tiles#c
height=##L
scale=%<factor%>
tile-dir=%<directory%>
color=#%color
no-aka=
river-cols=%<integer%>
river-row-gap=##L
#endkeyvals

\mj{tiles}