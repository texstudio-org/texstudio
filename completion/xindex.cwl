# xindex package
# Matthew Bertucci 2023/07/12 for v0.04

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

\braceLeft#*
\braceRight#*
