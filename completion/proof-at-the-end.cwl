# proof-at-the-end package
# Matthew Bertucci 2022/08/29 for v2022-08-24

#include:etoolbox
#include:thmtools
#include:thm-restate
#include:catchfile
#include:pgfkeys
#include:hyperref
#include:kvoptions

#keyvals:\usepackage/proof-at-the-end#c
conf={%<configuration%>}
disablePatchSection#true,false
commandRef=%<csname%>
createShortEnv#true,false
#endkeyvals

#ifOption:createShortEnv
\begin{proofE}
\begin{proofE}[options%keyvals]
\end{proofE}
\begin{thmE}
\begin{thmE}[title%text]
\begin{thmE}[title%text][options%keyvals]
\end{thmE}
\begin{lemmaE}
\begin{lemmaE}[title%text]
\begin{lemmaE}[title%text][options%keyvals]
\end{lemmaE}
\begin{theoremE}
\begin{theoremE}[title%text]
\begin{theoremE}[title%text][options%keyvals]
\end{theoremE}
\begin{corollaryE}
\begin{corollaryE}[title%text]
\begin{corollaryE}[title%text][options%keyvals]
\end{corollaryE}
\begin{propositionE}
\begin{propositionE}[title%text]
\begin{propositionE}[title%text][options%keyvals]
\end{propositionE}
\begin{propertyE}
\begin{propertyE}[title%text]
\begin{propertyE}[title%text][options%keyvals]
\end{propertyE}
\begin{factE}
\begin{factE}[title%text]
\begin{factE}[title%text][options%keyvals]
\end{factE}
\begin{proofED}#S
\end{proofED}#S
\begin{thmED}#S
\end{thmED}#S
\begin{lemmaED}#S
\end{lemmaED}#S
\begin{theoremED}#S
\end{theoremED}#S
\begin{corollaryED}#S
\end{corollaryED}#S
\begin{propositionED}#S
\end{propositionED}#S
\begin{propertyED}#S
\end{propertyED}#S
\begin{factED}#S
\end{factED}#S
#endif
#ifOption:createShortEnv=true
\begin{thmE}
\begin{thmE}[title%text]
\begin{thmE}[title%text][options%keyvals]
\end{thmE}
\begin{lemmaE}
\begin{lemmaE}[title%text]
\begin{lemmaE}[title%text][options%keyvals]
\end{lemmaE}
\begin{theoremE}
\begin{theoremE}[title%text]
\begin{theoremE}[title%text][options%keyvals]
\end{theoremE}
\begin{corollaryE}
\begin{corollaryE}[title%text]
\begin{corollaryE}[title%text][options%keyvals]
\end{corollaryE}
\begin{propositionE}
\begin{propositionE}[title%text]
\begin{propositionE}[title%text][options%keyvals]
\end{propositionE}
\begin{propertyE}
\begin{propertyE}[title%text]
\begin{propertyE}[title%text][options%keyvals]
\end{propertyE}
\begin{factE}
\begin{factE}[title%text]
\begin{factE}[title%text][options%keyvals]
\end{factE}
\begin{proofED}#S
\end{proofED}#S
\begin{thmED}#S
\end{thmED}#S
\begin{lemmaED}#S
\end{lemmaED}#S
\begin{theoremED}#S
\end{theoremED}#S
\begin{corollaryED}#S
\end{corollaryED}#S
\begin{propositionED}#S
\end{propositionED}#S
\begin{propertyED}#S
\end{propertyED}#S
\begin{factED}#S
\end{factED}#S
#endif

\begin{textAtEnd}
\begin{textAtEnd}[options%keyvals]
\end{textAtEnd}
\begin{proofEnd}
\begin{proofEnd}[options%keyvals]
\end{proofEnd}
\begin{theoremEnd}{theorem-env}
\begin{theoremEnd}{theorem-env}[title%text]
\begin{theoremEnd}[options%keyvals]{theorem-env}
\begin{theoremEnd}[options%keyvals]{theorem-env}[title%text]
\end{theoremEnd}
\begin{theoremEndRestateBefore}{theorem-env}{name}
\begin{theoremEndRestateBefore}{theorem-env}[title%text]{name}
\end{theoremEndRestateBefore}

\includeExternalAppendix[category]{file}#i
\includeExternalAppendix{file}#i
\newEndProof[options%keyvals]{envname}#N
\newEndProof{envname}#N
\newEndThm[options%keyvals]{envname}{old envname}#N
\newEndThm{envname}{old envname}#N
\pratendAddLabel
\pratendRef{label}#*r
\pratendSectionlikeCref#*
\pratendSetGlobal{options%keyvals}
\pratendSetLocal{options%keyvals}
\printProofs
\printProofs[category]
\textEnd[options%keyvals]{text}
\textEnd{text}

#keyvals:\begin{proofE}#c,\begin{thmE}#c,\begin{lemmaE}#c,\begin{theoremE}#c,\begin{corollaryE}#c,\begin{propositionE}#c,\begin{propertyE}#c,\begin{factE}#c,\begin{theoremEnd}#c,\begin{proofEnd}#c,\begin{textAtEnd}#c,\newEndThm#c,\newEndProof#c,\textEnd#c,\pratendSetGlobal#c,\pratendSetLocal#c
category=%<category%>
proof here
no proof here
proof end
no proof end
restate
no restate
link to proof
no link to proof
opt all end
no opt all end
text link=%<text%>
text proof=%<text%>
restate command=%<csname%>
restated before
both
no both
external appendix
normal
end
all end
proof at the end
debug
no link to theorem
stared
see full proof
one big link
one big link=%<text%>
one big link translated=%<text%>
text link section
text link section full proof
default text link
default text proof
text proof translated=%<text%>
text link external appendix
only external appendix
#endkeyvals

# not documented
\allattheendfalse#S
\allattheendtrue#S
\appendtofile{file}{code}#*
\appendwrite#S
\begin{proofEndDebug}#S
\begin{proofEndOrig}#S
\begin{theoremEndDebug}#S
\begin{theoremEndOrig}#S
\bothfalse#S
\bothtrue#S
\category#*
\currcounterval#S
\end{proofEndDebug}#S
\end{proofEndOrig}#S
\end{theoremEndDebug}#S
\end{theoremEndOrig}#S
\eraseIfNeeded{category}#*
\externalAppendixfalse#S
\externalAppendixtrue#S
\fileContent#*
\ifallattheend#S
\ifboth#S
\ifexternalAppendix#S
\iflinktoproof#S
\ifpratendOptcreateShortEnv#S
\ifpratendOptdisablePatchSection#S
\ifproofend#S
\ifproofhere#S
\ifrestatedbefore#S
\ifrestatethm#S
\linktoprooffalse#S
\linktoprooftrue#S
\makeallother#*
\pratendcountercurrent#*
\pratendcustomrestate#*
\pratendDisableDebugSynctex#*
\pratendEnableDebugSynctex#*
\pratendGeneratePrefixFile{prefix}#*
\pratendLabelProofSection#*
\pratendlastoptions#*
\pratendtextlink#*
\pratendtextproof#*
\prefixPrAtEndFiles#*
\proofendfalse#S
\proofendtrue#S
\proofherefalse#S
\proofheretrue#S
\restatedbeforefalse#S
\restatedbeforetrue#S
\restatethmfalse#S
\restatethmtrue#S
\temprest#S
\thecounterAllProofEnd#*