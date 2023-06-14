# runcode package
# Matthew Bertucci 2023/06/14 for v1.9

#include:morewrites
#include:tcolorbox
#include:tcolorboxlibrarymany
#include:xcolor
#include:inputenc
#include:textgreek
#include:filecontents
#include:xifthen
#include:xparse
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

\runJulia{source file%file}{output file%file}
\runJulia{source file%file}{output file%file}[run|cache]
\runJulia[server spec]{source file%file}{output file%file}
\runJulia[server spec]{source file%file}{output file%file}[run|cache]

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
