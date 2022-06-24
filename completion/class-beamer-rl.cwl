# beamer-rl class
# Matthew Bertucci 2022/06/21 for v1.6

#include:luatex
#include:kvoptions
#include:kvsetkeys
#include:ifluatex
#include:class-beamer
#include:babel
# loads bidi=basic option of babel (which loads fontspec)
#include:fontspec

#keyvals:\documentclass/beamer-rl#c
babel={%<babel options%>}
arabic
# options passed to beamer class
usepdftitle#true,false
envcountsect
notheorems
noamsthm
compress
t
c
leqno
fleqn
handout
trans
pdftex
nativepdf
pdfmark
dvips
dviwindo
dvipsone
vtex
ps2pdf
ignorenonframetext
noamssymb
bigger
smaller
8pt
9pt
10pt
11pt
12pt
14pt
17pt
20pt
draft
CJK
cjk
onlytextwidth
pgf={%<pgf options%>}
hyperref={%<hyperref options%>}
color={%<color options%>}
xcolor={%<xcolor options%>}
ucs
utf8x
utf8
aspectratio=#2013,1610,169,149,141,54,43,32,%<xxxx%>
#endkeyvals

\blacktriangleright
\blacktriangleleft
\redefbeamertemplate{element}{option}#*
\thebeginframepardir#*

\begin{oldpgfpicture}#S
\end{oldpgfpicture}#S
\oldframe#S
\oldpgfpicture#S
\endoldpgfpicture#S
\oldpgfuseshading#S