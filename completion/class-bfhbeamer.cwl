# bfhbeamer class
# Matthew Bertucci 2/12/2022 for v2.0.0

#include:l3keys2e
#include:class-beamer
# loads table option of xcolor
#include:beamerthemeBFH

#keyvals:\documentclass/bfhbeamer#c
authorontitle#true,false
logofile=%<file%>
enforce-title-logo=
beamerarticle#true,false
printNotes
tabletNotes
paperNotes
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

#ifOption:beamerarticle
#include:bfhpub
#endif
#ifOption:beamerarticle=true
#include:bfhpub
#endif

#ifOption:printNotes
#include:handoutWithNotes
#endif
#ifOption:paperNotes
#include:handoutWithNotes
#endif

\LoadBFHModule{list of modules%keyvals}

#keyvals:\LoadBFHModule
tabular
listings
terminal
boxes
rules
#endkeyvals

# tabular BFH module loaded by default
BFH-table#B
BFH-tablehead#B
\BFHarraystretch#*
\BFHarrayrulewidth#*
\setupBfhTabular
\begin{bfhTabular}{preamble}
\begin{bfhTabular}[pos]{preamble}
\end{bfhTabular}
\begin{bfhTblr}#S
\end{bfhTblr}#S

# from table option of xcolor
#include:colortbl
\rowcolors[commands]{row}{even-row-color}{odd-row-color}
\rowcolors[commands]{row}{color}{color}#S
\rowcolors*[commands]{row}{even-row-color}{odd-row-color}
\rowcolors*[commands]{row}{color}{color}#S
\showrowcolors
\hiderowcolors
\rownum