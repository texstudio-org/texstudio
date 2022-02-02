# runcode package
# Matthew Bertucci 12/30/2021 for v1.1

#include:morewrites
#include:tcolorbox
#include:xcolor
#include:inputenc
#include:textgreek
#include:filecontents
#include:xifthen
#include:xparse
#include:xstring
#include:minted

# from many option of tcolorbox
#include:amsmath
#include:tikz
#include:pdfcol

#keyvals:\usepackage/runcode#c
run
cache
nominted
nohup
R
julia
matlab
stopserver
#endkeyvals

\runExtCode{program}{source file}{output file}
\runExtCode{program}{source file}{output file}[run or cache]

\showCode{lang}{source file}
\showCode{lang}{source file}[first line]
\showCode{lang}{source file}[first line][last line]

\includeOutput{output file}
\includeOutput{output file}[type%keyvals]
#keyvals:\includeOutput
vbox
tex
inline
#endkeyvals

\inln{program}{code%definition}
\inln{program}{code%definition}[type%keyvals]

\runJulia{program}{source file}{output file}
\runJulia[server spec]{program}{source file}{output file}

\inlnJulia{code%definition}
\inlnJulia{code%definition}[type%keyvals]
\inlnJulia[server spec]{code%definition}
\inlnJulia[server spec]{code%definition}[type%keyvals]

\runMatlab{program}{source file}{output file}
\runMatlab[server spec]{program}{source file}{output file}

\inlnMatlab{code%definition}
\inlnMatlab{code%definition}[type%keyvals]
\inlnMatlab[server spec]{code%definition}
\inlnMatlab[server spec]{code%definition}[type%keyvals]

\runR{program}{source file}{output file}
\runR[server spec]{program}{source file}{output file}

\inlnR{code%definition}
\inlnR{code%definition}[type%keyvals]
\inlnR[server spec]{code%definition}
\inlnR[server spec]{code%definition}[type%keyvals]

#keyvals:\inln,\inlnJulia,\inlnMatLab,\inlnR
vbox
inline
#endkeyvals

\begin{codelisting}#*V
\begin{codelisting}[number]#*V
\end{codelisting}#*
\checkZeroBytes{arg}#*
\runcmd#*
\setvalue{cmd}{def}#*d
\thecodeOutput#*
\thecodelisting#*
\tempfile#S
\tmpname#S

\ifruncode#*
\runcodetrue#*
\runcodefalse#*
\ifminted#*
\mintedtrue#*
\mintedfalse#*
\ifnotnohup#*
\notnohuptrue#*
\notnohupfalse#*
