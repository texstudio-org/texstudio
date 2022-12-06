# tikz-feynman package
# Matthew Bertucci 11/23/2021 for v1.1.0

#include:tikz
#include:ifluatex
#include:pgfopts
#include:tikzlibrarycalc
#include:tikzlibrarydecorations
#include:tikzlibrarydecorations.markings
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarygraphs
#include:tikzlibrarypatterns
#include:tikzlibrarypositioning
#include:tikzlibraryshapes.geometric
#include:tikzlibrarygraphdrawing

\feynmandiagram{content};
\feynmandiagram[options%keyvals][diagram options]{content};

\tikzfeynmanset{options%keyvals}

\begin{feynman}
\begin{feynman}[options%keyvals]
\end{feynman}

\vertex(name) at (coordinate) {contents};
\vertex[options%keyvals](name) at (coordinate) {contents};

\diagram{contents}
\diagram[options%keyvals]{contents}
\diagram*{contents}
\diagram*[options%keyvals]{contents}

#keyvals:\feynmandiagram#c,\tikzfeynmanset#c,\begin{feynman}#c,\diagram#c,\diagram*#c
execute at begin feynman={%<code%>}
execute at end feynman={%<code%>}
every feynman=%<styles%>
inline=%<node%>
baseline=%<node%>
horizontal=%<node1%> to %<node2%>
horizontal'=%<node1%> to %<node2%>
vertical=%<node1%> to %<node2%>
vertical'=%<node1%> to %<node2%>
every diagram=%<styles%>
small
medium
large
spring layout
spring electrical layout
layered layout
tree layout
edges=%<options%>
nodes=%<options%>
vertex
every small=%<styles%>
every medium=%<styles%>
every large=%<styles%>
every vertex=%<styles%>
every dot=%<styles%>
every square dot=%<styles%>
every empty dot=%<styles%>
every crossed dot=%<styles%>
every particle=%<styles%>
every blob=%<styles%>
every edge=%<styles%>
every boson=%<styles%>
every photon=%<styles%>
every charges boson=%<styles%>
every anti charged boson=%<styles%>
every scalar=%<styles%>
every anti charge scalar=%<styles%>
every ghost=%<styles%>
every fermion=%<styles%>
every anti fermion=%<styles%>
eveyr majorana=%<styles%>
eveyr anti majorana=%<styles%>
every gluon=%<styles%>
#endkeyvals

#keyvals:\vertex#c
right=%<length%> of %<node%>
below=%<length%> of %<node%>
above=%<length%> of %<node%>
left=%<length%> of %<node%>
above right=of %<node%>
above left=of %<node%>
below right=of %<node%>
below left=of %<node%>
#endkeyvals

#keyvals:\tikzfeynmanset#c
compat=
#endkeyvals
