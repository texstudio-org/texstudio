# bargraph-js package
# Matthew Bertucci 2022/05/10 for v0.8

#include:xkeyval
#include:xcolor
#include:eforms

#keyvals:\usepackage/bargraph-js#c
dynamic
#endkeyvals

\begin{bargraphenv}{bgenv name}
\begin{bargraphenv}[options%keyvals]{bgenv name}
\end{bargraphenv}

#keyvals:\begin{bargraphenv}
width=##L
height=##L
o=#horiz,vert
origin=#0,.5
showaxis#true,false
#endkeyvals

\begin{bargraph}{bg name}
\begin{bargraph}[options%keyvals]{bg name}
\end{bargraph}

#keyvals:\begin{bargraph}
nbars=%<number%>
gap=%<number%>
bardimen=%<number%>
#endkeyvals

\nbars#*
\bargap#*
\bardimen#*
\presetsbarfor{bg name}{bar name}{eforms parameters}
\barfor{bar name}
\presetinputfor{bgenv name}{bg name.bar name}#*
\inputFor{bgenv name}{bg name}{bar name}{width}{height}
\inputFor[eforms parameters]{bgenv name}{bg name}{bar name}{width}{height}
\populateCommaData("%<bgenv name%>","%<bg name%>",%<str,validate%>)
\hs{skip}
\vs{skip}
\barLabelsTU{JS code%definition}
\barLabelsNoTU{JS code%definition}
\isdynamic
\scaleFactorDef{factor}
\displaysfFor{bgenv name}{width}{height}
\displaysfFor[eforms parameters]{bgenv name}{width}{height}
\manualsfFor{bgenv name}{width}{height}
\manualsfFor[eforms parameters]{bgenv name}{width}{height}
\labelFld{text}{bg name.bar name}{width}{height}
\labelFld[eforms parameters]{text}{bg name.bar name}{width}{height}

# not documented
\barDefColor#*
\barforCommon{arg}#*
\barLabelsNoTUJS#*
\barLabelsNoTUJSDef#*
\barNum#*
\bgtoks#*
\cntbars#*
\dybarforCommon{arg}#*
\expbarfor{arg}#*
\getBarName#*
\hmrk#*
\horizontalbarsfalse#*
\horizontalbarstrue#*
\ifhorizontalbars#*
\ifisbgenv#*
\isbgenvfalse#*
\isbgenvtrue#*
\oBgEnvs#*
\priorpresetinputfor{arg1}{arg2}#*
\simpleBarLabels#*
\txtBgValues#*
\usebarlabel#*