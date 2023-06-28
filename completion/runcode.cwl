# runcode package
# Matthew Bertucci 2023/06/23 for v2.0

#include:morewrites
#include:tcolorbox
#include:tcolorboxlibrarymany
#include:xcolor
#include:inputenc
#include:textgreek
#include:xifthen
#include:xstring
#include:minted

#keyvals:\usepackage/runcode#c
run
cache
nominted
minted
listings
fvextra
reducedspace
nohup
R
julia
matlab
python
stopserver
#endkeyvals

#ifOption:listings
#include:listings
#endif

\runExtCode{program}{source file%file}{output file%file}
\runExtCode{program}{source file%file}{output file%file}[run|cache]

\showCode{lang}{source file%file}
\showCode{lang}{source file%file}[first line]
\showCode{lang}{source file%file}[first line][last line]

\includeOutput{output file%file}
\includeOutput{output file%file}[type%keyvals]
#keyvals:\includeOutput
vbox
tex
inline
#endkeyvals

\inln{program}{code%definition}
\inln{program}{code%definition}[vbox|inline]
\inln{program}{code%definition}[output file%file]
\inln{program}{code%definition}[output file%file][vbox|inline]

\runCodeIncOut{program}{source file%file}
\runCodeIncOut{program}{source file%file}[run|cache]
\runCodeIncOut{program}{source file%file}[run|cache][output file%file]
\runCodeIncOut{program}{source file%file}[run|cache][output file%file][type%keyvals]
#keyvals:\runCodeIncOut
vbox
tex
inline
#endkeyvals

\runJulia{source file%file}{output file%file}
\runJulia{source file%file}{output file%file}[run|cache]
\runJulia[server spec]{source file%file}{output file%file}
\runJulia[server spec]{source file%file}{output file%file}[run|cache]

\runJuliaIncOut{source file%file}
\runJuliaIncOut{source file%file}[run|cache]
\runJuliaIncOut{source file%file}[run|cache][output file%file]
\runJuliaIncOut{source file%file}[run|cache][output file%file][type%keyvals]
\runJuliaIncOut[server spec]{source file%file}
\runJuliaIncOut[server spec]{source file%file}[run|cache]
\runJuliaIncOut[server spec]{source file%file}[run|cache][output file%file]
\runJuliaIncOut[server spec]{source file%file}[run|cache][output file%file][type%keyvals]
#keyvals:\runJuliaIncOut
vbox
tex
inline
#endkeyvals

\inlnJulia{code%definition}
\inlnJulia{code%definition}[vbox|inline]
\inlnJulia{code%definition}[output file%file]
\inlnJulia{code%definition}[output file%file][vbox|inline]
\inlnJulia[server spec]{code%definition}
\inlnJulia[server spec]{code%definition}[vbox|inline]
\inlnJulia[server spec]{code%definition}[output file%file]
\inlnJulia[server spec]{code%definition}[output file%file][vbox|inline]

\runMatlab{source file%file}{output file%file}
\runMatlab{source file%file}{output file%file}[run|cache]
\runMatlab[server spec]{source file%file}{output file%file}
\runMatlab[server spec]{source file%file}{output file%file}[run|cache]

\runMatlabIncOut{source file%file}
\runMatlabIncOut{source file%file}[run|cache]
\runMatlabIncOut{source file%file}[run|cache][output file%file]
\runMatlabIncOut{source file%file}[run|cache][output file%file][type%keyvals]
\runMatlabIncOut[server spec]{source file%file}
\runMatlabIncOut[server spec]{source file%file}[run|cache]
\runMatlabIncOut[server spec]{source file%file}[run|cache][output file%file]
\runMatlabIncOut[server spec]{source file%file}[run|cache][output file%file][type%keyvals]
#keyvals:\runMatlabIncOut
vbox
tex
inline
#endkeyvals

\inlnMatlab{code%definition}
\inlnMatlab{code%definition}[vbox|inline]
\inlnMatlab{code%definition}[output file%file]
\inlnMatlab{code%definition}[output file%file][vbox|inline]
\inlnMatlab[server spec]{code%definition}
\inlnMatlab[server spec]{code%definition}[vbox|inline]
\inlnMatlab[server spec]{code%definition}[output file%file]
\inlnMatlab[server spec]{code%definition}[output file%file][vbox|inline]

\runR{source file%file}{output file%file}
\runR{source file%file}{output file%file}[run|cache]
\runR[server spec]{source file%file}{output file%file}
\runR[server spec]{source file%file}{output file%file}[run|cache]

\runRIncOut{source file%file}
\runRIncOut{source file%file}[run|cache]
\runRIncOut{source file%file}[run|cache][output file%file]
\runRIncOut{source file%file}[run|cache][output file%file][type%keyvals]
\runRIncOut[server spec]{source file%file}
\runRIncOut[server spec]{source file%file}[run|cache]
\runRIncOut[server spec]{source file%file}[run|cache][output file%file]
\runRIncOut[server spec]{source file%file}[run|cache][output file%file][type%keyvals]
#keyvals:\runRIncOut
vbox
tex
inline
#endkeyvals

\inlnR{code%definition}
\inlnR{code%definition}[vbox|inline]
\inlnR{code%definition}[output file%file]
\inlnR{code%definition}[output file%file][vbox|inline]
\inlnR[server spec]{code%definition}
\inlnR[server spec]{code%definition}[vbox|inline]
\inlnR[server spec]{code%definition}[output file%file]
\inlnR[server spec]{code%definition}[output file%file][vbox|inline]

\runPython{source file%file}{output file%file}
\runPython{source file%file}{output file%file}[run|cache]
\runPython[server spec]{source file%file}{output file%file}
\runPython[server spec]{source file%file}{output file%file}[run|cache]

\runPythonIncOut{source file%file}
\runPythonIncOut{source file%file}[run|cache]
\runPythonIncOut{source file%file}[run|cache][output file%file]
\runPythonIncOut{source file%file}[run|cache][output file%file][type%keyvals]
\runPythonIncOut[server spec]{source file%file}
\runPythonIncOut[server spec]{source file%file}[run|cache]
\runPythonIncOut[server spec]{source file%file}[run|cache][output file%file]
\runPythonIncOut[server spec]{source file%file}[run|cache][output file%file][type%keyvals]
#keyvals:\runPythonIncOut
vbox
tex
inline
#endkeyvals

\inlnPython{code%definition}
\inlnPython{code%definition}[vbox|inline]
\inlnPython{code%definition}[output file%file]
\inlnPython{code%definition}[output file%file][vbox|inline]
\inlnPython[server spec]{code%definition}
\inlnPython[server spec]{code%definition}[vbox|inline]
\inlnPython[server spec]{code%definition}[output file%file]
\inlnPython[server spec]{code%definition}[output file%file][vbox|inline]

\runPythonBatch{code%definition}{output file%file}

\begin{codelisting}#*V
\begin{codelisting}[number]#*V
\end{codelisting}#*
\checkZeroBytes{arg}#S
\runcmd#S
\setvalue{cmd}{def}#Sd
\thecodeOutput#S
\thecodelisting#S
\generated#S
\tempfile#S
\tmpname#S
bg#B
\ifruncode#S
\runcodetrue#S
\runcodefalse#S
\ifminted#S
\mintedtrue#S
\mintedfalse#S
\ifreducedspace#S
\reducedspacetrue#S
\reducedspacefalse#S
\ifnotnohup#S
\notnohuptrue#S
\notnohupfalse#S
\ifinlnrun#S
\inlnruntrue#S
\inlnrunfalse#S
