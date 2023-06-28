# semantic-markup package
# Matthew Bertucci 2/15/2022

#include:csquotes
#include:environ
#include:stackengine

#keyvals:\usepackage/semantic-markup#c
defaultquotes
endnotes
#endkeyvals

#ifOption:endnotes
#include:endnotes
\DoBeforeEndnotes
\EndnoteFont
\SetupEndnotes
#endif

\ifdefaultquotes#*
\defaultquotestrue#*
\defaultquotesfalse#*
\ifendnotes#*
\endnotestrue#*
\endnotesfalse#*

\strong{text}
\quoted{text}
\soCalled{text}
\code{text%plain}
\term{text}
\mentioned{text}
\foreign{text}
\worktitle{text}
\parttitle{text}
\wtitle{text}#*
\ptitle{text}#*
\add{text}
\Dots
\gloss{term%text}{def%text}
\quotedgloss{term%text}{def%text}
\XXX
\XXX[text]
\citXXX
\citXXX[text]
\begin{Footnote}
\end{Footnote}
\fl
\na
\sh
\octave{text}
\musfig{upper}{lower}
\meter{upper}{lower}