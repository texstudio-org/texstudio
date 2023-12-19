# fitch package
# Matthew Bertucci 2023/12/19 for v1.0

#include:kvoptions

#keyvals:\usepackage/fitch#c,\setkeys/fitch#c,\begin{nd},\begin{fitchproof},\begin{ndresume},\begin{fitchproof*}
rules=%<csname%>
arrayenv=%<envname%>
justformat=%<csname%>
refformat=%<csname%>
height=##L
topheight=##L
depth=##L
labelsep=##L
indent=##L
hsep=##L
justsep=##L
linethickness=##L
cindent=##L
outerline#true,false
#endkeyvals

\begin{nd}#m
\begin{nd}[options%keyvals]#m
\end{nd}#m
\begin{fitchproof}#\math
\begin{fitchproof}[options%keyvals]#\math
\end{fitchproof}
\hypo{label}{formula%plain}
\hypo[symbol]{label}{formula%plain}
\hypo[symbol][offset]{label}{formula%plain}
\have{label}{formula%plain}
\have[symbol]{label}{formula%plain}
\have[symbol][offset]{label}{formula%plain}
\open
\open[guard]
\close
\close[guard]
\r{ref list}
\ii{ref list}
\ie{ref list}
\ai{ref list}
\ae{ref list}
\oi{ref list}
\oe{ref list}
\ni{ref list}
\ne{ref list}
\be{ref list}
\nne{ref list}
\Ai{ref list}
\Ae{ref list}
\Ei{ref list}
\Ee{ref list}
\guard{guard}
\guard[n]{guard}
\by{text}{ref list}
\ndref{ref list}
\begin{ndresume}#m
\begin{ndresume}[options%keyvals]#m
\end{ndresume}#m
\begin{fitchproof*}#\math
\begin{fitchproof*}[options%keyvals]#\math
\end{fitchproof*}
\hypocont{formula%plain}
\havecont{formula%plain}
\ndrules#*
\ndjustformat#*
\ndrefformat#*

# deprecated
\nddim{height}{topheight}{depth}{labelsep}{indent}{hsep}{justsep}{linethickness}#S
