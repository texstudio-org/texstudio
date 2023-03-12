# environ package
# Matthew Bertucci 9/7/2021 for v0.3

#include:trimspaces

\NewEnviron{envname}{definition}#N
\NewEnviron{envname}[args]{definition}#N
\NewEnviron{envname}[args][default]{definition}#N
\NewEnviron{envname}[args][default]{definition}[final code]#*N
\RenewEnviron{envname}{definition}
\RenewEnviron{envname}[args]{definition}
\RenewEnviron{envname}[args][default]{definition}
\RenewEnviron{envname}[args][default]{definition}[final code]#*
\BODY
\environfinalcode{code}
\environbodyname{cmd}#d
