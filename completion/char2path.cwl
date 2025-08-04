# char2path package
# Matthew Bertucci 2025/08/04 for v1.0.0

#include:tikz
#include:etoolbox

#keyvals:\usepackage/char2path#c
scale=%<size%>
#endkeyvals

\chartopath{string}
\chartopath[keyvals]{string}

#keyvals:\chartopath
font=#lmr,lms,lmm
draw=#%color
fill=#%color
outline=##L
scale=%<factor%>
hfading={%<color list%>}
vfading={%<color list%>}
rescan#true,false
#endkeyvals

\chartoclip{char}
\chartoclip[keyvals]{char}

#keyvals:\chartoclip
font=#lmr,lms,lmm
image=%<imagefile%>
scale=%<factor%>
anchor=%<TikZ anchor%>
offset={%<(x,y)%>}
height=##L
#endkeyvals

\ctpdata{font name}{char}#*