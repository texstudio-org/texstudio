# varvbtm package
# Matthew Bertucci 10/13/2021 for v1.1

#include:newvbtm

\newtabverbatim{envname}{beg-def-outer}{beg-def-inner}{end-def-inner}{end-def-outer}#N
\newtabverbatim{envname}[args]{beg-def-outer}{beg-def-inner}{end-def-inner}{end-def-outer}#N
\newtabverbatim{envname}[args][default]{beg-def-outer}{beg-def-inner}{end-def-inner}{end-def-outer}#N
\renewtabverbatim{envname}{beg-def-outer}{beg-def-inner}{end-def-inner}{end-def-outer}#N
\renewtabverbatim{envname}[args]{beg-def-outer}{beg-def-inner}{end-def-inner}{end-def-outer}#N
\renewtabverbatim{envname}[args][default]{beg-def-outer}{beg-def-inner}{end-def-inner}{end-def-outer}#N

\VVBbegintab#*
\VVBendtab#*
\VVBprintFF#*
\VVBprintFFas{string}#*
\VVBbreakatFF#*
\VVBbreakatFFonly#*
\VVBnonverb{\%<character%>}#*
\VVBnonverbmath#*
\VVBnonverbmath[\%<character%>]#*

\newverbatiminput{cmd}{beg-def-outer}{beg-def-inner}{end-def-inner}{end-def-outer}#d
\newverbatiminput{envname}[args]{beg-def-outer}{beg-def-inner}{end-def-inner}{end-def-outer}#d
\newverbatiminput{envname}[args][default]{beg-def-outer}{beg-def-inner}{end-def-inner}{end-def-outer}#d
\renewverbatiminput{cmd}{beg-def-outer}{beg-def-inner}{end-def-inner}{end-def-outer}#d
\renewverbatiminput{envname}[args]{beg-def-outer}{beg-def-inner}{end-def-inner}{end-def-outer}#d
\renewverbatiminput{envname}[args][default]{beg-def-outer}{beg-def-inner}{end-def-inner}{end-def-outer}#d