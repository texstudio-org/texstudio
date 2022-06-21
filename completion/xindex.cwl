# xindex package
# Matthew Bertucci 2022/06/20 for v0.02

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