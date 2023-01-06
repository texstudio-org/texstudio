# minimalist-plain package
# Matthew Bertucci 2023/01/02 for 2023/01/02 release

#include:relsize
#include:anyfontsize
#include:tikz
#include:tikzlibrarycalc
#include:tikzlibraryshadings
#include:tikzpagenodes
#include:geometry
#include:fancyhdr
#include:extramarks
#include:titlesec
#include:ulem
#include:titletoc
#include:enumitem
#include:imakeidx
#include:silence
#include:projlib-draft
#include:mathtools
#include:amsthm
#include:bookmark
#include:hyperref
#include:projlib-theorem
#include:projlib-author
# loads amsfashion options of projlib-author
#include:projlib-titlepage
#include:tcolorbox
#include:tcolorboxlibrarymany

\LocallyStopLineNumbers
\ResumeLineNumbers
\begin{keyword}
\end{keyword}
\parttext{text}
\begin{emphasis}
\end{emphasis}

\ifLNturnsON#*
\keywordname#*
\LNturnsONfalse#*
\LNturnsONtrue#*
\partstring#*
\customqedsymbol#S
\IndexDotfill#*
\IndexLinebreak#*
\IndexHeading{text}#*

# from amsfashion option of projlib-author
#include:projlib-language
#include:scontents
\keywords{keywords%text}
\dedicatory{text}
\subjclass{classification}
\subjclass[year]{classification}
