# phfparen package
# Matthew Bertucci 2/8/2022 for v1.0

#include:etoolbox
#include:kvoptions
#include:amsmath
#include:mathtools
#include:xstring

#keyvals:\usepackage/phfparen#c
backtick#true,false
nobacktick#true,false
registerdefaults#true,false
noregisterdefaults#true,false
#endkeyvals

\paren(expression in parenthesis)#m
\paren*(expression in parenthesis)#m
\paren[expression in brackets]#m
\paren*[expression in brackets]#m
\paren<expression in angle brackets>#m
\paren*<expression in angle brackets>#m
\paren{expression in curly braces}#m
\paren*{expression in curly braces}#m

\backtick

\parenMakeBacktickActiveParen#*
\parenMakeNormalBacktick#*
\parenRegister{name}{delim1%definition}{delim2%definition}{display delim1%definition}{display delim2%definition}#*
\parenRegsiterSimpleBraces{name}#*
\parenRegisterDefaults#*