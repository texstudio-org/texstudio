# rcsinfo package
# Matthew Bertucci 2/4/2022 for v1.10

#include:fancyhdr

#keyvals:\usepackage/rcsinfo#c
today
fancy
fancyhdr
scrpage2
nofancy
long
short
datehyphen
#endkeyvals

#ifOption:scrpage2
#include:scrpage2
#endif

\rcsInfo $Id$ %|
\rcsInfo $Id:$ %|
\rcsInfo $Id: %<file%>,v %<rev YYYY/MM/DD hh:mm:ss owner stat lock%> $
\rcsInfo $Id: %<file%>,v %<rev YYYY/MM/DD hh:mm:ss owner stat%> $

\rcsInfoFile
\rcsInfoRevision
\rcsInfoDate
\rcsInfoTime
\rcsInfoOwner
\rcsInfoStatus
\rcsInfoLocker
\rcsInfoYear
\rcsInfoMonth
\rcsInfoDay
\rcsInfoLongDate