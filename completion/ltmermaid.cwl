# ltmermaid package
# Matthew Bertucci 2026/04/28 for v1.0a

#include:ifluatex
#include:graphicx
#include:adjustbox
#include:fancyvrb
#include:luacode
#include:kvoptions

#keyvals:\usepackage/ltmermaid#c
Renderer=%<renderer%>
#endkeyvals

\begin{mermaid}
\end{mermaid}

\MermaidRendererOptions{options%plain}
\MermaidNoPdfFit
\MermaidGraphicsOpts{options%keyvals}
\MermaidAdjustBoxOpts{options%keyvals}