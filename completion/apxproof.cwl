# apxproof package
# Matthew Bertucci 2026/06/03 for v1.4.1

#include:environ
#include:etoolbox
#include:fancyvrb
#include:ifthen
#include:kvoptions
#include:catchfile
#include:amsthm
#include:bibunits

#keyvals:\usepackage/apxproof#c
appendix=#append,inline,strip
bibliography=#common,separate
bibengine=#bibtex,biblatex
repeqn=#same,independent
forwardlinking=#yes,no
#endkeyvals

\begin{toappendix}
\end{toappendix}
\begin{appendixproof}
\end{appendixproof}
\newtheoremrep{envname}{title%text}#N
\newtheoremrep{envname}[counter]{title%text}#N
\newtheoremrep{envname}{title%text}[countersec]#N
\newtheoremrep{envname}[counter]{title%text}[countersec]#N
\newtheoremrep*{envname}{title%text}#N
\newtheoremrep*{envname}[counter]{title%text}#N
\newtheoremrep*{envname}{title%text}[countersec]#N
\newtheoremrep*{envname}[counter]{title%text}[countersec]#N
\begin{proofsketch}
\end{proofsketch}
\begin{inlineproof}
\end{inlineproof}
\mainbodyrepeatedtheorem#*
\appendixsectionformat{number}{title%text}#*
\appendixproofname#*
\appendixrefname#*
\appendixbibliographystyle#*
\appendixbibliographyprelim#*
\appendixprelim#*
\chapterappendixprelim#*
\flushchapterappendix#*
\begin{nestedproof}#*
\end{nestedproof}#*
\noproofinappendix#*
\nosectionappendix#*
\apxproofhook{code}#*