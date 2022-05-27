# kaotheorems package
# Matthew Bertucci 2022/05/26 for v0.9.8

#include:kvoptions
#include:amsmath
#include:amsthm
#include:thmtools
#include:mdframed

#keyvals:\usepackage/kaotheorems#c
framed
background=#%color
theorembackground=#%color
propositionbackground=#%color
lemmabackground=#%color
corollarybackground=#%color
definitionbackground=#%color
assumptionbackground=#%color
remarkbackground=#%color
examplebackground=#%color
exercisebackground=#%color
#endkeyvals

#ifOption:framed
#include:tikz
#endif
#ifOption:framed=true
#include:tikz
#endif

#keyvals:\theoremstyle#c
kaoplain
kaodefinition
kaoassumption
kaoremark
kaoexample
kaoexercise
#endkeyvals

\begin{theorem}
\begin{theorem}[heading%text]
\end{theorem}
\begin{proposition}
\begin{proposition}[heading%text]
\end{proposition}
\begin{lemma}
\begin{lemma}[heading%text]
\end{lemma}
\begin{corollary}
\begin{corollary}[heading%text]
\end{corollary}
\begin{definition}
\begin{definition}[heading%text]
\end{definition}
\begin{assumption}
\begin{assumption}[heading%text]
\end{assumption}
\begin{remark}
\begin{remark}[heading%text]
\end{remark}
\begin{example}
\begin{example}[heading%text]
\end{example}
\begin{exercise}
\begin{exercise}[heading%text]
\end{exercise}