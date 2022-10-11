# gitstatus package
# Matthew Bertucci 2022/10/09 for v1.1

#include:kvoptions
#include:catchfile
#include:xstring

#keyvals:\usepackage/gitstatus#c
gitdir=%<file path%>
watermark
nowatermark
novariables
#endkeyvals

#ifOption:watermark
#include:xcolor
#include:xwatermark
#endif

\gitdir
\gitcommit
\gitbranch