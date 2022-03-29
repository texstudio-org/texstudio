# llncs class
# Matthew Bertucci 3/27/2022 for v2.21

#include:aliascnt
#include:multicol

#keyvals:\documentclass/llncs#c
citeauthoryear
runningheads
# options passed to article class
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
onecolumn
twocolumn
leqno
fleqn
#endkeyvals

\authorrunning{abbreviated author list}
\email{email address%URL}#U
\fnmsep
\inst{number}
\institute{institutes%text}
\keywords{keywords%text}
\orcidID{ORCID identifier}
\subtitle{text}
\titlerunning{abbreviated title%text}
\url{URL}#U

\grole#m
\getsto#m
\lid#m
\gid#m
\bbbc#m
\bbbf#m
\bbbh#m
\bbbk#m
\bbbm#m
\bbbn#m
\bbbp#m
\bbbq#m
\bbbr#m
\bbbs#m
\bbbt#m
\bbbz#m
\bbbone#m

\begin{theorem}
\end{theorem}
\begin{claim}
\end{claim}
\begin{proof}
\end{proof}
\begin{case}
\end{case}
\begin{conjecture}
\end{conjecture}
\begin{corollary}
\end{corollary}
\begin{definition}
\end{definition}
\begin{example}
\end{example}
\begin{exercise}
\end{exercise}
\begin{lemma}
\end{lemma}
\begin{note}
\end{note}
\begin{problem}
\end{problem}
\begin{property}
\end{property}
\begin{proposition}
\end{proposition}
\begin{question}
\end{question}
\begin{solution}
\end{solution}
\begin{remark}
\end{remark}

\qed
\spnewtheorem{envname}{caption}{cap font}{body font}#N
\spnewtheorem{envname}[numbered like]{caption}{cap font}{body font}#N
\spnewtheorem*{envname}{caption}{cap font}{body font}#N

#keyvals:\bibliographystyle#c
splncs04
#endkeyvals

\doi{DOI}

# not documented
\ackname#*
\addcontentsmark{file}{type}{text}#*
\addcontentsmarkwop{file}{type}{text}#*
\addnumcontentsmark{file}{type}{text}#*
\addtocmark[num]{file}{type}{text}#*
\addtocmark{file}{type}{text}#*
\andname#*
\authcount{arg}#*
\authrun#*
\backmatter#*
\calctocindent#*
\chapter*{title}#*L1
\chapter[short title]{title}#*L1
\chapter{title}#*L1
\chaptermark{code}#*
\chaptername#*
\claimname#*
\clearheadinfo#*
\conjecturename#*
\contriblistname#*
\corollaryname#*
\definitionname#*
\examplename#*
\exercisename#*
\fnindent#*
\fnnstart#*
\frontmatter#*
\headlineindent#*
\homedir#*
\hyperhrefextend#*
\idxquad#*
\instindent#*
\institutename#*
\keywordname#*
\lastand#*
\lastandname#*
\lemmaname#*
\mailname#*
\mainmatter#*
\noteaddname#*
\notename#*
\phantomsection#*
\problemname#*
\proofname#*
\propertyname#*
\propositionname#*
\questionname#*
\remarkname#*
\seename#*
\solutionname#*
\squareforqed#*
\subclassname#*
\theauco#*
\thechapter#*
\theopargself#*
\theoremname#*
\thisbottomragged#*
\titrun#*
\tocauthor{name}#*
\tocchpnum#*
\tocparanum#*
\tocparatotal#*
\tocsecnum#*
\tocsectotal#*
\tocsubparanum#*
\tocsubsecnum#*
\tocsubsectotal#*
\tocsubsubsecnum#*
\tocsubsubsectotal#*
\toctitle{text}#*
\ts#*

#ifOption:citeauthoryear
\citeauthoryear#*
#endif

#ifOption:oribibl
\oribibl#*
#endif