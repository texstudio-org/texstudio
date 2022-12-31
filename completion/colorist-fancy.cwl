# colorist-fancy package
# Matthew Bertucci 2022/09/05 for release 2022/09/03

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
#include:marginnote
#include:ifoddpage
#include:iftex
#include:projlib-author
# loads amsfashion options of projlib-author
#include:projlib-titlepage
#include:tcolorbox
#include:tcolorboxlibrarymany

\begin{keyword}
\end{keyword}
\parttext{text}
\begin{emphasis}
\end{emphasis}
\begin{proof}[heading%text]
\end{proof}

\AfterEnvEnd{code}#*
\ScanEnv{arg1}{arg2}{arg3}#*
\ScanEnv*{arg1}{arg2}{arg3}#*
\keywordname#*
\partstring#*
\customqedsymbol#S
\IndexDotfill#*
\IndexLinebreak#*
\IndexHeading{text}#*

maintheme#B
forestgreen#B
lightorange#B

# from amsfashion option of projlib-author
#include:projlib-language
#include:scontents
\keywords{keywords%text}
\dedicatory{text}
\subjclass{classification}
\subjclass[year]{classification}
