# PJLdraft package
# Matthew Bertucci 12/30/2021

#include:kvoptions
#include:etoolbox
#include:PJLlang
#include:xcolor
#include:tcolorbox

# from many option of tcolorbox
#include:amsmath
#include:tikz
#include:xparse
#include:pdfcol

#keyvals:\usepackage/PJLdraft#c
draft#true,false
fast#true,false
#endkeyvals

\dnfFont#*
\needgraphFont#*
\dnfTextEN#*
\needgraphTextEN#*
\dnfTextFR#*
\needgraphTextFR#*
\dnfTextDE#*
\needgraphTextDE#*
\dnfTextIT#*
\needgraphTextIT#*
\dnfTextPT#*
\needgraphTextPT#*
\dnfTextBR#*
\needgraphTextBR#*
\dnfTextES#*
\needgraphTextES#*
\dnfTextCN#*
\needgraphTextCN#*
\dnfTextTC#*
\needgraphTextTC#*
\dnfTextJP#*
\needgraphTextJP#*
\dnfTextRU#*
\needgraphTextRU#*

dnfColor
needgraphColor

\plainBox{text}#*
\plainBox[color]{text}#*

\thednfcnt#*
\theneedgraphcnt#*

\dnf
\dnf<text>

\needgraph
\needgraph<text>