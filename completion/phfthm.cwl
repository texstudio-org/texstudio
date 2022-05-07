# phfthm package
# Matthew Bertucci 2022/05/07 for v1.2

#include:xkeyval
#include:etoolbox
#include:aliascnt
#include:amsmath
#include:amsthm
#include:amssymb

#keyvals:\usepackage/phfthm#c
thmset=#simple,default,shortnames,rich
theoremstyle=%<theorem style%>
definitionstyle=%<theorem style%>
sepcounters#true,false
parentcounter=%<counter%>
proofref={%<attributes%>}
proofenv#true,false
smallproofs#true,false
qedsymbolblacksquare#true,false
prooftitleitbf#true,false
thmheading#true,false
thmheadingstyle=%<theorem style%>
#endkeyvals

#ifOption:thmset=shortnames
\begin{thm}
\begin{thm}[heading%text]
\end{thm}
\begin{prop}
\begin{prop}[heading%text]
\end{prop}
\begin{lem}
\begin{lem}[heading%text]
\end{lem}
\begin{cor}
\begin{cor}[heading%text]
\end{cor}
\begin{conj}
\begin{conj}[heading%text]
\end{conj}
\begin{rem}
\begin{rem}[heading%text]
\end{rem}
\begin{defn}
\begin{defn}[heading%text]
\end{defn}
\begin{thm*}
\begin{thm*}[heading%text]
\end{thm*}
\begin{prop*}
\begin{prop*}[heading%text]
\end{prop*}
\begin{lem*}
\begin{lem*}[heading%text]
\end{lem*}
\begin{cor*}
\begin{cor*}[heading%text]
\end{cor*}
\begin{conj*}
\begin{conj*}[heading%text]
\end{conj*}
\begin{rem*}
\begin{rem*}[heading%text]
\end{rem*}
\begin{defn*}
\begin{defn*}[heading%text]
\end{defn*}
#endif

\begin{theorem}
\begin{theorem}[heading%text]
\end{theorem}
\begin{proposition}
\begin{proposition}[heading%text]
\end{proposition}
\begin{lemma}
\begin{lemma}[heading%text]
\end{lemma}
\begin{corollary}
\begin{corollary}[heading%text]
\end{corollary}
\begin{definition}
\begin{definition}[heading%text]
\end{definition}
\begin{conjecture}
\begin{conjecture}[heading%text]
\end{conjecture}
\begin{remark}
\begin{remark}[heading%text]
\end{remark}
\begin{proposition}
\begin{proposition}[heading%text]
\end{proposition}
\begin{idea}
\begin{idea}[heading%text]
\end{idea}
\begin{question}
\begin{question}[heading%text]
\end{question}
\begin{problem}
\begin{problem}[heading%text]
\end{problem}
\begin{theorem*}
\begin{theorem*}[heading%text]
\end{theorem*}
\begin{proposition*}
\begin{proposition*}[heading%text]
\end{proposition*}
\begin{lemma*}
\begin{lemma*}[heading%text]
\end{lemma*}
\begin{corollary*}
\begin{corollary*}[heading%text]
\end{corollary*}
\begin{definition*}
\begin{definition*}[heading%text]
\end{definition*}
\begin{conjecture*}
\begin{conjecture*}[heading%text]
\end{conjecture*}
\begin{remark*}
\begin{remark*}[heading%text]
\end{remark*}
\begin{proposition*}
\begin{proposition*}[heading%text]
\end{proposition*}
\begin{idea*}
\begin{idea*}[heading%text]
\end{idea*}
\begin{question*}
\begin{question*}[heading%text]
\end{question*}
\begin{problem*}
\begin{problem*}[heading%text]
\end{problem*}

\begin{thmheading}{title%text}
\end{thmheading}

\phfMakeTheorem{envname}{theorem name}#N
\phfMakeTheorem[options%keyvals]{envname}{theorem name}#N

#keyvals:\phfMakeTheorem
counter=%<counter%>
aliascounter#true,false
thmstyle=%<theorem style%>
defnostar#true,false
defstar#true,false
proofref#true,false
proofrefstyle=#default,margin,marginbottom,longref
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
\claimname#*
\observationname#*
\problemname#*
\proofname#*
\proofofname#*

\phfMakeProofEnv{envname}#N
\phfMakeProofEnv[options%keyvals]{envname}#N

#keyvals:\phfMakeProofEnv
displayenv=%<envname%>
defaultproofname=%<title%>
parselabel#true,false
parselabelcmd=%<macro%>
override#true,false
internalcounter=%<counter%>
proofofname=%<macro%>
#endkeyvals

\phfPinProofAnchor#*

\noproofref

\phfMakeThmheadingEnvironment{envname}#N
\phfMakeThmheadingEnvironment[options%keyvals]{envname}#N

#keyvals:\phfMakeThmheadingEnvironment
thmstyle=%<theorem style%>
internalcounter=%<counter%>
#endkeyvals

\proofrefsize#*
\filledsquare#*
\phfProofrefPageAheadTolerance#*
\phfProofrefPageBackTolerance#*
\phfthmLoadThmSet{thm options}{def options}{thmset name}#S
\phfthmMakeThmheadingEnvironment{envname}#SN
\phfthmMakeThmheadingEnvironment[options]{envname}#SN
\phfthmPinProofAnchor#S
\proofonname{label name}{page ref}#*
\thephfthmheadingcounter#*
\thephfthmInternalProofrefCounter#*
