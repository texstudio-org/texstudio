# lpic package
# Matthew Bertucci 11/22/2021 for v0.8

#include:epsfig
#include:rotating
#include:calc
#include:ifthen
#include:color

\begin{lpic}{%<filename%>(%<x,y%>)}
\begin{lpic}[%<options%>]{%<filename%>(%<x,y%>)}
\end{lpic}

#keyvals:\begin{lpic}#c
l(%<length%>)
r(%<length%>)
t(%<length%>)
b(%<length%>)
grid(%<step%>)
coords(%<step%>)
frames(%<length%>)
frame(%<length%>)
figframe(%<length%>)
draft
clean
nolbl
nofigure
#endkeyvals

\lbl{%<coords%>;%<LaTeX content%>}#/lpic
\lbl[%<pos%>]{%<coords%>;%<LaTeX content%>}#/lpic

\lpunitlength#*
\lpmarginright#*
\lpmarginleft#*
\lpmargintop#*
\lpmarginbottom#*
\lpbgsep#*
\lpgridthickness#*
\lpframethickness#*
\lplblframethickness#*
\lpfigframethickness#*
\thelpgridstep#*
\thelpcoordstep#*