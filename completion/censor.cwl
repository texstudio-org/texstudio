# censor package
# Matthew Bertucci 12/26/2021 for v4.0

#include:pbox
#include:tokcycle

\censor{text}
\StopCensoring
\RestartCensoring
\censorbox{contents%text}
\blackout{text}
\xblackout{text}
\periodrlap#*
\afterperiodlap#*
\lletterlap#*
\rletterlap#*
\afterspacelap#*
\censor*{width}
\censorbox*{width}{height}{depth}
\censorbox*[pre-commands]{width}{height}{depth}
\blackoutenv
\endblackoutenv
\xblackoutenv
\endxblackoutenv
\censorruledepth#*
\censorruleheight#*
\censordot#*
\bpar#S
\censorversionnumber#S
