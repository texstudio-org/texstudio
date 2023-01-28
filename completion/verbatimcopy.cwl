# verbatimcopy package
# Matthew Bertucci 10/20/2021 for v0.06

#include:verbatim

#keyvals:\usepackage/verbatimcopy#c
compatibility
enquotefilenames
#endkeyvals

\setOutputDir{directory%definition}
\VerbatimCopy{input file%file}{output file%file}#i

\OldsetOutputDir{directory%definition}#S
\OldVerbatimCopy{input file%file}{output file%file}#Si
\VCverbaction{arg1}{arg2}#*
