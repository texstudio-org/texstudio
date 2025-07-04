# cloze package
# Matthew Bertucci 2025/07/04 for v2.0.0

#include:luatex
#include:setspace
#include:luakeys

#keyvals:\usepackage/cloze#c
align=#left,center,right
boxheight=##L
boxrule=##L
boxwidth=##L
distance=##L
hide
linecolor=#%color
margin=##L
minlines=%<integer%>
spacing=%<number%>
spread=%<number%>
textcolor=#%color
thickness=##L
width=##L
extension_count=%<integer%>
extension_height=##L
extension_width=##L
#endkeyvals

\cloze{text}
\cloze[options%keyvals]{text}
\clozesetfont{font}
\clozefix{text}
\clozefix[options%keyvals]{text}
\clozenol{text}
\clozenol[options%keyvals]{text}
\clozefil{text}
\clozefil[options%keyvals]{text}
\clozeextend[spaces]
\begin{clozepar}
\begin{clozepar}[options%keyvals]
\end{clozepar}
\clozeparplain{text}
\clozeparplain[options%keyvals]{text}
\clozeparcapture
\begin{clozebox}
\begin{clozebox}[options%keyvals]
\begin{clozebox}*
\begin{clozebox}*[options%keyvals]
\end{clozebox}
\begin{clozespace}
\begin{clozespace}[options%keyvals]
\end{clozespace}
\clozeline
\clozeline[options%keyvals]
\clozelinefil
\clozelinefil[options%keyvals]
\clozestrike{wrong text%text}{correct text%text}
\clozestrike[options%keyvals]{wrong text%text}{correct text%text}
\clozeset{options%keyvals}
\clozereset
\clozeshow
\clozehide

#keyvals:\cloze,\clozefix,\clozenol,\clozefil,\begin{clozepar},\clozeparplain,\begin{clozebox},\begin{clozebox}*,\begin{clozespace},\clozeline,\clozelinefil,\clozestrike,\clozeset
show
hide
distance=##L
linecolor=#%color
textcolor=#%color
thickness=##L
#endkeyvals

#keyvals:\clozefix,\clozeset
align=#left,center,right
#endkeyvals

#keyvals:\clozefix,\clozeline,\clozeset
width=##L
#endkeyvals

#keyvals:\begin{clozepar},\clozeparplain,\clozeset
minlines=%<integer%>
#endkeyvals

#keyvals:\begin{clozebox},\begin{clozebox}*,\clozeset
boxheight=##L
boxrule=##L
boxwidth=##L
#endkeyvals

#keyvals:\cloze,\clozefix,\clozenol,\clozefil,\clozeset
margin=##L
#endkeyvals

#keyvals:\begin{clozespace},\clozeset
spacing=%<number%>
#endkeyvals

#keyvals:\cloze,\clozenol,\clozeset
spread=%<number%>
#endkeyvals

\clozefont#*

\Cloze{arg1}{arg2}{arg3}#S
\ClozeExtend{arg}#S
\ClozeFil{arg1}{arg2}#S
\ClozeLine{arg}#S
\ClozeLinefil{arg}#S
\ClozeGetOption{arg}#S
\ClozeStartMarker{arg1}{arg2}#S
\ClozeStopMarker{arg}#S
\ClozeStrike{arg1}{arg2}{arg3}#S
\ClozeMargin{arg}#S
\ClozePar{arg1}{arg2}#S
\ClozeWrapWithFont{arg}#S
\ClozeBox#S
