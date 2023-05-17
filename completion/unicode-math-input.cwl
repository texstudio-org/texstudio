# unicode-math-input package
# Matthew Bertucci 2023/05/12 for v0.0.0

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

\umiDefineMathChar{character}{definition}
\umiDefineMathDelimiter{character}{definition}

\umiRefreshDelimiterList#*

\umiPatchCmdUnicodeArg{cmd}#*
\umiUnpatchCmdUnicodeArg{cmd}#*
\umiPatchCmdUnicodeTwoArgs{cmd}#*
\umiPatchCmdUnicodeArgExtraGroup{cmd}#*

\umiBraceNext{arg}#*

\umiPatchPrime#*
\umiUnpatchPrime#*

# not documented
\umiPrime#S
\umiPrimeNormalDefinition#S
\umiBackprime#S
\umiBackprimeNormalDefinition#S