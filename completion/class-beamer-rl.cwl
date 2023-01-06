# beamer-rl class
# Matthew Bertucci 2023/01/02 for v1.7

#include:luatex
#include:ifluatex
#include:class-beamer
#include:babel
# loads bidi=basic option of babel (which loads fontspec)
#include:fontspec

#keyvals:\documentclass/beamer-rl#c
arabic
arabic={%<\babelprovide options%>}
arabic-dz
arabic-dz={%<\babelprovide options%>}
arabic-tn
arabic-tn={%<\babelprovide options%>}
arabic-ma
arabic-ma={%<\babelprovide options%>}
arabic-eg
arabic-eg={%<\babelprovide options%>}
arabic-sa
arabic-sa={%<\babelprovide options%>}
arabic-iq
arabic-iq={%<\babelprovide options%>}
arabic-sy
arabic-sy={%<\babelprovide options%>}
arabic-lb
arabic-lb={%<\babelprovide options%>}
arabic-ps
arabic-ps={%<\babelprovide options%>}
arabic-jo
arabic-jo={%<\babelprovide options%>}
centralkurdish
centralkurdish={%<\babelprovide options%>}
hebrew
hebrew={%<\babelprovide options%>}
kashmiri
kashmiri={%<\babelprovide options%>}
mazanderani
mazanderani={%<\babelprovide options%>}
malayalam
malayalam={%<\babelprovide options%>}
northernkurdish-arab
northernkurdish-arab={%<\babelprovide options%>}
pashto
pashto={%<\babelprovide options%>}
persian
persian={%<\babelprovide options%>}
punjabi-arab
punjabi-arab={%<\babelprovide options%>}
syriac
syriac={%<\babelprovide options%>}
urdu
urdu={%<\babelprovide options%>}
uyghur
uyghur={%<\babelprovide options%>}
uzbek-arab
uzbek-arab={%<\babelprovide options%>}
yiddish
yiddish={%<\babelprovide options%>}
layout=#sectioning,counters,counters*,contents,footnotes,captions,columns,graphics,extras
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

#ifOption:layout=footnotes
\localfootnote{text}
\mainfootnote{text}
\localfootnotetext#*
\mainfootnotetext#*
#endif

\blacktriangleright
\blacktriangleleft
\redefbeamertemplate{element}{option}#*

\begin{oldpgfpicture}#S
\end{oldpgfpicture}#S
\oldpgfpicture#S
\endoldpgfpicture#S
\oldpgfuseshading#S
