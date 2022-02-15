# verbatimcopy package
# Matthew Bertucci 10/20/2021 for v0.06

#include:verbatim

#keyvals:\usepackage/verbatimcopy#c
compatibility
enquotefilenames
#endkeyvals

\setOutputDir{directory}
\VerbatimCopy{input file}{output file}

\OldsetOutputDir{directory}#*
\OldVerbatimCopy{input file}{output file}#*
\VCverbaction{arg1}{arg2}#*
