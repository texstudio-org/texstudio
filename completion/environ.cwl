# environ package
# Matthew Bertucci 9/7/2021 for v0.3

#include:trimspaces

\NewEnviron{envname}{definition}#N
\NewEnviron{envname}[args]{definition}#N
\NewEnviron{envname}[args][optarg]{definition}#N
\NewEnviron{envname}[args][optarg]{definition}[final code]#*N
\RenewEnviron{envname}{definition}#N
\RenewEnviron{envname}[args]{definition}#N
\RenewEnviron{envname}[args][optarg]{definition}#N
\RenewEnviron{envname}[args][optarg]{definition}[final code]#*N
\BODY
\environfinalcode{code}
\environbodyname{cmd}#d