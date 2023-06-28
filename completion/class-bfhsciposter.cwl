# bfhsciposter class
# Matthew Bertucci 2022/06/04 for v2.1.2

#include:l3keys2e
#include:class-scrartcl
#include:bfhfonts
#include:bfhlogo
#include:graphicx
#include:tikz
#include:tikzlibrarycalc
#include:tcolorbox
#include:tcolorboxlibraryposter
#include:geometry
#include:bfhcolors
#include:qrcode
#include:bfhmodule
# loads tabular bfhmodule

\authorandname#*
\contentheight#L
\contentwidth#L
\footer{text}
\footergraphics{graphics code}
\footerhsep#L
\footerqrcode*{URL}#U
\footerqrcode{URL}#U
\inst{arg}
\institute{institute%text}
\raggedfooter#*
\raggedtitle#*
\titlegraphic{graphics code}

#keyvals:\posterbox,\begin{posterboxenv}
BFH-plain
BFH-inner
BFH-abstract
BFH-colored
BFH-framed
BFH-framed-inner
BFH-colored-inner
#endkeyvals

backgroundcolor#B
framecolor#B
titlefgcolor#B
titlerulecolor#B
footerrulecolor#B
blocktitlefgcolor#B
blocktitlebgcolor#B
blockbodybgcolor#B
blockbodyfgcolor#B
innerblocktitlebgcolor#B
innerblocktitlefgcolor#B
innerblockbodybgcolor#B
innerblockbodyfgcolor#B

# from tabular bfhmodule
BFH-table#B
BFH-tablehead#B
\BFHarraystretch#*
\BFHarrayrulewidth#*
\setupBfhTabular
\begin{bfhTabular}{preamble}#\tabular
\begin{bfhTabular}[pos]{preamble}#\tabular
\end{bfhTabular}
\begin{bfhTblr}{preamble}#*\tabular
\end{bfhTblr}#*
