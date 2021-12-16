# ed package
# Matthew Bertucci 12/13/2021 for v1.8

#include:paralist
#include:xcolor
#include:verbatim

#keyvals:\usepackage/ed#c
show
hide
nomargins
draft
final
#endkeyvals

\ednote{text%todo}#D
\ednote[label]{text%todo}#D
\Ednote{text%todo}#D
\Ednote[label]{text%todo}#D
\edissue{text%todo}#D
\edissue[label]{text%todo}#D
\edIssue{text%todo}#D
\edIssue[label]{text%todo}#D
\tweak{text%todo}#D
\tweak[label]{text%todo}#D
\Tweak{text%todo}#D
\Tweak[label]{text%todo}#D

\begin{todo}{comment%text}
\end{todo}
\begin{Todo}{comment%text}
\end{Todo}
\begin{todolist}{comment%text}
\end{todolist}
\begin{Todolist}{comment%text}
\end{Todolist}

\begin{newpart}{comment%text}
\end{newpart}
\begin{Newpart}{comment%text}
\end{Newpart}
\begin{oldpart}{comment%text}
\end{oldpart}
\begin{Oldpart}{comment%text}
\end{Oldpart}

\begin{edstub}{file}
\begin{edstub}[desc]{file}
\end{edstub}
\edstubURI{URI}

\ednoteshape#*
\ifshowednotes#*
\showednotestrue#*
\showednotesfalse#*
\ifmargins#*
\marginstrue#*
\marginsfalse#*
\theednote#*
\ednotelabel{text}#*
\ednotemargin{text}#*
\tweaklabel{text}#*
\tweakmargin{text}#*
\edissuelabel{text}#*
\edissuemargin{text}#*
\newpartmargins{text1}{text2}#*
\oldpartlabels{text1}{text2}#*
\oldpartmargins{text1}{text2}#*
\todolabels{text1}{text2}#*
\todomargins{text1}{text2}#*
\begin{musings}#*
\end{musings}#*
\ifhref#*
\hreftrue#*
\hreffalse#*

# deprecated
\issue{text%todo}#SD
\issue[label]{text%todo}#SD
\Issue{text%todo}#SD
\Issue[label]{text%todo}#SD
\edexplanation#S
\ednotemessage#S