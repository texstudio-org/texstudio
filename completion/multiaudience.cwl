# multiaudience package
# Matthew Bertucci 2/4/2022 for v1.04

#include:environ
#include:xkeyval

\CurrentAudience
\DefCurrentAudience{audiences}
\SetNewAudience{audience%specialDef}#s#%audience

\begin{shownto}{audiences%keyvals}
\end{shownto}
\showto{audiences%keyvals}{text}
\Footnote{audiences%keyvals}{text}
\begin{Section}{audiences%keyvals}{title}
\begin{Section}{audiences%keyvals}[short title]{title}
\end{Section}
\begin{Subsection}{audiences%keyvals}{title}
\begin{Subsection}{audiences%keyvals}[short title]{title}
\end{Subsection}
\begin{Subsubsection}{audiences%keyvals}{title}
\begin{Subsubsection}{audiences%keyvals}[short title]{title}
\end{Subsubsection}
\begin{Paragraph}{audiences%keyvals}{title}
\begin{Paragraph}{audiences%keyvals}[short title]{title}
\end{Paragraph}
\begin{Subparagraph}{audiences%keyvals}{title}
\begin{Subparagraph}{audiences%keyvals}[short title]{title}
\end{Subparagraph}

#keyvals:\begin{shownto}#c,\showto#c,\Footnote#c,\begin{Section}#c,\begin{Subsection}#c,\begin{Subsubsection}#c,\begin{Paragraph}#c,\begin{Subparagraph}#c
%audience
#endkeyvals

\DefMultiaudienceCommand{new command%cmd}{old command%definition}#d
\NewMultiaudienceSectionEnv{envname}{command}#N