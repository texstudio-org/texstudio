# fancyslides class
# Matthew Bertucci 2/12/2022 for v1.0

#include:class-beamer
#include:framed
#include:tikz

#keyvals:\documentclass/fancyslides#c
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

\fitem{text}
\pitem{text}
\begin{mybox}#*
\end{mybox}#*
\begin{mybox2}#*
\end{mybox2}#*
\customtextcol{text}#*
\slogan{slogan%text}#*
\fbckg{imagefile}#g
\thankyou
\pointedsl{slogan%text}
\framedsl{slogan%text}
\itemized{itemize contents%text}
\startingslide
\misc{content%text}
\sources{list of resources%text}