# phfthm package
# Matthew Bertucci 10/6/2021 for v1.0

#include:etoolbox
#include:aliascnt
#include:amsmath
#include:amsthm

#ifOption:thmset=shortnames
\begin{thm}
\end{thm}
\begin{prop}
\end{prop}
\begin{lem}
\end{lem}
\begin{cor}
\end{cor}
\begin{conj}
\end{conj}
\begin{rem}
\end{rem}
\begin{thm*}
\end{thm*}
\begin{prop*}
\end{prop*}
\begin{lem*}
\end{lem*}
\begin{cor*}
\end{cor*}
\begin{conj*}
\end{conj*}
\begin{rem*}
\end{rem*}
#endif

\begin{theorem}
\end{theorem}
\begin{proposition}
\end{proposition}
\begin{lemma}
\end{lemma}
\begin{corollary}
\end{corollary}
\begin{definition}
\end{definition}
\begin{conjecture}
\end{conjecture}
\begin{remark}
\end{remark}
\begin{proposition}
\end{proposition}
\begin{idea}
\end{idea}
\begin{question}
\end{question}
\begin{problem}
\end{problem}
\begin{theorem*}
\end{theorem*}
\begin{proposition*}
\end{proposition*}
\begin{lemma*}
\end{lemma*}
\begin{corollary*}
\end{corollary*}
\begin{definition*}
\end{definition*}
\begin{conjecture*}
\end{conjecture*}
\begin{remark*}
\end{remark*}
\begin{proposition*}
\end{proposition*}
\begin{idea*}
\end{idea*}
\begin{question*}
\end{question*}
\begin{problem*}
\end{problem*}

\begin{thmheading}{title%text}
\end{thmheading}

\phfMakeTheorem{envname}{theorem name}#N
\phfMakeTheorem[options%keyvals]{envname}{theorem name}#N

#keyvals:\phfMakeTheorem
counter=
aliascounter#true,false
thmstyle=
defnostar#true,false
defstar#true,false
proofref#true,false
proofrefstyle=#default,margin,longref
#endkeyvals

\phfLoadThmSet{thm options}{def options}{thmset name%keyvals}

#keyvals:\phfLoadThmSet
empty
simple
default
shortnames
rich
#endkeyvals

\theoremname#*
\propositionname#*
\lemmaname#*
\corollaryname#*
\conjecturename#*
\remarkname#*
\definitionname#*
\ideaname#*
\questionname#*
\problemname#*
\proofname#*
\proofofname#*

\phfMakeProofEnv{envname}#N
\phfMakeProofEnv[options%keyvals]{envname}#N

#keyvals:\phfMakeProofEnv
displayenv=
defaultproofname=
parselabel#true,false
parselabelcmd=
override#true,false
internalcounter=
proofofname=
#endkeyvals

\phfPinProofAnchor#*

\noproofref

\phfMakeThmheadingEnvironment{envname}#N
\phfMakeThmheadingEnvironment[options%keyvals]{envname}#N

#keyvals:\phfMakeThmheadingEnvironment
thmstyle=
internalcounter=
#endkeyvals