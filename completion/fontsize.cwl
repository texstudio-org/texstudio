# fontsize package
# Matthew Bertucci 12/13/2021 for v0.8.5

#include:xkeyval

#keyvals:\usepackage/fontsize#c
fontsize=##L
parindent=##L
cloname=%<name%>
#endkeyvals

\changefontsize{fontsize}
\changefontsize[baselineskip]{fontsize}

\generateclofile{name}{fontsize}#*
\generateclofile{name}[baselineskip]{fontsize}#*

\printsamples{baselineskip}{fontsize}#*
\printsamples{baselineskip}{fontsize}[sizes]#*
\sampletext{text}#*

\tinyr
\tinyrr
\tinyrrr
\scriptsizer
\scriptsizerr
\scriptsizerrr
\footnotesizer
\footnotesizerr
\footnotesizerrr
\smallr
\smallrr
\smallrrr
\normalsizer
\normalsizerr
\normalsizerrr
\larger
\largerr
\largerrr
\Larger
\Largerr
\Largerrr
\LARGEr
\LARGErr
\LARGErrr
\huger
\hugerr
\hugerrr
\Huger
\Hugerr
\Hugerrr
\HUGE
\HUGEr
\HUGErr
\HUGErrr