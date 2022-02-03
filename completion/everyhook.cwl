# everyhook package
# Matthew Bertucci 2/2/2022 for v1.0

#include:svn-prov
#include:etoolbox

#keyvals:\usepackage/everyhook#c
excludeor
#endkeyvals

\PushPreHook{hook}{balanced text}#*
\PopPreHook{hook}#*

\PushPostHook{hook}{balanced text}#*
\PopPostHook{hook}#*

\SavePreHook{hook}{command}#*d
\SavePostHook{hook}{command}#*d
\RestorePreHook{hook}{command}#*
\RestorePostHook{hook}{command}#*
\ClearPreHook{hook}#*
\ClearPostHook{hook}#*