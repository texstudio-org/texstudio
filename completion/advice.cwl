# advice package
# Matthew Bertucci 2023/10/11 for v1.0.0

#include:collargs

\AdviceSetup{namespace}{command or env}{setup code}#*
\AdviceTracingOn#*
\AdviceTracingOff#*
\AdviceNamespace#*
\AdviceName#*
\AdviceReplaced#*
\AdviceOriginal#*
\AdviceGetOriginal{namespace}{control sequence}#*
\AdviceCollectTikZArguments#*

\ifAdviceRun#S
\AdviceRuntrue#S
\AdviceRunfalse#S
\AdviceRunConditions#S
\AdviceBailoutHandler#S
\AdviceOuterHandler#S
\AdviceCollector#S
\AdviceArgs#S
\AdviceCollectorOptions#S
\AdviceRawCollectorOptions#S
\AdviceInnerHandler#S
\AdviceOptions#S
\AdviceAfterSetup#S
\AdviceType#S