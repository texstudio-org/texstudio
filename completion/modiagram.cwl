# modiagram package
# Matthew Bertucci 11/8/2021 for v0.3a

#include:l3keys2e
#include:tikz
#include:chemgreek

\begin{modiagram}
\begin{modiagram}[options%keyvals]
\end{modiagram}

\setmodiagram{options%keyvals}

#keyvals:\setmodiagram#c,\begin{modiagram}#c
style=#plain,square,circle,round,fancy
distance=##L
AO-width=##L
el-sep=%<number%>
up-el-pos=%<number%>
down-el-pos=%<number%>
lines={%<TikZ%>}
names#true,false
names-style={%<TikZ%>}
names-style-add={%<TikZ%>}
labels#true,false
labels-fs=%<cmd%>
labels-style={%<TikZ%>}
#endkeyvals

\atom{left or right}{AO-spec%keyvals}
\atom[name]{left or right}{AO-spec%keyvals}

#keyvals:\atom#c
1s={%<rel-energy%>; %<el-spec%>}
2s={%<rel-energy%>; %<el-spec%>}
2p={%<rel-energy%>; %<x el-spec%>, %<y el-spec%>, %<z el-spec%>}
label=
color=
up-el-pos=
down-el-pos=
#endkeyvals

\molecule{MO-spec%keyvals}
\molecule[name]{MO-spec%keyvals}

#keyvals:\molecule#c
1sMO={%<energy gain%>/%<energy loss%>; %<s el-spec%>, %<s* el-spec%>}
2sMO={%<energy gain%>/%<energy loss%>; %<s el-spec%>, %<s* el-spec%>}
2pMO={%<s gain%>/%<s loss%>, %<p gain%>/%<p loss%>; %<s%>, %<py%>, %<pz%>, %<py*%>, %<pz*%>, %<s*%>}
label=
color=
up-el-pos=
down-el-pos=
#endkeyvals

\AO(%<xshift%>){%<type%>}{%<energy%>; %<el-spec%>}
\AO(%<xshift%>){%<type%>}[%<options%>]{%<energy%>; %<el-spec%>}
\AO[%<name%>](%<xshift%>){%<type%>}{%<energy%>; %<el-spec%>}
\AO[%<name%>](%<xshift%>){%<type%>}[%<options%>]{%<energy%>; %<el-spec%>}

#keyvals:\AO#c
label=
label[x]=
label[y]=
label[z]=
color=#%color
color[x]=#%color
color[y]=#%color
color[z]=#%color
up-el-pos=%<number%>
up-el-pos[x]=%<number%>
up-el-pos[y]=%<number%>
up-el-pos[z]=%<number%>
down-el-pos=%<number%>
down-el-pos[x]=%<number%>
down-el-pos[y]=%<number%>
down-el-pos[z]=%<number%>
#endkeyvals

\connect{AO-connect}

\EnergyAxis
\EnergyAxis[options%keyvals]

#keyvals:\EnergyAxis
title=
head=%<TikZ arrow head%>
#endkeyvals