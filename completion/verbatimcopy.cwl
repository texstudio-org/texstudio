# verbatimcopy package
# Matthew Bertucci 10/20/2021 for v0.06

#include:verbatim

#keyvals:\usepackage/verbatimcopy#c
compatibility
enquotefilenames
#endkeyvals

\setOutputDir{directory%definition}
\VerbatimCopy{input file}{output file}#i
\VerbatimCopy{file}{file}#Si

\OldsetOutputDir{directory%definition}#*
\OldVerbatimCopy{input file}{output file}#*i
\OldVerbatimCopy{file}{file}#Si
\VCverbaction{arg1}{arg2}#*
