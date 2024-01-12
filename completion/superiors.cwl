# superiors package
# Matthew Bertucci 2024/01/12 for v2.0

#include:xkeyval
#include:xcolor
#include:iftex
#include:etoolbox
#include:ifthen
#include:trace

#keyvals:\usepackage/superiors#c
notitlepatch#true,false
supscale=%<factor%>
supscolor=#%color
supsraised=##L
supsfam=%<family%>
supsotf=%<.otf file%>
supsLspaced=##L
supsRspaced=##L
supspaced=##L
#endkeyvals

\textfnscript{text}
\textSuperscript{text}

# not documented
\supsStyle#S
