# darkmode package
# Matthew Bertucci 2022/09/04 for v1.0.1

#include:l3keys2e
#include:xcolor
#include:pagecolor

#keyvals:\usepackage/darkmode#c
enable#true,false
defaulthook#true,false
nodefaulthook
#endkeyvals

\enabledarkmode
\disabledarkmode

\IfDarkModeT{true code}
\IfDarkModeF{false code}
\IfDarkModeTF{true code}{false code}

fgcolor#B