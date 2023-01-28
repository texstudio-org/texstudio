# codeanatomy package
# Matthew Bertucci 2023/01/27 for v0.4-Beta

#include:tikz
#include:tikzlibrarytikzmark
#include:tikzlibraryfit
#include:tikzlibrarybending
#include:tikzlibraryshapes
#include:tikzlibrarychains
#include:tikzlibrarybackgrounds
#include:tikzlibrarydecorations
#include:tikzlibrarydecorations.pathmorphing

annotationcolor#B
bgcmdcolor#B

\codeBlock{code}
\cPart{node name}{code}
\cPart[TikZ keys]{node name}{code}
\iPart{node name}{code}
\iPart[TikZ keys]{node name}{code}
\mtPoint{node name}
\hmtPoint{node name}
\mbPoint{node name}
\dmbPoint{node name}
\extremPoint{node name}
\extremPoint{node name}[yshift]
\extremPoint{node name}[yshift][xshift]
\extremPoint{node name}[yshift][xshift][TikZ keys]
\fitExtrem{node name}{extrem points}
\bgcode{code}
\ptab
\phspace
\codeAnnotation{node name}(coordinate){label text%text}