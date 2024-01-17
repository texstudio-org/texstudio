# verifycommand package
# Matthew Bertucci 2024/01/12 for v1.00

#include:etoolbox
#include:iftex

#keyvals:\usepackage/verifycommand
disable
#endkeyvals

\VerifyCommand{cmd}{md5 checksum}#*
\VerifyCommand[your package]{cmd}{md5 checksum}#*
\VerifyCommand[your package][other package]{cmd}{md5 checksum}#*
\VerifyEnvironment{envname}{begin md5 checksum}{end md5 checksum}#*
\VerifyEnvironment[your package]{envname}{begin md5 checksum}{end md5 checksum}#*
\VerifyEnvironment[your package][other package]{envname}{begin md5 checksum}{end md5 checksum}#*