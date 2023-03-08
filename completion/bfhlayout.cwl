# bfhlayout package
# Matthew Bertucci 2023/03/07 for v2.1.5

#include:l3keys2e
#include:geometry
#include:bfhcolors
# passes table option to xcolor
#include:zref
# loads lastpage and user options of zref
#include:zref-lastpage
#include:zref-user
#include:translations
#include:scrlayer-scrpage
#include:amsmath
#include:bfhfonts
#include:graphicx
#include:bfhlogo
#include:trimclip
#include:xparse
#include:bfhmodule
# loads tabular and rules bfhmodules

\backmatter
\bfhitemlabel
\coverpagebottommargin#*
\coverpageleftmargin#*
\coverpagerightmargin#*
\coverpagetopmargin#*
\department{department%text}
\frontmatter
\institute{institute%text}
\institution{institution%text}
\Logo#*
\Logoplain#*
\mainmatter
\partnerlogo{graphics code}
\titlefooterleft{text}
\titlefooterright{text}
\titlegraphic*{graphics code}
\titlegraphic{graphics code}
\version{version}
\versionformat{text}#*

BFH-info#B
BFH-textaccentcolor#B
BFH-Title#B

# from table option of xcolor
#include:colortbl

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

# from rules bfhmodule
#include:tikz
\bfhRule
\bfhRule[length]
