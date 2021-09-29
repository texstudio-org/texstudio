# ragged2e package
# Matthew Bertucci 9/28/2021 for v3.0

\Centering
\RaggedLeft
\RaggedRight
\justifying

\begin{Center}
\end{Center}
\begin{FlushLeft}
\end{FlushLeft}
\begin{FlushRight}
\end{FlushRight}
\begin{justify}
\end{justify}

\CenteringLeftskip#*
\CenteringRightskip#*
\CenteringParfillskip#*
\CenteringParindent#*
\RaggedLeftLeftskip#*
\RaggedLeftRightskip#*
\RaggedLeftParfillskip#*
\RaggedLeftParindent#*
\RaggedRightLeftskip#*
\RaggedRightRightskip#*
\RaggedRightParfillskip#*
\RaggedRightParindent#*
\JustifyingParfillskip#*
\JustifyingParindent#*

#ifOption:footnotes
#include:footmisc
#endif

#ifOption:document
#include:footmisc
#endif

#ifOption:newcommands
\LaTeXcentering#*
\LaTeXraggedleft#*
\LaTeXraggedright#*
\begin{LaTeXflushleft}#*
\end{LaTeXflushleft}#*
\begin{LaTeXflushleft}#*
\end{LaTeXflushright}#*
\begin{LaTeXcenter}#*
\end{LaTeXcenter}#*
#endif