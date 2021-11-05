# dlfltxbmarkup package
# Matthew Bertucci 11/5/2021 for v0.70

#include:keyval
#include:ragged2e

#ifOption:loadsampleconfig
#include:dlfltxbmarkupbookkeys
#endif

\markup{text}
\markup[options%keyvals]{text}

#keyvals:\markup#c
notxt
nowr
nomk
noidx
idxit
idxbf
idxn
addtospvrt=%<number%>
vaddtosp=%<number%>
forcesidepar
#endkeyvals

\felineKeyGenerator{key%plain}{description}{margin code}{index code}{text code}
\cs{text%plain}
\css{text%plain}
\felineWriteInMargin{text}

\ifNoMarginparAvail#*
\NoMarginparAvailfalse
\NoMarginparAvailtrue

\felineMarginAdjustment#*
\felineIndexCmd#*
\itindex{text}#*
\felineStandardKey#*
\felineMarkupDescription#*