# runcode package
# Matthew Bertucci 2022/07/26 for v1.5

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
python
stopserver
#endkeyvals

\runExtCode{program}{source file}{output file}
\runExtCode{program}{source file}{output file}[run or cache]
\runExtCode{program}{file}{output file}#Si

\showCode{lang}{source file}
\showCode{lang}{source file}[first line]
\showCode{lang}{source file}[first line][last line]
\showCode{lang}{file}#Si

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
\runJulia{program}{file}{output file}#Si
\runJulia[server spec]{program}{file}{output file}#Si

\inlnJulia{code%definition}
\inlnJulia{code%definition}[type%keyvals]
\inlnJulia[server spec]{code%definition}
\inlnJulia[server spec]{code%definition}[type%keyvals]

\runMatlab{program}{source file}{output file}
\runMatlab[server spec]{program}{source file}{output file}
\runMatlab{program}{file}{output file}#Si
\runMatlab[server spec]{program}{file}{output file}#Si

\inlnMatlab{code%definition}
\inlnMatlab{code%definition}[type%keyvals]
\inlnMatlab[server spec]{code%definition}
\inlnMatlab[server spec]{code%definition}[type%keyvals]

\runR{program}{source file}{output file}
\runR[server spec]{program}{source file}{output file}
\runR{program}{file}{output file}#Si
\runR[server spec]{program}{file}{output file}#Si

\inlnR{code%definition}
\inlnR{code%definition}[type%keyvals]
\inlnR[server spec]{code%definition}
\inlnR[server spec]{code%definition}[type%keyvals]

\runPython{program}{source file}{output file}
\runPython{program}{source file}{output file}[run or cache]
\runPython{program}{file}{output file}#Si

\inlnPython{code%definition}
\inlnPython{code%definition}[type%keyvals]
\inlnPython[server spec]{code%definition}
\inlnPython[server spec]{code%definition}[type%keyvals]

\runPythonBatch{code%definition}{output file}

#keyvals:\inln,\inlnJulia,\inlnMatLab,\inlnR,\inlnPython
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
bg#B
\ifruncode#*
\runcodetrue#*
\runcodefalse#*
\ifminted#*
\mintedtrue#*
\mintedfalse#*
\ifnotnohup#*
\notnohuptrue#*
\notnohupfalse#*
