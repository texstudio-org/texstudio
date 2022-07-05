# srcltx package
# Matthew Bertucci 2022/07/04 for v1.6

#include:ifthen

#keyvals:\usepackage/srcltx#c
active
inactive
nowinedt
dviwin
debug
nopar
nomath
nodisplay
#endkeyvals

\Input{file}#i
\MainFile
\srcIncludeHook{file}#i
\CurrentInput#*
\srcInputHook{file}#i
\ifSRCOK#*
\SRCOKtrue
\SRCOKfalse
\WinEdt{arg}#*