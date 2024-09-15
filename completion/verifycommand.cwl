# verifycommand package
# Matthew Bertucci 2024/09/03 for v1.10

#include:etoolbox
#include:iftex

#keyvals:\usepackage/verifycommand
disable
#endkeyvals

\VerifyCommand{command}{md5 checksum}#*
\VerifyCommand[your package]{command}{md5 checksum}#*
\VerifyCommand[your package][their package]{command}{md5 checksum}#*
\VerifyEnvironment{envname}{begin md5 checksum}{end md5 checksum}#*
\VerifyEnvironment[your package]{envname}{begin md5 checksum}{end md5 checksum}#*
\VerifyEnvironment[your package][their package]{envname}{begin md5 checksum}{end md5 checksum}#*
\IfVerifyCommand{command}{md5 checksum}{true}{false}#*
\IfVerifyCommand[your package]{command}{md5 checksum}{true}{false}#*
\IfVerifyCommand[your package][their package]{command}{md5 checksum}{true}{false}#*
\IfVerifyEnvironmentBegin{envname}{begin md5 checksum}{true}{false}#*
\IfVerifyEnvironmentBegin[your package]{envname}{begin md5 checksum}{true}{false}#*
\IfVerifyEnvironmentBegin[your package][their package]{envname}{begin md5 checksum}{true}{false}#*
\IfVerifyEnvironmentEnd{envname}{end md5 checksum}{true}{false}#*
\IfVerifyEnvironmentEnd[your package]{envname}{end md5 checksum}{true}{false}#*
\IfVerifyEnvironmentEnd[your package][their package]{envname}{end md5 checksum}{true}{false}#*
\TestVerifyCommands#*
\IfVerifyCommandPassed{true}{false}#*
\IfVerifyCommandFailed{true}{false}#*
\VERCMDWarning{your package}{their package}{defn name}#*
