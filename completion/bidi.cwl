# bidi package
# hadi_sfr (info@hadisafari.ir)
# updated 3/14/2022 for v36.7

#include:xetex
#include:iftex
#include:biditools
#include:zref-abspage
#include:auxhook
#include:ltxcmds
#include:xkeyval

#keyvals:\usepackage/bidi#c
RTLdocument
rldocument
extrafootnotefeatures
#endkeyvals

\bidiversion#*
\bididate#*
\TeXXeTOn#*
\TeXXeTOf#*

#ifOption:extrafootnotefeatures
\normalfootnotes
\twocolumnfootnotes
\threecolumnfootnotes
\fourcolumnfootnotes
\fivecolumnfootnotes
\sixcolumnfootnotes#*
\sevencolumnfootnotes#*
\eightcolumnfootnotes#*
\ninecolumnfootnotes#*
\tencolumnfootnotes#*
\RTLcolumnfootnotes
\LTRcolumnfootnotes
\paragraphfootnotes
\setLTRparagraphfootnotes
\setRTLparagraphfootnotes
#endif

\setLTR
\setLR
\unsetRL
\unsetRTL
\setRTL
\setRL
\unsetLTR
\begin{LTR}
\end{LTR}
\begin{RTL}
\end{RTL}
\LRE{text}
\LR{text}
\RLE{text}
\RL{text}
\LTRfootnote{text}
\LTRfootnote[num]{text}
\RTLfootnote{text}
\RTLfootnote[num]{text}
\setfootnoteRL
\setfootnoteLR
\unsetfootnoteRL
\LTRthanks{text}
\RTLthanks{text}
\LTRfootnotetext{text}
\LTRfootnotetext[num]{text}
\RTLfootnotetext{text}
\RTLfootnotetext[num]{text}
\autofootnoterule
\rightfootnoterule
\leftfootnoterule
\LRfootnoterule
\textwidthfootnoterule
\SplitFootnoteRule
\debugfootnotedirection
\RTLdblcol
\LTRdblcol
\RTLcases{%<\text{brach1}\cr\text{brach2}\cr...%>}
\XeTeX
\XeLaTeX
\SepMark{mark}
\hboxR{text}
\hboxL{text}
\vboxR{text}
\vboxL{text}
\bidillap
\bidirlap
\begin{LTRitems}
\end{LTRitems}
\begin{RTLitems}
\end{RTLitems}
\begin{LTRbibitems}
\end{LTRbibitems}
\begin{RTLbibitems}
\end{RTLbibitems}
\setLTRbibitems
\setRTLbibitems
\setdefaultbibitems
\setRTLmarginpar
\setLTRmarginpar
\setdefaultmarginpar
\LTRmarginpar[left-text%text]{right-text%text}
\RTLmarginpar[left-text%text]{right-text%text}

# if dblfnote loaded
\RTLdfnmakecol#S
\LTRdfnmakecol#S

# if listings loaded
#keyvals:\lstset,\lstinline,\begin{lstlisting},\lstinputlisting,\lstMakeShortInline,\lstdefinelanguage,\lstdefinestyle
captiondirection=#textdirection,RTL,LTR
#endkeyvals

# if multicol loaded
\RTLmulticolcolumns#S
\LTRmulticolcolumns#S
