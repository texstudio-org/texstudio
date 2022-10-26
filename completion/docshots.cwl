# docshots package
# Matthew Bertucci 2022/10/26 for v0.1.0

#include:iexec
#include:fancyvrb
#include:xcolor
#include:graphicx
#include:tikz
#include:pgfopts

#keyvals:\usepackage/docshots#c
pdflatex=%<path%>
gs=%<path%>
pdfcrop=%<path%>
margin=%<number%>
hspace=##L
left=##L
right=##L
dtx
tmpdir=%<path%>
runs=%<integer%>
small
tiny
log
inputminted=%<language%>
lstinputlisting
#endkeyvals

\docshotPrerequisite{file}
\docshotAfter{command line}

\begin{docshot}
\end{docshot}
