# seqcalc package
# Matthew Bertucci 2026/02/02 for v1.0

#include:bussproofs

#keyvals:\usepackage/seqcalc#c
normalize-formulas#true,false
debug#true,false
shortcuts#true,false
standard-rules#true,false
#endkeyvals

\begin{seqproofinline}
\end{seqproofinline}
\begin{seqproof}
\end{seqproof}

\seq{arg1}{arg2}
\seqL{arg}
\seqR{arg}
\SeqAxiom{arg}
\SeqPremise{arg}
\SeqConclusion{command}{formula}
\SeqConclusion{command}{formula}[hint%formula]
\SeqConclusion[label%formula]{command}{formula}
\SeqConclusion[label%formula]{command}{formula}[hint%formula]
\SeqConclusionU{formula}
\SeqConclusionU{formula}[hint%formula]
\SeqConclusionU[label%formula]{formula}
\SeqConclusionU[label%formula]{formula}[hint%formula]
\SeqConclusionB{formula}
\SeqConclusionB{formula}[hint%formula]
\SeqConclusionB[label%formula]{formula}
\SeqConclusionB[label%formula]{formula}[hint%formula]
\EnableSeqShortcuts
\SeqCalcDeclareRule{name}{premises}
\SeqCalcDeclareRule{name}{premises}[label]
\SeqRule{name}{formula}
\SeqRule{name}{formula}[hint]
\EnableSeqStandardRules

\SeqAx{arg}#*
\SeqPr{arg}#*
\Cc{command}{formula}#*
\Cc{command}{formula}[hint%formula]#*
\Cc[label%formula]{command}{formula}#*
\Cc[label%formula]{command}{formula}[hint%formula]#*
\CU{formula}#*
\CU{formula}[hint%formula]#*
\CU[label%formula]{formula}#*
\CU[label%formula]{formula}[hint%formula]#*
\CB{formula}#*
\CB{formula}[hint%formula]#*
\CB[label%formula]{formula}#*
\CB[label%formula]{formula}[hint%formula]#*

# not documented
\SeqCalcDeclareShortcut{command}{old command}#Sd