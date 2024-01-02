# advice package
# Matthew Bertucci 2024/01/01 for v1.1.0

#include:collargs
#include:xparse

\AdviceSetup{namespace}{command or env}{setup code}#*
\AdviceTracingOn#*
\AdviceTracingOff#*
\AdviceNamespace#*
\AdviceName#*
\AdviceCsname#*
\AdviceReplaced#*
\AdviceOriginal#*
\AdviceGetOriginal{namespace}{control sequence}#*
\AdviceCsnameGetOriginal{namespace}{csname}#*
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
