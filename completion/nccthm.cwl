# nccthm package
# Matthew Bertucci 2/3/2022 for v1.1

#include:amsgen
#include:dcounter

#keyvals:\usepackage/nccthm#c
whiteqed
blackqed
noindent
indent
nomargin
margin
#endkeyvals

\qedsymbol
\qed
\qed*
\qef

#ifOption:blackqed
\blackqed
\blackqedsymbol
#endif

#ifOption:whiteqed
\whiteqed
\whiteqedsymbol
#endif

\newtheoremtype{type}{title style}{comment style}{body style}
\renewtheoremtype{type}{title style}{comment style}{body style}

\liketheorem{title%text}{number}
\liketheorem{title%text}{number}[comment%text]
\liketheorem*{title%text}
\liketheorem*{title%text}[comment%text]
\likeremark{title%text}{number}
\likeremark{title%text}{number}[comment%text]
\likeremark*{title%text}
\likeremark*{title%text}[comment%text]

\newtheorem{envname}{title%text}#N
\newtheorem{envname}[counter]{title%text}#N
\newtheorem{envname}{title%text}[type]#N
\newtheorem{envname}[counter]{title%text}[type]#N
\newtheorem*{envname}{title%text}#N
\newtheorem*{envname}{title%text}[type]#N
\renewtheorem{envname}{title%text}#N
\renewtheorem{envname}[counter]{title%text}#N
\renewtheorem{envname}{title%text}[type]#N
\renewtheorem{envname}[counter]{title%text}[type]#N
\renewtheorem*{envname}{title%text}#N
\renewtheorem*{envname}{title%text}[type]#N

\TheoremBreakStyle
\TheoremNoBreakStyle

\breakafterheader
\nobreakafterheader

\proof %<body%> \qed
\proof[%<of-theorem%>] %<body%> \qed
\begin{proof}
\begin{proof}[of-theorem]
\end{proof}

\apar
\apar[title%text]

\TheoremCommentDelimiters{left}{right}
\AfterTheoremHeaderChar{char}
\AfterTheoremHeaderSkip{skip cmd}
\ProofStyleParameters{style}{title%text}
\AparStyleParameters{style}{prefix}{suffix}