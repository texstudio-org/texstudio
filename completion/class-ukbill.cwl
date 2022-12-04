# ukbill class
# Matthew Bertucci 2022/12/01 for v1.0.0

#include:class-memoir
#include:hyphenat
#include:paralist
#include:textpos
#include:ccicons
#include:geometry
#include:changepage
#include:setspace
#include:titlesec
#include:fontspec
#include:babel
# loads english option of babel
#include:enumitem
#include:lettrine

#keyvals:\documentclass/ukbill#c
private
#endkeyvals

\drafter{name}
\printdrafter
\billcopyright{text}
\printbillcopyright
\publishedby{name}
\printpublishedby
\billtitle{text}
\printbilltitle
\billto{text}
\printbillto
\humanrights{text}
\printhumanrights
\exptitle{text}
\printexptitle
\exptext{text}
\printexptext
\billnum{number}
\printbillnum
\whereas{text}
\printwhereas

\begin{numstat}
\end{numstat}
\begin{alphstat}
\end{alphstat}
\begin{romstat}
\end{romstat}
\begin{twoalphstat}
\end{twoalphstat}
\begin{nostat}
\end{nostat}

\startschedule
\schedule{title}#L3
\schdpart{title}#L4

# not in main documentation
\begin{instatquote}#S
\begin{schumstat}#S
\begin{statquote}#S
\currentsubsection#S
\currentsubsubsection#S
\enactingformula#S
\end{instatquote}#S
\end{schumstat}#S
\end{statquote}#S
\extfont#S
\Firstblock#S
\intl{arg1}{arg2}#S
\Leftblock#S
\oldsubsection{title}#SL3
\oldsubsubsection{title}#SL4
\Rightblock#S
\stat{arg1}{arg2}#S
\stathead{arg1}{arg2}#S
\statquotelabel#S
\thealphcount#S
\theschedcount#S
\theschedon#S
\ukbillversionnumber#S

# from english option of babel
\captionsenglish#*
\dateenglish#*
\extrasenglish#*
\noextrasenglish#*
\englishhyphenmins#*
\britishhyphenmins#*
\americanhyphenmins#*
\prefacename#*
\bibname#*
\chaptername#*
\enclname#*
\ccname#*
\headtoname#*
\pagename#*
\seename#*
\alsoname#*
\proofname#*
\glossaryname#*