# gettitlestring package
# Matthew Bertucci 11/10/2021 for v1.6

#include:kvoptions

\GetTitleStringSetup{options%keyvals}#*

#keyvals:\GetTitleStringSetup,\usepackage/gettitlestring#c
expand#true,false
#endkeyvals

\GetTitleString{text}#*
\GetTitleStringExpand{text}#*
\GetTitleStringNonExpand{text}#*
\GetTitleStringResult#*
\GetTitleStringDisableCommands{code}#*
