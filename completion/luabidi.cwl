# luabidi package
# Matthew Bertucci 3/14/2022 for v0.5

#include:luatex
#include:etoolbox

#keyvals:\usepackage/luabidi#c
arabmaths
autofootnoterule
textwidthfootnoterule
#endkeyvals

#ifOption:autofootnoterule
# from luabidi-autofootnoterule.def
#include:perpage
\thepagefnt#*
\FnppOrigFootnote{text}#*
\FnppOrigFootnote[num]{text}#*
\FnppOrigFootnotemark#*
\FnppOrigFootnotemark[mark]#*
#endif

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
\hboxR{text}

# from luabidi-footnotes.def
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

# not documented
\bracetext#*
\moreLRE#*
\moreRLE#*
\pLRE{text}#*
\pRLE{text}#*

# deprecated
\Footnote{text}#S