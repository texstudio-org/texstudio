# spy tikzlibrary
# 2022/11/21 for v3.1.9a

\spy on %<〈coordinate〉%> in node %<〈node spec〉%>;
\spy[%<options%>] on %<〈coordinate〉%> in node %<〈node spec〉%>;

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
spy scope={%<options%>}
every spy in node/.style={%<options%>}
spy connection path=%<code%>
every spy on node/.style={%<options%>}
spy using outlines={%<options%>}
spy using overlays={%<options%>}
#endkeyvals

#keyvals:\spy#c
size=##L
height=##L
width=##L
connect spies
%color
#endkeyvals