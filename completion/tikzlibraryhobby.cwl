# hobby tikzlibrary
# 2022/12/06 for v1.8

# tikzlibraryhobby.code.tex
# └─ pgflibraryhobby.code.tex
#    └─ hobby.code.tex

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\path#c,\draw#c,\fill#c,\filldraw#c,\pattern#c,\shade#c,\shadedraw#c,\clip#c
use Hobby shortcut
use quick Hobby shortcut
#endkeyvals
 
#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c
hobby
closed hobby
quick hobby
#endkeyvals

\curvethrough{spec}#*
\curvethrough[options]{spec}#*

# from hobby pgflibrary
\pgfpathhobby#*
\pgfpathhobby{options}#*
\pgfpathhobbypt{pgf point spec}#*
\pgfpathhobbypt{pgf point spec}{options}#*
\pgfpathhobbyptparams{options}#*
\pgfpathhobbyend#*
\pgfplothanderhobby#*
\pgfplothandlerclosedhobby#*
\pgfplothandlerquickhobby#*

# from hobby.code.tex
\hobbyVersion#S
\hobbyDate#S
\hobbyinit{moveto}{curveto}{close}#*
\hobbyaddpoint{options}#*
\hobbysetparams{options}#*
\hobbygenpath#*
\hobbygenifnecpath{name}#*
hobbygenifnecusepath{name}#*
\hobbyusepath{options}#*
\hobbysavepath{name}#*
\hobbyrestorepath{name}#*
\hobbyshowpath{name}#*
\hobbygenusepath#*
\hobbyclearpath#*