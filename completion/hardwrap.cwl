# hardwrap package
# Matthew Bertucci 10/29/2021 for v0.2

#include:ifplatform
#include:pdftexcmds
#include:ifxetex

\HardWrap{function}{width}{setup code}{newline}{text}
\GenerateLogMacros{type%keyvals}{name}
\GenerateLogMacros{type%keyvals}[prefix]{name}
#keyvals:\GenerateLogMacros
package
class
#endkeyvals
\HardWrapSetup#*
\setmaxprintline{integer}#*
\GeneratePackageLogMacros{name}#*
\GeneratePackageLogMacros[prefix]{name}#*
\GenerateClassLogMacros{name}#*
\GenerateClassLogMacros[prefix]{name}#*