# circledsteps package
# Matthew Bertucci 2023/08/11 for v1.3.3

#include:xcolor
#include:pict2e
#include:picture
#include:pgfkeys
#include:etoolbox

\Circled{text}
\Circled[options%keyvals]{text}
\CircledTop{text}
\CircledTop[options%keyvals]{text}
\CircledText{text}
\CircledText[options%keyvals]{text}

#keyvals:\Circled,\CircledTop,\CircledText,\CircledParamOpts
inner ysep=##L
inner xsep=##L
inner color=#%color
outer color=#%color
fill color=#%color
#endkeyvals

\cstep
\startcstep
\resetcstep
\thecstepcnt

\CircledParamOpts{options%keyvals}{0 or 1}{text}#*
\cstepsversion#S
