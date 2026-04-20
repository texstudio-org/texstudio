# luabidi package
# Matthew Bertucci 2026/04/20 for v1.0

#include:luatex

#keyvals:\usepackage/luabidi#c
arabmaths
autofootnoterule
textwidthfootnoterule
#endkeyvals

\setRTLmain
\setRTL
\setRL#*
\unsetLTR#*
\setLTR
\setLR#*
\unsetRTL#*
\begin{RTL}
\end{RTL}
\begin{LTR}
\end{LTR}
\RLE{text}
\RL{text}#*
\LRE{text}
\LR{text}#*
\hboxR{text}#*
\vboxR{text}#*
\vtopR{text}#*
\hboxL{text}#*
\vboxL{text}#*
\vtopL{text}#*

\localnumeral{number}#*
\localnumeral*{counter}#*
\footnotemarkLR#*
\footnotemarkLR[mark]#*
\footnotemarkRL#*
\footnotemarkRL[mark]#*
\LTRfootnote{text}
\LTRfootnote[num]{text}
\RTLfootnote{text}
\RTLfootnote[num]{text}
\footnoterulewidth#*
\leftfootnoterule
\rightfootnoterule
\textwidthfootnoterule
\autofootnoterule

# deprecated
\Footnote{text}#S