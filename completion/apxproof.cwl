# apxproof package
# Matthew Bertucci 2026/04/20 for v1.3.0

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
repeqn=#same,independent
forwardlinking=#yes,no
#endkeyvals

\begin{toappendix}
\end{toappendix}
\begin{appendixproof}
\end{appendixproof}
\newtheoremrep{envname}{title%text}#N
\newtheoremrep{envname}[counter]{title%text}#N
\newtheoremrep{envname}{title%text}[countersec]#*N
\newtheoremrep{envname}[counter]{title%text}[countersec]#N
\begin{proofsketch}
\end{proofsketch}
\begin{inlineproof}
\end{inlineproof}
\mainbodyrepeatedtheorem#*
\appendixsectionformat{number}{title%text}#*
\appendixrefname#*
\appendixbibliographystyle#*
\appendixbibliographyprelim#*
\appendixprelim#*
\chapterappendixprelim#*
\begin{nestedproof}#*
\end{nestedproof}#*
\noproofinappendix#*
\nosectionappendix#*