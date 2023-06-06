# censor package
# Matthew Bertucci 2023/06/06 for v4.3

#include:pbox
#include:tokcycle

\blackout{text}
\blackoutenv
\censor*{width multiplier}
\censor{text}
\censorbox*[pre-commands]{width mult}{height mult}{depth mult}
\censorbox*{width mult}{height mult}{depth mult}
\censorbox[pre-commands]{contents%text}
\censorbox{contents%text}
\censordot#*
\censormathgreekfalse#*
\censormathgreektrue#*
\censorrule{length}#*
\censorruledepth#*L
\censorruleheight#*L
\endblackoutenv
\endxblackoutenv
\RestartCensoring
\StopCensoring
\xblackout{text}
\xblackoutenv

# not in main documentation
\ccenspace#S
\censorfalse#S
\censortrue#S
\censorversiondate#S
\censorversionnumber#S
\censpace#S
\expandargfalse#S
\expandargtrue#S
\ifcensor#S
\ifcensormathgreek#S
\ifexpandarg#S
