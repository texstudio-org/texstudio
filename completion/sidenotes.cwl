# sidenotes package
# Matthew Bertucci 11/3/2021 for v1.00

#include:l3keys2e
#include:marginnote
#include:caption
#include:xparse
#include:changepage

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