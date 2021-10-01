# censor package
# Matthew Bertucci 9/27/2021 for v3.22

#include:pbox
#include:ifnextok

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
\censorruledepth#*
\censorruleheight#*
\censordot#*
\bpar#S
\censorversionnumber#S