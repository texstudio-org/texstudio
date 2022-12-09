# matrix.skeleton tikzlibrary
# 2022/12/06 for v1.1

#include:tikzlibrarymatrix
#include:tikzlibraryfit
#include:tikzlibrarybackgrounds

\matrix (m) [%<options%>] {%<content%>};

#keyvals:\matrix#c
label skeleton
style odd rows={%<TikZ keys%>}
style odd rows on layer={%<layer%>}{%<TikZ keys%>}
style even rows={%<TikZ keys%>}
style even rows on layer={%<layer%>}{%<TikZ keys%>}
style odd tiling rows={%<TikZ keys%>}
style odd tiling rows on layer={%<layer%>}{%<TikZ keys%>}
style even tiling rows={%<TikZ keys%>}
style even tiling rows on layer={%<layer%>}{%<TikZ keys%>}
style odd columns={%<TikZ keys%>}
style odd columns on layer={%<layer%>}{%<TikZ keys%>}
style even columns={%<TikZ keys%>}
style even columns on layer={%<layer%>}{%<TikZ keys%>}
style odd tiling columns={%<TikZ keys%>}
style odd tiling columns on layer={%<layer%>}{%<TikZ keys%>}
style even tiling columns={%<TikZ keys%>}
style even tiling columns on layer={%<layer%>}{%<TikZ keys%>}
style grid={%<TikZ keys%>}
style grid on layer={%<layer%>}{%<TikZ keys%>}
style tiling grid={%<TikZ keys%>}
style tiling grid on layer={%<layer%>}{%<TikZ keys%>}
style contour={%<TikZ keys%>}
style contour on layer={%<layer%>}{%<TikZ keys%>}
#endkeyvals

\fitandstyle{node spec}{TikZ keys%keyvals}
\fitandstyle[layer name]{node spec}{TikZ keys%keyvals}

# list not exhaustive
#keyvals:\fitandstyle#c
fill=#%color
highlight=#%color
opacity=%<factor%>
draw=#%color
#endkeyvals

## not documented
# from pgflibrarymatrix.skeleton.code.tex
\pgfmatrixlabelskeleton#S

# from tikzlibrarymatrix.skeleton.code.tex
\stylecontour{TikZ keys}#S
\stylegrid{TikZ keys}#S
\styletilinggrid{TikZ keys}#S