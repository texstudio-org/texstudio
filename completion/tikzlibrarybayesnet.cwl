# bayesnet tikzlibrary
# 2022/12/09 for v0.1

#include:tikzlibraryshapes
#include:tikzlibraryfit
#include:tikzlibrarychains

#keyvals:\node#c
latent
obs
det
const
factor
plate
gate
#endkeyvals

\factor{name}{caption%text}{inputs}{outputs}
\factor[TikZ keys]{name}{caption%text}{inputs}{outputs}
\plate{name}{fitlist}{caption%text}
\plate[TikZ keys]{name}{fitlist}{caption%text}
\gate{name}{fitlist}{inputs}
\gate[TikZ keys]{name}{fitlist}{inputs}
\vgate{name}{fitlist-left}{caption-left%text}{fitlist-right}{caption-right%text}{inputs}
\vgate[TikZ keys]{name}{fitlist-left}{caption-left%text}{fitlist-right}{caption-right%text}{inputs}
\hgate{name}{fitlist-top}{caption-top%text}{fitlist-bottom}{caption-bottom%text}{inputs}
\hgate[TikZ keys]{name}{fitlist-top}{caption-top%text}{fitlist-bottom}{caption-bottom%text}{inputs}
\edge{inputs}{outputs}
\edge[TikZ keys]{inputs}{outputs}
\factoredge{inputs}{factors}{outputs}
\factoredge[TikZ keys]{inputs}{factors}{outputs}