# cloze package
# Matthew Bertucci 2025/06/07 for v1.7.0

#include:luatex
#include:setspace
#include:xcolor
#include:stackengine
#include:ulem
#include:transparent
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
\clozesetoption{option}{value}
\clozeset{options%keyvals}
\clozereset
\clozeshow
\clozehide

#keyvals:\cloze,\clozefix,\clozenol,\clozefil,\begin{clozepar},\begin{clozebox},\begin{clozebox}*,\begin{clozespace},\clozeline,\clozelinefil,\clozestrike,\clozeset,\ClozeSetLocalOptions
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

#keyvals:\begin{clozepar},\clozeset
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

\ifclozeshow#*
\clozeshowtrue#*
\clozeshowfalse#*
\ClozeSetToGlobal#*
\ClozeSetToLocal#*
\ClozeGetOption{arg}#*
\ClozeColor{color}#*
\ClozeStartMarker{arg}#*
\ClozeStopMarker{arg}#*
\ClozeMargin{arg}#*
\clozefont#*
\ClozeSetLocalOptions{options%keyvals}#*
\ClozeTextColor{color}#*
\ClozeStrikeLine#*
\ClozeBox#*
