# altsubsup package
# Matthew Bertucci 3/17/2022 for v1.1

#include:amstext

#keyvals:\usepackage/altsubsup#c
subscript
superscript
both
spbmark
#endkeyvals

#ifOption:spbmark
#include:spbmark
#endif

\SetAltSubscriptCommand{command}
\SetAltSuperscriptCommand{command}
\SetAltSubSupCommands{command}
