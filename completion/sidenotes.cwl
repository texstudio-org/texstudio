# sidenotes package
# Matthew Bertucci 2021/11/03 for v1.00

#include:l3keys2e
#include:marginnote
#include:caption
#include:changepage

#keyvals:\usepackage/sidenotes#c
oneside
#endkeyvals

\sidenote{text}
\sidenote[number]{text}
\sidenote[number][offset%l]{text}
\sidenotemark{text}
\sidenotemark[number]{text}
\sidenotemark[number][offset%l]{text}
\sidenotetext{text}
\sidenotetext[number]{text}
\sidenotetext[number][offset%l]{text}
\sidecaption{text}
\sidecaption[entry]{text}
\sidecaption[entry][offset%l]{text}
\begin{marginfigure}
\begin{marginfigure}[offset%l]
\end{marginfigure}
\begin{margintable}
\begin{margintable}[offset%l]
\end{margintable}
\thesidenote
