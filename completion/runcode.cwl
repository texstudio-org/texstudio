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

\inln{program}{code}
\inln{program}{code}[type%keyvals]

\runJulia{program}{source file}{output file}
\runJulia[server spec]{program}{source file}{output file}

\inlnJulia{code}
\inlnJulia{code}[type%keyvals]
\inlnJulia[server spec]{code}
\inlnJulia[server spec]{code}[type%keyvals]

\runMatlab{program}{source file}{output file}
\runMatlab[server spec]{program}{source file}{output file}

\inlnMatlab{code}
\inlnMatlab{code}[type%keyvals]
\inlnMatlab[server spec]{code}
\inlnMatlab[server spec]{code}[type%keyvals]

\runR{program}{source file}{output file}
\runR[server spec]{program}{source file}{output file}

\inlnR{code}
\inlnR{code}[type%keyvals]
\inlnR[server spec]{code}
\inlnR[server spec]{code}[type%keyvals]

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