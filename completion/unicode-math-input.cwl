# unicode-math-input package
# Matthew Bertucci 2024/01/18 for v0.1.0

#include:iftex

#keyvals:\usepackage/unicode-math-input#c
ignore-refresh-delimiter-list
ignore-patch-delimiter-commands
ignore-patch-prime
#endkeyvals

\umiMathbf#*
\umiMathit#*
\umiMathbfit#*
\umiMathscr#*
\umiMathbfscr#*
\umiMathfrak#*
\umiMathbb#*
\umiMathbbit#*
\umiMathbffrak#*
\umiMathsf#*
\umiMathsfbf#*
\umiMathsfit#*
\umiMathsfbfit#*
\umiMathtt#*
\umiFrac#*

\umiDeclareMathChar{character}{definition}
\umiDeclareMathDelimiter{character}{definition}

\umiRefreshDelimiterList#*

\umiPatchCmdUnicodeArg{cmd}#*
\umiUnpatchCmdUnicodeArg{cmd}#*
\umiPatchCmdUnicodeTwoArgs{cmd}#*
\umiPatchCmdUnicodeArgExtraGroup{cmd}#*

\umiBraceNext{arg}#*

\umiPatchPrime#*
\umiUnpatchPrime#*

\umiDeclareMathCharCopy{character}{cmd}
\umiDeclareMathDelimiterCopy{character}{cmd}

# not documented
\umiPrime#S
\umiPrimeNormalDefinition#S
\umiBackprime#S
\umiBackprimeNormalDefinition#S

# deprecated
\umiDefineMathChar{character}{definition}#S
\umiDefineMathDelimiter{character}{definition}#S
