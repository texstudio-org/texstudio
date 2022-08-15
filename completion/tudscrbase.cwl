# tudscrbase package
# Matthew Bertucci 2022/08/14 for v2.06o

#include:scrbase
#include:iftex
#include:etoolbox
#include:xpatch
#include:letltxmacro
#include:kvsetkeys
#include:trimspaces

\TUDoptions{Optionenliste%keyvals}
\TUDoption{Option%keyvals}{Werteliste}

\iflanguageloaded{language}{true}{false}#*
\TUDProcessOptions#*
\TUDProcessOptions[member]#*
\TUDExecuteOptions{options}#*
\TUDExecuteOptions[member]{options}#*

\TUDScriptVersion#*
\TUDScriptVersionNumber#*
\TUDScript#*
\TUDScriptContact#*
\TUDScriptRepository#*
\TUDScriptForum#*