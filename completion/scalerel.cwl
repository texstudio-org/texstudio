# scalerel package
# Matthew Bertucci 9/21/2021 for v1.8

#include:calc
#include:graphicx
#include:etoolbox

\scalerel{object}{reference}
\scalerel[max width]{object}{reference}
\scalerel*{object}{reference}
\scalerel*[max width]{object}{reference}
\stretchrel{object}{reference}
\stretchrel[narrowest aspect]{object}{reference}
\stretchrel*{object}{reference}
\stretchrel*[narrowest aspect]{object}{reference}
\scaleto{object}{height}
\scaleto[max width]{object}{height}
\stretchto{object}{height}
\stretchto[narrowest aspect]{object}{height}
\scaleleftright{left obj}{reference}{right obj}
\scaleleftright[max width]{left obj}{reference}{right obj}
\stretchleftright{left obj}{reference}{right obj}
\stretchleftright[narrowest aspect]{left obj}{reference}{right obj}
\hstretch{scale}{object}
\vstretch{scale}{object}
\scaleobj{scale}{object}

\ThisStyle#*
\SavedStyle#*
\LMex#*
\LMpt#*
\scriptstyleScaleFactor#*
\scriptscriptstyleScaleFactor#*
\Isnextbyte[optional q]{test byte}{string}#*
\theresult#*
\ignoremathstyle#*
\discernmathstyle#*
