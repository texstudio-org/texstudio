# mermaid package
# Matthew Bertucci 2026/04/28 for v1.0a

#include:shellesc
#include:graphicx
#include:adjustbox
#include:fancyvrb
#include:kvoptions

#keyvals:\usepackage/mermaid#c
Renderer=%<renderer%>
#endkeyvals

\begin{mermaid}
\end{mermaid}

\MermaidRendererOptions{options%plain}
\MermaidNoPdfFit
\MermaidGraphicsOpts{options%keyvals}
\MermaidAdjustBoxOpts{options%keyvals}