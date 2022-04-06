# luainputenc package
# Matthew Bertucci 4/2/2022 for v0.973

#include:ifluatex
#include:ifxetex
#include:inputenc
#include:luatexbase

#keyvals:\usepackage/luainputenc#c
utf8
utf8x
unactivate
#endkeyvals

#ifOption:utf8x
#include:ucs
#endif

\InputNonUtfFile{file}#*i
\InputUtfFile{file}#*i