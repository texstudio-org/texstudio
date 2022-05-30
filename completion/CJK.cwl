# CJK package
# Matthew Bertucci 2022/05/09 for v4.8.5

#include:MULEenc

#keyvals:\usepackage/CJK#c
lowercase
global
local
active
encapsulated
#endkeyvals

\CJKbold
\CJKnormal
\CJKboldshift#*
\CJKsymbol{n}
\CJKpunctsymbol{n}#*
\CJKsymbols{codepoint1}{codepoint2}#*
\CJKchar{byte1}{byte2}
\CJKchar[UTF8]{byte1}{byte2}
\Unicode{byte1}{byte2}
\CJKCJKchar
\CJKhangulchar
\CJKlatinchar
\CJKhwkatakana
\CJKnohwkatakana
\CJKenc{encoding}
\CJKfontenc{encoding}{font encoding}
\CJKfamily{family}
\CJKencfamily{encoding}{family}
\CJKencfamily[font encoding]{encoding}{family}
\CJKshape{family}#*
\CJKencshape{encoding}{family}#*
\CJKencshape[font encoding]{encoding}{family}#*
\CJKaddEncHook{encoding}{code}#*
\CJKhanja
\CJKhangul
\CJKkern
\CJKglue
\CJKtolerance#*
\nbs
\CJKtilde
\standardtilde
\CJKspace
\CJKnospace
\CJKindent#*
\begin{CJK}{encoding}{family}
\begin{CJK}[font encoding]{encoding}{family}
\end{CJK}
\begin{CJK*}{encoding}{family}
\begin{CJK*}[font encoding]{encoding}{family}
\end{CJK*}
\CJKcaption{caption}
\CJKhdef{arg1}{arg2}#*
\CJKhlet{arg1}{arg2}#*
\CJKvdef{arg1}{arg2}#*
\CJKvlet{arg1}{arg2}#*