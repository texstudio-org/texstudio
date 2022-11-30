# calligraphy tikzlibrary
# 2022/11/24 for v2.4

#include:spath3

\calligraphy %<〈path spec〉%>;
\calligraphy[%<options%>] %<〈path spec〉%>;
\pen %<〈path spec〉%>;
\pen[%<options%>] %<〈path spec〉%>;
\definepen %<〈path spec〉%>;
\definepen[%<options%>] %<〈path spec〉%>;

#keyvals:\calligraphy#c,\pen#c,\definepen#c
pen colour=#%color
nib style={%<index%>}{%<options%>}
stroke style={%<index%>}{%<options%>}
this stroke style=
taper=#none,both,start,end
weight=#heavy,light
heavy
light
heavy line width=##L
light line width=##L
taper line width=##L
line width=##L
#endkeyvals

#keyvals:\calligraphy#c
copperplate
#endkeyvals