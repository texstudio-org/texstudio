# xindex package
# Matthew Bertucci 2023/07/07 for v0.03

#include:xkeyval
#include:makeidx

#keyvals:\usepackage/xindex#c
imakeidx
# options passed to imakeidx
xindy
texindy
truexindy
makeindex
noautomatic
nonewpage
splitindex
original
quiet
#endkeyvals

#ifOption:imakeidx
#include:imakeidx
#endif

\writeidx{code}

\parenLeft#*
\parenRight#*
