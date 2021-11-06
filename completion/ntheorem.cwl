# ntheorem package
# Matthew Bertucci 11/5/2021 for v1.33

#include:ifthen
#include:amssymb

\renewtheorem{envname}[numbered like]{caption}#N
\renewtheorem{envname}{caption}#N
\renewtheorem{envname}{caption}[within]#N

\theoremstyle{style%keyvals}
#keyvals:\theoremstyle#c
plain
break
change
changebreak
margin
marginbreak
nonumberplain
nonumberbreak
empty
#endkeyvals

\theoremheaderfont{font cmds}
\theorembodyfont{font cmds}
\theoremnumbering{style%keyvals}
#keyvals:\theoremnumbering
arabic
alph
Alph
roman
Roman
greek
Greek
fnsymbol
#endkeyvals
\theoremseparator{symbol}
\theorempreskip{skip%l}
\theorempostskip{skip%l}
\theoremindent%<<dimen>%>
#ifOption:thmmarks
\theoremsymbol{symbol}
#endif
\theoremprework{code}
\theorempostwork{code}
\theoremclass{theorem type}

\theorempreskipamount{skip%l}
\theorempostskipamount{skip%l}

#ifOption:standard
\begin{Theorem}
\begin{Theorem}[name]
\end{Theorem}
\begin{Lemma}
\begin{Lemma}[name]
\end{Lemma}
\begin{Proposition}
\begin{Proposition}[name]
\end{Proposition}
\begin{Corollary}
\begin{Corollary}[name]
\end{Corollary}
\begin{Satz}
\begin{Satz}[name]
\end{Satz}
\begin{Korollar}
\begin{Korollar}[name]
\end{Korollar}
\begin{Definition}
\begin{Definition}[name]
\end{Definition}
\begin{Example}
\begin{Example}[name]
\end{Example}
\begin{Beispiel}
\begin{Beispiel}[name]
\end{Beispiel}
\begin{Anmerkung}
\begin{Anmerkung}[name]
\end{Anmerkung}
\begin{Bemerkung}
\begin{Bemerkung}[name]
\end{Bemerkung}
\begin{Remark}
\begin{Remark}[name]
\end{Remark}
\begin{Proof}
\begin{Proof}[name]
\end{Proof}
\begin{Beweis}
\begin{Beweis}[name]
\end{Beweis}
\TheoremSymbol#*
\LemmaSymbol#*
\PropositionSymbol#*
\CorollarySymbol#*
\SatzSymbol#*
\KorollarSymbol#*
\DefinitionSymbol#*
\ExampleSymbol#*
\BeispielSymbol#*
\AnmerkungSymbol#*
\BemerkungSymbol#*
\RemarkSymbol#*
\ProofSymbol#*
\BeweisSymbol#*
\Theoremname#*
\Lemmaname#*
\Propositionname#*
\Corollaryname#*
\Satzname#*
\Korollarname#*
\Definitionname#*
\Examplename#*
\Beispielname#*
\Anmerkungname#*
\Bemerkungname#*
\Remarkname#*
\Proofname#*
\Beweisname#*
#endif

\newframedtheorem{envname}[numbered like]{caption}#N
\newframedtheorem{envname}{caption}#N
\newframedtheorem{envname}{caption}[within]#N
\newshadedtheorem{envname}[numbered like]{caption}#N
\newshadedtheorem{envname}{caption}#N
\newshadedtheorem{envname}{caption}[within]#N
\shadecolor{color}
\theoremframecommand#*
\theoremframepreskip{skip}
\theoremframepostskip{skip}
\theoreminframepreskip{skip}
\theoreminframepostskip{skip}

\listtheorems{thmset1,thmset2,...}

\theoremlisttype{type%keyvals}
#keyvals:\theoremlisttype
all
allname
opt
optname
#endkeyvals

\addtheoremline{name}{text}
\addtheoremline*{name}{text}

\addtotheoremfile{text}
\addtotheoremfile[name]{text}

\newtheoremstyle{name}{head}{opt-head}
\renewtheoremstyle{name}{head}{opt-head}

\newtheoremlisttype{name}{start}{line}{end}
\renewtheoremlisttype{name}{start}{line}{end}

\qed
\qedsymbol{symbol}
\NoEndMark

#ifOption:thref
\label{label}[type]#l
\thref{label}#r
#endif

\PotEndMark#S
\SetEndMark#S
\OrganizeTheoremSymbol#S
\TagsPlusEndmarks#S
\SetOnlyEndMark#S
\SetTagPlusEndMark#S
\RestoreTags#S
\theoremkeyword#S
\theoremlistall#S
\theoremlistallname#S
\theoremlistoptional#S
\theoremlistoptname#S
\theoremlistdo#S