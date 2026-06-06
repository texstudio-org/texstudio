# contracard class
# Matthew Bertucci 2026/06/06 for v3.0.0

#include:geometry
#include:titlesec
#include:contracard

#keyvals:\documentclass/contracard#c
small
medium
large
a7paper
draft
# options passed to contracard package
showcountafter
showcountbefore
enableidx
#endkeyvals

#ifOption:enableidx
#include:imakeidx
#endif