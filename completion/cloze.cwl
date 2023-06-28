# cloze package
# Matthew Bertucci 11/26/2021 for v1.6

#include:luatex
#include:fontspec
#include:luatexbase
#include:kvoptions
#include:setspace
#include:xcolor
#include:stackengine
#include:ulem
#include:transparent

#keyvals:\usepackage/cloze#c
align=#left,center,right
boxheight=##L
boxwidth=##L
distance=##L
hide
linecolor=#%color
margin=##L
spacing=%<number%>
textcolor=#%color
thickness=##L
width=##L
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
\clozeparcmd{text}
\clozeparcmd[options%keyvals]{text}
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

#keyvals:\cloze,\clozefix,\clozenol,\clozefil,\begin{clozepar},\clozeparcmd,\begin{clozebox},\begin{clozebox}*,\begin{clozespace},\clozeline,\clozelinefil,\clozestrike,\clozeset,\ClozeSetLocalOptions
show
hide
distance=##L
linecolor=#%color
textcolor=#%color
thickness=##L
#endkeyvals

#keyvals:\clozefix,\clozeset
align=#left,center,right
width=##L
#endkeyvals

#keyvals:\begin{clozebox},\begin{clozebox}*,\clozeset
boxheight=##L
boxwidth=##L
#endkeyvals

#keyvals:\cloze,\clozefix,\clozefil,\clozeset
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
