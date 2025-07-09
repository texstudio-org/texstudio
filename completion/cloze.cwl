# cloze package
# Matthew Bertucci 2025/07/09 for v2.0.0

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
line_color=#%color
text_color=#%color
thickness=##L
debug
font=%<font commands%>
visibility#true,false
#endkeyvals

#keyvals:\clozefix,\clozeset
align=#left,center,right
#endkeyvals

#keyvals:\clozefix,\clozeline,\clozeset
width=##L
#endkeyvals

#keyvals:\begin{clozepar},\clozeparplain,\clozeset
min_lines=%<integer%>
#endkeyvals

#keyvals:\begin{clozebox},\begin{clozebox}*,\clozeset
box_height=##L
box_rule=##L
box_width=##L
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

#keyvals:\clozeset
extend_count=%<integer%>
extend_height=##L
extend_width=##L
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
