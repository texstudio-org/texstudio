# rmathbr package
# Matthew Bertucci 2/2/2022 for v1.1.1

#include:ifetex
#include:ifluatex
#include:xkeyval

#keyvals:\usepackage/rmathbr#c
scripts=#noactive,mathactive,active
run=#atload,atbegindocument,auto
cdottimes#true,false
brokencolon#true,false
brokenminus#true,false
brokenbin#true,false
#endkeyvals

\*#m
\cdott#m

\nobr
\SetBreakableRel{command}
\SetBreakableBin{command}
\SetBreakableInner{command}
\SetOpenBracket{command}
\SetMathOperator{command}
\SetPunctuation{command}
\UnsetBrokenCmd{command}
\BrokenBinOff
\BrokenBinOn

\brokenbin{arg}#*
\brokeninner{arg}#*
\brokenrel{arg}#*
\xDeclareBoolOptionX{key%plain}{func}#*
\xDeclareChoiceOptionX{key%plain}[bin]{al}[dft]{func}#*