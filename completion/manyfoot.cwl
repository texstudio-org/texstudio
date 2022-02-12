# manyfoot.cwl
# manyfoot package
# neeraavi 27 Mar 2007

#include:nccfoots

#keyvals:\usepackage/manyfoot#c
ruled
para
para*
perpage
#endkeyvals

#ifOption:perpage
#include:perpage
#endif

\extrafootnoterule
\defaultfootnoterule
\newfootnote{suffix}
\newfootnote[style]{suffix}
\DeclareNewFootnote{suffix}
\DeclareNewFootnote[footnote-style]{suffix}[enumeration-style]
\SelectFootnoteRule{rule-name}
\SelectFootnoteRule[priority]{rule-name}[action]
\footnoterulepriority
\SetFootnoteHook{code}
\SplitNote
\ExtraParaSkip{space%l}
