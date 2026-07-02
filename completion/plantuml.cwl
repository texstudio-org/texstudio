# plantuml package
# Matthew Bertucci 2026/07/01 for v0.7.0

#include:adjustbox
#include:capt-of
#include:fancyvrb
#include:iftex
#include:ifthen
#include:l3keys2e
#include:luacode
#include:pdftexcmds
#include:tikz

#keyvals:\usepackage/plantuml#c
output=%<type%>
server=%<URL%>
#endkeyvals

\begin{plantuml}#\pictureHighlight
\end{plantuml}
\begin{plantumlpreamble}#\pictureHighlight
\end{plantumlpreamble}

\plantumlinput{file}
\plantumlinput[options%keyvals]{file}
\plantumlset{options%keyvals}

#keyvals:\plantumlinput,\plantumlset
caption=%<text%>
label=##l
float
float=%<spec%>
#endkeyvals

\plantumlpreamblefile{file}

\PlantUmlTikzFont#*

# not documented
\CurrentDirectory#S
\maxwidth{width}#S
\plantumlEmit#S
\PlantUmlEnvReset#S
\PlantUmlHash#S
\PlantUmlIODir#S
\PlantUMLJobname#S
\PlantUmlMode#S
\plantumlParseOpts{arg}#S
\PlantUmlPreambleIO#S
\PlantUmlPreambleMd5#S
\PlantUmlPreambleName#S
\PlantUmlProbeStream#S
\plantumlResetOpts#S
\PlantUmlServer#S
\PlantumlStripTrailingSlash#S
\thePlantUmlFigureNumber#S
\thePlantUmlFigureNumberSVG#S
\UMLcountUp#S
